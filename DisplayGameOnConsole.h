//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX2_DisplayGameOnConsole_H
#define EX2_DisplayGameOnConsole_H

#include "DisplayGame.h"

class DisplayGameOnConsole: public DisplayGame {
public:

    /**
     * constructor of DisplayGameOnConsole object.
     * @param board
     */
    DisplayGameOnConsole(Board *board);
    /**
     * printGameBoard function will print the board to the screen as requested.
     */
    virtual void printGameBoard() const;
    /**
     * destructor of DisplayGameOnConsole object
     */
    virtual ~DisplayGameOnConsole(){}
};

#endif //EX2_DisplayGameOnConsole_H
