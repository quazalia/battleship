#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
const int BOARD_SIZE = 7;
const int NUM_SHIPS_OF_LENGTH_3 = 1;
const int NUM_SHIPS_OF_LENGTH_2 = 2;
const int NUM_SHIPS_OF_LENGTH_1 = 4;

int board[BOARD_SIZE][BOARD_SIZE];
int game[BOARD_SIZE][BOARD_SIZE];
bool isValidPosition(int x, int y) {
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
}

bool isAdjacent(int x, int y) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;
            if (isValidPosition(newX, newY) && board[newX][newY] != 0) {
                return true;
            }
        }
    }
    return false;
}

bool isValidPlacement(int x, int y, int shipLength, bool horizontal) {
    if (horizontal) {
        if (y + shipLength > BOARD_SIZE) {
            return false;
        }
        for (int i = y; i < y + shipLength; ++i) {
            if (board[x][i] != 0 || isAdjacent(x, i)) {
                return false;
            }
        }int game[BOARD_SIZE][BOARD_SIZE];
    } else {
        if (x + shipLength > BOARD_SIZE) {
            return false;
        }
        for (int i = x; i < x + shipLength; ++i) {
            if (board[i][y] != 0 || isAdjacent(i, y)) {
                return false;
            }
        }
    }
    return true;
}

void placeShip(int x, int y, int shipLength, bool horizontal, int shipNumber) {
    if (horizontal) {
        for (int i = y; i < y + shipLength; ++i) {
            board[x][i] = shipNumber;
        }
    } else {
        for (int i = x; i < x + shipLength; ++i) {
            board[i][y] = shipNumber;
        }
    }
}

void placeShipsRandomly() {
    int shipsPlaced = 0;
    while (shipsPlaced < NUM_SHIPS_OF_LENGTH_3) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        bool horizontal = rand() % 2 == 0;
        if (isValidPlacement(x, y, 3, horizontal)) {
            placeShip(x, y, 3, horizontal, 3);
            shipsPlaced++;
        }
    }

    shipsPlaced = 0;
    while (shipsPlaced < NUM_SHIPS_OF_LENGTH_2) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        bool horizontal = rand() % 2 == 0;
        if (isValidPlacement(x, y, 2, horizontal)) {
            placeShip(x, y, 2, horizontal, 2);
            shipsPlaced++;
        }
    }

    shipsPlaced = 0;
    while (shipsPlaced < NUM_SHIPS_OF_LENGTH_1) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (board[x][y] == 0 && !isAdjacent(x, y)) {
            placeShip(x, y, 1, true, 1);
            shipsPlaced++;
        }
    }
}

void displayBoard() {
      std::cout << "  1 2 3 4 5 6 7\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
       std:: cout<<i+1<<" ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std:: cout<<'\n';
}

void displayGame() {
      std::cout << "  1 2 3 4 5 6 7\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
      std:: cout<<i+1<<" ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << game[i][j] << " ";
        }
        std::cout << std::endl;
    }
      std:: cout<<'\n';
}
void clear(){
      // Clear screen using escape sequences based on different operating systems
            #ifdef _WIN32
            system("cls"); // For Windows
            #else
            // For Unix-like systems (Linux, macOS)
            std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear screen
            std::cout.flush(); // Flush output
            #endif
}

void play(){
      clear();
      int count=0;
      for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                  game[i][j] = 0;
            }
      }

      placeShipsRandomly();

    
      displayBoard();
      std:: cout<<'\n';

      displayGame();
      std:: cout<<'\n';
      int big=1, med=2, sm=4;
      int x,y,q,w;
      while (big >0 or med>0 or sm>0)
      {
            std:: cin>>x>>y;
            q=x-1; w=y-1;
            if(x > 7 or y > 7){
                  
                  clear();
                  std:: cout<<"You put coordinates incorect! Try again!";
                  std :: cout<<'\n';
                  displayGame();
            }
            else if(game[q][w]==8 or game[q][w]==5){
                  
                  clear();
                  std :: cout<<"Sorry you already hit this place";
                  std :: cout<<'\n';
                  displayGame();
            }
            else{
                  if(game[q][w]!=board[q][w]){
                        clear();
                        if(board[q][w]==1){
                              std :: cout<<"Sunk!";
                              sm--;
                              game[q][w]=5;
                              std:: cout<<'\n';
                              displayGame();

                        }
                        if(board[q][w]==2){
                              game[q][w]=5;
                              if(game[q-1][w]==5 or game[q+1][w]==5 or game[q][w-1]==5 or game[q][w+1]==5 ){
                                    std :: cout<<"Sunk!";
                                    med--;
                                    game[q][w]=5;
                                    std:: cout<<'\n';
                                    displayGame();
                              }
                              else{
                                    std :: cout<<"Hit!"<<'\n';
                                    displayGame();
                              }
                        }
                        if(board[q][w]==3){
                              game[q][w]=5;
                              if(game[q-1][w]==5 or game[q+1][w]==5 or game[q][w-1]==5 or game[q][w+1]==5){
                                    if( game[q-2][w]==5 or game[q+2][w]==5 or game[q][w-2]==5 or game[q][w+2]==5){
                                          std :: cout<<"Sunk!";
                                          big--;
                                          game[q][w]=5;
                                          std:: cout<<'\n';
                                          displayGame();
                                    }
                                    else{
                                          std :: cout<<"Hit!"<<'\n';
                                          displayGame();
                                    }
                                    
                              }
                              else{
                                    std :: cout<<"Hit!"<<'\n';
                                    displayGame();
                              }
                        }
                  }
                  else{
                        clear();
                        std :: cout<<"You miss!";
                        std:: cout<<'\n';
                        game[q][w]=8;
                        displayGame();
                        }
         
                  }
            count++;
      } 
      char ans;
      std:: cout<<"Congratulations! "<<"Your count of hit is "<<count<<". Do you want to play again? Y or N"<<'\n';
      std :: cin>>ans;
      if(ans=='Y'){
            play();
      }
      else std:: cout<< "Good luck!";

}
int main() {
      std ::  string name;
      srand(static_cast<unsigned int>(time(0)));
      std:: cout<<"Hello, input your name!"<<'\n';
      std:: cin>>name;
      std :: cout<<'\n';
      play();


}
       
