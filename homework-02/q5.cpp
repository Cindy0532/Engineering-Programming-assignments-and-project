#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    // input
    double inputs[]= {3.0, 1.5, 3.0, 2.5, 4.5};
    int length = sizeof(inputs) / sizeof(inputs[0]);

	// bubble sort 
	for (int i=0; i<length - 1; i++)
	{
		for (int j=i+1; j<length; j++)
		{
			if (inputs[i] > inputs[j])
			{
				char temp = inputs[i];
				inputs[i] = inputs[j];
				inputs[j] = temp;
			}
		}
	}

    // mean
    double sum = 0;
    for (double input : inputs)
    {
        sum += input;
    }
    double mean = sum / length;
    // median
    double median;
    if (length % 2 == 1)
    {
        median = inputs[length / 2];
    }
    else
    {
        median = (inputs[length / 2] + inputs[length / 2 - 1]) / 2;
    }
    // mode
    int count = 0;
    int max = 0;
    double pre = inputs[0];
    double mode = inputs[0];
    for (double input : inputs)
    {
        if (input == pre)
        {
            count++;
            if (count > max)
            {
                max = count;
                mode = input;
            }
        }
        else
        {
            count = 1;
            pre = input;
        }
    }
    // variance
    double variance = 0;
    for (double input : inputs)
    {
        variance += pow((input - mean), 2);
    }
    variance /= length;
    // standard deviation
    double deviation = sqrt(variance);

    cout << "mean: " << mean << endl;
    cout << "median: " << median << endl;
    cout << "mode: " << mode << endl;
    cout << "variance: " << variance << endl;
    cout << "standard deviation: " << deviation << endl;
    return 0;
}