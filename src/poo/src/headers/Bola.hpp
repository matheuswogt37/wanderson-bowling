#ifndef Bola_hpp
#define Bola_hpp

#include "Pos.hpp"

class Bola : public Pos {
    private:
        int velocidade, direcao, efeito;
    
    public:
        Bola(int x, int y);
        ~Bola();
        int getVelocidade();
        int getDirecao();
        int getEfeito();
        void setAtributos(int vel, int dir, int eff);

};

#endif