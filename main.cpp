#include "Board.h"
#include "GameEngine.h"
#include "GUI.cpp"
#include <iostream>


using namespace std;

int main() {

    int rows = 8;
    int cols = 8;

    Board boardDi = Board::getInstance(rows,cols);
    GameEngine gEngine(boardDi);

    gEngine.startGame();


    return 0;
}
