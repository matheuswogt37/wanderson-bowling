#ifndef App_hpp
#define App_hpp

#include <iostream>
#include "Console.hpp"
#include "Bola.hpp"
#include "Pino.hpp"
#include "Pista.hpp"

class App {
    private:
        Console *console;
        Pino *pinos[10];
        Bola *bola;
        Pista *pista;

        void atualizarPontuacaoMax(int points);
        void run();
        void playGame();
        void end();
    public:
        App();
        ~App();
        void start();

};

#endif