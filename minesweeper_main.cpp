#include "minesweeper.h"

using namespace std;

char gameBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
char mineBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int flagsPlaced = 0;
int minesFlagged = 0;
bool gameOver = false;
time_t startTime, endTime;
int boardSize = 10;
int numMines = 10;

void createMinePositions() {
    int minesPlaced = 0;
    srand(time(NULL));
    while (minesPlaced < numMines) {
        int x = rand() % boardSize;
        int y = rand() % boardSize;
        if (mineBoard[x][y] != MINE) {
            mineBoard[x][y] = MINE;
            minesPlaced++;
        }
    }
    countAdjacentMines();
}

void countAdjacentMines() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (mineBoard[i][j] != MINE) {
                int count = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int ni = i + dx;
                        int nj = j + dy;
                        if (ni >= 0 && ni < boardSize && nj >= 0 && nj < boardSize && mineBoard[ni][nj] == MINE) {
                            count++;
                        }
                    }
                }
                mineBoard[i][j] = count + '0';
            }
        }
    }
}

void createGameBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            gameBoard[i][j] = HIDDEN;
        }
    }
}

void printGameBoard() {
    cout << "   ";
    for (int i = 0; i < boardSize; i++) {
        cout << setw(3) << i;
    }
    cout << endl << "  ";
    for (int i = 0; i < boardSize * 3 + 1; i++) {
        cout << "_";
    }
    cout << endl;
    for (int i = 0; i < boardSize; i++) {
        cout << setw(2) << i << "|";
        for (int j = 0; j < boardSize; j++) {
            cout << setw(3) << gameBoard[i][j];
        }
        cout << endl;
    }
}

void openCell(int x, int y) {
    if (gameBoard[x][y] != HIDDEN) {
        return;
    }
    if (mineBoard[x][y] == MINE) {
        gameOver = true;
        gameBoard[x][y] = MINE;
    } else if (mineBoard[x][y] == EMPTY) {
        gameBoard[x][y] = OPEN;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int ni = x + dx;
                int nj = y + dy;
                if (ni >= 0 && ni < boardSize && nj >= 0 && nj < boardSize) {
                    openCell(ni, nj);
                }
            }
        }
    } else {
        gameBoard[x][y] = mineBoard[x][y];
    }
}

void flagCell(int x, int y) {
    if (gameBoard[x][y] == HIDDEN) {
        if (flagsPlaced < numMines) {
            gameBoard[x][y] = FLAG;
            flagsPlaced++;
            if (mineBoard[x][y] == MINE) {
                minesFlagged++;
            }
        }
    } else if (gameBoard[x][y] == FLAG) {
        gameBoard[x][y] = HIDDEN;
        flagsPlaced--;
        if (mineBoard[x][y] == MINE) {
            minesFlagged--;
        }
    }
}

void checkGameStatus() {
    if (minesFlagged == numMines) {
        bool win = true;
        for (int i = 0; i < boardSize && win; i++) {
            for (int j = 0; j < boardSize && win; j++) {
                if (mineBoard[i][j] == MINE && gameBoard[i][j] != FLAG) {
                    win = false;
                }
            }
        }
        if (win) {
            gameOver = true;
            endTime = time(NULL);
        }
    }
}

void printInstructions() {
    cout << "Rules:" << endl;
    cout << "Enter 'o' followed by row and column to open a cell." << endl;
    cout << "Enter 'f' followed by row and column to place or remove a flag." << endl;
}

void welcomeMessage() {
    cout << "Welcome to Minesweeper!" << endl;
}

void victoryMessage() {
    cout << "Congratulations! You win!" << endl;
}

void gameOverMessage() {
    cout << "Game over! You lose!" << endl;
}

void saveGame() {
    ofstream outfile("minesweeper_save.txt");
    if (outfile.is_open()) {
        outfile << boardSize << " " << numMines << endl;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                outfile << gameBoard[i][j];
            }
            outfile << endl;
        }
        outfile.close();
        cout << "Game saved successfully." << endl;
    } else {
        cout << "Unable to save game." << endl;
    }
}

void loadGame() {
    ifstream infile("minesweeper_save.txt");
    if (infile.is_open()) {
        infile >> boardSize >> numMines;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                infile >> gameBoard[i][j];
            }
        }
        infile.close();
        cout << "Game loaded successfully." << endl;
    } else {
        cout << "No saved game found." << endl;
    }
}

void printOptions() {
    cout << "Options:" << endl;
    cout << "1. Save game" << endl;
    cout << "2. Load game" << endl;
    cout << "3. Change difficulty" << endl;
    cout << "4. Quit game" << endl;
    cout << "Enter your choice: ";
}

void playAgain() {
    char choice;
    cout << "Do you want to play again? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        gameOver = false;
        createMinePositions();
        createGameBoard();
        flagsPlaced = 0;
        minesFlagged = 0;
    }
}

void setDifficulty() {
    cout << "Enter board size (4-20): ";
    cin >> boardSize;
    boardSize = max(4, min(boardSize, MAX_BOARD_SIZE));
    cout << "Enter number of mines: ";
    cin >> numMines;
    numMines = max(1, min(numMines, boardSize * boardSize));
}

void playGame() {
    welcomeMessage();
    startTime = time(NULL);
    createMinePositions();
    createGameBoard();
    printInstructions();
    while (!gameOver) {
        cout << endl;
        printGameBoard();
        cout << "Flags placed: " << flagsPlaced << "/" << numMines << endl;
        cout << "Enter action (o/f) followed by row and column: ";
        char action;
        int row, col;
        cin >> action >> row >> col;
        if (action == 'o') {
            openCell(row, col);
        } else if (action == 'f') {
            flagCell(row, col);
        } else {
            cout << "Invalid action! Please enter 'o' or 'f'." << endl;
            continue;
        }
        checkGameStatus();
    }
    printGameBoard();
    if (gameOver) {
        if (endTime == 0) {
            endTime = time(NULL);
        }
        if (minesFlagged == numMines) {
            victoryMessage();
        } else {
            gameOverMessage();
        }
        cout << "Time taken: " << difftime(endTime, startTime) << " seconds" << endl;
        playAgain();
    }
}

int main() {
    bool quit = false;
    while (!quit) {
        printOptions();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                saveGame();
                break;
            case 2:
                loadGame();
                break;
            case 3:
                setDifficulty();
                break;
            case 4:
                quit = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
