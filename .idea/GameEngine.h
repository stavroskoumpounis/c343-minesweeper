#include "Board.h"

class GameEngine {
private:
    Board& board;
    int gameOver;
    const int MINES_NUM = 10;

public:
    explicit GameEngine(Board& board);

    void startGame();

    void playGame(std::pair<int, int> excludedCell);

    std::vector<std::pair<int, int>> generateRandomMines(std::pair<int, int> excludedCell);

    void explode();

    void checkCell(std::pair<int, int> clickCoords);

    void calculateCellNumbers(const std::vector<std::pair<int, int>>& mines);

    void openCellBoard(int row, int col);

    void flagCell(int row, int col);

    std::pair<int, int> firstMove();

    void placeMines();
};