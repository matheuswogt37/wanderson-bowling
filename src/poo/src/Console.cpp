#include "headers/Console.hpp"

Console::Console() {
    this->points = 0;
    this->pinos_caidos = 0;
}

Console::~Console() {
}

int Console::_kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void Console::_sleep(float seconds) {
    usleep(1000000 * seconds);
}

void Console::clearKeyboardBuffer() {
    __fpurge(stdin);
}

void Console::initConsole() {
    clearConsole();
    printf("\033[0;0H");  // move to (0,0)
}

void Console::clearConsole() {
    printf("\033[1;1H\e[2J");
}

float Console::calcModDirection(int direction) {
    // ta vendo esse 7 na proxima linha, quanto mais alto, menos a direção vai fazer a bola se afastar das laterais, quero que vc execute o codigo e veja se ta bom assim, pode ser? dai eu ajeito um codigo la em baixo pra facilitar vc testar
    float mod = 1.0 / 14;  // 1 - quantidade maxima que a bola pode deslocar | 7 - intensidade que a direcao pode ter
    float res = mod;
    // verifica onde a direcao esta a partir do meio (8)
    if (direction > 8)  // vai para a direita
    {
        res = res * (direction - 8.0);  // menos 8 porque precisa saber quantas casas se deslocou para a direita
    } else if (direction < 8)           // vai para a esquerda
    {
        res *= -1.0;
        res += res * (8.0 - direction);  // o 8 ta ali para que os valores extermos como 1 tenha um valor maior que o 7 por exemplo

        // mod *= -1.0; // o -1 eh para que o modificador seja um numero negativo
    } else {
        res = 0;
    }

    return res;
}

float Console::calcModEffect(int &effect) {
    float mod = 1.0 / 21;  // quando for alterar o numero dividendo favor deixar um multiplo de 7 // REVER ISSO - talvez seja melhor mudar para um numero menor ainda, ver isso a partir da execucao
    float res = mod;

    if (effect > 8) {  // vai para a direita
        res = mod * (effect - 8.0);
        if (effect < 15) {  // aumenta o efeito para a direita
            effect = effect + 1;
        }
    } else if (effect < 8) {  // vai para a esquerda
        res = mod * (effect - 8.0);
        if (effect > 1) {
            effect = effect - 1;
        }
    } else {
        res = 0;
    }

    return res;
}

int Console::roundFUp(float number) {
    return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0);
}

int Console::randColisaoMult(int speed) {
    int r;
    int maxProb = 80;
    int maxSpeed = 15;
    int prob = speed * (maxProb / maxSpeed);
    r = rand() % 100 + 1;
    if (r > prob) {
        return 0;
    }
    return 1;
}

void Console::swapBallPos(int x, int y, int newX, int newY) {
    moveCursor(x, y);
    printf(" ");
    moveCursor(newX, newY);
    printf("%c", BOLA);
}

void Console::downAndMultipleCollision(Pista *pista, int xPine, int yPine, int ballSpeed) {
    pista->setCustomPista(xPine - 1, yPine - 1, PINO_CAIDO);
    moveCursor(xPine, yPine);
    printf("%c", PINO_CAIDO);
    this->points++;
    this->pinos_caidos++;
    resetCursorPos();
    if (yPine != 2)  // se for 2 entao eh um pino na ultima linha
    {
        if (randColisaoMult(ballSpeed))  // se a colisao para esquerda superior vai acontecer
        {
            // verificar se ha pinos nas diagonais e usar essa mesma funcao como recursiva, depois dela acabar eu desenho o novo pino depois do if(yPine != 2)
            if (pista->getPista(xPine - 1, yPine - 1))  // se tem uma bola na esquerda superior
            {
                downAndMultipleCollision(pista, xPine - 1, yPine - 1, ballSpeed);
            }
        }
        if (randColisaoMult(ballSpeed))  // se a colisao para direita superior vai acontecer
        {
            if (pista->getPista(xPine + 1, yPine + 1))  // se tem uma bola na esquerda superior
            {
                downAndMultipleCollision(pista, xPine + 1, yPine - 1, ballSpeed);
            }
        }
    }
}

// terminal
void Console::moveCursor(int x, int y) {
    printf("\033[%i;%iH", y, x);
}

void Console::writeStringIn(int x, int y, std::string str) {
    moveCursor(x, y);
    printf("%s", str);
}

void Console::deleteLastChar() {
    printf("\033[1D");
    printf(" ");
    printf("\033[1D");
}

void Console::resetCursorPos() {
    moveCursor(SIZE_X + 20, 0);
}

void Console::pressEnter() {
    moveCursor(2, SIZE_Y + 3);
    printf("Pressione Enter para continuar\n");
    while (getchar() != '\n');
    printf("\n");
}

void Console::pressEnterCord(int x, int y) {
    moveCursor(x, y);
    printf("Pressione Enter para continuar\n");
    while (getchar() != '\n');
    printf("\n");
}

int Console::getControlLoad(int x, int y) {
    moveCursor(x, y);
    int mod, load, cont;
    mod = cont = 1;
    load = 0;
    printf("#");       // cxomo vai de 1 - 15 o primeiro # sempre esta ali
    while (!_kbhit())  // REVER ISSO - pode acontecer de encerrar o while logo depois de somar o load mas nao printar o #
    {
        if (mod == 1) {
            load++;
            printf("#");
        } else {
            load--;
            deleteLastChar();
        }
        if (cont == 14) {
            mod *= -1;
            cont = 0;
            load -= (2 * mod);  // isso aqui existe para o load ser igual em dados e visualmente
        }
        cont++;
        _sleep(0.0625);
    }
    clearKeyboardBuffer();
    deleteLastChar();
    return load;
}

void Console::renderGame(Pista *pista, Pino *pinos[10], Bola *bola) {
    this->pinos_caidos = 0;
    Bola newBall(0, 0);
    float delaySleep;
    float modDirection;  // modificador da direcao
    float modEffect;     // modificador do efeito
    float xFloat;
    int randColisaoMult;  // randomiza um numero para colisao multipla (quando um pino derruba outro)

    xFloat = 0;
    while (bola->getVelocidade() > 0 && bola->getY() > 1)  // enquanto a bola permanecer em movimento
    {
        int temp = bola->getEfeito();
        modEffect = calcModEffect(temp);
        modDirection = calcModDirection(bola->getDirecao());
        xFloat += modDirection;
        xFloat += xFloat + modEffect;
        newBall.setPos(newBall.getX(), bola->getY() - 1);

        // calcular as novas coordenadas
        // effect
        if (xFloat < 0)  // esquerda
        {
            // verificar se o xFloat passou de 1
            if (xFloat > 1)  // se vai avancar mais de um quadrado para a direita
            {
                xFloat = 1;
            } else if (xFloat < -1)  // se vai avancar mais de um quadrado para a esquerda
            {
                xFloat = -1;
            }
            newBall.setPos(bola->getX() + roundFUp(xFloat), newBall.getY());
        } else if (xFloat > 0)  // direita
        {
            // verificar se o xFloat passou de 1
            if (xFloat > 1)  // se vai avancar mais de um quadrado para a direita
            {
                xFloat = 1;
            } else if (xFloat < -1)  // se vai avancar mais de um quadrado para a esquerda
            {
                xFloat = -1;
            }
            newBall.setPos(bola->getX() + xFloat, newBall.getY());
        }

        // verificar se ela bate no final da linha
        if (newBall.getX() == SIZE_X - 1)  // bateu na linha direita
        {
            bola->setAtributos(bola->getVelocidade(), (16 - bola->getDirecao()), bola->getEfeito() - 8);
            xFloat *= -1.0;
            newBall.setPos(newBall.getX() - 2, newBall.getY());
        } else if (newBall.getX() == 2)  // bateu na linha esquerda
        {
            bola->setAtributos(bola->getVelocidade(), (16 - bola->getDirecao()), bola->getEfeito() + 8);
            xFloat *= -1.0;
            newBall.setPos(newBall.getX() + 2, newBall.getY());
        }

        // verificar colisao de pino
        if (pista->getPista(newBall.getX() - 1, newBall.getY() - 1) == PINO_ERQUIDO)  // se colidiu o pino se abaixa e a bola passa por ele
        {
            // derruba o pino e verifica se houve colisao dupla
            downAndMultipleCollision(pista, newBall.getX(), newBall.getY(), bola->getVelocidade());

            // move a nova bola para depois do pino
            newBall.setPos(newBall.getX(), newBall.getY()-1);
            // diminui a velocidade da bola porque ela bateu no pico // REVER ISSO - mexer para a velocidade diminuir mais
            bola->setAtributos(bola->getVelocidade() / 2, bola->getDirecao(), bola->getEfeito());

        } else if (pista->getPista(newBall.getX() - 1 , newBall.getY() - 1) == PINO_CAIDO)  // se colidiu com um pino /derrubado
        {
            // move a nova bola para depois do pino
            newBall.setPos(newBall.getX(), newBall.getY()-1);
            // diminui a velocidade da bola porque ela bateu no pico // REVER ISSO - mexer para a velocidade diminuir mais
            bola->setAtributos(bola->getVelocidade() / 2, bola->getDirecao(), bola->getEfeito());
        }

        // desenhar a nova bola e atribuir os novos valores a bola
        swapBallPos(bola->getX(), bola->getY(), newBall.getX(), newBall.getY());
        bola->setPos(newBall.getX(), newBall.getY());
        if (xFloat == -1 || xFloat == 1) {
            xFloat = 0;
        }
        resetCursorPos();
        delaySleep = (60.0 / (SLEEP_MOD * bola->getVelocidade()));  // quanto maior o numero multiplicando o speed, mais rapido sera
        printf("%f", delaySleep);
        printf("\n");
        _sleep(delaySleep);  // o calculo da velocidade, no pior caso (speed = 1) sleep(1) e no melhor caso (speed = 15) sleep(0,5) // REVER ISSO - da pra fazer ficar mais veloz, so mexer no 4 para 8 e etc
    }

    if (this->pinos_caidos == 10)  // strike = +5 pontos
    {
        this->points += 5;
        if (this->points == 30)  // se na primeira rodada vc fez strike e nessa tb, entao leva mais pontos extra
        {
            this->points += 10;
        }
    }
}

void Console::exibirInstrucoes() {
    printf("\n===== Instruções do Jogo de Boliche =====\n");
    printf("1. O jogo de boliche consiste em 2 tentativas.\n");
    printf("2. Cada pino derrubado tem um valo de 1 ponto.\n");
    printf("3. Se derrubar todos os pinos em uma tentativa, isso é um 'strike' e você ganha 5 pontos extras.\n");
    printf("4. Se derrubar todos os pinos duas vezes seguidas, isso é um 'spare' e você ganha 10 pontos extras.\n");
    printf("5. Se não derrubar todos os pinos em duas tentativas, você ganha a quantidade de pontos equivalentes aos pinos derrubados.\n");
    printf("6. Após cada jogo, sua pontuação máxima será salva e exibida se for um novo recorde.\n");
    printf("=========================================\n\n");
}

void Console::printSizeControlLoads(int y) {
    moveCursor(LABELS_X - 1, y + 1);
    printf("|");
    moveCursor(LABELS_X + 1 + 15, y + 1);
    printf("|");
}

void Console::showBoard(Pista *pista) {
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            printf("%c", pista->getPista(j, i));
        }
        printf("\n");
    }
}

void Console::showBoardItems(Pino *pinos[10], Bola *bola) {
    for (int i = 0; i < 10; i++) {
        this->moveCursor(pinos[i]->getX(), pinos[i]->getY());
        printf("%c", PINO_ERQUIDO);
    }

    this->moveCursor(bola->getX(), bola->getY());
    printf("%c", BOLA);

    this->resetCursorPos();
}

void Console::showPoints() {
    moveCursor(1, SIZE_Y + 1);
    printf("Pontuacao obtida - %i\n", this->points);
}

void Console::showControlLabels() {
    // velocidade
    moveCursor(LABELS_X, SPEED_Y);
    printf("SPEED");
    printSizeControlLoads(SPEED_Y);

    // direcao
    moveCursor(LABELS_X, DIRECTION_Y);
    printf("DIRECTION");
    printSizeControlLoads(DIRECTION_Y);

    // efeito
    moveCursor(LABELS_X, EFFECT_Y);
    printf("EFFECT");
    printSizeControlLoads(EFFECT_Y);

    resetCursorPos();
}