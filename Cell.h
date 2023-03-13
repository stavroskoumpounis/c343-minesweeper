//
// Created by stv14 on 10/03/2023.
//

#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H


class Cell {
private:
    bool mine;
    bool flag;
    bool open;
    bool visited;
    int number;
public:
    Cell();

    bool isMine() const;
    bool isFlag() const;
    bool isOpen() const;
    int getNumber() const;

    void setMine(bool state);
    void setFlag(bool state);
    void setOpen(bool state);
    void setNumber(int num);

    Cell& operator++();

    bool isVisited() const;

    void setVisited(bool visited);
};

#endif //MINESWEEPER_CELL_H
