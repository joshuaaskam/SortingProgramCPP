// Name Joshua Askam
// Class CECS 325-02
// Project Name Prog 4 - Multi thread
// Due Date 10/20/22
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <thread>
using namespace std;

struct nums
{
    int *ptr;
    int beg;
    int end;
};

int partition(int v[], int beg, int end)
{
 
    int pivot = v[beg];
 
    int count = 0;
    for (int i = beg + 1; i <= end; i++) {
        if (v[i] <= pivot)
            count++;
    }
 
    int pivotNum = beg + count;
    swap(v[pivotNum], v[beg]);
 
    int i = beg, j = end;
 
    while (i < pivotNum && j > pivotNum) {
 
        while (v[i] <= pivot) {
            i++;
        }
 
        while (v[j] > pivot) {
            j--;
        }
 
        if (i < pivotNum && j > pivotNum) {
            swap(v[i++], v[j--]);
        }
    }
 
    return pivotNum;
}

// This quick sort function uses an array
void quick(int v[], int beg, int end)
{
    if (beg >= end)
        return;
 
    int p = partition(v, beg, end);
 
    quick(v, beg, p - 1);
 
    quick(v, p + 1, end);
}

//used to merge the sorted arrays
void myMerge(int v[], int arg1[], int beg1, int end1, int arg2[], int beg2, int end2)
{
    int temp[end2 - beg1 + 1];
    int index1 = beg1;
    int index2 = beg2;
    int indexT = 0;
    //comparing between both arrays and storing in temp
    while(index1 <= end1 && index2 <= end2)
    {
        if(arg1[index1] <= arg2[index2])
            temp[indexT++] = arg1[index1++];
        else
            temp[indexT++] = arg2[index2++];
    }
    // store remainder of arg1 into temp
    while(index1 <= end1)
      temp[indexT++] = arg1[index1++];
    // store remainder of arg2 into temp
    while(index2 <= end2)
      temp[indexT++] = arg2[index2++];
    // copy temp into sorted array
    for(int i = 0; i < end2 - beg1 + 1; i++)
    {
        v[beg1 + i] = temp[i];
    }
}




int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Please include input filename and output filename in param list.\n";
		cout << "Example:\n";
		cout << "     % mySort numbers.txt mySorted.txt\n";
		exit(EXIT_SUCCESS);
	}


	const int MAX = 1000000;
  	ofstream fout;
	ifstream fin;
	int n;
	
	int v[MAX];
	int count = 0;
	
	fin.open(argv[1]);
	while (fin >> n )
	{
		v[count++] = n;	// insert a number into the array and increase the index
	}

    nums argList[8];
    for(int i = 0; i < 8; i++)
    {
        argList[i].ptr = v;
        argList[i].beg = 125000 * i;
        argList[i].end = (125000 * i) + 124999;
    }
	cout << "Starting multithreaded Array quick sort with "<<count<< " items\n";

    thread thread0 (quick, v, argList[0].beg, argList[0].end);
    thread thread1 (quick, v, argList[1].beg, argList[1].end);
    thread thread2 (quick, v, argList[2].beg, argList[2].end);
    thread thread3 (quick, v, argList[3].beg, argList[3].end);
    thread thread4 (quick, v, argList[4].beg, argList[4].end);
    thread thread5 (quick, v, argList[5].beg, argList[5].end);
    thread thread6 (quick, v, argList[6].beg, argList[6].end);
    thread thread7 (quick, v, argList[7].beg, argList[7].end);

    thread0.join();
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();

	cout << "Ending multithreaded quick sort\n";

    //merging 8 blocks
    myMerge(v, argList[0].ptr, argList[0].beg, argList[0].end, argList[1].ptr, argList[1].beg, argList[1].end);
    myMerge(v, argList[2].ptr, argList[2].beg, argList[2].end, argList[3].ptr, argList[3].beg, argList[3].end);
    myMerge(v, argList[4].ptr, argList[4].beg, argList[4].end, argList[5].ptr, argList[5].beg, argList[5].end);
    myMerge(v, argList[6].ptr, argList[6].beg, argList[6].end, argList[7].ptr, argList[7].beg, argList[7].end);


    //merging 4 blocks
    myMerge(v, v, 0, 249999, v, 250000, 499999);
    myMerge(v, v, 500000, 749999, v, 750000, 999999);

    //merging 2 blocks
    myMerge(v, v, 0, 499999, v, 500000, 999999);



    fout.open(argv[2], ios::out | ios::trunc);
    for (int i = 0; i < count; i++)
		fout << v[i]<<endl;
    fout.close();
	fin.close();
    return 0;
}	