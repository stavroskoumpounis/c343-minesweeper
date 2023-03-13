#include "Cell.h"

Cell::Cell() : mine(false), flag(false), open(false), visited(false), number(0) {}

bool Cell::isMine() const {
    return mine;
}

bool Cell::isFlag() const {
    return flag;
}

bool Cell::isOpen() const {
    return open;
}

int Cell::getNumber() const {
    return number;
}

void Cell::setMine(bool state) {
    mine = state;
}

void Cell::setFlag(bool state) {
    flag = state;
}

void Cell::setOpen(bool state) {
    open = state;
}

void Cell::setNumber(int num) {
    number = num;
}

Cell& Cell::operator++() {
    number++;
    return *this;
}

bool Cell::isVisited() const {
    return visited;
}

void Cell::setVisited(bool visited) {
    Cell::visited = visited;
}
