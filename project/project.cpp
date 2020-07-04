/**
EE 5103 Final Project – Due May 5, 11:59 PM 

Late submissions will not receive any points. This is a strict rule. Please submit in time. 

Total Points: 100 

Consider a folder structure that contains many files. Each folder can contain one or more sub-folders. 
Each file could be of any arbitrary size. Assume that the files are all in text format (letters, numbers, 
symbols and whitespaces). Write a modular and well-structured C++ program that supports the 
following features. You can use any container and any algorithm from STL. While you can do research 
online, do not copy code. 

    1. (10 points) Given a search word, display the number of times that word occurs per file. 
    2. (20 points) Given a search word, display the lines on which that word occurs along with the 
       filename and line number. 
    3. (20 points) Given a search phrase with a pattern, list the lines on which that pattern occurs 
       along with the filename and line number. 
           a. A * indicates zero or more occurrences of any character. For example, the pattern 
              “hello*world” (excluding quotes) would match the lines containing “helloworld”,  
              “hello world” and “hello, world”. 
           b. A ? indicates one or more occurrences of any character. For example, the pattern 
              “hello?world” (excluding quotes) would match the lines containing “hello world” and 
              “hello, world”, but not “helloworld”. 
           c. The search patterns could be used in complex ways. E.g.: “I w?d rather have questions * 
              can't be answered than answers that can't * questioned.” 
    4. (10 points) Display a total frequency of all the words that occur across all the files. Display them 
       in descending order. 
    5. (10 points) Check if all kinds of parenthesis are balanced. The files might contain (, {, [, ), } and ]. 
       If not balanced, show the lines along with the line number and filenames where they are not 
       balanced. 
    6. (30 points) A search functionality that returns the file names that matches a search parameter 
       by use the TF-IDF measure to identify files that closely match the search term. Learn more about 
       TF-IDF here: https://en.wikipedia.org/wiki/Tf–idf  

Remember to show fully qualified file names (i.e., the full path of the file names). 

@author Xin Li
@version 1.0 04/28/20 
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <regex>
#include <map>
#include <cmath>
#include <windows.h>

using namespace std;

class Folder
{
private:
    vector<string> dirs;
    int occur(string, string);

public:
    Folder(vector<string>);
    Folder(string root);
    void search_word_occur(string);
    void search_word_line(string);
    void search_pattern_line(string);
    void calculate_word_freq();
    void search_unbalanced_parenthesis();
    void search_closest_file(string);
};

/**
    Initialize the class with all file directories in the folder structure.

    @param file directory.
*/
Folder::Folder(vector<string> files)
{
    dirs = files;
}

/**
    Initialize the class with only root directory. Automatically find all txt files.

    @param root root directory which contains subdirectories and files.
*/
Folder::Folder(string root)
{
    vector<string> sub_dirs;
    sub_dirs.push_back(root);

    while(!sub_dirs.empty())
    {
        WIN32_FIND_DATA find_data;
        HANDLE handler;
        string file = sub_dirs.back();
        sub_dirs.pop_back(); 
        vector<string> founds;

        handler = FindFirstFile((file + "\\*").c_str(), &find_data);

        if(INVALID_HANDLE_VALUE == handler)
        {
            cout << "Error in finding files." << endl
                 << "Error: " <<GetLastError() << endl;
        }
        else
        {
            //cout << "File found: " << find_data.cFileName << endl;
            founds.push_back(find_data.cFileName);
        }

        while (FindNextFile(handler, &find_data))
        {
            //cout << "File found: " << find_data.cFileName << endl;
            founds.push_back(find_data.cFileName);
        }

        if (!founds.empty())
        {
            for (auto found : founds)
            {
                if ((int)found.find(".txt") >= 0)
                {
                    dirs.push_back(file + "\\" + found);
                }
                else if ((int)found.find(".") < 0)
                {
                    sub_dirs.push_back(file + "\\" + found);
                }
            }
            founds.clear();
        }
        FindClose(handler);
    }
}

/**
    Returns the number of times a given search occurs in the content.

    @param content string content.
    @param word search word.
    @return word occurrences.
*/
int Folder::occur(string content, string word)
{
    int cnt = 0;
    int found = 0; //-1 means not found, else return found index

    while(found >= 0)
    {
        // find first occurrence of search word
        found = content.find(word); 
        if (found >= 0) 
        {
            cnt++;
            content = content.substr(found + word.size());
        }
    }

    return cnt;
}

/**
    Given a search word, display the number of times that word occurs per file. 

    @param word search word.
*/
void Folder::search_word_occur(string word)
{
    for (string dir : dirs) 
    {
        ifstream infile(dir);
        string content;
        getline(infile, content, (char)infile.eof());
          
        cout << dir << " occurs " << occur(content, word) << " times." << endl;
    }
}

/**
    Given a search word, display the lines on which that word occurs along with the filename and line number.
    Note: 
    If the word occurs two more times in a line, only display once.

    @param word search word.
*/
void Folder::search_word_line(string word)
{
    for (string dir : dirs) 
    {
        string line;
        int num = 0;
        ifstream infile;
        infile.open(dir);

        while(getline(infile, line))
        {
            num++;
            int occurs = occur(line, word);
            if (occurs) 
            {
                cout << dir << " line " << num << ": " << line << endl;
            }
        }
        infile.close();
    }
}

/**
    Given a search phrase with a pattern, list the lines on which that pattern occurs 
    along with the filename and line number. 
    Notes: 
    1. If the pattern occurs two more times in a line, only display once.
    2. If the pattern across multiple lines, consider not valid.

    @param pattern search pattern.
*/
void Folder::search_pattern_line(string pattern)
{
    // if pattern does not contain '*' or '?', use search_word_line fuction
    if ((int)pattern.find('*') < 0 && (int)pattern.find('?') < 0)
    {
        search_word_line(pattern);
        return;
    }

    // create regex
    // replace * with .*, replace ? with .+
    int index = 0;
    while ((index = pattern.find("*", index)) != string::npos) {
         pattern.replace(index, 1, ".*");
         index += 2;
    }
    index = 0;
    while ((index = pattern.find("?", index)) != string::npos) {
         pattern.replace(index, 1, ".+");
         index += 2;
    }

    // size_t pos = 0;
    // while ((pos = pattern.find("*", pos)) != string::npos) {
    //      pattern.replace(pos, 1, ".*");
    //      pos += 2;
    // }
    // pos = 0;
    // while ((pos = pattern.find("?", pos)) != string::npos) {
    //      pattern.replace(pos, 1, ".+");
    //      pos += 2;
    // }


    for (string dir : dirs) 
    {
        string line;
        int num = 0;
        ifstream infile;
        infile.open(dir);

        while(getline(infile, line))
        {
            num++;
  
            regex rgx(pattern); 
            smatch matches; 
            regex_search(line, matches, rgx); 
  
            if (matches.size())
            {
                cout << dir << " line " << num << ": " << line << endl;
            }
        }
        infile.close();       
    }
}

/**
    Display a total frequency of all the words that occur across all the files. Display them 
    in descending order. 
*/
void Folder::calculate_word_freq()
{
    map<string, int> words;

    // find all words and occurances
    for (string dir : dirs) 
    {
        ifstream infile(dir);
        string content;
        getline(infile, content, (char)infile.eof());

        regex rgx("\\w+"); 

        for(sregex_iterator it(content.begin(), content.end(), rgx), it_end; it != it_end; ++it)
        {
            string word = (*it)[0];
            if (words.count(word))
            {
                words[word]++;
            }
            else
            {
                words.insert(pair<string, int>(word, 1)); 
            }
        }
    }

    // sort in descending order
    vector<pair<int, string>> sorted;
    for (auto word : words)
    {
        sorted.push_back(make_pair(word.second, word.first));
    }
    sort(sorted.rbegin(), sorted.rend()); 

    // display
    for (auto word: sorted)
    {
        cout << word.second << ' ' << word.first << endl;
    }
}

/**
    Check if all kinds of parenthesis are balanced. The files might contain (, {, [, ), } and ]. 
    If not balanced, show the lines along with the line number and filenames where they are not 
    balanced.

    Note: 
    1. If a valid parenthesis across multiple lines. It is considered a balanced parenthesis.
    2. If two unbalanced parenthesis appear in the same line, only display once.
*/
void Folder::search_unbalanced_parenthesis()
{
    string parenthesis = "(){}[]";

    for (string dir : dirs) 
    {
        vector<pair<char, int>> pairs;
        vector<string> lines;
        vector<int> unbalanced;

        // read file
        string line;      
        ifstream infile;
        infile.open(dir);
        while(getline(infile, line))
        {
            lines.push_back(line);
        }
        infile.close();

        // retrieve all parenthesis
        for (int i=0; i<lines.size(); i++)
        {
            for (int j=0; j<lines[i].size(); j++)
            {
                if ((int)parenthesis.find(lines[i][j]) >= 0)
                {
                    pairs.push_back(make_pair(lines[i][j], i));
                }
            }
        }

        // check unbalance
        while(!pairs.empty())
        {
            pair<char, int> cur = pairs.back();
            pairs.pop_back();
            if (cur.first == '(' || cur.first == '{' || cur.first == '[')
            {
                unbalanced.push_back(cur.second);
                break;
            }
            if (pairs.empty())
            {
                break;
            }
            pair<char, int> pre = pairs.back();
            if (cur.first == ')' && pre.first == '(' || cur.first == '}' && pre.first == '{' || cur.first == ']' && pre.first == '[')
            {
                pairs.pop_back();
                continue;
            }
            else
            {
                unbalanced.push_back(cur.second);                
            }
        }

        // remove duplicates
        sort(unbalanced.begin(), unbalanced.end());   
        vector<int>::iterator size = unique(unbalanced.begin(), unbalanced.begin() + unbalanced.size());  
        unbalanced.resize(distance(unbalanced.begin(), size));

        // display unbalanced lines
        for(auto u : unbalanced)
        {
            cout << dir << " line " << u + 1 << ": " << lines[u] << endl;
        }
    }
}

/**
    A search functionality that returns the file names that matches a search parameter 
    by use the TF-IDF measure to identify files that closely match the search term. Learn more about 
    TF-IDF here: https://en.wikipedia.org/wiki/Tf–idf 

    tfidf(t, d, D) = tf(t, d) * idf(t, D)
    term frequency tf(t, d) = t occurences in d / total terms in d
    inverse document frequency idf(t, D) = log(total number of documents / number of documents with term t)

    @param term search term.
*/
void Folder::search_closest_file(string term)
{
    vector<pair<string, double>> closests;
    map<string, double> tf;

    // term frequency
    for (auto dir : dirs)
    {
        ifstream infile (dir);
        string content;
        getline (infile, content, (char)infile.eof());
        int total = 0;
        int occ= 0;
        regex rgx("\\w+"); 

        for(sregex_iterator it(content.begin(), content.end(), rgx), it_end; it != it_end; ++it)
        {
            total++;
            if ((*it)[0] == term)
            {
                occ++;
            }
        }
        tf.insert(pair<string, double>(dir, (double)occ / total)); 
    }
    
    // document freqency: the number of documents with term
    int doc_freq = 0;
    for (auto freq : tf)
    {
        if (freq.second > 0) 
        {
            doc_freq++;
        } 
    }

    // find closest documents
    for (auto freq : tf)
    {
        double tfidf = freq.second * log10((double)dirs.size() / doc_freq);

        if (closests.empty() || tfidf == closests.back().second)
        {        
            closests.push_back(make_pair(freq.first, tfidf));
        }
        else if (tfidf > closests.back().second)
        {
            closests.clear();
            closests.push_back(make_pair(freq.first, tfidf));
        }
    }

    // display
    for (auto closest : closests)
    {
        cout << closest.first << ' ' << endl;
    }
}

int main()
{
    cout << "This program uses a folder structure to analyze txt files within the root folder and its subfolders. \n";
    cout << "Please enter the root directory of the folder structure: \n";
    string root;
    // example root directory: C:\Users\iamdoublewei\Documents\root
    cin >> root;
    // initailize the folder structure
    Folder folder(root);

    cout << "1. Enter a search word, display the number of times that word occurs per file. \n"
         << "2. Enter a search word, display the lines on which that word occurs along with the filename and line number. \n"
         << "3. Enter a search phrase with a pattern(*: 0 or 0 more; ?: 1 or 1 more), \n"
         << "   list the lines on which that pattern occurs along with the filename and line number. \n"
         << "4. Display a total frequency of all the words that occur across all the files in descending order. \n"
         << "5. Check if all kinds of parenthesis are balanced. The files might contain (, {, [, ), } and ]. \n"
         << "   If not balanced, show the lines along with the line number and filenames where they are not balanced. \n"
         << "6. A search functionality that returns the file names that matches a search parameter \n"
         << "   by use the TF-IDF measure to identify files that closely match the search term. \n\n";

    while(true)
    {
        cout << "Please select what you want to do(Enter 1 - 6), Enter \"q\" to exit: ";
        string input;
        cin >> input;

        if (input == "q" || input == "Q")
            break;
        else if (input == "1")
        {      
            string sword;    
            cout << "Please enter a search word: ";
            cin >> sword;

            folder.search_word_occur(sword);
        }
        else if (input == "2")
        {
            string sword;    
            cout << "Please enter a search word: ";
            cin >> sword;

            folder.search_word_line(sword);
        }
        else if (input == "3")
        {
            string pattern;    
            cout << "Please enter a search pattern: ";
            cin >> pattern;

            folder.search_pattern_line(pattern);
        }
        else if (input == "4")
        {
            folder.calculate_word_freq();
        }
        else if (input == "5")
        {
            folder.search_unbalanced_parenthesis();
        }
        else if (input == "6")
        {
            string term;    
            cout << "Please enter a search term: ";
            cin >> term;

            folder.search_closest_file(term);
        }
        else
        {
            cout << "Please enter a number between 1 to 6.";
        }
        cout << endl;
    }

    return 0;
}