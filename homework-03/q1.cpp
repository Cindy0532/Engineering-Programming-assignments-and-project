#include <iostream>
using namespace std;


int main()
{
	int a, b, q, r;

	cout<<"Please input two positive integer number a and b" << endl;
	cout << "Please enter a, press enter to finish: ";
	cin >> a;
	cout << "Please enter b, press enter to finish: ";
	cin >> b;
	
	do
	{   
		q=a/b;
		r=a%b;
		if(r==0)
			break;
		a=b;
		b=r;
	}
	while(r !=0);
	cout<<"gcd(a,b) = "<<b<<endl;

	return 0;


}