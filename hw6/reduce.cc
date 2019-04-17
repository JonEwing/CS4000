////////////////////////////////////////////////////////////////////////////////////////
// Author: Jonathan Feige
// File: mapper.cc
// Date: 04/17/2019
// Description: This reads in from the standard input cin. 
// It takes the infromation and compiles it all into an unsorted map. 
// 						
//						g++ -o map mapper.cc -I.
//						g++ -o reduce reduce.cc -I.
//						cat *file_name*.csv | ./map *ngrams*| ./reduce
////////////////////////////////////////////////////////////////////////////////////////#include <iostream>


#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// Name: freq
// In: N/A
// Out: N/A
// Description: This is the struct that helps manage the hashmap
////////////////////////////////////////////////////////////////////////////////////////
struct freq
{
	int count;
	string str;
};

////////////////////////////////////////////////////////////////////////////////////////
// Name: wayToSort
// In: freq a, freq b
// Out: bool
// Description: Helps sort a vector of freqs
////////////////////////////////////////////////////////////////////////////////////////
bool wayToSort(freq a, freq b) 
{
	return a.count < b.count; 
}


int main()
{
	vector<freq> freq;
	vector<string> str;
	std::unordered_map<std::string,int> mymap;
    std::string line;

    while(std::getline(std::cin, line)) // read from std::cin
    {
		struct freq tmp;
		tmp.str = line;
		
		std::getline(std::cin, line);
		tmp.count = stoi(line);
		
		std::unordered_map<std::string,int>::iterator got = mymap.find (tmp.str);
		if (got == mymap.end()) //If not in the map
		{
			mymap.insert (std::make_pair<std::string,int>((string)tmp.str,(int)tmp.count));
		}
		else //If is in the map
		{
			int hold = got-> second; //Add to counter
			got->second = hold + tmp.count;
		}	
	}
	

	for (auto it = mymap.begin(); it != mymap.end(); ++it )
	{
		struct freq tmp;
		tmp.str = it->first;
		tmp.count = it->second;
		freq.push_back(tmp);
	}
	
	sort(freq.begin(), freq.end(), wayToSort); //sorts
	for(int j = 0; j < freq.size(); j++) 
	{
		cout<<freq[j].str<<" "<<freq[j].count<<endl; //Outputs sorted map
	}
}