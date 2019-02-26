#include <iostream>
#include <vector>

using namespace std;

class GameOfLife
{
public:
	vector<vector<int>> SimulateLife(vector<vector<int>> &board, int life_cycle);
	void print_board(vector<vector<int> > &board);
};

void print_board(vector<vector<int> > &board) {
  int n = board.size();
  for (int i=0;i<n;i++) {
    for (int j=0;j<n;j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

vector<vector<int>> SimulateLife(vector<vector<int>> &board, int life_cycle)
{
	int n = board.size();
	int alive;
	
	for(int k = 0; k < life_cycle; k++)
	{
		vector<vector<int>> new_board;
		for(int i = 0; i < n; i++)
		{
			new_board.push_back(vector<int>());
			for(int j = 0; j < n; j++)
			{
				alive = 0;
				if(board[i][j] == 2)
				{
					new_board[i].push_back(2);
				}
				else
				{
					if(board[(i + 1) % n][j] == 1 || board[(i + 1) % n][j] == 2)
					{
						alive++;
					}

					if(board[(n + (i - 1)) % n][j] == 1 || board[(n + (i - 1)) % n][j] == 2)
					{
						alive++;
					}
	
					if(board[(n + (i - 1)) % n][(j + 1) % n] == 1 || board[(n + (i - 1)) % n][(j + 1) % n] == 2)
					{
						alive++;
					}

					if(board[(n + (i - 1)) % n][(n + (j - 1)) % n] == 1 || board[(n + (i - 1)) % n][(n + (j - 1)) % n] == 2)
					{
						alive++;
					}

					if(board[(i + 1) % n][(j + 1) % n] == 1 || board[(i + 1) % n][(j + 1) % n] == 2)
					{
						alive++;
					}

					if(board[(i + 1) % n][(n + (j - 1)) % n] == 1 || board[(i + 1) % n][(n + (j - 1)) % n] == 2)
					{
						alive++;
					}

					if(board[i][(j + 1) % n] == 1 || board[i% n][(j + 1) % n] == 2)
					{
						alive++;
					}

					if(board[i][(n + (j - 1)) % n] == 1 || board[i% n][(n + (j - 1)) % n] == 2)
					{
						alive++;
					}

					if(alive == 0 || alive == 1)
					{
						new_board[i].push_back(0);
					}
					else if(alive == 2)
					{
						new_board[i].push_back(board[i][j]);
					}
					else if(alive == 3)
					{
						new_board[i].push_back(1);
					}
					else
					{
						new_board[i].push_back(0);
					}
				}
			}
		}
		board = new_board;
	}

	return board;


}