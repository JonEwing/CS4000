//******************************************
//Jonathan Feige
//CS4900
//P2.2
//Takes the files as a path
//returns a dir or a file
//******************************************

#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{	
	vector<string> words;
	vector<string> cyrps;
	vector<string> nums;
	vector<string> combo;

	string in;
	cout<<"Enter dictionary"<<endl;
	cin >> in;

	in = "words";
	string line;
	ifstream myfile (in);
	if (myfile.is_open())
	{
   		while ( getline (myfile,line) )
		{ 
			words.push_back(line);
    	}
    myfile.close();
	}

	cout<<"Enter passwords"<<endl;
	cin >> in;
	in = "enc_passwords";

 	ifstream myfile_other (in);
  	if (myfile_other.is_open())
 	{
   		while ( getline (myfile_other,line) )
		{ 
			cyrps.push_back(line);
    	}
    myfile_other.close();
	}

	for(int i = 0; i < 10; i++)
	{
		std::string x = std::to_string(i);
		nums.push_back(x);
	}

	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			std::string x = std::to_string(i);
			std::string y = std::to_string(j);
			nums.push_back(x + y);
		}
	}

	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{	
			for(int k = 0; k < 10; k++)
			{
				std::string x = std::to_string(i);
				std::string y = std::to_string(j);
				std::string z = std::to_string(k);
				nums.push_back(x + y + z);
			}
		}
	}

	combo = words;

	for(int i = 0; i < words.size(); i++) // two words
	{
		for(int j = 0; j < words.size(); j++)
		{
			combo.push_back(words[i] + words[j]);
		}
	}

	for(int i = 0; i < words.size(); i++) //one word one num
	{
		for(int j = 0; j < nums.size(); j++)
		{
			combo.push_back(words[i] + nums[j]);
			combo.push_back(nums[j] + words[i]);
		}
	}

	for(int i = 0; i < words.size(); i++) //one word one num
	{
		for(int j = 0; j < words.size(); j++)
		{	
			for(int k = 0; k < nums.size(); k++)
			{
				combo.push_back(nums[k] + words[i] + words[j]);
				combo.push_back(words[i] + nums[k] + words[j]);
				combo.push_back(words[i] + words[j] + nums[k]);
			}
		}
	}


	std::string delimiter = "$";
	vector<string> tok;


	for(int i = 0; i < cyrps.size(); i++)
	{
		size_t pos = 0;
		string path = cyrps[i];
		std::string token;
			while ((pos = path.find(delimiter)) != std::string::npos) 
		{
   			token = path.substr(0, pos);
			tok.push_back(token);
   			path.erase(0, pos + delimiter.length());
		}
		//tok.push_back(path);
	}
		//tok.shrink_to_fit();
		
	bool match = false;
	int j = 0;

	#pragma omp	parallel for
	for(int i = 0; i < cyrps.size(); i++)
	{
		while(match == false && j < combo.size())
		{
			string salt  = "$6$" + tok[((i + 1) * 3) - 1];
			string pass = combo[j];
			string t = crypt(pass.c_str(),salt.c_str());
			if(j % 1000 == 0)
			{
				cout<<j<<endl;
			}

			if(t == cyrps[i])
			{
				match = true;
				j--;
			}
			j++;
		}
		if(match == true)
		{
			cout<<"Password "<<i + 1<<" is "<<combo[j]<< endl;
		}
		else
		{
			cout<<"Password "<<i + 1<<" Does Not Match "<<combo[j]<< endl;
		}
		match = false;
		j = 0;
	}

}
