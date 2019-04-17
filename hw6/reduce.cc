#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

struct freq
{
	int count;
	string str;
};

bool wayToSort(freq a, freq b) { return a.count < b.count; }


int main()
{
	vector<freq> freq;
	vector<string> str;
    std::string line;

	std::getline(std::cin, line);
	std::cout <<line <<endl;
	
	std::getline(std::cin, line);
	std::cout <<line <<endl;
	
	std::getline(std::cin, line);

	int i = 0;
    while(std::getline(std::cin, line)) // read from std::cin
    {
		str.push_back(line);
	}
	
	int k = 0;
	for(int i = 0; i < str.size(); i++)
	{
		bool match = false;
		for(int j = 0; j < freq.size(); j++)
			{
				if(str[i] == freq[j].str)
				{
					match = true;
					freq[j].count++;
				}
			}
		if(match == false)
		{
			struct freq tmp;
			tmp.str = str[i];
			tmp.count = 1;
			freq.push_back(tmp);
		}	
		k++;
		if(k % 100000 == 0)
			cout<<k<<endl;
	}	
	sort(freq.begin(), freq.end(), wayToSort);
	
	for(int j = 0; j < freq.size(); j++)
	{
		cout<<freq[j].str<<" "<<freq[j].count<<endl;
	}
}