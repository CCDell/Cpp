#pragma once

#ifndef _LEVEL_MAKER_H
#define _LEVEL_MAKER_H

#define _GREEN 0x02
#define _BLUE 0x05
#define _RED  0x04
#define _BLACK 0x00
#define _WHITE 0x0f
#define _YEN ¥

#include "stdafx.h"
#include <vector>
#include "Room.h"
#include <random>
#include "windows.h"

using namespace std;

class LevelMaker {
public:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // handle to console
	LevelMaker(int);// constructor for LevelMaker, takes an int to assign current level

	void printMazeAnswer();// prints the maze
	void calculateMazeAnswer(); // Makes a binding of Isaac like maze
	void update(Room* nextRoom); // updates the room, takes a room that will be the room that will be acted in by the player
	  
    // Getter funcs
	int getCurrentLevel(); 
	std::vector<Room*> getMaze(); // returns the entire maze vector as a pointers
	std::vector<int> getMazeRooms();
	Room * getPlayerRoom();   // gets a player's point in the maze

	

private:
	short levelSize;

	/*
	Because the maze is formed with a single array acting as the entire maze with artificial columns and rows,
	this structure allows simpler access of locations.
	*/

	struct coordinates { 
		int x;
		int y;
		int mazeCoordinate(int columns); // gets the coordinate of the maze based on the x and y of the coordinate and the number of columns.
	};

	void adjustMazeExits(); // method for assigning neighbouring room locations to all of the maze's rooms.
	// the maze's dimensions
	short columns = (int)rand() % 20 + 5;// this acts as the x distance of the maze, in terms of the square this forms the bottom of the square
	short rows = (int)rand() % 10 + 5; // this acts as the y distance of the maze, in terms of the square this forms the side of the square
	std::vector<int> mazeRoomLocations; // an array of the actual locations of the rooms in maze
	int currentLevel; // current level in the maze
	int playerPosition; // position of player
	/*maze size properties*/
	std::vector<Room*> maze; // entire map of the maze including all locations of the empty rooms
	
	//These two functions direct the new room locations in the creation of the maze.
	LevelMaker::coordinates * mazeDirection(int, coordinates); 	
	void mazeDirection(int, coordinates *);

}; 


#endif