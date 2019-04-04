#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include <list>
using namespace std;

#define	START -1
#define END	2
#define KEY	3

class MazeGenerator
{
private:
	vector < vector <bool> > mazevec;		// the maze itself
	list < pair < int, int> > drillers;		// list of paths to go
	void PaveStartAndEnd();
	void PrintMaze();
	void VecTo2DArray();
public:
	const int maze_size_x;					// number of cols
	const int maze_size_y;					// number of rows
	int** maze;
	int keyr, keyc;
	MazeGenerator(int r, int c);
	void Generate();
};