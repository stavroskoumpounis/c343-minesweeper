#include "Board.h"
#include "Cell.h"
#include <utility>
#include <algorithm>
#include <iostream>
#include <string>
#include "windows.h"

Board::Board(int rowsNum, int colsNum) : ROWS(rowsNum), COLS(colsNum) {

    //memory allocation for the grid
    grid = new Cell *[ROWS];
    for (int i = 0; i < ROWS; i++) {
        grid[i] = new Cell[COLS];
    }

    //initializing with empty cells
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = Cell();
        }
    }

    openedCells = 0;
}

Board::~Board() {
    for (int i = 0; i < ROWS; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

Cell &Board::getCell(int row, int col) const {
    return grid[row][col];
}

void Board::showBoard() {
    //shows the board
    std::system(("chcp " + std::to_string(CP_UTF8) + " >nul").c_str());

    std::cout << "   ";
    for (int j = 0; j < COLS; j++) {
        std::cout << j << "  ";
    }
    std::cout << std::endl;
    for (int i = 0; i < ROWS; i++) {
        std::cout << i << " ";
        for (int j = 0; j < COLS; j++) {
            Cell &cell = getCell(i, j);
            int num = cell.getNumber();

            if (cell.isMine()) {
                std::cout << "\033[1;37;41m M \033[0m";
            } else if (num == 0) {
                if(cell.isOpen()){
                    std::cout << "\033[1;37;47m o \033[0m";
                } else {
                    std::cout << "\033[1;30;47m . \033[0m";
                }
            } else if (num != -1) {
                std::cout << "\033[1;37;43m " << num << " \033[0m";
            } else if (cell.isFlag()) {
                std::cout << "\033[1;37;42m F \033[0m";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "\n\n" << std::endl;
}

void Board::hiddenBoard() {
    int x = firstCell.first;
    int y = firstCell.second;

    std::system(("chcp " + std::to_string(CP_UTF8) + " >nul").c_str());

    std::cout << "   ";
    for (int j = 0; j < COLS; j++) {
        std::cout << j << "  ";
    }
    std::cout << std::endl;
    for (int i = 0; i < ROWS; i++) {
        std::cout << i << " ";
        for (int j = 0; j < COLS; j++) {
            Cell &cell = getCell(i, j);
            int num = cell.getNumber();

            if (cell.isFlag()) {
                std::cout << "\033[1;37;42m F \033[0m";
            } else if (cell.isMine()) {
                if(cell.isOpen()){
                    std::cout << "\033[1;37;41m M \033[0m";
                }
                std::cout << "\033[1;30;47m . \033[0m";

            } else if (cell.isOpen()) {
                if(i == x && j == y) {
                    std::cout << "\033[1;30;42m";
                    if (num == 0) {
                        std::cout << " X \033[0m";
                    } else if (num > 0) {
                        std::cout << " " << num << " \033[0m";
                    }
                } else {
                    if (num == 0) {
                        std::cout << "\033[1;37;47m o \033[0m";
                    } else if (num > 0) {
                        std::cout << "\033[1;37;43m " << num << " \033[0m";
                    }
                }
            }  else {
                std::cout << "\033[1;30;47m . \033[0m";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "\n\n" << std::endl;
}

void Board::initBoard(const std::vector<std::pair<int, int>> &mines) {
    //update board with mines (-1 for mines)
    int count = 0;
    for (auto &cord: mines) {
        std::cout << "Mine " << ++count << ": (" << cord.first << ", " << cord.second << ")\t";
        grid[cord.first][cord.second].setMine(true);
        grid[cord.first][cord.second].setNumber(-1);
    }

    std::cout << std::endl;
}

Board &Board::getInstance(int rowsNum, int colsNum) {
    static Board instance(rowsNum, colsNum);
    return instance;
}

int Board::getRows() const {
    return ROWS;
}

int Board::getCols() const {
    return COLS;
}

bool Board::isValidCell(int i, int j) {
    return (i >= 0 && i < ROWS && j >= 0 && j < COLS);
}

void Board::incrementOpenedCells() {
    Board::openedCells++;
}

int Board::getOpenedCells() const {
    return openedCells;
}

void Board::resetBoard() {
    // initialize the grid with empty cells
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = Cell();
        }
    }
}

const std::pair<int, int> &Board::getFirstCell() const {
    return firstCell;
}

void Board::setFirstCell(const std::pair<int, int> &firstCell) {
    Board::firstCell = firstCell;
}




