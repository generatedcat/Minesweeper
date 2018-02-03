#pragma once
#include "Cell.h"

using namespace std;
class Game {
private:
	bool gameIsOn;
	int rows, columns, minecount;
	Cell *cells;
	int openCellsCount;
public:
	Game();
	Game(int rows, int columns, int minecount);
	~Game();
	bool getState();
	void setRowCount(int rows);
	int getRowCount();
	void setColumnCount(int columns);
	int getColumnCount();
	void setMineCount(int minecount);
	int getMinesCount();
	void setOpenCellsCount(int openCellsCount);
	int getOpenCellsCount();

	void Display();
	void Request();

};