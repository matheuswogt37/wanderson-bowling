#include "headers/Pista.hpp"

Pista::Pista() {
    
}

Pista::~Pista() {

}

void Pista::setPista() {
    int maxY = (SIZE_Y - 1);
    int maxX = (SIZE_X - 1);

    for (int i = 0; i < SIZE_Y; i++)  // preenchendo a pista com espaços
    {
        for (int j = 0; j < SIZE_X; j++) {
            this->pista[i][j] = ' ';
        }
    }

    for (int j = 0; j < SIZE_X; j++)  // as linhas superiores
    {
        this->pista[0][j] = LINHAS_SUPERIORES;
    }

    for (int i = 1; i < (SIZE_Y - 1); i++)  // as linhas demonstrando as laterais da pista
    {
        this->pista[i][1] = this->pista[i][maxX - 1] = LINHAS_LATERAIS;
    }

    for (int j = 0; j < SIZE_X; j++)  // as linhas inferiores demonstrando o comeco da pista
    {
        this->pista[maxY][j] = LINHAS_INFERIORES;
    }
}

void Pista::setCustomPista(int x, int y, char state) {
    this->pista[x][y] = state;
}

void Pista::setPistaItems(Pino *pinos[10], Bola *bola) {
    int qtdPerLines, initSpaces, initY, initX, x, y, qtdLinePines, pineIndex;

    bola->setPos(SIZE_X / 2 + 1, SIZE_Y - 2);
    pista[bola->getX()][bola->getY()] = BOLA;

    // coordenadas dos pinos
    qtdPerLines = 4;   // quantidade de pinos por linha
    initSpaces = 1;    // quantidade de espacos antes dos pinos
    initX = x = 4;     // onde comeca a aparecer os pinos nessa linha
    initY = y = 2;     // onde comeca a aparecer os pinos no board, numa posicao Y
    qtdLinePines = 4;  // quantas linhas de pinos vai ter
    pineIndex = 0;     // index do pino para o array

    // calcular as posicoes dos pinos
    for (int i = 0; i < qtdLinePines; i++) {
        for (int j = 0; j < qtdPerLines; j++) {
            pinos[pineIndex]->setPos(x, y);
            pista[y - 1][x - 1] = PINO_ERQUIDO;
            pineIndex++;
            x += 2;
        }
        qtdPerLines--;
        initX++;
        initY++;
        x = initX;
        y = initY;
    }
}

char Pista::getPista(int x, int y) {
    return this->pista[y][x];
}