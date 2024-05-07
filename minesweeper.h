#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>

const int MAX_BOARD_SIZE = 20;
const int MAX_NUM_MINES = 50;
const char MINE = 'X';
const char FLAG = 'F';
const char HIDDEN = '*';
const char EMPTY = ' ';
const char OPEN = 'O';

extern char gameBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
extern char mineBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
extern int flagsPlaced;
extern int minesFlagged;
extern bool gameOver;
extern time_t startTime, endTime;
extern int boardSize;
extern int numMines;

void createMinePositions();
void countAdjacentMines();
void createGameBoard();
void printGameBoard();
void openCell(int x, int y);
void flagCell(int x, int y);
void checkGameStatus();
void printInstructions();
void welcomeMessage();
void victoryMessage();
void gameOverMessage();
void saveGame();
void loadGame();
void printOptions();
void playAgain();
void setDifficulty();
void playGame();

#endif // MINESWEEPER_H
