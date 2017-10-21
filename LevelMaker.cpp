#include "stdafx.h"
#include "LevelMaker.h"
#include <iostream>
#include <vector>
#include "Room.h"
#include "Player.h"
#include <ctime>


LevelMaker::LevelMaker(int playerStartPosition)
{
	currentLevel = 0; // This variable is in the case that the game gets to a point where binding of Isaac-like levels can be implemented, then there will be multiple levels.
	levelSize = columns*rows; // makes a rectangle based on the various dimensions of the level that are generated
	maze.assign(levelSize,nullptr); // assigns the room with null rooms
	playerPosition = playerStartPosition; 
	calculateMazeAnswer(); // makes the actual maze
}


void LevelMaker::update(Room* room)
{
	playerPosition = room->locationOnMap;
}

void LevelMaker::printMazeAnswer() { 

	/* for loop printing the way out of the dungeon/ maze level. X's show a location that can be travelled on, O's show a place that cannot be traveled on.*/

	cout << "Your current location in the maze:\n";
	for (int y = 0; y < rows; y++) { // for each row
		for (int x = 0; x < columns; x++) { // x column on the row y 
			
			short currentMazeLocation = y*columns + x; // getting the curren maze location to place a letter, either an x or o
			if (currentMazeLocation == playerPosition) { // if the player is in this room print a T
				SetConsoleTextAttribute(hConsole, _GREEN);
				std::cout << "T" << " ";
			}
			else if (maze[currentMazeLocation] != nullptr) { // If the current maze room is a room with a size, (an accessable room) then print an x
				SetConsoleTextAttribute(hConsole, _RED); // set the text to red
				std::cout << 'X' << " ";
			}
			else if(maze[currentMazeLocation] == nullptr){
				SetConsoleTextAttribute(hConsole, _WHITE);  // if the room is inaccessable, print an o that is black and therefore invisible
				std::cout << "@" << " ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n\n\n";
	SetConsoleTextAttribute(hConsole, _WHITE);
}

void LevelMaker::calculateMazeAnswer() {
	/*
	THIS ALSO SETS THE PLAYER'S LOCATION
	*/

	//This is used to find the elements in a 2d array when passed in as a pointer.
	//0 0 0
	//0 0 0
	//0 0 0
	//mazep refers to 0,0. add (no decimals for integers, rounds down.)1x3 spaces to that location and 0,1 is the location of 2.
	//General equation is *((*pointer)+yval*rowcount+xval)

	const int branchMax = (columns + rows)/10;
	int branchCount = 0;
	std::vector<coordinates *> mazePaths; 
	
	// new vector of coordinates these coordinates refer to the frontmost maze room in their respective lines 
	
	coordinates * firstRoom = new coordinates{ 0,  }; 
	playerPosition = firstRoom->mazeCoordinate(columns);
	mazePaths.emplace_back(firstRoom); // add a new coordinate 0,0

	std::srand(std::time(0));
	for (int i = 0; i < mazePaths.size(); i++) {
			do { // This loop continues for a single maze path until it has reached the entire end of the level.
				maze[mazePaths[i]->x + mazePaths[i]->y*columns] = new Room(); // Assigns a location that previously had an empty room with a room with dimensions.

				int newPath = (int)rand() % 4; // random number to decide if there will be a new path branching from the original path.
				if ( i == 0) { 
					// if 0 go forward with the maze and make a new path on a random side
					// made to ensure at least more than 1 path exists
					mazePaths.emplace_back(mazeDirection(newPath, *mazePaths[i]));
					mazePaths[i]->x += 1;
				} 
				else if (newPath ==2 || newPath == 1 &&  branchCount < branchMax) { 
					// if new path is one make a new path on a random side of the first path
					branchCount++;
					mazePaths.emplace_back(mazeDirection(newPath, *mazePaths[i]));
					mazePaths[i]->x += 1;
				} 
				else {
					// the path will continue in a random direction.
					int direction = rand() % 3;// integer that decides the direction that the room will spawn in relative to the last one
					mazeDirection(direction, mazePaths[i]);
				}

				mazeRoomLocations.emplace_back(mazePaths[i]->mazeCoordinate(columns));


			} while (mazePaths[i]->x < columns);
	}

	
	/*
	ensures that the room only extends as far as it must downward
	*/
	short lowestRoom = 0;
	for (int i = 0; i < mazePaths.size(); i++) {
		if (mazePaths[i]->y > lowestRoom) { lowestRoom = mazePaths[i]->y; }
	} 
	rows = lowestRoom+1;
	
	adjustMazeExits();
	for (int i = 0; i < levelSize; i++) {
		if (maze[i]!=nullptr) {
			maze[i]->locationOnMap = i;
		}
	}// Assigns each room's location on the map
}

void LevelMaker::adjustMazeExits()
{ // This method tells each room where the surrounding rooms are for the room, using 1 for the room and going clockwize around
	// the square of the room ending at 4 on the left.
	Room *  surroundingRooms[4];
	for ( int i = 0; i < maze.size(); i++) {
		if (maze[i] != nullptr) { // If the room is an actual room
			// if the room is has a northern neighbour assign it as a surrounding room,
			//otherwise the position in the array corresponding to north is nullptr

			if (i - columns >= 0 && maze[i - columns] != nullptr) {
				
				surroundingRooms[0] = maze[i - columns];
			} 
			else { surroundingRooms[0] = (nullptr); }

			 

			// Same for eastern neighbouring room, otherwise its nullptr
			if ((i + 1) % columns != 0 && (i + 1) <= rows*columns - 1 && maze[i + 1] != nullptr) {
				surroundingRooms[1] = maze[i + 1];
			}
			else { surroundingRooms[1] = (nullptr); }

			//for neighbouring southern rooms
			if (i + columns <= rows * columns - 1 && maze[i + columns] != nullptr) {
				surroundingRooms[2] = maze[i + columns];
			}
			else { surroundingRooms[2] = nullptr; }

			//for neighbouring western rooms
			if (((i - 1) % (columns) != 7 || i == 1) && i - 1 >= 0 && maze[i - 1] != nullptr) {
				surroundingRooms[3] = maze[i - 1];
			}
			else { surroundingRooms[3] = (nullptr); }

			//Assign the exits in each room that has surrounding rooms.
			maze[i]->assignExits(surroundingRooms);
		}
	}
}

LevelMaker::coordinates * LevelMaker::mazeDirection(int direction, coordinates coordinate) {

	if (direction == 1 && coordinate.y >0 && maze[coordinate.mazeCoordinate(columns)] != nullptr) {
		coordinate.y -= 1; 
	} // if 1 go up
	else if (direction == 2 && coordinate.y<rows - 1 && maze[coordinate.mazeCoordinate(columns)] != nullptr) {
		coordinate.y += 1;
	} // if 2 go down
	coordinates * newCoord = new coordinates;
	*newCoord = coordinate;
	return newCoord;
}

void LevelMaker::mazeDirection(int direction, coordinates * coordinate) {
	if (direction == 1 && coordinate->y > 0 && maze[coordinate->mazeCoordinate(columns) - columns] != nullptr && coordinate->x<columns-1) { 
		coordinate->y -= 1;
	} // if 1 go up
	else if (direction == 2 && coordinate->y < rows - 1 && maze[coordinate->mazeCoordinate(columns) + columns] != nullptr	 && coordinate->x<columns - 1) {
		coordinate->y += 1; 
	} // if 2 go down
	else if (maze[coordinate->mazeCoordinate(columns)+1]!= nullptr && coordinate-> x < columns-1) { 
		coordinate->x += 1; 
	}
	else { coordinate->x = columns + 1; } // Cancels the continuation of the maze path 
}

int LevelMaker::coordinates::mazeCoordinate(int columns){return this->x + y*columns;}

//getter definitions
int LevelMaker::getCurrentLevel() { return currentLevel; } // Get's current maze difficulty level
vector<Room*> LevelMaker::getMaze(){ return maze; } // returns the actual maze vector
std::vector<int> LevelMaker::getMazeRooms(){ return mazeRoomLocations; }
Room * LevelMaker::getPlayerRoom(){ return maze[playerPosition]; }

