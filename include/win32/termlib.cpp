#include <stdlib.h>
#include <conio.h>
#include "termlib.h"

namespace term {

    void clrscr(){
        system ("cls");
    }
    
    char getch(){
        return _getch();
    }

}