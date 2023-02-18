void gotoXY(int x, int y);
void drawBoard();
void resetGame();
void fixConsoleWindow();
void startNewGame();
void playGame(bool isFirstPlayerTurn, int**& board);
bool isValidPosition(int x, int y, int i, int j, int**& board);