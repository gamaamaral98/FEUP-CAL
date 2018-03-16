/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}

// 1.a)
bool Labirinth::findGoal(int x, int y)
{
	initializeVisited();
	return goal_aux(x,y);
}

bool Labirinth::goal_aux(int x, int y){

	//Test the position given as argument.

	if(x < 0 || y < 0 || x >= 10 || y >= 10 || labirinth[y][x] == 0 || visited[y][x] )
		return false;

	// If the position is valid and isn't visited nor a wall, we will mark it as visited
	visited[y][x] = true;

	//Time to check if the position is the goal

	if(labirinth[y][x] == 2){
		cout << "You just reached the way out!" << endl;
		return true;
	}

	//Else test all the other possibilities
	return goal_aux(x+1, y) || goal_aux(x-1, y) || goal_aux(x, y+1) || goal_aux(x, y-1);
}

//1.b)
/**
 * T(n) = O(n^2)
 */


