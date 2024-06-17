#ifndef Pino_hpp
#define Pino_hpp

#include "Pos.hpp"

class Pino : public Pos {
    private:
        bool erguido;
    public:
        Pino(int x, int y);
        ~Pino();
        bool getErguido();
        void setErguido(bool erg);        
};

#endif