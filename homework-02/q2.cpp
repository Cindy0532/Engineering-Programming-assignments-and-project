#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	string input = "BOb";

	for (int i=0; i<input.size(); i++)
	{
		if (input[i] >= 'A' && input[i] <= 'Z')
		{
			input[i] += 32;
		}
	}

	for (int i=0; i<input.size() - 1; i++)
	{
		for (int j=i+1; j<input.size(); j++)
		{
			if (input[i] > input[j])
			{
				char temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}
	}

	cout << "All permutations: " << endl;
	do
	{
		cout << input << endl;
	} while (next_permutation(input.begin(), input.end()));

	return 0;
}