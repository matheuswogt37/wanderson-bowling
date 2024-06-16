#include "headers/Pos.hpp"

Pos::Pos(int x, int y) {
    this->x = x;
    this->y = y;
}

Pos::~Pos() {
}

void Pos::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

int Pos::getX() {
    return this->x;
}

int Pos::getY() {
    return this->y;
}