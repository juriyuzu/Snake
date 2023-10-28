#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

string bit = "  ";
int size[2] = {22, 50};
string map[22] = {
	"==================================================",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=            +                                   =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"=                                                =",
	"==================================================",
};

struct Snake {
	int coords[3] = {1, 2, 0};
	int length = 3;
	int trail[22][50];
	
	Snake(int y, int x) {
		coords[0] = y;
		coords[1] = x;
		
		for (int i = 0; i < 22; i++) {
			for (int j = 0; j < 50; j++) {
				trail[i][j] = 0;
			}
		}
	}
};

int rng(int min, int max) {
	return min + (rand() % max + 1);
}

void food() {
	int x, y;
	do {
		x = rng(1, 20);
		y = rng(1, 48);
	}
	while (map[x][y] != ' ');
	map[x][y] = '+';
}

void display(vector<Snake> snake) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int count = 0;
	bool end = false;
	bool foodFlag = true;
	while (true) {
		system("cls");
		cout << count++ << endl;
		for (int i = 0; i < size[0]; i++) {
			for (int j = 0; j < size[1]; j++) {
				if (map[i][j] == '+') {
					SetConsoleTextAttribute(hConsole, 45);
					cout << bit;
					SetConsoleTextAttribute(hConsole, 15);
				}
				bool flag = true;
				for (int k = 0; k < snake.size(); k++) {
					if (i == snake[k].coords[0] && j == snake[k].coords[1]) {
						SetConsoleTextAttribute(hConsole, 255);
						cout << bit;
						SetConsoleTextAttribute(hConsole, 15);
						flag = false;
					}
				}
				if (flag) {
					for (int k = 0; k < snake.size(); k++) {
						if (snake[k].trail[i][j] > 0) {
							if (foodFlag) {
								snake[k].trail[i][j]--;
								if (snake[k].trail[i][j] == 0) map[i][j] = ' ';
								SetConsoleTextAttribute(hConsole, 255);
								cout << bit;
								SetConsoleTextAttribute(hConsole, 15);
							}
							else foodFlag = true;
						}
						else cout << bit;
					}
				}
			}
			cout << endl;
		}
		for (int key = 0; key < 256; key++) {
            if (GetAsyncKeyState(key) & 0x8000) {
				std::cout << "Key pressed: " << key << std::endl;
	            switch (key) {
	            	case 81:
	            		snake[0].coords[2] = (snake[0].coords[2] == 3) ? 0 : snake[0].coords[2] + 1;
	            		break;
	            	case 87:
						snake[0].coords[2] = (snake[0].coords[2] == 0) ? 3 : snake[0].coords[2] - 1;
	            		break;
	            	case 37:
	            		snake[1].coords[2] = (snake[1].coords[2] == 3) ? 0 : snake[1].coords[2] + 1;
	            		break;
	            	case 39:
						snake[1].coords[2] = (snake[1].coords[2] == 0) ? 3 : snake[1].coords[2] - 1;
	            		break;
				}
            }
        }
        for (int i = 0; i < snake.size(); i++) {
	        snake[i].trail[snake[i].coords[0]][snake[i].coords[1]] = snake[i].length;
	        map[snake[i].coords[0]][snake[i].coords[1]] = '*';
        	switch (snake[i].coords[2]) {
	        	case 0:
					snake[i].coords[0]--;
		            if (map[snake[i].coords[0]][snake[i].coords[1]] == '=') snake[i].coords[0] = size[0] - 2;
	        		break;
	        	case 1:
	        		snake[i].coords[1]--;
		            if (map[snake[i].coords[0]][snake[i].coords[1]] == '=') snake[i].coords[1] = size[1] - 2;
	        		break;
	        	case 2:
	        		snake[i].coords[0]++;
	        		if (map[snake[i].coords[0]][snake[i].coords[1]] == '=') snake[i].coords[0] = 1;
	        		break;
	        	case 3:
	        		snake[i].coords[1]++;
	        		if (map[snake[i].coords[0]][snake[i].coords[1]] == '=') snake[i].coords[1] = 1;
	        		break;
			}
	        cout << "\n[Q] to move left, [W] to move right"
				 << "\nx coords: " << snake[i].coords[0] 
				 << "\ny coords: " << snake[i].coords[1] 
				 << "\n  length: " << snake[i].length;
			if (map[snake[i].coords[0]][snake[i].coords[1]] == '*') end = true;
			if (map[snake[i].coords[0]][snake[i].coords[1]] == '+') {
				map[snake[i].coords[0]][snake[i].coords[1]] = ' ';
				snake[i].length++;
				foodFlag = false;
				food();
			}
		}
		if (end) break;
//		Sleep(1);
	}
	cout << "gameover";
	system("pause");
}

void snake() {
	vector<Snake> snake;
	Snake aaa(1, 2), bbb(1, 5);
	snake.push_back(aaa);
//	snake.push_back(bbb);
	display(snake);
}

int main() {
	snake();
//    int i = 0;
//    while (true) {
//    	SetConsoleTextAttribute(hConsole, i);
//    	printf("  ");
//    	Sleep(10);
//    	i += 16;
//    	if (i > 255) i = 0;
//	}

//    int ch;
//    while (true) {
//        for (int key = 0; key < 256; key++) {
//            if (GetAsyncKeyState(key) & 0x8000) {
//                // Key with code 'key' is pressed
//                system("cls");
//				std::cout << "Key pressed: " << key << std::endl;
//
//                // Exit the loop if the ESC key is pressed
//                if (key == VK_ESCAPE) {
//                    return 0;
//                }
//            }
//        }
//    }
	return 0;
}
