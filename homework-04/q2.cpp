#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Sequence {
    public:
        vector<double> sequence;
        double mean;
        double median;
        double mode;
        double stdDev;
        double variance;

        Sequence(vector<double> s){
            sequence = s;
            mean = calMean();
            median = calMedian();
            mode = calMode();
            variance = calVariance();
            stdDev = calStdDev();
        }
        void display()
        {
            cout << "mean " << mean << ", "
                 << "median " << median << ", "
                 << "mode " << mode << ", "
                 << "standard deviation " << stdDev << ", "
                 << "variance " << variance << endl;
        }
    private:
        void sort()
        {
            int length = sequence.size();
        	for (int i=0; i<length - 1; i++)
        	{
        		for (int j=i+1; j<length; j++)
        		{
        			if (sequence[i] > sequence[j])
        			{
        				double temp = sequence[i];
        				sequence[i] = sequence[j];
        				sequence[j] = temp;
        			}
        		}
        	}
        }
        double calMean()
        {
            double sum = 0;
            for (double num : sequence){
                sum += num;
            }

            return sum / sequence.size();
        }
        double calMedian()
        {
            sort();
            int length = sequence.size();
            if (length % 2 == 1)
            {
                return sequence[length / 2];
            }
            else
            {
                return (sequence[length / 2] + sequence[length / 2 - 1]) / 2;
            }
        }
        double calMode()
        {
            sort();
            int count = 0;
            int max = 0;
            double pre = sequence[0];
            double mode = sequence[0];
            for (double num : sequence)
            {
                if (num == pre)
                {
                    count++;
                    if (count > max)
                    {
                        max = count;
                        mode = num;
                    }
                }
                else
                {
                    count = 1;
                    pre = num;
                }
            }

            return mode;
        }
        double calVariance()
        {
            double variance;
            for (double num : sequence)
            {
                variance += pow((num - mean), 2);
            }
            variance /= sequence.size();

            return variance;
        }
        double calStdDev()
        {
            return sqrt(variance);
        }
};

int main()
{
    cout << "This program read multiple sequences of doubles and display its mean, median, mode, standard deviation and variance.\n" 
         << "Each sequence is ended by type \"ENTER\" key.\n" 
         << "Each double within a sequence is seperate by\",\", not space in between.\n"
         << "Enter \"q\" or \"Q\" to finish all inputs.\n"
         << "Please enter your sequences: \n";
         
    // get inputs
    vector<Sequence> sequences;
    string input;
    while(true){
        getline(cin, input);
        if (input == "q" || input == "Q"){
            break;
        }
        
        vector<double> doubles;
        int start = 0;
        input += ",";
        for (int i=0; i<input.size(); i++){
            if (input[i] == ','){
                double num = stod(input.substr(start, i - start));
                doubles.push_back(num);
                start = i + 1;
            }
        }
        
        Sequence seq(doubles);
        sequences.push_back(seq);
    }
    
    // display
    for (int i=0; i<sequences.size(); i++){
        cout << "Sequence " << i + 1 <<": ";
        sequences[i].display();
    }

    return 0;
}