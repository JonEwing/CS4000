//============================================================================
// Name        : HW.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "GameOfLife_par.h"
using namespace std;

int main() {
	int n;
	cin >> n;
	
	vector<vector<int> > M;
	M.resize(n);
	for (int i=0;i<n;i++) 
	{
		M[i].resize(n);
		for (int j=0;j<n;j++) 
		{
			cin >> M[i][j];
		}
	}
	
	int k;
	cin >> k;
	
	vector<vector<int> > board;
	board = SimulateLife(M,k);
	
	print_board(board);
	
	return 0;
}
