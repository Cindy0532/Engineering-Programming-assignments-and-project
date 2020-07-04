#include <iostream>
#include <vector>

using namespace std;

void printOccurs(int gram, string text);

int main()
{
    cout << "This program reads text from users and display: \n"
         << "1. The number of occurrences of each character in the input lines.\n"
         << "2. The number of occurrences of each of the bigrams (a sequence of 2 chars) in the input lines.\n"
         << "3. The number of occurrences of each of the trigrams (a sequence of 3 chars) in the input lines.\n\n"
         << "Rules:\n"
         << "Include a - z, A - Z\n"
         << "Include 0 - 9\n"
         << "Exclude symbols\n"
         << "Exclude all whitespaces\n\n"
         << "Please enter a number of lines of text, type \"enter\" and \"end of file\" to finish:\n";
         
    // get input
    string characters = "";
    string temp;
    while(cin >> temp){
        if (!cin.eof()){
            characters += temp;
        }
        else
            break;
    }
    int size = characters.size();
    for(auto chr : characters){
        if (chr >= '0' && chr <= '9' || chr >= 'a' && chr <= 'z' || chr >= 'A' && chr <= 'Z'){
            characters += chr;
        }
    }
    characters = characters.substr(size, characters.size() - size);
   
    cout << "Question 1: ";
    printOccurs(1, characters);
    cout << "Question 2: ";
    printOccurs(2, characters);
    cout << "Question 3: ";
    printOccurs(3, characters);
   
    return 0;
}

void printOccurs(int gram, string characters)
{
    vector<string> chrs;
    vector<int> occurs;
    int size = 0;
   
    for (int i=0; i<characters.size()-gram+1; i++) {
        string pre = characters.substr(i, gram);
        int count = 0;
        bool skip = false;
        for (auto chr : chrs){
            if (chr == pre){
                skip = true;
                break;
            }
        }
        if (skip){
            continue;
        }
        for (int j=0; j<characters.size()-gram+1; j++){
            string cur = characters.substr(j, gram);
            if (cur == pre){
                count++;
            }
        }
        chrs.push_back(pre);
        occurs.push_back(count);
        size++;
    }
   
    for (int i=0; i<size; i++){
        cout << chrs[i] << ":" << occurs[i] << ", ";
    }
    cout << endl;
}