#include <iostream>  
#include <pch.h>
#include <conio.h>  
#include <windows.h>  
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

void Setup() {
    gameOver = false;  //  Если gameOver будет правдой то игра закончится
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;  // Фруктик который змейка может собирать она появляется в рандомном месте
    fruitY = rand() % height; // Фруктик который змейка может собирать она появляется в рандомном месте
    score = 0;
}

void Draw() {
    system("cls"); // Очистка екрана 
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << "\n";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O"; // Змейка  
            else if (i == fruitY && j == fruitX)
                cout << "+"; // Еда
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Хвостик 
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << "\n";
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << "\n";
    cout << "Score: " << score << "\n";
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 72: // стрелка вверх  
            y--;
            break;
        case 80: // стрелка вниз  
            y++;
            break;
        case 75: // стрелка влево  
            x--;
            break;
        case 77: // стрелка вправо  
            x++;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // вышла ли змея за грани?  
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // ударилась ли змея об хвостик?
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // сьёла ли змейка еду?  
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(13); // замедлеение игры  
    }
    return 0;
}