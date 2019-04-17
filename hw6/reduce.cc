#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>


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
	std::unordered_map<std::string,int> mymap;
    std::string line;

	int k = 0;
    while(std::getline(std::cin, line)) // read from std::cin
    {
		struct freq tmp;
		tmp.str = line;
		
		std::getline(std::cin, line);
		tmp.count = stoi(line);
		
		
		std::unordered_map<std::string,int>::iterator got = mymap.find (tmp.str);
		if (got == mymap.end())
		{
			mymap.insert (std::make_pair<std::string,int>((string)tmp.str,(int)tmp.count));
		}
		else
		{
			int hold = got-> second;
			got->second = hold + tmp.count;
		}	
	
		if(k % 100000 == 0)
		{cout<<k<<endl;}
		k++;
	}
	

	for ( auto it = mymap.begin(); it != mymap.end(); ++it )
	{
		struct freq tmp;
		tmp.str = it->first;
		tmp.count = it->second;
		freq.push_back(tmp);
	}
	
	sort(freq.begin(), freq.end(), wayToSort);
	for(int j = 0; j < freq.size(); j++)
	{
		cout<<freq[j].str<<" "<<freq[j].count<<endl;
	}
}
	
	
	
	
	/*bool match = false;
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
		
		
		
	sort(freq.begin(), freq.end(), wayToSort);
	for(int j = 0; j < freq.size(); j++)
	{
		cout<<freq[j].str<<" "<<freq[j].count<<endl;
	}*/