#include "Game.h"
#include <iostream>

using namespace std;

void main() {
	cout << "Welcome! Enter number of rows, columns and mines" << endl;
	int x, y, z;
	cin >> x >> y >> z;
	Game g = Game(x, y, z);
	while (g.getState()){
		g.Request();
		system("cls");
		g.Display();
	}
	cout << "See you soon" << endl;
	system("pause");
}