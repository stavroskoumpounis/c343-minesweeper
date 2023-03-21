//
// Created by stv14 on 10/03/2023.
//

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include "Cell.h"
#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include "random_util.h"

class Board {
private:
    const int ROWS;
    const int COLS;
    int openedCells;
//    const int MINES_NUM = 10;
    Cell **grid;

    std::pair<int,int> firstCell;

    Board(int rowsNum, int colsNum);

public:
    static Board &getInstance(int rowsNum, int colsNum);

    ~Board();

    void setCell(int row, int col, const Cell &cell);

    Cell &getCell(int row, int col) const;

    void showBoard();

    void resetBoard();

    void initBoard(const std::vector<std::pair<int, int>>& mines);

    int getRows() const;

    int getCols() const;

    bool isValidCell(int i, int j);

    int getOpenedCells() const;

    void incrementOpenedCells();

    void hiddenBoard();

    const std::pair<int, int> &getFirstCell() const;

    void setFirstCell(const std::pair<int, int> &firstCell);
};



#endif //MINESWEEPER_BOARD_H
