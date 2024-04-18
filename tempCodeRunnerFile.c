#include "games/pacman.c"

#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void pacman();
void tictactoe();
void hangman();
void wordel();

int main()
{
    int choice;
    system("cls");
    // Display menu
    printf("Welcome to the Game Center!\n");
    printf("1. Pacman\n");
    printf("2. Tic Tac Toe\n");
    printf("3. Hangman\n");
    printf("4. Wordel\n");
    printf("Please enter the number of the game you want to play: ");
    scanf("%d", &choice);

    // Perform action based on user choice
    system("cls");

    switch (choice)
    {
    case 1:
        pacman();
        break;
    case 2:
        tictactoe();
        break;
    case 3:
        hangman();
        break;
    case 4:
        wordel();
        break;
    default:
        printf("Invalid choice. Please enter a number between 1 and 4.\n");
        break;
    }

    return 0;
}



void hangman()
{
    // Implementation of Hangman game
    printf("Hangman game is under development.\n");
}

void wordel()
{
    // Implementation of Wordel game
    printf("Wordel game is under development.\n");
}
