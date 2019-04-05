//***************************************************************
// File: Hamiltonian_Path.cc
// Author: David W. Juedes
// Edit: Jonathan Feige
// Purpose: This code finds whether there exists a Hamiltonian Path 
// from one vertex to another in a graph.
//****************************************************************

#include <iostream>
#include<fstream>
#include <vector>
#include <omp.h>
#include <unistd.h> 
#include <mpi.h>
using namespace std;


int main(int argc, char *argv[]) {
	string file;
	ifstream infile;
	int num_processes;
	int proc_num;
	vector<string> dictionary;
	vector<string> passwords;
	vector<string> combo;
	vector<string> numbers_combo;
		
	infile.open (argv[1]);
        while(!infile.eof()) // To get you all the lines.
        {
	        getline(infile,file); // Saves the line in STRING.
			dictionary.push_back(file);
        }
	infile.close();
	
	infile.open (argv[2]);
        while(!infile.eof()) // To get you all the lines.
        {
	        getline(infile,file); // Saves the line in STRING.
			passwords.push_back(file);
        }
	infile.close();
	
	
	combo = dictionary; //one word
	
	for(int i = 0; i < dictionary.size(); i++) //one word, nums
	{
		for(int j = 0; j < dictionary.size(); j++)
		{
			combo.push_back(dictionary[i] + dictionary[j]);
		}
	}
	
	for(int i = 0; i < 10; i++) //one num
	{
		std::string x = std::to_string(i);
		numbers_combo.push_back(x);
	}
	
	for(int i = 0; i < 10; i++) //two num
	{
		for(int j = 0; j < 10; j++)
		{
			std::string x = std::to_string(i);
			std::string y = std::to_string(j);
			numbers_combo.push_back(x + y);
		}
	}
	
	for(int i = 0; i < 10; i++) //three num
	{
		for(int j = 0; j < 10; j++)
		{
			for(int k = 0; k < 10; k++)
			{
				std::string x = std::to_string(i);
				std::string y = std::to_string(j);
				std::string z = std::to_string(k);
				numbers_combo.push_back(x + y + z);
			}
		}
	}
	
	for(int i = 0; i < dictionary.size(); i++) //one word, nums
	{
		for(int j = 0; j < numbers_combo.size(); j++)
		{
			std::string x = std::to_string(j);
			combo.push_back(dictionary[i] + numbers_combo[j]);
			combo.push_back(numbers_combo[j] + dictionary[i]);
		}
	}
	
	std::string delimiter = "$";
	vector<string> tok;
	
	for (int i = 0; i < passwords.size();i++)
	{
		string path = passwords[i];
		size_t pos = 0;
		std::string token;
	
		while ((pos = path.find(delimiter)) != std::string::npos) 
		{
			token = path.substr(0, pos);
			tok.push_back(token);
			path.erase(0, pos + delimiter.length());
		}
	}
	
	int size = passwords.size();
	string found[size];
	
	//cout<<combo.size()<<endl;
	
	//#pragma omp parallel for
	
	MPI_Init(NULL,NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD,&num_processes);
	MPI_Comm_rank(MPI_COMM_WORLD,&proc_num);
	
	for(int i = 0; i < passwords.size(); i ++)
	{		
		bool match = false;
		int j = 0;
		string t; 
		string salt = "$6$" + tok[(i + 1)*3 - 1];
		
		
		for(int j = proc_num; j < combo.size(); j += num_processes)
		{	 
			string pass = combo[j]; 
			t = crypt(pass.c_str(),salt.c_str()); 
			
			if(t == passwords[i])
			{
				match = true;
				found[i] = combo[j];
				j = combo.size() + 1;			
			}
		}
		if(match == true)
		{
			cout<<"Password "<<i + 1<<" is "<<found[i]<<endl;
		}
		j = 0;
		match = false;
	}	
	
	MPI_Finalize();
}