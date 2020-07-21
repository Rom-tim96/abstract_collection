#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

void clrscr(){
    std::system ("clear");
}

static struct termios stored_settings;

char _getch(){

    struct termios new_settings;

    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;

    /*Отключение канонического режима и вывода на экран
        и установка буфера ввода размером в 1 байт*/

    new_settings.c_lflag &= (~ICANON);
    new_settings.c_lflag &= (~ECHO);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(0,TCSANOW,&new_settings);

    char ch = getchar();

    tcsetattr(0,TCSANOW,&stored_settings);

    return ch;
}
