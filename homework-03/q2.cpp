#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// M * N matrix
#define M_SIZE 1
#define N_SIZE 1

int* copy(int* a, int size);
int** copy(int** a, int size);

int main()
{
	int** matrix = new int*[M_SIZE]; // output two-demensional array
	int* n_sizes = new int[M_SIZE]; 
	int m_cur = 0;
	int m_cap = M_SIZE;

	cout << "This is a program for user to input two-dimensional arrays and display." << endl
		 << "This program only accepts positive numbers. " << endl
		 << "Please input positive numbers in the form of columns, seperate by \",\", finish with a nagative number: " << endl
		 << "Enter a negative number to exit." << endl;
	while(true)
	{
		string nums;
		cout << "Please enter column " << m_cur + 1 << ": ";
		cin >> nums;
		if (nums == "")
		{
			cout << "Please input at least one number." <<endl;
			continue;
		}

		bool finished = false; // indicate if input finished
		bool currect_input = true; // indicate if user input something other than numbers
		int* column = new int[N_SIZE];
		int n_cur = 0;
		int n_cap = N_SIZE;
		// covnert string to int array
		int start = 0; // start position of a number
		for (int i=0; i<nums.size(); i++)
		{
			// check if of input characters are digits, comma and negative sign
			if (!(nums[i] >= '0' && nums[i] <= '9' || nums[i] == '-' || nums[i] == ','))
			{
				cout << nums[i];
				cout << "Input is not in right format. Please enter valid numbers." << endl;
				currect_input= false;
				break;
			}
			if (nums[i] == '-' && i == 0)
			{
				finished = true;
				break;
			}
			if (nums[i] == '-' && i != 0)
				break;
			if (i == nums.size() - 1)
			{
				cout << "Please enter a negative number to finish one column input. "<< endl;
				currect_input = false;
				break;
			}
			if (nums[i] == ',')
			{
				int num = stoi(nums.substr(start, i - start));
				if (!num)
				{
					cout << "Please enter positive number, not zero." << endl;
					currect_input = false;
					break;
				}
				if (n_cur == n_cap)
				{
					column = copy(column, n_cur);
					n_cap++;
				}
				column[n_cur++] = num;
				start = i + 1;
			}
		}

		if (finished)
			break;
		if (!currect_input)
			continue;
		if (m_cur == m_cap)
		{
			matrix = copy(matrix, m_cur);
		}
		matrix[m_cur] = column;
		n_sizes[m_cur] = n_cur;
		m_cur++;
	}

	// display matrix
	int max = 0;
	for (int i=0; i<m_cur; i++)
	{
		if (n_sizes[i] > max)
			max = n_sizes[i];
	}
	for (int i=0; i<max; i++)
	{
		cout << setw(5);
		for (int j=0; j<m_cur; j++)
		{
			if (i < n_sizes[j])
				cout << matrix[j][i];
			else
				cout << ' ';
			cout << ' ';
		}
		cout << endl;
	}
	cout << endl;

	while(true)
	{	
		int column;
		cout << "Please select which column to display." << endl
			 << "enter from 1 - " << m_cur << " to select, everything else to exit: " << endl;
		cin >> column;
		if (column <= 0 || column > m_cur)
			break;
		for (int i=0; i<n_sizes[column - 1]; i++)
			cout << matrix[column - 1][i] << ' ';
		cout << endl;

	}
	
	return 0;
}

int* copy(int* a, int size)
{
	int *na = new int[size + 1];

	for (int i=0; i<size; i++)
		na[i] = a[i];
	delete[] a;

	return na;
}

int** copy(int** a, int size)
{
	int** na = new int*[size + 1];

	for (int i=0; i<size; i++)
		na[i] = a[i];
	delete[] a;

	return na;
}