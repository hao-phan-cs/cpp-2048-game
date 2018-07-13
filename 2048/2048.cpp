#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <conio.h>

using namespace std;

class Map {

private:
	vector<vector<int>> map;

public:

	int size;
	Map(int size) {
	
		this->size = size;
		resetMap();
	}

	void resetMap() {
	
		//map.resize(size);
		for (int i = 0; i < size; i++) {
			
			vector<int> row;
			for (int j = 0; j < size; j++) {

				row.push_back(0);
			}
			map.push_back(row);
		}
	}

	void setValue(int y, int x, int val) {
	
		map[y][x] = val;
	}

	int getValue(int y, int x) {
	
		return map.at(y).at(x);
	}

	void RandomSpawn() {
	
		int i = rand() % size;
		int j = rand() % size;

		while (getValue(i, j) != 0) {
		
			i = rand() % size;
			j = rand() % size;
		}
		int k = rand() % 100 + 1;
		if (k > 20) {
			
			setValue(i, j, 2);
		}
		else {
		
			setValue(i, j, 4);
		}
	}

	int moveLeft() {

		int addingScore = 0;
		
		for (int i = 0; i < size; i++) {
		
			for (int j = 0; j < size; j++) {
			
				if (getValue(i, j) > 0) {

					int x = j;
					while (x >= 1) {

						if (getValue(i, x - 1) == 0) {

							setValue(i, x - 1, getValue(i, x));
							setValue(i, x, 0);
						} 
						else if (getValue(i, x - 1) == getValue(i, x)) {
						
							int new_value = getValue(i, x) * 2;
							setValue(i, x - 1, new_value);
							setValue(i, x, 0);
							addingScore += new_value;
							break;
						}
						x--;
					}
				}
			}
		}
		return addingScore;
	}

	int moveRight() {

		int addingScore = 0;

		for (int i = 0; i < size; i++) {

			for (int j = size - 1; j >= 0; j--) {

				if (getValue(i, j) > 0) {

					int x = j;
					while (x < size - 1) {

						if (getValue(i, x + 1) == 0) {

							setValue(i, x + 1, getValue(i, x));
							setValue(i, x, 0);
						}
						else if (getValue(i, x + 1) == getValue(i, x)) {

							int new_value = getValue(i, x) * 2;
							setValue(i, x + 1, new_value);
							setValue(i, x, 0);
							addingScore += new_value;
							break;
						}
						x++;
					}
				}
			}
		}
		return addingScore;
	}

	int moveUp() {

		int addingScore = 0;
	
		for (int j = 0; j < size; j++) {

			for (int i = 0; i < size; i++) {

				if (getValue(i, j) > 0) {

					int y = i;
					while (y > 0) {

						if (getValue(y - 1, j) == 0) {

							setValue(y - 1, j, getValue(y, j));
							setValue(y, j, 0);
						}
						else if (getValue(y - 1, j) == getValue(y, j)) {

							int new_value = getValue(y, j) * 2;
							setValue(y - 1, j, new_value);
							setValue(y, j, 0);
							addingScore += new_value;
							break;
						}
						y--;
					}
				}
			}
		}
		return addingScore;
	}
	
	int moveDown() {
	
		int addingScore = 0;

		for (int j = 0; j < size; j++) {

			for (int i = size - 2; i >= 0; i--) {

				if (getValue(i, j) > 0) {

					int y = i;
					while (y < size - 1) {

						if (getValue(y + 1, j) == 0) {

							setValue(y + 1, j, getValue(y, j));
							setValue(y, j, 0);
						}
						else if (getValue(y + 1, j) == getValue(y, j)) {

							int new_value = getValue(y, j) * 2;
							setValue(y + 1, j, new_value);
							setValue(y, j, 0);
							addingScore += new_value;
							break;
						}
						y++;
					}
				}
			}
		}
		return addingScore;
	}

	bool operator != (Map &otherMap) {
	
		if (this->size != otherMap.size) return true;
		
		for (int i = 0; i < this->size; i++) {
		
			for (int j = 0; j < this->size; j++) {
			
				if (this->getValue(i, j) != otherMap.getValue(i, j)) {
				
					return true;
				}
			}
		}
		return false;
	}

	void print() {
	
		for (int i = 0; i < size; i++) {
		
			for (int j = 0; j < size; j++) {
			
				cout << getValue(i, j);
			}
			cout << endl;
		}
	}
};

void goto_yx(int y, int x)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void textcolor(int color_code) {

	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, color_code);
}

class Drawer {


public:

	int getThingColor(char c) {
	
		if (c == '/' || c == '\\')
			return 11;
		else if (c == '|')
			return 14;
		else if (c == '-')
			return 10;
		else
			return 15;
	}

	char mapThing(int y, int x, int max_y, int max_x) {
	
		if (y == 0 && x == 0) {
		
			return '/';
		} 
		else if (y == 0 && x == max_x - 1) {

			return '\\';
		}
		else if (y == max_y - 1 && x == 0) {
		
			return '\\';
		}
		else if (y == max_y - 1 && x == max_x - 1) {
			
			return '/';
		}
		else if (x % 7 == 0) {
			
			return '|';
		}
		else if (y % 2 == 0) {
		
			return '-';
		}
		else {
		
			return ' ';
		}
	}

	int getValColor(int val = 4096) {
		
		int key = log(val) / log(2);
		
		switch (key) {

		case 1:
			return 15;

		case 2:
			return 14;

		case 3:
			return 14;

		case 4:
			return 14;

		case 5:
			return 13;

		case 6:
			return 13;

		case 7: 
			return 13;
		
		case 8:
			return 12;

		case 9:
			return 12;

		case 10:
			return 10;

		case 11:
			return 10;
		}
		return 0;
	}

	void printScore(int score, int size) {

		string sc_str = to_string(score);
		textcolor(11);
		goto_yx(size * 2 + 3, 0);
		cout << "Score: " << score;
		textcolor(0);
	}

	void Draw(Map map) {
	
		goto_yx(1, 0);

		int max_y = map.size * 2 + 1;
		int max_x = map.size * 6 + map.size + 1;

		for (int i = 0; i < max_y; i++) {
		
			for (int j = 0; j < max_x; j++) {
			
				char m = mapThing(i, j, max_y, max_x);
				textcolor(getThingColor(m));
				cout << m;
			}
			cout << endl;
		}

		for (int i = 0; i < map.size; i++) {
		
			for (int j = 0; j < map.size; j++) {
			
				int val = map.getValue(i, j);
				string val_str = to_string(val);
				if (val_str == "0") val_str = " ";

				if (val_str.length() < 4) {
				
					int l = val_str.length();
					for (int k = 0; k < 4 - l; k++) {
						val_str = " " + val_str;	
					}
				}
				textcolor(getValColor(val));
				goto_yx(i * 2 + 1 + 1, j * 7 + 1 + 1);
				cout << val_str;
			}
		}
		textcolor(7);
	}
};

class GameManager {

private:
	Map *map;
	Drawer drawer;

public:
	int score = 0;
	int size;
	int currentMax = 0;
	bool isGameOver = false;
	bool hasWon = false;
	bool exit = false;

	GameManager(int size) {
	
		this->size = size;
	}

	void Init() {
	
		system("cls");
		score = 0;
		currentMax = 0;
		isGameOver = false;
		map = new Map(size);

		map->RandomSpawn();
		map->RandomSpawn();

		/*map->setValue(0, 0, 4);
		map->setValue(1, 0, 32);
		map->setValue(2, 0, 8);
		map->setValue(3, 0, 2);

		map->setValue(0, 1, 16);
		map->setValue(1, 1, 4);
		map->setValue(2, 1, 32);
		map->setValue(3, 1, 4);

		map->setValue(0, 2, 8);
		map->setValue(1, 2, 64);
		map->setValue(2, 2, 4);
		map->setValue(3, 2, 8);
		
		map->setValue(0, 3, 4);
		map->setValue(1, 3, 2);
		map->setValue(2, 3, 2);
		map->setValue(3, 3, 2);*/
	}

	void getAction() {
		
		while (true) {
		
			bool pressed = false;

			if (GetAsyncKeyState(VK_LEFT) & 0x8000 != 0) {
				score += map->moveLeft();
				pressed = true;
			}
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 != 0) {
				score += map->moveRight();
				pressed = true;
			}
			else if (GetAsyncKeyState(VK_UP) & 0x8000 != 0) {
				score += map->moveUp();
				pressed = true;
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000 != 0) {
				score += map->moveDown();
				pressed = true;
			}
			else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 != 0) {
				exit = true;
				pressed = true;
			}
			
			if (pressed) {

				drawer.printScore(score, size);
				map->RandomSpawn();
				break;
			}
		}
	}
	
	bool checkGo(int y, int x) {
	
		for (int i = y - 1; i <= y + 1; i++) {
		
			for (int j = x - 1; j <= x + 1; j++) {
			
				if (i >= 0 && i < size && j >= 0 && j < size) {
				
				if ((i == y - 1 && x == j) || (i == y + 1 && x == j) || (i == y && x == j - 1) || (i == y && x == j + 1)) {
					
						if (map->getValue(i, j) == 0 || map->getValue(i, j) == map->getValue(y, x)) {
						
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	void checkWon() {
	
		for (int i = 0; i < size; i++) {
		
			for (int j = 0; j < size; j++) {
			
				int val;
				val = map->getValue(i, j);
				if (val > currentMax) {
				
					currentMax = val;
					if (currentMax == 2048) {
					
						hasWon = true;
					}
				}
			}
		}
	}

	void checkGameOver() {
	
		bool differ = false;

		Map expMap = *map;
		expMap.moveLeft();
		if (*map != expMap) {
			differ = true;
		}

		if (!differ) {

			expMap = *map;
			expMap.moveRight();
			if (*map != expMap) {
				differ = true;
			}
		}

		if (!differ) {

			expMap = *map;
			expMap.moveUp();
			if (*map != expMap) {
				differ = true;
			}
		}

		if (!differ) {

			expMap = *map;
			expMap.moveDown();
			if (*map != expMap) {
				differ = true;
			}
		}

		if (differ == false) {
		
			isGameOver = true;
		}
	}

	void Play() {

	play:
		Init();
		while (true) {

			drawer.Draw(*map);
			drawer.printScore(score, size);
			checkWon();
			checkGameOver();

			if (hasWon || isGameOver) {

				goto_yx(size * 2 + 4, 0);
				if (hasWon) {
					textcolor(10);
					cout << "You got 2048! Do you want to restart? (y/n): ";
				}
				else {
					textcolor(12);
					cout << "You lost! Do you want to restart? (y/n): ";
				}
				char c;
				cin >> c;
				if (c == 'y') {
					goto play;
				}
				else {
					exit = true;
					break;
				}
			}
			getAction();
			if (exit) goto out;
		}
	out: {
		textcolor(7);
		goto_yx(0, 0);
		system("cls");
		}
	}
};

int main(int argc, char* argv[]) {

	system("cls");
	int size;
	if (argc <= 1) {
		size = 4;
	}
	else {
		size = atoi(argv[1]);
	}

	GameManager gameManager(size);
	gameManager.Play();
}