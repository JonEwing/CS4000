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

	int k = 0;
    while(std::getline(std::cin, line)) // read from std::cin
    {
		struct freq tmp;
		tmp.str = line;
		
		std::getline(std::cin, line);
		tmp.count = stoi(line);
		
		bool match = false;
		for(int i = 0; i < freq.size(); i++)
		{
			if(tmp.str == freq[i].str)
			{
				freq[i].count += tmp.count;
				match = true;	
			}
		}
		if(match == false)
		{			
			freq.push_back(tmp);
		}
		
		k++;
		
		if(k % 100000 == 0)
		{
			cout<<k<<endl;
		}
	}
	
	sort(freq.begin(), freq.end(), wayToSort);
	for(int j = 0; j < freq.size(); j++)
	{
		cout<<freq[j].str<<" "<<freq[j].count<<endl;
	}
}