//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "DisplayGameOnConsole.h"

DisplayGameOnConsole::DisplayGameOnConsole(Board *board) : DisplayGame(board) {}

void DisplayGameOnConsole::printGameBoard() const {
    //iterating over the board in order to print it as requested
    for(int i = 0; i <= this->board->getRows(); i++){
        for(int j = 0; j <= this->board->getColumns(); j++){
            if(i == 0 && j == 0){
                cout << " " << "|" ;
            }
            if(i == 0 && j != 0){
                cout << " " << j << " " << "|";
            }
            if(i != 0 && j == 0){
                cout << i << "|" ;
            }
            if(i != 0 && j != 0){
                cout << " " << this->board->getBoard()[i-1][j-1].cellToPrint() << " " << "|";
            }

        }
        cout << endl;
        for(int k = 0; k < ((4*this->board->getColumns())+2); k++){
            cout << "-" ;
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}
