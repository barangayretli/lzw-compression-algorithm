#include <iostream>
#include <string>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

//Baran Gayretli - Fall 2018 - HW2

bool isExist(string arr[],int size, int toFind)// check if the index is empty or not
{
	if(arr[toFind].size()==0)
		return false;
	return true;
}

int main()
{
	ofstream decompout;
	decompout.open("decompout.txt");
	ifstream input;
	input.open("compout.txt");
	int temp;// store the integer codes temporarily
	vector <int>codes;
	while(input >>temp)
	{
		codes.push_back(temp);//store the codes in vector
	}
	
	vector <int>::iterator begin=codes.begin();
	vector<int>::iterator end=codes.end();
	int Size = 256;//dictionary size
	string dictionary[4096];
	for (int i = 0; i < 256; i++)//dictionary initialization
		dictionary[i] = string(1, i);

	string w(1, *begin++);//get the character at where begin points to
	string result = w;
	string first;
	for ( ; begin != end; begin++) 
	{
		int it = *begin;
		if (isExist(dictionary,Size,it))//if dict[it] is not empty
			first = dictionary[it];
		else if (it == Size)
			first = w + w[0];

		result += first;// add it to the result string
		
		dictionary[Size] = w + first[0];// add w + first index of entry to the dictionary

		if(Size<4096)//size wil not exceed 4096
			Size++;

		w = first;
	}
	decompout << result; // write the original string back to the decompout file

	return 0;
}