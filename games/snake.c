#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

int height = 20, width = 20, x, y, fruitx, fruity, flag, gameend, score;
int tailx[100], taily[100], piece = 0;

void makelogic() {
    int i;
    int prevx, prevy, prev2x, prev2y;
    prevx = tailx[0];
    prevy = taily[0];
    tailx[0] = x;
    taily[0] = y;
    for (i = 1; i <= piece; i++) {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (flag) {
        case 1:
            x--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y--;
            break;
        case 4:
            y++;
            break;
    }
    if (x <= 0 || x >= height || y <= 0 || y >= width) {
        gameend = 1;
    }
    if (x == fruitx && y == fruity) {
        fruitx = rand() % 20;
        fruity = rand() % 20;
        score += 10;
        piece++;
    }
}

void input() {
    if (kbhit()) {
        switch (getch()) {
            case 'w':
                flag = 1;
                break;
            case 's':
                flag = 2;
                break;
            case 'a':
                flag = 3;
                break;
            case 'd':
                flag = 4;
                break;
        }
    }
}

void setup() {
    x = height / 2;
    y = width / 2;
    fruitx = rand() % 20;
    fruity = rand() % 20;
    gameend = 0;
    score = 0;
    piece++;
}

void draw() {
    system("cls");
    int i, j, k, ch;
    for (i = 0; i <= height; i++) {
        for (j = 0; j <= width; j++) {
            if (i == 0 || i == height || j == 0 || j == width) {
                printf("*");
            } else {
                if (i == x && j == y) {
                    printf("0");
                } else if (i == fruitx && j == fruity) {
                    printf("@");
                } else {
                    ch = 0;
                    for (k = 0; k < piece; k++) {
                        if (i == tailx[k] && j == taily[k]) {
                            printf("0");
                            ch = 1;
                        }
                    }
                    if (ch == 0)
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("your score is \t %d", score);
}

int main() {
    setup();
    while (!gameend) {
        input();
        draw();
        makelogic();
        // Introducing  a delay here
        usleep(1000); // 1000 milliseconds
    }
    return 0;
}

         








