#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <windows.h>
using namespace std;

#define CHECK(i1, j1, i2, j2, i3, j3) \
    if (s->board[i1][j1] != -1 && s->board[i1][j1] == s->board[i2][j2] && s->board[i1][j1] == s->board[i3][j3]) \
        return (s->board[i1][j1] == 0) ? 1 : -1;    //if O take the position, return 1 , O win, else X win and return -1

typedef struct
{
    int board[3][3];   // -1=empty  0=O   1=X
    int turn;
}state;

void init(state* s)
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            s->board[i][j] = -1;
    s->turn = 0;
}

void RED_Print(const char* s)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
    printf(s);
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);   //改回白色
}

void display(const state* s)
{
    system("cls");
   
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            switch (s->board[i][j])
            {
            case -1: printf(" %d ", i * 3 + j + 1); break;
            case 0: RED_Print(" O ") ;  break;
            case 1: RED_Print(" X ") ;  break;
            }
            if (j < 2) putchar('|');
            else putchar('\n');
        }
        if (i < 2) printf("---+---+---\n");
        else putchar('\n');

    }
}

int judge(const state* s)
{
    for (int i = 0; i < 3; i++)
    {
        CHECK(i, 0, i, 1, i, 2);
        CHECK(0,i,1,i,2,i);
    }
    CHECK(0, 0, 1, 1, 2, 2);
    CHECK(0, 2, 1, 1, 2, 0);
    return 0;
}

int move(state* s, int i, int j)
{
    if (s->board[i][j] != -1) return 0;
    s->board[i][j] = s->turn++ % 2;
    return 1;
}

void player(state* s)
{
    char c;
    do {
        printf("%c:", "OX"[s->turn % 2]);
        cin >> c;
        getchar();
    } while (c < '1' || c > '9' || !move(s, (c - '1') / 3, (c - '1') % 3));
}

int main()
{
    state s;
    init(&s);
    display(&s);
    int flag = 0;
    while (s.turn < 9 && !flag) //0-8
    {
        player(&s);
        display(&s);
        switch(judge(&s))
        {
            case 1:printf("O获胜!"); flag = 1; break;
            case -1:printf("X获胜!"); flag = 1; break;
        }
    }
    if(!flag) printf("平局!");
    getchar();
    return 0;
}