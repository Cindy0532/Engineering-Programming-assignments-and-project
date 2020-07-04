/*
This is the programming part of your exam. The question and the relevant files are posted
on Blackboard. When finished, name your file as hLastNameFirstNamei.cpp. Upload that cpp code to
blackboard by the deadline.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

// b
map<string, vector<pair<string, string>>> transform(map<string, vector<pair<string, string>>> docs)
{
	map<string, vector<pair<string, string>>> users;

    for (auto doc : docs)
    {
    	for (auto user : doc.second)
    	{
    		if (users.find(user.first) != users.end())
    		{
    			users[user.first].push_back(make_pair(doc.first, user.second));
    		}
    		else
    		{
    			vector<pair<string, string>> ops;
    			ops.push_back(make_pair(doc.first, user.second));
    			users.insert({user.first, ops});
    		}
    	}
    }

	return users;
}

// c
bool check(string user, string op, string doc, map<string, vector<pair<string, string>>> docs)
{
	if (docs.find(doc) == docs.end())
	{
		return false;
	}

	for (auto users : docs[doc])
	{
		if (users.first == user && users.second == op)
		{
			return true;
		}
	}

	return false;
}

int main()
{
	// a
	// this is he container I choose to put txt content
	map<string, vector<pair<string, string>>> docs; 
	string path = "access_rights.txt";
	string line;
	ifstream infile;

	infile.open(path);
	while(getline(infile, line))
	{
		vector<string> words;
		vector<pair<string, string>> users;
		string word = "";

		for (auto s : line)
		{
			if (s == ' ' || s == '\r')
			{
				words.push_back(word);
				word = "";
			}
			else
			{
				word += s;
			}
		}
		if (word != "")
		{
			words.push_back(word);
			word = "";
		}

		string doc = words[0];
		words.erase(words.begin());

		for (auto word : words)
		{	
			word = word.substr(1, word.size() - 2);
			string user = "";
			string right = "";

			for (int i=0; i<word.size();i++)
			{
				if (word[i] == ',')
				{
					right = word.substr(i + 1, word.size() - 1);
					break;
				}
				else
				{
					user += word[i];
				}
			}			
			users.push_back(make_pair(user, right));
		}
		docs.insert({doc, users});
    }

    // display stored content
    cout << "Qa:" << endl;
    for (auto doc : docs)
    {
    	cout << doc.first << ' ';
    	for (auto user : doc.second)
    	{
    		cout << '(' << user.first << ',' << user.second << ") ";
    	}
    	cout << endl;
    }
    cout << endl;

	infile.close();

	// b
	auto transformed = transform(docs);
	// display new content
	cout << "Qb:" << endl;
	for (auto user : transformed)
	{
		cout << user.first << ' ';
		for (auto doc : user.second)
		{
    		cout << '(' << doc.first << ',' << doc.second << ") ";
		}
		cout << endl;
	}
	cout << endl;

	// c
	cout << "Qc: " << endl;
	cout << "check Alice, read, doc1: " << check("Alice", "read", "doc1", docs) << endl;
	cout << "check Alice, read, doc2: " << check("Alice", "read", "doc2", docs) << endl;
	cout << "check Bob, read, doc3: " << check("Bob", "read", "doc3", docs) << endl;


    return 0;

}