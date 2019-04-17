#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

string str1 = "https://";
string str2 = "#";

vector<string> rm_url_hash(vector<string> test)
{
	vector<string> ret;
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

vector<string> rm_special_chars(vector<string> test)
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
	return test;
}


vector<string> mk_ngram(vector<string> test,int n)
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

int main() {

	string t;
	int n;
	vector<string> qouted;
	vector<string> valid;
	vector<string> ngrams;
	
	cout<<"Enter your filename"<<endl;
	cin>>t;
	
	cout<<"Enter your ngram length"<<endl;
	cin>>n;
	
	std::ifstream in;
	in.open(t);
	
	int i = 0;
	while(!in.eof()) {
		if(in.peek() ==',') {
			char c;
			in.get(c);
		}
		else{	
			in >> quoted(t);
			i++;
			
			while(in.peek() =='"') {
				string temp;
				in >> quoted(temp);
				t = t + temp;
			}
			
			if(i == 12)
			{
				string hold;
				istringstream in_string(t);
				while (in_string >> hold) {
				qouted.push_back(hold);
				}
				
				valid = rm_url_hash(qouted);
				valid = rm_special_chars(valid);
				ngrams = mk_ngram(valid,n);
					
				int len = ngrams.size() - (n - 1);
				for(int i = 0; i < len; i++)
				{
					cout<<ngrams[i]<<endl;
				}
				qouted.erase (qouted.begin(),qouted.end());
				valid.erase (valid.begin(),valid.end());
				ngrams.erase (valid.begin(),valid.end());
			}
			else if(i == 30)
			{
				i = 0;
			}
		}
	}
}