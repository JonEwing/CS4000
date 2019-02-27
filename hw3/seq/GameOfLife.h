//****************************************************************************
//GameOfLife.h
//Jonathan Feige
//Spring 2019
//CS400
//****************************************************************************

using namespace std;

class GameOfLife
{
public:
	vector<vector<int>> SimulateLife(vector<vector<int>> &board, int life_cycle);
	vector<vector<int>> get_next(vector<vector<int>> &board);
	static int whos_alive(vector<vector<int>> &board, int x, int y);
};

//*******************************************************************
// Function: SimulateLife.
// Takes: Vector of Vector of int's and an int.
// Returns: Vector of Vector of int's
// Purpose: Runs the program lifecycle times, in parallel
//********************************************************************
vector<vector<int>> GameOfLife::get_next(vector<vector<int>> &board)
{
	int alive;
	int n = board.size();
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
					alive = whos_alive(board,i,j);

					if(alive == 2)
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
		return new_board;
}

//*******************************************************************
// Function: get_next.
// Takes: Vector of Vector of int's, Vector of Vector of int's,
//		  int, and an int
// Returns: Void
// Purpose: Pushes values into the new board based on alive.
//********************************************************************
vector<vector<int>> GameOfLife::SimulateLife(vector<vector<int>> &board, int life_cycle)
{
	
	for(int k = 0; k < life_cycle; k++)
	{
		board = get_next(board);
	}

	return board;
}

//*******************************************************************
// Function: whos_alive.
// Takes: Vector of Vector of int's, int , and an int
// Returns: int
// Purpose: checks all neghbor spaces to get alve amount.
//********************************************************************
int GameOfLife::whos_alive(vector<vector<int>> &board, int x, int y)
{
	int alive = 0;
    int n = board.size();
    for(int i = x - 1; i <= x + 1; i++)
	{
        for(int j = y - 1; j <= y + 1; j++)
		{
			int overflow_fix_i;
			int overflow_fix_j;
            if(i == -1)
			{
				overflow_fix_i = (n + i) % n;
			}
			
			else if(i == n)
			{
				overflow_fix_i = i % n;
			}
			
			else
			{
				overflow_fix_i = i;
			}
			
			if(j == -1)
			{
				overflow_fix_j = (n + j) % n;
			}
			else if(j == n)
			{
				overflow_fix_j = j % n;
			}
			else
			{
				overflow_fix_j = j;
			}
			
            if(board[overflow_fix_i][overflow_fix_j] != 0 && !(overflow_fix_i == x && overflow_fix_j == y))
			{
                alive++;
			}
        }
    }
    return alive;
}