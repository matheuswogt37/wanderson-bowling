#include "headers/Bola.hpp"

Bola::Bola(int x, int y) : Pos(x, y) {

}

Bola::~Bola() {

}

int Bola::getVelocidade() {
    return this->velocidade;
}

int Bola::getDirecao() {
    return this->direcao;
}

int Bola::getEfeito() {
    return this->efeito;
}

void Bola::setAtributos(int vel, int dir, int eff) {
    this->velocidade = vel;
    this->direcao = dir;
    this->efeito = eff;
}