#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>

#define GRIDSIZE 4
int board[GRIDSIZE][GRIDSIZE];

int checkLose() {
    int count = 0;
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if (board[i][j] == 0) {
                count ++;
	    }
	}
    }
    return count;
}

void newGame() {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            board[i][j] = 0;
	}
    }
}

void showNow() {
    for (int i = 0; i < GRIDSIZE; i++) {
	std::cout << "-----------------------------" << std::endl;
	for (int j = 0; j < GRIDSIZE; j++) {
	    std::cout << "| " << std::setw(4) << board[i][j] << " ";
	}
	std::cout << "|" << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}

int displayCurrent() {
    //showNow();
    //system("cls");
    std::cout << "-------------------- NOW: ---------------------" << std::endl;
    std::cout << "w: up, a: left, s: down, d: right, q: quit" << std::endl;
    
    int adds = rand() % 2;
    if (adds == 1) {

	if (checkLose() < 2) {
	    return 0;
	}
        
	int v1, v2;
        int invalid = 1;
        int rowNum1, colNum1, rowNum2, colNum2;
        while (invalid == 1) {
            v1 = rand() % (GRIDSIZE * GRIDSIZE);
            v2 = rand() % (GRIDSIZE * GRIDSIZE);
            if (v1 != v2) {
	        rowNum1 = v1 / GRIDSIZE;
	        colNum1 = v1 % GRIDSIZE;
	        rowNum2 = v2 / GRIDSIZE;
	        colNum2 = v2 % GRIDSIZE;
                if (board[rowNum1][colNum1] == 0 && board[rowNum2][colNum2] == 0) {
                    invalid = 0;
	        }
	    }
        }

        board[rowNum1][colNum1] = 2;
        board[rowNum2][colNum2] = 2;
    }

    else {
	// adding 1 new
        if (checkLose() < 1) {
	    return 0;
	}
	int spot;
	int row, col;
	int invalid = 1;
	while (invalid == 1) {
            spot = rand() % (GRIDSIZE * GRIDSIZE);
	    row = spot / GRIDSIZE;
	    col = spot % GRIDSIZE;
	    if (board[row][col] == 0) {
                invalid = 0;
	    }
	}
	board[row][col] = 2;
    }

    for (int i = 0; i < GRIDSIZE; i++) {
	std::cout << "-----------------------------" << std::endl;
	for (int j = 0; j < GRIDSIZE; j++) {
	    if (board[i][j] != 0) {
	    std::cout << "| " << std::setw(4) <<  board[i][j] << " ";
	    } else {
            std::cout << "| " << "    " << " ";
	    }
	}    
	std::cout << "|" << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
    return 1;
}

void shiftLeftOrUp(char pick) {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int k = 0; k < GRIDSIZE; k++) {
            for (int m = 0; m < GRIDSIZE - 1; m++) {
                if (pick == 'l') {
                    if (board[i][m] == 0) {
                        for (int h = m; h < GRIDSIZE - 1; h++) 
                            board[i][h] = board[i][h+1];
			board[i][GRIDSIZE-1] = 0;
		    }
		} else {
		    if (board[m][i] == 0) {
                        for (int h = m; h < GRIDSIZE - 1; h++) 
                            board[h][i] = board[h+1][i];
		        board[GRIDSIZE - 1][i] = 0;
		    }
		}
	    }
	}
    }
}

int goUp() {
    // shift all up
    shiftLeftOrUp('u');

    // combine

    for (int i = 0; i < GRIDSIZE; i++) {
        if (board[0][i] == board[1][i]) {
            board[0][i] = (board[0][i] * 2);
	    board[1][i] = 0;
	    if (board[2][i] == board[3][i]) {
                board[2][i] = (board[2][i] * 2);
		board[3][i] = 0;
	    } 
	    //shiftLeftOrUp('u');
	} else if (board[1][i] == board[2][i]) {
            board[1][i] = (board[1][i] * 2);
	    board[2][i] = 0;
	    //shiftLeftOrUp('u');
	} else if (board[2][i] == board[3][i]) {
            board[2][i] = (board[2][i] * 2);
	    board[3][i] = 0;
	}
	
    }
    shiftLeftOrUp('u');

    return displayCurrent();
} 

int goLeft() {
    // shift all left
    shiftLeftOrUp('l');

    // combine
 
    for (int i = 0; i < GRIDSIZE; i++) {
        if (board[i][0] == board[i][1]) {
            board[i][0] = (board[i][0] * 2);
	    board[i][1] = 0;
	    if (board[i][2] == board[i][3]) {
                board[i][2] = (board[i][2] * 2);
		board[i][3] = 0;
	    } 
	    //shiftLeftOrUp('u');
	} else if (board[i][1] == board[i][2]) {
            board[i][1] = (board[i][1] * 2);
	    board[i][2] = 0;
	    //shiftLeftOrUp('u');
	} else if (board[i][2] == board[i][3]) {
            board[i][2] = (board[i][2] * 2);
	    board[i][3] = 0;
	}
	
    }
    shiftLeftOrUp('l');
  
    return displayCurrent();
}

void shiftRightOrDown(char pick) {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int k = 0; k < GRIDSIZE; k++) {
            for (int m = GRIDSIZE - 1; m >= 1; m--) {
                if (pick == 'd') {
                    if (board[m][i] == 0) {
                        for (int h = m; h >= 1; h--) 
                            board[h][i] = board[h-1][i];
			board[0][i] = 0;
		    }
		} else {
                    if (board[i][m] == 0) {
                        for (int h = m; h >= 1; h--) 
                            board[i][h] = board[i][h-1];
			board[i][0] = 0;
		    }
		}
	    }
	}
    }
}

int goDown() {
    // shift all down
    shiftRightOrDown('d');
    
    // combine
    for (int i = 0; i < GRIDSIZE; i++) {
        if (board[3][i] == board[2][i]) {
            board[3][i] = (board[3][i] * 2);
	    board[2][i] = 0;
	    if (board[1][i] == board[0][i]) {
                board[1][i] = (board[1][i] * 2);
		board[0][i] = 0;
	    }
	} else if (board[2][i] == board[1][i]) {
            board[2][i] = (board[2][i] * 2);
	    board[1][i] = 0;
	} else if (board[1][i] == board[0][i]) {
            board[1][i] = (board[1][i] * 2);
	    board[0][i] = 0;
	}
    }
    shiftRightOrDown('d');

    return displayCurrent();
}

int goRight() {
    shiftRightOrDown('r');

    // combine
    
    for (int i = 0; i < GRIDSIZE; i++) {
        if (board[i][3] == board[i][2]) {
            board[i][3] = (board[i][3] * 2);
	    board[i][2] = 0;
	    if (board[i][1] == board[i][0]) {
                board[i][1] = (board[i][1] * 2);
		board[i][0] = 0;
	    }
	} else if (board[i][2] == board[i][1]) {
            board[i][2] = (board[i][2] * 2);
	    board[i][1] = 0;
	} else if (board[i][1] == board[i][0]) {
            board[i][1] = (board[i][1] * 2);
	    board[i][0] = 0;
	}
    }
    shiftRightOrDown('r');

    return displayCurrent();
}

void printBoard() {
    //std::cout << "w: up, a: left, s: down, d: right, q: quit" << std::endl;
    std::cout << "BOARD CLEARED" << std::endl;
    for (int i = 0; i < GRIDSIZE; i++) {
        std::cout << "-----------------------------" << std::endl;
        std::cout << "|      |      |      |" << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}

bool checkWin() {
    for (int i = 0; i < GRIDSIZE; i++) {
        for (int j = 0; j < GRIDSIZE; j++) {
            if (board[i][j] == 2048) {
                return true;
	    }
	}
    }
    return false;
}

int main() {
    printBoard();
    
    int check;

    check = displayCurrent();
    
    char userInput;
    while (true) {
        std::cin >> userInput;
	switch (userInput) {
	    case 'w':
                check = goUp();
		break;
	    case 'a':
                check = goLeft();
		break;
	    case 's':
                check = goDown();
		break;
	    case 'd':
                check = goRight();
		break;
	    case 'q':
                exit(1);
            default:
		std::cout << "Try again: " << std::endl;
	}
        if (checkWin()) {
	    std::cout << "You win!" << std::endl;
            return 0;
	}
	if (check == 0) {
            std::cout << "You lose!" << std::endl;
	    return 1;
	}
    }
    return 0;
}
