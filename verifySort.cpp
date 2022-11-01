// Name Joshua Askam
// Class CECS 325-02
// Project Name Prog 4 - Multi thread
// Due Date 10/20/22
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
	{
		cout << "Please include output filename in param list.\n";
		cout << "Example:\n";
		cout << "     % verifySort mySort.out\n";
		exit(EXIT_SUCCESS);
	}
    ifstream fin;
    int n;
    int last;
    fin.open(argv[1]);
    fin >> last;
    int count = 1; //Starts at 1 and not 0 because I already added a value to int last
    while(fin >> n)
    {
        if(n < last)
        {
            cout << "The array is not sorted!\n";
            return 0;
        }
        last = n;
        count++;
    }
    cout << "The array is sorted and has " << count << " integers!\n";
    fin.close();
    return 0;
}