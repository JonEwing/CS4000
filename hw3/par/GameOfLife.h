//****************************************************************************
//GameOfLife.h
//Jonathan Feige
//Spring 2019
//CS400
//****************************************************************************

#include <thread>
#ifndef GOL
#define GOL

using namespace std;

class GameOfLife
{
public:
    vector<vector<int>> SimulateLife(std::vector<std::vector<int>> &board, int life_cycles);
    static void get_next(vector<std::vector<int>> &board, vector<vector<int>> &next, int thread_num, int total_threads);
	static int whos_alive(vector<std::vector<int>> &board, int i, int j);
};

//*******************************************************************
// Function: SimulateLife.
// Takes: Vector of Vector of int's and an int.
// Returns: Vector of Vector of int's
// Purpose: Runs the program lifecycle times, in parallel
//********************************************************************
vector<vector<int>> GameOfLife::SimulateLife(vector<vector<int>> &board, int life_cycles)
{
	int n = board.size();
    for(int x = 0; x < life_cycles; x++)
	{
        vector<vector<int>> tmp;
        tmp.resize(n);
		
        for(int i = 0; i < n; i++){
            tmp[i].resize(n);
        }

		int num_threads = thread::hardware_concurrency();
        thread threads[num_threads];
		
        for(int i = 0; i < num_threads; i++)
		{
            threads[i] = thread(get_next, ref(board), ref(tmp), i, num_threads);
        }

        for(thread& thread: threads)
            thread.join();

        board = tmp;
    }
    return board;
}

//*******************************************************************
// Function: get_next.
// Takes: Vector of Vector of int's, Vector of Vector of int's,
//		  int, and an int
// Returns: Void
// Purpose: Pushes values into the new board based on alive.
//********************************************************************
void GameOfLife::get_next(vector<vector<int>> &board, vector<vector<int>> &next, int thread_num, int total_threads)
{
	int n = board.size();
    for(int i = thread_num; i < n; i += total_threads)
	{
        for(int j = 0; j < n; j++)
		{
            if(board[i][j] == 2)
			{
                next[i][j] = 2;
            }
			else
			{
				int alive = whos_alive(board, i, j);
				if(alive == 2)
				{
                    next[i][j] = board[i][j];
                }
				else if(alive == 3)
				{
                    next[i][j] = 1;
				}
				else
				{
					next[i][j] = 0;
				}				
			}   
		}
	}
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

#endif

