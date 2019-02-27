//*****************************************************************************
//File: Test_Harness.cc
//Author: David W. Juedes
//Date: Spring 2019
//Purpose:  Test Harness for CS 4000, HW #3.
//****************************************************************************

#include <iostream>
#include <vector>

using namespace std;
#include "GameOfLife.h"


//*****************************************************************************
//Function: print_board.
//Purpose: Prints the contents of the matrix "board" to the standard output.
//
//****************************************************************************
void print_board(vector<vector<int> > &board) {
  int n = board.size();
  for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}
//***************************************************************************
//Function: main()
//Purpose: Reads in the data from the standard input (cin), calls the
//appropriate function in GameOfLife class (SimulateLife), and
//prints out final board.
//**************************************************************************
int main() {
  int n;
  cin >> n;
  vector<vector<int> > board;
  board.resize(n);
  for (int i=0;i<n;i++) {
    board[i].resize(n);
    for (int j=0;j<n;j++) {
      cin >> board[i][j];
    }
  }
  int k;
  cin >> k;

  GameOfLife obj;
  vector<vector<int> > result;

  result = obj.SimulateLife(board,k);
  print_board(result);
}
  
  

 
