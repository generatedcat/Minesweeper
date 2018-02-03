#include "Game.h"
#include <iostream>

using namespace std;
class TooManyMinesException {
public:
	TooManyMinesException() {
		cout << "Cannot put mines more than 2/3 of number of cells" << endl;
	}
};

Game::Game() {
	gameIsOn=false;
}
Game::Game(int myrow, int mycolumn, int mmyminecount){

	gameIsOn=true;
	//проверить не слишком ли много мин попросил пользователь
	if (mmyminecount > myrow*mycolumn * 2 / 3) {
		throw TooManyMinesException();
		gameIsOn = false;
		return;
	}

	//определить класс
	int cellcount = myrow*mycolumn;
	cells = new Cell[cellcount];
	rows = myrow;
	columns = mycolumn;
	minecount = mmyminecount;
	//заполнить пол€ минами и цифрами
	for (int i = 0; i < minecount; i++) {
		int index = rand() % cellcount;
		while (cells[index].value=='@') index = rand() % cellcount; //чтобы не выбрал €чейку, где уже есть мина
		cells[index].value = '@';
	}
	for (int i = 0; i < cellcount; i++) {
		cells[i].cellClosed = true;
		cells[i].flagged = false; //»значально они все закрыты и не отмечены
		if (cells[i].value != '@') {
			int result = 0;//будем увеличивать если р€дом мина
			int rownumber = (int)i / columns;
			int columnnumber = i%columns;
			if (rownumber > 0 && columnnumber > 0) {
				if (cells[i - columns - 1].value == '@') result++;
			}
			if (rownumber > 0) {
				if (cells[i - columns].value == '@') result++;
			}
			if (rownumber > 0 && columnnumber < columns-1) {
				if (cells[i - columns + 1].value == '@') result++;
			}
			if (columnnumber > 0) {
				if (cells[i - 1].value == '@') result++;
			}
			if (columnnumber < columns-1) {
				if (cells[i + 1].value == '@') result++;
			}
			if (rownumber < rows-1 && columnnumber>0) {
				if (cells[i + columns - 1].value == '@') result++;
			}
			if (rownumber < rows-1) {
				if (cells[i + columns].value == '@') result++;
			}
			if (rownumber < rows-1 && columnnumber < columns-1) {
				if (cells[i + columns + 1].value == '@') result++;
			}
			cells[i].value = result + '0';
		}
	}
}
Game::~Game() {
	delete cells;
}
bool Game::getState() {
	return gameIsOn;
}
void Game::setRowCount(int myrow) {
	rows = myrow;
}
int Game::getRowCount() {
	return rows;
}
void Game::setColumnCount(int mycolumn) {
	columns = mycolumn;
}
int Game::getColumnCount() {
	return columns;
}
void Game::setMineCount(int myminecount) {
	minecount = myminecount;
}
int Game::getMinesCount() {
	return minecount;
}
void Game::setOpenCellsCount(int mycount) {
	openCellsCount = mycount;
}
int Game::getOpenCellsCount() {
	return openCellsCount;
}
void Game::Display() {
	int rows = getRowCount();
	int columns = getColumnCount();
	for (int i = 1; i <= rows*columns; i++) {
		if (cells[i - 1].cellClosed) {
			if (cells[i - 1].flagged) cout << 'f';
			else cout << 'x';
		}
		else cout << cells[i-1].value;
		if (i%columns == 0) cout <<endl;
	}
	
}
void Game::Request() {
	char temp;
	cout << "Enter action: o - open cell, f - flag cell, e - exit" << endl;
	cin >> temp;
	while (temp != 'o' && temp != 'f' && temp != 'e') {
		cout << "Enter valid action" << endl;
		cin >> temp;
	}
	if (temp == 'f') {
		cout << "Enter index of row from 1 to " << getRowCount() << endl;
		int enteredRow;
		cin >> enteredRow;
		cout << "Enter index of column from 1 to " << getColumnCount() << endl;
		int enteredColumn;
		cin >> enteredColumn;
		int index = (enteredRow - 1)*getColumnCount() + (enteredColumn - 1);
		cells[index].flagged = true;
	}
	if (temp == 'o') {

		cout << "Enter index of row from 1 to " << getRowCount() << endl;
		int enteredRow;
		cin >> enteredRow;
		cout << "Enter index of column from 1 to " << getColumnCount() << endl;
		int enteredColumn;
		cin >> enteredColumn;
		int index = (enteredRow - 1)*getColumnCount() + (enteredColumn - 1);
		cells[index].cellClosed = false;
		if (cells[index].value == '@') {
			gameIsOn = false;
		}
		else {
			openCellsCount++;
			if (openCellsCount == rows*columns - minecount) {
				cout << "Hurray!!!!!";
				gameIsOn = false;
			}
		}

	}
	if (temp == 'e') {
		gameIsOn = false;
	}
	
}