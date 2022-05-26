#include "GhostBuster.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Currently rows and columns are set to 8, however your game implementation should work for any other number
const int rows = 8, cols = 8;   

// grid will store characters matrix of rows*cols size, you have to allocate memory to it in initialize function below
char* grid = NULL;

// Ghost will be placed over this location
int ghostRow, ghostCol;

// ***********************************
// No change zone: Don't change anything until the next stars line
// ***********************************

// Don't Change it: Screen width and height values
const int width = 1000, height = 600;

// Don't Change: This function is dealing with SDL and currently it's complete. Don't change anything here
void drawOneBlock(SDL_Renderer* renderer, SDL_Texture* texture, int row, int col, char sym){
    int xbox = width/cols;
    int ybox = height/rows;
    SDL_Rect src;
    switch(sym){
        case 'L': src = {141, 7, 104, 113}; break;
        case 'S': src = {427, 12, 129, 103}; break;
        case 'T': src = {268, 10, 130, 111}; break;
        case 'B': src = {0, 3, 114, 111}; break;
        case 'G': src = {571, 0, 123, 121}; break;
        case 'Z': src = {571, 0, 25, 25}; break;
        case 'F': src = {707, 16, 90, 86}; break;
    }
    SDL_Rect mov = { xbox*col, ybox*row, xbox - 10, ybox - 10};
    SDL_RenderCopy(renderer, texture, &src, &mov);
}

void drawBlocks(SDL_Renderer* renderer, SDL_Texture* texture){
    // Call drawOneBlock for all of the blocks of grid
    // for example to draw a snake over block (3, 5) you call it this way:
    // drawOneBlock(renderer, texture, 3, 5, 'S');
    if(grid == NULL) return;
    for(int i=0;i<rows; i++){
        for(int j=0;j<cols; j++){
            drawOneBlock(renderer, texture, i, j, grid[i*cols+j]);
        }   
    }
}

// ***********************************
// No change zone ends here
// ***********************************

// To Do zone:
// The game is not ended untill the condition is set to True: 
// Initially, ended is equal to false or zero.
bool ended = false;

// each block size is width/cols x height/rows
//Width of each block
int _Width_ = width/cols;
//height of each block   
int _Height_ = height/rows;

void initialize()
{
    // Create memory for grid here, it should be one dimensional array.
    // The memory should be rows*cols size.
    int size = rows*cols;
    grid = new char[size];             
    // Initialize entire grid with 'L' so that locks are displayed all over
    // This loop will thus display all the locks
    int i = 0;
    while(i < size)
    {
        *(grid + i) = 'L';
        i++;
    }
    // generate two random numbers and store in ghostRow and ghostCol variables
    // Mode function would minimize the row nnumber with accordance to no of rows and columns
    ghostRow = (rand() % rows) + 1; //this will generate till 7 therefore we added one to it.    
    ghostCol = (rand() % cols) + 1;
}

// This function will help in finding distance between current cell and ghost cell
int _Distance_(int x1, int x2, int y1, int y2)
{
    int dist = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    return dist;
}

//This will help in finding area of the cells upto current cell;
int _Area_(int length, int bredth)
{
    int area = length * bredth;
    return area;
}

void huntGhost(int x, int y)
{
    // this function is called every time you click on the screen
    // x, y are screen coordinates, you need to identify the block from these coordinates and using screen width and height values
    // according to game rules you need to put appropriate character in the grid for that block
    
    if(ended == false) //This condition satisties untill the game is ended, once ended == True, the game is stuck
    {
        // Variable declaration
        int row, column, Area, Distance;
        
        //this will give us the row number and column number of the current cell
        row = y /_Height_ + 1;  
        column = x /_Width_ + 1;
        
        // display the co-ordinates of the current cell
        cout << "(Row, Column) = (" <<row<< ", " << column <<")"<<endl;
        
        Area = _Area_(cols, row) - (cols - column) - 1;
    
        //distance between the ghost location and current location
        Distance = _Distance_(ghostRow, row, ghostCol, column);     
        
        // Following are the game rules;
        // A snake is drawn if the clicked block is 0-1 blocks away from the ghost
        if(Distance <= 1)
        {
            *(grid + Area) = 'S'; // Place 'S' to draw a snake
        }
        // A turtle is drawn if the clicked block is 2-3 blocks away from the ghost
        else if((Distance>=2) && (Distance <= 3))
        {
            *(grid + Area) = 'T'; // place 'T' to draw a turtle
        }
        // A bunny is drawn if the clicked block is 4 blocks away from the ghost
        else if(Distance == 4)
        {
            *(grid + Area) = 'B'; // // place 'B' to draw a bunny   
        }
        //  if the clicked block is more than 4 blocks away, a snake, turtle or a bunny is drawn randomly.
        else
        {
            int randn = rand() % 3; //this modes with 3 because we want only three random numbers, those would be 'S', 'T', OR 'B'.
            //These position can be changed by clicking again, you will get another symbol.
            if(randn == 0)
            {
                *(grid + Area) = 'S';   
            }
            else if(randn == 1)
            {
                *(grid + Area) = 'T';
            }
            else if(randn == 2)
            {
                *(grid + Area) = 'B';
            }
        }
    }
}

void bustGhost(int x, int y){
    // this function is called when you right-click
    // it should work only one time, and you decide whether game is won or failed
    // once the game is won/failed, nothing in game should change anymore.
    // according to game rules you need to put appropriate character in the grid for that block
    
    
    if(ended == false) //This condition satisties untill the game is ended, once ended == True, the game is stuck
    {
        // Variable declaration
        int row, column, Area, Distance;
        // each block size is width/cols x height/rows
        row = y /_Height_ + 1;
        column = x /_Width_ + 1;
        
        Area = _Area_(cols, row) - (cols - column) - 1;
    
        //distance between the ghost location and current location
        Distance = _Distance_(ghostRow, row, ghostCol, column);     

        if (Distance == 0) //If the distance between ghost location and current location is equal to zero, it means they are at the same position.
        {
            *(grid + Area) = 'G'; // place 'G' to draw snake, when the game is won
            ended = true; //The game will be stuck at this point
            cout<<"You Won The Game, The Ghost Has Been Busted."<<endl;
        }
        
        else
        {
            *(grid + Area) = 'F';// place 'F' to draw failed symbol, when the game is failed
            ended = true;
            cout<<"The Game is Failed"<<endl;
        }    
    }
}

void quitGhostBuster()
{
    // delete the grid here
    delete [] grid;
}