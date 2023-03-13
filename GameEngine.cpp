#include "GameEngine.h"

GameEngine::GameEngine(Board &board) : board(board), gameOver(-5) {}

/**
 * Start game and generate mines
 * @param excludedCell
 */
void GameEngine::startGame() {
    board.resetBoard();
    gameOver = 0;
    //get first move and init board
    std::pair<int, int> excludedCell = firstMove();

    std::vector<std::pair<int, int>> mines = generateRandomMines(excludedCell);
    board.initBoard(mines);

    //calc cell nums
    calculateCellNumbers(mines);

//    board.showBoard();
    std::cout << "\n" << std::endl;


    playGame(excludedCell);

}

std::pair<int, int> GameEngine::firstMove() {
    int row, col;
    char choice;
    while (gameOver == 0) {
        board.hiddenBoard();

        std::cout << "Enter row and column (e.g. 3 4) or 'q' to quit: \n";
        std::cin >> choice;
        if (choice == 'q') {
            std::cout << "Thanks for playing!\n";
            exit(0);
        }
        row = choice - '0';
        std::cin >> col;

        std::cout << "You have entered coords (" << row << ", " << col << ")" << std::endl;
        if (!board.isValidCell(row, col)) {
            std::cout << "Invalid cell. Try again.\n";
            continue;
        } else {
            break;
        }
    }
    return std::make_pair(row, col);
}

void GameEngine::playGame(std::pair<int, int> excludedCell) {
    checkCell(excludedCell);
    board.setFirstCell(std::make_pair(excludedCell.first, excludedCell.second));

    int row, col;
    char choice;
    while (gameOver == 0) {
        board.hiddenBoard();

        std::cout << "Enter row and column (e.g. 3 4) or 'q' to quit: \n";
        std::cin >> choice;
        if (choice == 'q') {
            std::cout << "Thanks for playing!\n";
            exit(0);
        }
        row = choice - '0';
        std::cin >> col;

        std::cout << "Enter 'o' to open cell or 'f' to flag cell: \n";
        std::cin >> choice;

        std::cout << "You have entered coords (" << row << ", " << col << ")" << std::endl;
        if (!board.isValidCell(row, col)) {
            std::cout << "Invalid cell. Try again.\n";
            continue;
        }

        if (choice == 'o') {
            // check and open the cell
            checkCell(std::make_pair(row, col));
        } else if (choice == 'f') {
            // flag the cell
            flagCell(row, col);
        } else {
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }
    }
}


/**
 * Gets mines at random evenly distributed in the grid using reservoir sampling
 * @param excludedCell
 * @return
 */
std::vector<std::pair<int, int>> GameEngine::generateRandomMines(std::pair<int, int> excludedCell) {
    std::vector<std::pair<int, int>> mines;
    //preallocate memory with reserve
    mines.reserve(MINES_NUM);

    //init possible coords
    std::vector<std::pair<int, int>> possibleCoords;
    for (int i = 0; i < board.getRows(); ++i) {
        for (int j = 0; j < board.getCols(); ++j) {
            if (std::make_pair(i, j) != excludedCell) {
                possibleCoords.emplace_back(i, j);
            }
        }
    }
    //shuffle coords 1 to 3 times
    int rep = random_util::randInt(1, 3);
    for (int i = 0; i < rep; ++i) {
        std::shuffle(possibleCoords.begin(), possibleCoords.end(), random_util::gen);
    }
    //take first X coords for Mines
    for (int i = 0; i < MINES_NUM; ++i) {
        mines.push_back(possibleCoords.at(i));
    }
    return mines;
}

void GameEngine::checkCell(std::pair<int, int> clickCoords) {

//        std::cout << "You have coords (" << clickCoords.first << ", " << clickCoords.second << ") inside open func" << std::endl;

    Cell &clickedCell = board.getCell(clickCoords.first, clickCoords.second);

    if (gameOver == 0 || !clickedCell.isFlag()) {

        if (clickedCell.isMine()) {
            clickedCell.setOpen(true);
            explode();
            // -1 is game loss
            gameOver = -1;
            //end game
        } else {
            openCellBoard(clickCoords.first, clickCoords.second);
            board.showBoard();

            if (board.getRows() * board.getCols() - board.getOpenedCells() == MINES_NUM) {
                clickedCell.setOpen(true);
                gameOver = 1;
                //player wins function
                std::cout << "Player Wins!" << std::endl;
            }
        }
    }

}

void GameEngine::flagCell(int row, int col) {
    Cell &cell = board.getCell(row, col);
    if (cell.isOpen()) {
        std::cout << "You can't flag an open cell." << std::endl;
        return;
    }
    cell.setFlag(!cell.isFlag());
    std::cout << cell.isFlag() << std::endl;
    board.showBoard(); // update the board display
}


void GameEngine::calculateCellNumbers(const std::vector<std::pair<int, int>> &mines) {
    for (auto &mine: mines) {

        int row = mine.first;
        int col = mine.second;
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = col - 1; j <= col + 1; ++j) {
                if (board.isValidCell(i, j) && !(i == row && j == col) && !board.getCell(i, j).isMine()) {
                    //overloaded operator ++ to increment number
                    ++board.getCell(i, j);
                }
            }
        }
    }

}

void GameEngine::openCellBoard(int row, int col) {
    Cell &cell = board.getCell(row, col);
    cell.setVisited(true);

    // base case: if current cell already opened or a mine, return
    if (cell.isOpen() || cell.isMine()) {
        return;
    }

    // open current cell
    cell.setOpen(true);
    board.incrementOpenedCells();

    // if current cell has a number, no need to check neighbors
    if (cell.getNumber() != 0) return;

    // recursively open all adjacent empty cells
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (!board.isValidCell(i, j) || (i == row && j == col) || board.getCell(i, j).isVisited()) continue;
            board.hiddenBoard();
            openCellBoard(i, j);
        }
    }
}

void GameEngine::explode() {
    board.hiddenBoard();
    std::cout << "\033[31m" << "Game Over" << "\033[0m\n";
}





