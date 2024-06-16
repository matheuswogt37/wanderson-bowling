#ifndef Console_hpp
#define Console_hpp

#include <string>
//* kbhit libs start
#include <fcntl.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
//* kbhit libs end

//* my libs
#include "headers/Global.hpp"
#include "headers/Bola.hpp"
#include "headers/Pino.hpp"


class Console {
    public:
        Console();
        ~Console();
        // utilitarios
        int _kbhit(void);
        void _sleep(float seconds);
        void clearKeyboardBuffer();
        void initConsole();
        void clearConsole();
        // terminal 
        void moveCursor(int x, int y);
        void writeStringIn(int x, int y, std::string str);
        void deleteLastChar();
        void resetCursorPos();
        void pressEnter();
        void pressEnterCord(int x, int y);
        void resetCursorPos();
        // controles do jogo

        // output terminal
        void exibirInstrucoes();
        void showBoard(char board[SIZE_Y][SIZE_X]);
};

#endif