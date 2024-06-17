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
#include "Global.hpp"
#include "Bola.hpp"
#include "Pino.hpp"
#include "Pista.hpp"


class Console {
    private:
        int points;
        int pinos_caidos;
    public:
        Console();
        ~Console();
        // utilitarios
        int _kbhit(void);
        void _sleep(float seconds);
        void clearKeyboardBuffer();
        void initConsole();
        void clearConsole();
        // utilitarios matematicos
        float calcModDirection(int direction);
        float calcModEffect(int &effect);
        int roundFUp(float number);
        int randColisaoMult(int speed);
        void swapBallPos(int x, int y, int newX, int newY);
        void downAndMultipleCollision(Pista *pista, int xPine, int yPine, int ballSpeed);
        // terminal 
        void moveCursor(int x, int y);
        void writeStringIn(int x, int y, std::string str);
        void deleteLastChar();
        void resetCursorPos();
        void pressEnter();
        void pressEnterCord(int x, int y);
        int getControlLoad(int x, int y);
        // controles do jogo
        void renderGame(Pista *pista, Pino *pinos[10], Bola *bola);

        // output terminal
        void exibirInstrucoes();
        void printSizeControlLoads(int y);
        void showBoard(Pista *pista);
        void showBoardItems(Pino *pinos[10], Bola *bola);
        void showPoints();
        void showControlLabels();
        
};

#endif