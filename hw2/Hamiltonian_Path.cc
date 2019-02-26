//***************************************************************
// File: Hamiltonian_Path.cc
// Author: David W. Juedes
// Edit: Jonathan Feige
// Purpose: This code finds whether there exists a Hamiltonian Path 
// from one vertex to another in a graph.
//****************************************************************

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <list>
#include <omp.h>
using namespace std;

//*******************************************************************
// Function: valid_tour.
// Takes: Vector of lists of int and a vector of int.
// Returns: Bool.
// Purpose: Vhecks for a valid tour.
//********************************************************************

bool valid_tour(vector<list<int> >&adj_list, vector<int> &tour) {
  // Tests whether the tour is valid
  // Returns the total distance

	int start = tour[0];
	bool valid = true;
	for (int i=1;i<tour.size();i++) 
	{
		bool found = false;    // Is there an edge from tour[i-1] to tour[i]
		
		for (list<int >::iterator p = adj_list[tour[i-1]].begin();p!=adj_list[tour[i-1]].end();++p) 
		{
			if (*p == tour[i]) 
			{
				found = true;
				break;
			}
		}
		if (!found) valid = false;
	}
  return valid;
}


//*******************************************************************
// Function: Hamiltonian_tour.
// Takes: Vector of lists of int, two ints, and a bool.
// Returns: Vector of ints.
// Purpose: Takes the tour and calculataes all possible permutations.
//********************************************************************

vector<int> Hamiltonian_tour(vector<list<int> >&adj_list, int i1, int j1, bool &found_it) {

 	int n = adj_list.size();
	vector<int> return_tour;
	
	#pragma omp parallel num_threads(4)
  	{
    	vector<int> perm;
		
    	for (size_t i=0;i<n;i++) 
		{
    		if ((i!=i1)&&(i!=j1)) 
			{
        		perm.push_back(i);
      		}
    	}
		
    	int per = 0;
		
    	do 
		{
      		if(per % omp_get_num_threads() == omp_get_thread_num())
      		{
        		vector<int> tour;
        		tour.resize(n);
        		tour[0] = i1;
        		tour[n-1] = j1;

        		for (int i=0;i<n-2;i++) 
				{
        			tour[i+1] = perm[i];
        		}

       			bool found;
		        found = valid_tour(adj_list,tour);
		        if (found) 
				{  
        			found_it=true;
          			return_tour = tour;
        		}
      		}
      		per++;

		}  while (next_permutation(perm.begin(),perm.end()) && found_it == false);
	}
    
return return_tour;
 
}

int main() {
	int n;
	int i1;
	int j1;
	cin >> n;
	cin >> i1;
	cin >> j1;
	string line;
	getline(cin,line); // Get the newline
	vector<list<int> > adj_list;
	adj_list.resize(n);

	while (!cin.eof()) 
	{
		getline(cin,line);
		if (!cin.fail()) 
		{
			istringstream in(line);

			int j;
			in >> j;
			char c;
			in >> c;
			assert(c==':');
			while (!in.eof()) 
			{
				int i;
				in >> i;
				if (!in.fail()) 
				{
					adj_list[j].push_back(i);
				}
			}
		}
	}
	bool found=false;
	vector<int> opt;
  
	opt = Hamiltonian_tour(adj_list,i1,j1,found);
	if (found) 
	{
		cout << "Tour = ";
		for (int i=0;i<opt.size();i++) 
		{
			cout << opt[i] << " ";
		}
    cout << endl;
	} 
	else 
	{
		cout << "No Hamiltonian Tour" << endl;
	}
}
