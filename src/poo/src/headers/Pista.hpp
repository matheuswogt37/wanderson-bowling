#ifndef Pista_hpp
#define Pista_hpp

#include "Global.hpp"
#include "Pino.hpp"
#include "Bola.hpp"

class Pista {
    private:
        char pista[SIZE_Y][SIZE_X];
    public:
        Pista();
        ~Pista();
        void setPista();
        void setCustomPista(int x, int y, char state);
        void setPistaItems(Pino *pinos[10], Bola *bola);
        char getPista(int x, int y);

};


#endif