#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Structure to represent a chess piece
typedef struct {
    char type;  // P=pawn, R=rook, N=knight, B=bishop, Q=queen, K=king
    char color; // W=white, B=black
} Piece;

// Function declarations
void initializeBoard(Piece board[8][8]);
void printBoard(Piece board[8][8]);
bool isValidMove(Piece board[8][8], int fromRow, int fromCol, int toRow, int toCol, char currentPlayer);
bool isPathClear(Piece board[8][8], int fromRow, int fromCol, int toRow, int toCol);

int main() {
    Piece board[8][8];
    char currentPlayer = 'W'; // W for White, B for Black
    char moveFrom[3], moveTo[3];
    
    initializeBoard(board);
    
    while (1) {
        printBoard(board);
        
        printf("\n%s player's turn (e.g., a2 a4): ", currentPlayer == 'W' ? "White" : "Black");
        scanf("%s %s", moveFrom, moveTo);
        
        // Convert chess notation to array indices
        int fromRow = 8 - (moveFrom[1] - '0');
        int fromCol = tolower(moveFrom[0]) - 'a';
        int toRow = 8 - (moveTo[1] - '0');
        int toCol = tolower(moveTo[0]) - 'a';
        
        if (isValidMove(board, fromRow, fromCol, toRow, toCol, currentPlayer)) {
            // Make the move
            board[toRow][toCol] = board[fromRow][fromCol];
            board[fromRow][fromCol].type = ' ';
            board[fromRow][fromCol].color = ' ';
            
            // Switch players
            currentPlayer = (currentPlayer == 'W') ? 'B' : 'W';
        } else {
            printf("Invalid move! Try again.\n");
        }
    }
    
    return 0;
}

void initializeBoard(Piece board[8][8]) {
    // Initialize empty squares
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j].type = ' ';
            board[i][j].color = ' ';
        }
    }
    
    // Set up white pieces
    board[7][0] = board[7][7] = (Piece){'R', 'W'};
    board[7][1] = board[7][6] = (Piece){'N', 'W'};
    board[7][2] = board[7][5] = (Piece){'B', 'W'};
    board[7][3] = (Piece){'Q', 'W'};
    board[7][4] = (Piece){'K', 'W'};
    for (int i = 0; i < 8; i++) {
        board[6][i] = (Piece){'P', 'W'};
    }
    
    // Set up black pieces
    board[0][0] = board[0][7] = (Piece){'R', 'B'};
    board[0][1] = board[0][6] = (Piece){'N', 'B'};
    board[0][2] = board[0][5] = (Piece){'B', 'B'};
    board[0][3] = (Piece){'Q', 'B'};
    board[0][4] = (Piece){'K', 'B'};
    for (int i = 0; i < 8; i++) {
        board[1][i] = (Piece){'P', 'B'};
    }
}

void printBoard(Piece board[8][8]) {
    printf("\n");
    printf("    a   b   c   d   e   f   g   h\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    
    for (int i = 0; i < 8; i++) {
        printf("%d |", 8 - i);
        for (int j = 0; j < 8; j++) {
            char piece = board[i][j].type;
            if (board[i][j].color == 'B') {
                piece = tolower(piece);
            }
            printf(" %c |", piece);
        }
        printf(" %d\n", 8 - i);
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    printf("    a   b   c   d   e   f   g   h\n");
}

bool isValidMove(Piece board[8][8], int fromRow, int fromCol, int toRow, int toCol, char currentPlayer) {
    // Check if coordinates are within bounds
    if (fromRow < 0 || fromRow > 7 || fromCol < 0 || fromCol > 7 ||
        toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7) {
        return false;
    }
    
    // Check if source square has a piece of the current player
    if (board[fromRow][fromCol].color != currentPlayer) {
        return false;
    }
    
    // Check if destination square is empty or has enemy piece
    if (board[toRow][toCol].color == currentPlayer) {
        return false;
    }
    
    // Get the piece type and validate move based on piece rules
    char pieceType = board[fromRow][fromCol].type;
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    
    switch (pieceType) {
        case 'P': // Pawn
            if (currentPlayer == 'W') {
                // White pawns move upward
                if (fromCol == toCol && board[toRow][toCol].type == ' ') {
                    // Normal move
                    if (fromRow - toRow == 1) return true;
                    // First move can be 2 squares
                    if (fromRow == 6 && fromRow - toRow == 2 && 
                        board[fromRow-1][fromCol].type == ' ') return true;
                }
                // Capture diagonally
                if (fromRow - toRow == 1 && colDiff == 1 && 
                    board[toRow][toCol].color == 'B') return true;
            } else {
                // Black pawns move downward
                if (fromCol == toCol && board[toRow][toCol].type == ' ') {
                    // Normal move
                    if (toRow - fromRow == 1) return true;
                    // First move can be 2 squares
                    if (fromRow == 1 && toRow - fromRow == 2 && 
                        board[fromRow+1][fromCol].type == ' ') return true;
                }
                // Capture diagonally
                if (toRow - fromRow == 1 && colDiff == 1 && 
                    board[toRow][toCol].color == 'W') return true;
            }
            return false;
            
        case 'R': // Rook
            if ((fromRow == toRow || fromCol == toCol) && 
                isPathClear(board, fromRow, fromCol, toRow, toCol))
                return true;
            return false;
            
        case 'N': // Knight
            if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))
                return true;
            return false;
            
        case 'B': // Bishop
            if (rowDiff == colDiff && isPathClear(board, fromRow, fromCol, toRow, toCol))
                return true;
            return false;
            
        case 'Q': // Queen
            if ((fromRow == toRow || fromCol == toCol || rowDiff == colDiff) && 
                isPathClear(board, fromRow, fromCol, toRow, toCol))
                return true;
            return false;
            
        case 'K': // King
            if (rowDiff <= 1 && colDiff <= 1)
                return true;
            return false;
    }
    
    return false;
}

bool isPathClear(Piece board[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    int rowStep = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
    int colStep = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;
    
    int currentRow = fromRow + rowStep;
    int currentCol = fromCol + colStep;
    
    while (currentRow != toRow || currentCol != toCol) {
        if (board[currentRow][currentCol].type != ' ') {
            return false;
        }
        currentRow += rowStep;
        currentCol += colStep;
    }
   
}
