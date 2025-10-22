#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 6
#define COLS 7
#define EMPTY '.'

// Task 1: Ali Zain – Board creation and printing
void create_board(char board[ROWS][COLS]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            board[r][c] = EMPTY;
        }
    }
}

void print_board(char board[ROWS][COLS]) {
    system("clear");
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            printf("%c ", board[r][c]);
        }
        printf("\n");
    }
    for (int i = 1; i <= COLS; i++) printf("%d ", i);
    printf("\n\n");
}

// Task 2: Jad Timani – Piece dropping + board status checks + Play Again mechanic
int drop_piece(char board[ROWS][COLS], int col, char piece) {
    for (int r = ROWS - 1; r >= 0; r--) {
        if (board[r][col] == EMPTY) {
            board[r][col] = piece;
            return 1;
        }
    }
    return 0;
}

int is_board_full(char board[ROWS][COLS]) {
    for (int c = 0; c < COLS; c++) {
        if (board[0][c] == EMPTY) return 0;
    }
    return 1;
}

int play_again() {
    char choice;
    printf("Would you like to play again? (Y/N): ");
    scanf(" %c", &choice);
    if (choice == 'Y' || choice == 'y')
        return 1;
    else
        return 0;
}

// Task 3: Rami Merhi – Winning condition
int is_winning_move(char board[ROWS][COLS], char piece) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS - 3; c++) {
            if (board[r][c] == piece && board[r][c+1] == piece &&
                board[r][c+2] == piece && board[r][c+3] == piece)
                return 1;
        }
    }
    for (int c = 0; c < COLS; c++) {
        for (int r = 0; r < ROWS - 3; r++) {
            if (board[r][c] == piece && board[r+1][c] == piece &&
                board[r+2][c] == piece && board[r+3][c] == piece)
                return 1;
        }
    }
    for (int r = 3; r < ROWS; r++) {
        for (int c = 0; c < COLS - 3; c++) {
            if (board[r][c] == piece && board[r-1][c+1] == piece &&
                board[r-2][c+2] == piece && board[r-3][c+3] == piece)
                return 1;
        }
    }
    for (int r = 0; r < ROWS - 3; r++) {
        for (int c = 0; c < COLS - 3; c++) {
            if (board[r][c] == piece && board[r+1][c+1] == piece &&
                board[r+2][c+2] == piece && board[r+3][c+3] == piece)
                return 1;
        }
    }
    return 0;
}

// Task 4: All Members – Easy Bot Implementation
int bot_move(char board[ROWS][COLS]) {
    int col;
    do {
        col = rand() % COLS;
    } while (board[0][col] != EMPTY);
    drop_piece(board, col, 'B');
    return col + 1;
}

// Task 5: Rami Merhi – Main Game Loop and Mode Selection
int main() {
    char board[ROWS][COLS];
    int col, valid, turn, mode, play = 1;
    char player, winner;

    srand(time(NULL));

    while (play) {
        create_board(board);
        winner = '\0';
        turn = 0;

        printf("Welcome to Connect Four!\n");
        printf("Choose mode:\n1. Player vs Player\n2. Player vs Bot (Easy)\n");
        scanf("%d", &mode);

        print_board(board);

        while (1) {
            player = (turn % 2 == 0) ? 'A' : 'B';

            if (mode == 2 && player == 'B') {
                printf("Bot is thinking...\n");
                col = bot_move(board);
                printf("Bot chooses column %d\n", col);
            } else {
                printf("Player %c, choose a column (1-7): ", player);
                if (scanf("%d", &col) != 1) {
                    printf("Invalid input. Try again.\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (col < 1 || col > COLS) {
                    printf("Column must be between 1 and 7. Try again.\n");
                    continue;
                }
                valid = drop_piece(board, col - 1, player);
                if (!valid) {
                    printf("Column %d is full. Try another.\n", col);
                    continue;
                }
            }

            print_board(board);

            if (is_winning_move(board, player)) {
                winner = player;
                break;
            }

            if (is_board_full(board))
                break;

            turn++;
        }

        if (winner != '\0') {
            if (mode == 2 && winner == 'B')
                printf("Bot wins!\n");
            else
                printf("Player %c wins!\n", winner);
        } else {
            printf("Game over. It's a draw!\n");
        }

        play = play_again();
    }

    printf("Thanks for playing! Goodbye!\n");
    return 0;
}