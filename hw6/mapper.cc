////////////////////////////////////////////////////////////////////////////////////////
// Author: Jonathan Feige
// File: mapper.cc
// Date: 04/17/2019
// Description: Takes a file input (twitter data) and parses it down to words. 
// creats a hash map and passes it through the pipe to reduccer.cc
// To run: run the make file with make or for manual input
// 						
//						g++ -o map mapper.cc -I.
//						g++ -o reduce reduce.cc -I.
//						cat *file_name*.csv | ./map *ngrams*| ./reduce
////////////////////////////////////////////////////////////////////////////////////////


#include <iomanip>
#include <iostream>
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
// Name: rm_url_hash
// In: vector<string> test
// Out: vector<string>
// Description: This takes a vector of strings and returns a vector of string 
// -websites and -#
////////////////////////////////////////////////////////////////////////////////////////
vector<string> rm_url_hash(vector<string> &test)
{
	vector<string> ret;
	string str1 = "https://";
	string str2 = "#";

	for(int i = 0; i < test.size(); i++)
	{
		string tmp = test[i];
		
		size_t found1 = tmp.find(str1); 
		size_t found2 = tmp.find(str2); 
		if (found1 == string::npos && found2 == string::npos) 
		{
			ret.push_back(tmp);
		}
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////
// Name: rm_special_chars
// In: vector<string> test
// Out: void
// Description: This takes a vector of strings and removes all 
// special characters from each string in the vector
////////////////////////////////////////////////////////////////////////////////////////
void rm_special_chars(vector<string> &test)
{
	for(int i = 0; i < test.size(); i++)
	{
		string tmp = test[i];
		
		for(int j = 0; j < tmp.size();j++)
		{
			if(tmp[j] == '!' || tmp[j] == '?' || tmp[j] == 39 || tmp[j] == 44|| tmp[j] == ';'|| tmp[j] == ':' ||tmp[j] == '-'||tmp[j] == '.' )
			{
				tmp.erase(tmp.begin()+j);
				test[i] = tmp;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////
// Name: mk_ngram
// In: vector<string> test, int n
// Out: vector<string>
// Description: This takes a vector  and creates strings, length based on n.
// These combinations form n-grams.
////////////////////////////////////////////////////////////////////////////////////////
vector<string> mk_ngram(vector<string> &test,int n)
{
	vector<string> ret;
	for(int i = 0; i < test.size(); i++)
	{	
		string tmp = test[i];
		for (int j = 1; j <= n; j++)
		{
			if (j != 1 && (i + n) <= test.size())
			{
				tmp = tmp + " " + test[i + (j - 1)];
			}
		}
		ret.push_back(tmp);
	}
	return ret;
}

int main(int argc, char *argv[]) {

	string t;
	vector<freq> freq;
	vector<string> qouted;
	vector<string> valid;
	vector<string> ngrams;
	
	cin>>t;
	
	int n = atoi(argv[1]);
	
	string first;
	getline(cin, first, '\n');
	
	int i = 0;
	while(std::getline(cin, t))
	while(!cin.eof()) {
		if(cin.peek() ==',') //Seperates the cells
		{
			char c;
			cin.get(c);
		}
		else{	
			cin >> quoted(t); //Reads in the cell
			i++;
			
			while(cin.peek() =='"') { //Reads in the embeded quote
				string temp;
				cin >> quoted(temp);
				t = t + temp;
			}
			
			if(i == 12)
			{
				string hold;
				istringstream in_string(t);
				while (in_string >> hold) { //Seperates by spaces
				qouted.push_back(hold);
				}
				
				valid = rm_url_hash(qouted);
				rm_special_chars(valid);
				ngrams = mk_ngram(valid,n);
					
				int len = ngrams.size() - (n - 1);
				
				for(int i = 0; i < len; i++)
				{
					bool match = false;
					for(int j = 0; j < freq.size(); j++)
					{
						if(ngrams[i] == freq[j].str)
						{
						match = true;
						freq[j].count++;
						}
					}
					if(match == false)
					{
						struct freq tmp;
						tmp.str = ngrams[i];
						tmp.count = 1;
						freq.push_back(tmp);
					}	
				}	
				
				for(int i = 0; i < freq.size(); i++) //Send to Reducer
				{
					cout<<freq[i].str<<endl;
					cout<<freq[i].count<<endl;
				}
	
				qouted.erase (qouted.begin(),qouted.end());
				valid.erase (valid.begin(),valid.end());
				ngrams.erase (ngrams.begin(),ngrams.end());
				freq.erase (freq.begin(),freq.end());
			}
			else if(i == 30)
			{
				i = 0;
			}
		}
	}
}