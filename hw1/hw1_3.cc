#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cassert>
#include <omp.h>

using namespace std;

int read_q(istream &in) {
  int q;
  in >> q;
  return q;
}

int read_m(istream &in) {
  int m;
  in >> m;
  return m;
}

vector<vector<int> > read_M(istream &in) {
  string line;
  vector<vector<int> > M;
  while (!in.eof()) {
    getline(in,line);
    if (!in.fail()) {
      istringstream in1(line);
      vector<int> row;
      while (!in1.eof()) {
	int x;
	in1 >> x;
	if (!in1.fail()) {
	  row.push_back(x);
	}
      }
      M.push_back(row);
    }
  }
  return M;
}
 
 int horiztonal(vector<vector<int>> &M, int q, int m) 
{
	int max = 0;
	
	#pragma omp parallel for num_threads(4)
	for(int i = 0; i< M.size(); i++)
	{
		for(int j = 0; j < m; j++)
			{
				int pro = 1;
				int travle = 0;
				int k = j;
				while(travle < m && k < M.size())
				{
					pro = (pro * M[i][k]) % q;
					travle++;
					k++;
				}
				if(max < pro)
					max = pro;
			}
	}
	return max;
}

int vertical(vector<vector<int>> &M, int q, int m) 
{
	int max = 0;
	
	#pragma omp parallel for num_threads(4)
	for(int i = 0; i< m; i++)
	{
		for(int j = 0; j < M.size(); j++)
			{
				int pro = 1;
				int travle = 0;
				int k = i;
				while(travle < m && k < M.size())
				{
					pro = pro * (M[k][j] % q) % q;
					travle++;
					k++;
				}
				if(max < pro)
					max = pro;
			}
	}
	return max;
}
 
 int diagonal_down(vector<vector<int>> &M, int q, int m) 
{
	int max = 0;
	
	#pragma omp parallel for num_threads(4)
	for(int i = 0; i< m; i++)
	{
		for(int j = 0; j < m; j++)
			{
				int pro = 1;
				int travle = 0;
				int k = i;
				int l = j;
				while(travle < m && k < M.size() && l < M.size())
				{
					pro = pro * (M[k][l] % q) % q;
					travle++;
					k++;
					l++;
				}
				if(max < pro)
					max = pro;
			}
	}
	return max;
}

 int diagonal_up(vector<vector<int>> &M, int q, int m) 
{
	int max = 0;
	
	#pragma omp parallel for num_threads(4)
	for(int i = 0; i< M.size() - (m - 1); i++)
	{
		for(int j = m - 1; j < M.size(); j++)
			{
				int pro = 1;
				int travle = 0;
				int k = i;
				int l = j;
				while(travle < m && k < M.size() && l < M.size())
				{
					pro = pro * (M[k][l] % q) % q;
					travle++;
					k++;
					l--;
				}
				if(max < pro)
					max = pro;
			}
	}
	return max;
}

int main() {
  int q;
  int m;
  int max = 0;
  int hold = 0;
  
  vector<vector<int> > M;
  m = read_m(cin);
  q = read_q(cin);
  string line;
  getline(cin,line);
  assert(line == "");

  M = read_M(cin);
	
	hold = horiztonal(M, q, m);
	if (max < hold)
		max = hold;
	
	hold = vertical(M, q, m);
	if (max < hold)
		max = hold;
	
	hold = diagonal_up(M, q, m);
	if (max < hold)
		max = hold;
	
	hold = diagonal_down(M, q, m);
	if (max < hold)
		max = hold;
	
	cout<<max<<endl;
}
  
 