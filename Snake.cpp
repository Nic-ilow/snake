#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = width / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw() {
	system("cls");
	// Here we draw the top wall
	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;

	// Here we draw what is on each line

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {
			// If we are on the far left draw a wall
			if (j == 0) {
				cout << "#";
			}
			// If we are on the far right draw a wall
			else if (j == width - 1) {
				cout << "#";
			}		
			// If our head is at the current position draw O	
			else if (i == y && j == x) {
				cout << "O";
			}
			// If the fruit is at the current position draw F
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}

			else {
				bool print = false;
                // Loop over the list containing tail position
				for (int k = 0; k < nTail; k++) {
					// If the tail is at the current position draw o
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						// Update print to true so we know not to print an extra empty space
						print = true;
					}
				}
				// If we didn't print anything print an empty space
				if (!print) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	// Here we draw the bottom wall
	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input() {

	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic() {
	// Initialize previous x and y to the first tail position
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	// Update the first tail position to be the current head position (before moving the head)
	tailX[0] = x;
	tailY[0] = y;
	// Loop over the tail positions
	for (int i = 1; i < nTail; i++) {
		// Set the position of the tail one position back from where we're investigating to memory	
		prev2X = tailX[i];
		prev2Y = tailY[i];
		// Update the position of the tail to the previous position
		tailX[i] = prevX;
		tailY[i] = prevY;
		// Update the previous position to the previous2 position
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	// If the head touches a wall the game is over
	if (x >= width || x < 0 || y >= height || y < 0) {
		gameOver = true;
	}
	// If the head touches a part of the tail the game is over
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
	// If the head touches fruit, gain points, generate a new fruit, increase tail length, and spawn a new fruite at a new location not within the snake
	if (x == fruitX && y == fruitY) {
		score += 10;
				
		fruitX = rand() % width;
		fruitY = rand() % height;
		while (x == fruitX && y == fruitY) {
			fruitX = rand() % width;
			fruitY = rand() % height;
		}
		nTail++;
	}

}
int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(100);
		// Sleep is needed because my processor is too fast
	}
	cout << "Game Over! " << endl;
	cout << "Your Score is: " << score << endl;
}