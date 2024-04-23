#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

// Define colors
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RED "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RESET "\x1b[0m"

int height = 20, width = 20, x, y, fruitx, fruity, flag, gameend, score;
int tailx[100], taily[100], piece = 0;

// Function to save score to file
void saveScore(char *username, int score) {
    FILE *file = fopen("scores_snake", "a");
    if (file != NULL) {
        fprintf(file, "%s %d\n", username, score);
        fclose(file);
    }
}

// Function to update score if username exists, or save if new user
void updateOrSaveScore(char *username, int score) {
    FILE *file = fopen("scores_snake", "r+");
    if (file != NULL) {
        char name[100];
        int oldScore;
        while (fscanf(file, "%s %d", name, &oldScore) != EOF) {
            if (strcmp(username, name) == 0) {
                if (score > oldScore) {
                    fseek(file, -strlen(name) - 2, SEEK_CUR);
                    fprintf(file, "%s %d\n", username, score);
                }
                fclose(file);
                return;
            }
        }
        fclose(file);
    }
    saveScore(username, score);
}

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
        score += 10;
        piece++;
        // Generate new fruit coordinates
        fruitx = rand() % (height - 1) + 1; // Exclude the border
        fruity = rand() % (width - 1) + 1; // Exclude the border
    }
}

void input() {
    if (kbhit()) {
        char ch = getch();
        switch (ch) {
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
            case 'q':
                gameend = 1; // Quit the game if 'q' is pressed
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
                printf(COLOR_GREEN "* " COLOR_RESET);
            } else {
                if (i == x && j == y) {
                    printf(COLOR_RED "0 " COLOR_RESET);
                } else if (i == fruitx && j == fruity) {
                    printf(COLOR_YELLOW "@ " COLOR_RESET);
                } else {
                    ch = 0;
                    for (k = 0; k < piece; k++) {
                        if (i == tailx[k] && j == taily[k]) {
                            printf(COLOR_RED "0 " COLOR_RESET);
                            ch = 1;
                        }
                    }
                    if (ch == 0)
                        printf("  ");
                }
            }
        }
        printf("\n");
    }
    printf("Your score is: %d\n", score);
}

int snake() {
    char username[100];
    printf("Enter your username: ");
    scanf("%s", username);
    setup();
    while (!gameend) {
        input();
        draw();
        makelogic();
        // Introducing a delay here
        Sleep(100); // 100 milliseconds
    }
    updateOrSaveScore(username, score); // Save or update score
    return 0;
}
