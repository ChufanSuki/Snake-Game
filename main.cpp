#include <iostream>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <curses.h>

using namespace std;
bool gameOver = false;
const int width = 20;
const int height = 20;
int x, y, preX, preY;
int fruitX, fruitY;
int tailX[100], tailY[100], preTailX[100], preTailY[100];
int score;
int tailNum;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Input()
{
    while (1)
    {
        switch (getch())
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'q':
            gameOver = true;
            break;
        }
    }
}

void Draw()
{
    system("clear");
    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < tailNum; k++)
            {
                if (tailX[k] == i && tailY[k] == j)
                    cout << "o";
                else
                    cout << " ";
            }
            if (i == fruitX && j == fruitY)
                cout << "$";
            else if (j == 0 || j == width - 1)
                cout << "#";
            else if (i == x && j == y)
                cout << "O";
            else
                cout << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++)
        cout << "#" << endl;
    cout << score << endl;
}

void Logic()
{
    preX = x;
    preY = y;
    for (int i = 0; i < tailNum; i++)
    {
        preTailX[i] = tailX[i];
        preTailY[i] = tailY[i];
    }
    while (1)
    {
        switch (dir)
        {
        case STOP:
            break;
        case UP:
            y--;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
        }
        if (x == fruitX && y == fruitY)
        {
            tailNum++;
            tailX[tailNum - 2] = tailX[tailNum - 3];
            tailY[tailNum - 2] = tailY[tailNum - 3] + 1;
            //Overlapping??
            score++;
        }
        if (x < 0 || x > width || y < 0 || y > height)
            gameOver = true;
        tailX[0] = preX;
        tailY[0] = preY;
        for (int i = 1; i < tailNum; i++)
        {
            tailX[i] = preTailX[i - 1];
            tailY[i] = preTailY[i - 1];
        }
    }
}

int main()
{
    Setup();
    // while (!gameOver)
    // {
    //     Draw();
    //     Input();
    //     Logic();
    // }
    Draw();
    Input();
    Logic();
    if (gameOver)
        cout << "GAME OVER!";

    return 0;
}
