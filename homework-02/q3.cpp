#include <iostream> 
#include <cmath> 
using namespace std; 
  
int main() 
{ 
    char set[] = {'1','2','3'}; 

    int size = sizeof(set) / sizeof(set[0]);
    for(int i = 0; i < pow(2, size); i++) 
    { 
        char output[size];
        int counter = 0;
        for(int j = 0; j < size; j++) 
        { 
            if(i & (1 << j)) 
            {
                output[counter++] = set[j];
            }
        } 
        cout << '{';
        for (int j=0; j < counter; j++)
        {
            cout << output[j];
            if (j != counter - 1)
            {
                cout << ',';
            }
        }
        cout << '}' << endl; 
    } 

    return 0; 
} 