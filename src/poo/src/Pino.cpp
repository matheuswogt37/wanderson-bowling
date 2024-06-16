#include "headers/Pino.hpp"

Pino::Pino(int x, int y) : Pos(x, y) {
    
}

Pino::~Pino() {

}

bool Pino::getErguido() {
    return this->erguido;
}

void Pino::setErguido(bool erg) {
    this->erguido = erg;
}