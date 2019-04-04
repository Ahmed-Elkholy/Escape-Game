#include "MazeGenerator.hpp"

MazeGenerator::MazeGenerator(int r, int c) : maze_size_x(c - 2), maze_size_y(r - 2)
{
	// intialize the maze with false indicating all walls
	mazevec.resize(maze_size_y);
	for (size_t y = 0; y < maze_size_y; y++) mazevec[y].resize(maze_size_x); //to make it 2D
	for (size_t x = 0; x < maze_size_x; x++) for (size_t y = 0; y < maze_size_y; y++) mazevec[y][x] = false;  //zero means wall
}

void MazeGenerator::Generate()
{
	srand(time(NULL));

	// add any pair in the size range
	drillers.push_back(make_pair(maze_size_x / 2, maze_size_y / 2));
	while (drillers.size() > 0)
	{
		list < pair < int, int> >::iterator m, _m; // create 3 iterators to use in the list
		m = drillers.begin(); // list beginning
		_m = drillers.end(); // list ending
		while (m != _m) // not at the end of the list
		{
			bool remove_driller = false;
			switch (rand() % 4) //4 directions
			{
			case 0:
				(*m).second -= 2; // second integer in the first pair -= 2
				if ((*m).second < 0 || mazevec[(*m).second][(*m).first]) // if that second integer is greater than or equal 0 or the maze of that pair is equal to one (path)
				{
					remove_driller = true; // mark pair for removal
					break;
				}
				mazevec[(*m).second + 1][(*m).first] = true; // pave the one below
				break;
			case 1:
				(*m).second += 2;
				if ((*m).second >= maze_size_y || mazevec[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				mazevec[(*m).second - 1][(*m).first] = true; // pave the one above
				break;
			case 2:
				(*m).first -= 2;
				if ((*m).first < 0 || mazevec[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				mazevec[(*m).second][(*m).first + 1] = true; // pave the one to its right
				break;
			case 3:
				(*m).first += 2;
				if ((*m).first >= maze_size_x || mazevec[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				mazevec[(*m).second][(*m).first - 1] = true; // pave the one to its left
				break;
			}
			if (remove_driller) m = drillers.erase(m);
			else
			{
				drillers.push_back(make_pair((*m).first, (*m).second));
				// uncomment the line below to make the maze easier 
				// if (rand()%2) 
				drillers.push_back(make_pair((*m).first, (*m).second));

				mazevec[(*m).second][(*m).first] = true;
				++m;
			}
		}
	}
	PaveStartAndEnd(); //fix start and end
	VecTo2DArray();
	int randr, randc;
	srand(time(NULL));
    maze[1][0] = START;

	do
	{
		randr = rand() % (maze_size_y + 2);
		randc = rand() % (maze_size_x + 2);
	} while (maze[randr][randc] != 0);
	keyr = randr;
	keyc = randc;

	maze[randr][randc] = KEY;

	PrintMaze();
}

void MazeGenerator::PaveStartAndEnd()
{
	int fzx, fzy;
	int lzx, lzy;
	bool found = false;
	for (int y = 0; y < maze_size_y; y++)
	{
		for (int x = 0; x < maze_size_x; x++)
		{
			if (mazevec[y][x] == true)
			{
				found = true;
				fzx = x;
				fzy = y;
				break;
			}
		}
		if (found) break;
	}
	for (int x = 0; x <= fzx; x++) mazevec[0][x] = true;
	for (int y = 0; y <= fzy; y++) mazevec[y][fzx] = true;

	found = false;
	for (int y = maze_size_y - 1; y >= 0; y--)
	{
		for (int x = maze_size_x - 1; x >= 0; x--)
		{
			if (mazevec[y][x] == true)
			{
				found = true;
				lzx = x;
				lzy = y;
				break;
			}
		}
		if (found) break;
	}
	for (int x = maze_size_x - 1; x >= lzx; x--) mazevec[maze_size_y - 1][x] = true;
	for (int y = maze_size_y - 1; y >= lzy; y--) mazevec[y][lzx] = true;
}

void MazeGenerator::PrintMaze()
{
	for (size_t y = 0; y < maze_size_y + 2; y++)
	{
		for (size_t x = 0; x < maze_size_x + 2; x++) printf("%d ", maze[y][x]);
		printf("\n");
	}
}

void MazeGenerator::VecTo2DArray()
{
	maze = new int*[maze_size_y + 2];
	for (int i = 0; i < maze_size_y + 2; i++) maze[i] = new int[maze_size_x + 2];

	for (int y = 0; y < maze_size_y; y++) for (int x = 0; x < maze_size_x; x++) maze[y + 1][x + 1] = !mazevec[y][x];

	for (int x = 0; x < maze_size_x + 2; x++) maze[0][x] = 1;
	for (int x = 0; x < maze_size_x + 2; x++) maze[maze_size_y + 1][x] = 1;
	for (int y = 0; y < maze_size_y + 2; y++) maze[y][0] = 1;
	for (int y = 0; y < maze_size_y + 2; y++) maze[y][maze_size_x + 1] = 1;

	maze[1][0] = 0;
	maze[maze_size_y][maze_size_x + 1] = 0;
}