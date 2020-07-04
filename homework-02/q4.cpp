#include <iostream>
#include <string>

using namespace std;

int main()
{
	bool result = true;
    string input;
    cout << "Please enter a phone number: ";
    getline(cin, input);
    
    if (input.length() != 14 || input[0] != '(' || input[4] != ')' || input[5] != ' ' || input[9] != '-')
    {
        result = false;
    }
    if (input[1] < '1' || input[1] > '9')
    {
        result = false;
    }
    int nums[] = {2, 3, 6, 7, 8, 10, 11, 12, 13};
    for (int num : nums)
    {
        if (input[num] < '0' || input[num] > '9')
        {
            result = false;
        }
    }
    if (result)
    {
    	cout << "right format.";
    }
    else
    {
    	cout << "wrong format.";
    }

    return 0;
}
