#include <iostream>
using namespace std;

int main()
{	
	for(int i=0; i<6; i++)
	{
		char c;
		if(i % 2 == 0)
		{
			c='*';
		}
		else
		{
			c='^';
		}
		for(int j=0; j<6-i-1; j++)
		{
			cout<<' ';
		}
		for(int j=0; j<2*i+1; j++)
		{
			cout<<c;
		}
		cout<<endl<<endl;
	
	}
	
	return 0;
}