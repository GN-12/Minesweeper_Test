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

#include <iostream>
#include <cassert>
#include <fstream>
#include "minesweeper.h"
#include <deepstate/DeepState.hpp>

using namespace deepstate;

// Test case 1: Test creating mine positions
TEST(Minesweeper, CreateMinePositions) {
    createMinePositions();
    int countMines = 0;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (mineBoard[i][j] == MINE)
                countMines++;
        }
    }
    ASSERT_EQ(countMines, numMines);
}

// Test case 2: Test counting adjacent mines
TEST(Minesweeper, CountAdjacentMines) {
    // Set up mineBoard for testing
    mineBoard[0][0] = MINE;
    mineBoard[0][1] = MINE;
    mineBoard[1][1] = MINE;

    // Call countAdjacentMines
    countAdjacentMines();

    // Assert counts
    ASSERT_EQ(mineBoard[0][0], '2');
    ASSERT_EQ(mineBoard[0][1], MINE);
    ASSERT_EQ(mineBoard[1][1], MINE);
}

// Test case 3: Test flagging cells
TEST(Minesweeper, FlagCell) {
    // Initialize gameBoard for testing
    gameBoard[0][0] = HIDDEN;

    // Flag a cell
    flagCell(0, 0);

    // Assert if the cell is flagged
    ASSERT_EQ(gameBoard[0][0], FLAG);
}

// Test case 4: Test opening cells
TEST(Minesweeper, OpenCell) {
    // Initialize mineBoard for testing
    mineBoard[0][0] = MINE;

    // Open a cell
    openCell(0, 0);

    // Assert if the game is over
    ASSERT_TRUE(gameOver);
}

// Test case 5: Test checking game status
TEST(Minesweeper, CheckGameStatus) {
    // Initialize mineBoard and gameBoard for testing
    mineBoard[0][0] = MINE;
    gameBoard[0][0] = FLAG;
    minesFlagged = 1;
    numMines = 1;

    // Check game status
    checkGameStatus();

    // Assert if the game is over
    ASSERT_TRUE(gameOver);
}

// Test case 6: Test saving and loading game
TEST(Minesweeper, SaveLoadGame) {
    // Save the game
    saveGame();

    // Load the game
    loadGame();

    // Assert if the loaded game state matches the saved state
    ASSERT_EQ(gameBoard[0][0], HIDDEN);
}

// Test case 7: Test setting difficulty
TEST(Minesweeper, SetDifficulty) {
    // Set board size and number of mines
    boardSize = 20;
    numMines = 50;

    // Set difficulty
    setDifficulty();

    // Assert if the difficulty is set correctly
    ASSERT_EQ(boardSize, 20);
    ASSERT_EQ(numMines, 50);
}

// Test case 8: Test playing the game
TEST(Minesweeper, PlayGame) {
    // Call playGame
    playGame();

    // Assert if the game is over
    ASSERT_TRUE(gameOver);
}