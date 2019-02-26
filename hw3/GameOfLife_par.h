#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <pthread.h>

using namespace std;

vector<vector<int>> hold;
vector<vector<int>> board;
pthread_mutex_t mymutex;
pthread_barrier_t mybarrier;

class GameOfLife
{
public:
	void* get_next(void* argument);
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

void* get_next(void* argument)
{
	int n = board.size();
	int alive;

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
					
					pthread_mutex_lock(&mymutex);
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
					pthread_mutex_unlock(&mymutex);
					
					pthread_barrier_wait(&mybarrier);
				}
			}
		}
	hold = new_board;
	return NULL;
}

vector<vector<int>> SimulateLife(vector<vector<int>> &start, int life_cycle)
{
	int n = start.size();
	board = start;
	
	int end = 0;
	pthread_t* thread_array;
	int return_code = pthread_mutex_init(&mymutex,NULL);
	thread_array = new pthread_t[4];
	
	for(int k = 0; k < life_cycle; k++)
	{
		end = k%4 %4;
		pthread_create(&thread_array[k%4],NULL, get_next, &end);
		//get_next(&end);
		board = hold;
	}
	return board;
}






/*
class GameOfLife
{
public:
	vector<vector<int>> SimulateLife(vector<vector<int>> &board, int life_cycle);
	void* get_next(void* end);
	void print_board(vector<vector<int> > &board);
};

void *get_next(void* end)
{
	int n = board.size();
	vector<vector<int>> new_board;

		for(int i = 0; i < n; i++)
		{
			new_board.push_back(vector<int>());
			for(int j = 0; j < n; j++)
			{
				int alive = 0;
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

					pthread_mutex_lock(&mymutex);
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
					pthread_mutex_unlock(&mymutex);
				}
			}
		}
		hold = new_board;
		return NULL;
}

vector<vector<int>> SimulateLife(vector<vector<int>> &board, int life_cycle)
{
	int n = board.size();
	int end = 0;
	pthread_t* thread_array;
	int return_code = pthread_mutex_init(&mymutex,NULL);
	thread_array = new pthread_t[4];
	
	for(int k = 0; k < life_cycle; k++)
	{
		get_next(&end);
		//pthread_create(&thread_array[k%4],NULL, get_next, &end);
		board = hold;
	}
	return board;
} */