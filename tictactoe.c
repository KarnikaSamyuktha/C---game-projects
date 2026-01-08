

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define computer_turn 0
#define player_turn 1
#define size 3

struct move { 
    int row, col; 
}; 

const char player = 'x';
const char computer = 'o';

void initialise(char board[size][size]){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '_';
        }
    }
}

int display_instructions(){
    printf("GAME: TIC-TAC-TOE\n");
    printf(" 1 | 2 | 3 \n");
    printf(" --------- \n");
    printf(" 4 | 5 | 6 \n");
    printf(" --------- \n");
    printf(" 7 | 8 | 9 \n");
    printf("The player has to choose a cell-number out of (1-9) for every move\n");
    printf("The player gets to move with %c\nThe computer gets to move with %c\n", player, computer);
    char first_turn;
    while (1) {
        printf("Would you like to start first (y/n): ");
        scanf(" %c", &first_turn); // Note the space before %c to consume any leftover newlines
        if (first_turn == 'y') return player_turn;
        else if (first_turn == 'n') return computer_turn;
        else printf("Please enter a valid option (y/n)\n");
    }
}

bool nomovesleft(char board[3][3]) {
    for (int i = 0; i < 3; i++) 
        for (int j = 0; j < 3; j++) 
            if (board[i][j] == '_') 
                return false; 
    return true; 
}

int checkforwin(char b[3][3]) {
    // Check Rows
    for (int row = 0; row < 3; row++) { 
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) { 
            if (b[row][0] == player) return 1; 
            if (b[row][0] == computer) return -1; 
        } 
    }
    // Check Columns
    for (int col = 0; col < 3; col++) { 
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) { 
            if (b[0][col] == player) return 1; 
            if (b[0][col] == computer) return -1; 
        } 
    }
    // Check Diagonals
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) { 
        if (b[0][0] == player) return 1; 
        if (b[0][0] == computer) return -1; 
    }
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) { 
        if (b[0][2] == player) return 1; 
        if (b[0][2] == computer) return -1; 
    }
    return 0; 
}

bool gameOver(char board[3][3]) {
    if ( checkforwin(board)==1 && checkforwin(board)==-1) return true ;
    else false;
}

void showBoard(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf(" --------- \n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf(" --------- \n");
    printf(" %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

void declareWinner(int whoseturn) {
    if (whoseturn == computer_turn) 
        printf("Congrats! You have won\n"); 
    else 
        printf("COMPUTER has won :(\n"); 
}

int minimax(char board[3][3], int depth, bool isMax) {
    int score = checkforwin(board);
    if (score == 1) return score - depth;
    if (score == -1) return score + depth;
    if (nomovesleft(board)) return 0;
  
    int best = isMax ? -1000 : 1000;
  
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = isMax ? computer : player;
                int moveVal = minimax(board, depth + 1, !isMax);
                best = isMax ? (moveVal > best ? moveVal : best) : (moveVal < best ? moveVal : best);
                board[i][j] = '_';
            }
        }
    }
    return best;
}

struct move findbestmove(char board[3][3]) {
    int bestVal = -1000;
    struct move bestMove = {-1, -1};
  
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = computer;
                int moveVal = minimax(board, 0, false);
                board[i][j] = '_';
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void play_tictactoe(int whoseturn) {
    char board[size][size];
    initialise(board);
    int moveindex = 0;
  
    while (!gameOver(board) && moveindex != size * size) {
        int i=0;
        showBoard(board);
        if (whoseturn == computer_turn) {
            //aimed to generate a random int for first mive rather than default (0,0 move)
            if (i=0){
                //ensure different values every time
                struct move bestMove;
                bestMove.row=rand()%3;
                bestMove.col=rand()%3;
                i=1;
                board[bestMove.row][bestMove.col] = computer;
                printf("Computer has put a %c in cell %d %d\n", computer, bestMove.row, bestMove.col);
                moveindex++;
                whoseturn = player_turn;
                //failed
            }
        else{
            struct move bestMove = findbestmove(board);
            board[bestMove.row][bestMove.col] = computer;
            printf("Computer has put a %c in cell %d %d\n", computer, bestMove.row, bestMove.col);
            moveindex++;
            whoseturn = player_turn;
            if(gameOver(board)){ showBoard(board);
            declareWinner(whoseturn);}

        } }else {
            int move;
            printf("Enter your move (1-9): ");
            scanf("%d", &move);
            int x = (move - 1) / size;
            int y = (move - 1) % size; 
            if (board[x][y] == '_') { 
                board[x][y] = player;
                showBoard(board); 
                moveindex++; 
                whoseturn = computer_turn; 
                if(gameOver(board)){showBoard(board);
                declareWinner(whoseturn);}
                }
            else { 
                printf("The Cell is already occupied. Try another move.\n"); 
                }
                i=1; //if first turn is by player then bestmove to be taken in}

            if (!gameOver(board) && moveindex == size*size) {showBoard(board);
            printf("It's a draw :)\n"); }
            
}}}
int main(){
    srand(time(NULL));
    int first_turn=display_instructions();
    if (first_turn==1) play_tictactoe(player_turn);
    else play_tictactoe(computer_turn);
}
