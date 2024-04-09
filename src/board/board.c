#include <stdio.h>

// variaveis globais
#define SIZE_X 13
#define SIZE_X_LANE (SIZE_X - 4) // this exclude gutters and respective lines // REVER ISSO
#define SIZE_Y 32
#define SIZE_Y_LANE (SIZE_Y - 2) // this exclude top and bottom lines // REVER ISSO
#define LABELS_X (SIZE_X + 10)

char SIDE_LINES = '|';
char TOP_LINES = '_';
char BOTTOM_LINES = '=';
char BALL_CHAR = '*';
char PINE_UP_CHAR = '0';
char PINE_DOWN_CHAR = '>';

// posicoes para controladores
#define SPEED_Y 3
#define DIRECTION_Y 6
#define EFFECT_Y 9

typedef struct
{
    int x, y, speed, direction, effect;
} coordBall;

typedef struct
{
    int x, y, state;
} coordPine;

typedef struct
{
    coordBall ball;
    coordPine pins[10];
} boardCoord;

// REVER ISSO - apagar pq nao uso mais
// typedef struct
// {
//     int speed;       // 1 (low) - 15 (high)
//     float direction; // 1 (left) - 2 (middle) - 3(right)
//     float effect;    // 1 (leftToRight) - 2 (noEffect) - 3 (rightToLeft)
// } ballStatus;

// prototipacao para as funcoes especiais para cada sistema operacional
void moveCursorTo(int x, int y);
int _kbhit(void);
void initiateConsole();
void writeStringIn(int x, int y, char *str);
void swapBallPos(int x, int y, int newX, int newY);
void _sleep(float seconds);
void deleteLastChar();
void clearKeyboardBuffer();

// verificações para o sistema operacional
#ifdef linux // se o sistema operacional for um linux

// kbhit function
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio_ext.h>

int _kbhit(void)
{
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

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void initiateConsole()
{
    printf("\033[2J");   // like system("clear") // REVER ISSO
    printf("\033[0;0H"); // move to (0,0)
};

void moveCursorTo(int x, int y)
{
    printf("\033[%i;%iH", y, x);
};

void writeStringIn(int x, int y, char *str)
{
    moveCursorTo(x, y);
    printf("%s", str);
};

void swapBallPos(int x, int y, int newX, int newY)
{
    moveCursorTo(x, y);
    printf(" ");
    moveCursorTo(newX, newY);
    printf("%c", BALL_CHAR);
}

void _sleep(float seconds)
{
    usleep(1000000 * seconds);
}

void deleteLastChar()
{
    // old only work when space is the action button
    printf("\033[1D");
    printf(" ");
    printf("\033[1D");

    // new
    // printf("\033[2D");
    // printf("\033[K");
    // printf("\033[1C");
}

void clearKeyboardBuffer()
{
    __fpurge(stdin);
}

#endif

#ifndef _WIN32 // se o sistema operacional for windows

// ter as mesmas funcoes que no linux

#endif

void resetCursorPos()
{
    moveCursorTo(SIZE_X + 20, 0);
}

int randColisaoMult(int speed)
{
    int r;
    int maxProb = 80;
    int maxSpeed = 15;
    int prob = speed * (maxProb / maxSpeed);
    r = rand() % 100 + 1;
    if (r > prob)
    {
        return 0;
    }
    return 1;
}

void setBoard(char board[SIZE_Y][SIZE_X])
{
    int maxY = (SIZE_Y - 1);
    int maxX = (SIZE_X - 1);

    for (int i = 0; i < SIZE_Y; i++) // preenchendo a pista com espaços
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            board[i][j] = ' ';
        }
    }

    for (int j = 0; j < SIZE_X; j++) // as linhas superiores
    {
        board[0][j] = TOP_LINES;
    }

    for (int i = 1; i < (SIZE_Y - 1); i++) // as linhas demonstrando as laterais da pista
    {
        board[i][1] = board[i][maxX - 1] = SIDE_LINES;
    }

    for (int j = 0; j < SIZE_X; j++) // as linhas inferiores demonstrando o comeco da pista
    {
        board[maxY][j] = BOTTOM_LINES;
    }
}

void showBoard(char board[SIZE_Y][SIZE_X])
{
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void setBoardItems(char board[SIZE_Y][SIZE_X], boardCoord *coords)
{
    int qtdPerLines, initSpaces, initY, initX, x, y, qtdLinePines, pineIndex;

    // coordenadas das bolas
    coords->ball.x = SIZE_X / 2 + 1; // coloca a bola bem no meio do board
    coords->ball.y = SIZE_Y - 2;     // coloca a bola bem em baixo mas nao encostando no comeco da board
    board[coords->ball.x][coords->ball.y] = BALL_CHAR;

    // coordenadas dos pinos
    qtdPerLines = 4;  // quantidade de pinos por linha
    initSpaces = 1;   // quantidade de espacos antes dos pinos
    initX = x = 4;    // onde comeca a aparecer os pinos nessa linha
    initY = y = 2;    // onde comeca a aparecer os pinos no board, numa posicao Y
    qtdLinePines = 4; // quantas linhas de pinos vai ter
    pineIndex = 0;    // index do pino para o array

    // calcular as posicoes dos pinos
    for (int i = 0; i < qtdLinePines; i++)
    {
        for (int j = 0; j < qtdPerLines; j++)
        {
            coords->pins[pineIndex].x = x;
            coords->pins[pineIndex].y = y;
            board[y - 1][x - 1] = PINE_UP_CHAR;
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

void showControlLabels()
{
    // velocidade
    moveCursorTo(LABELS_X, SPEED_Y);
    printf("SPEED");

    // direcao
    moveCursorTo(LABELS_X, DIRECTION_Y);
    printf("DIRECTION");

    // efeito
    moveCursorTo(LABELS_X, EFFECT_Y);
    printf("EFFECT");

    resetCursorPos();
}

int getControlLoad(int x, int y)
{
    moveCursorTo(x, y);
    int mod, load, cont;
    mod = cont = 1;
    load = 0;
    printf("#");      // cxomo vai de 1 - 15 o primeiro # sempre esta ali
    while (!_kbhit()) // REVER ISSO - pode acontecer de encerrar o while logo depois de somar o load mas nao printar o #
    {
        if (mod == 1)
        {
            load++;
            printf("#");
        }
        else
        {
            load--;
            deleteLastChar();
        }
        if (cont == 14)
        {
            mod *= -1;
            cont = 0;
            load -= (2 * mod); // isso aqui existe para o load ser igual em dados e visualmente
        }
        cont++;
        _sleep(0.0625);
    }
    clearKeyboardBuffer();
    deleteLastChar();
    return load;
}

void showBoardItems(boardCoord coords)
{
    // printar os pinos
    for (int i = 0; i < 10; i++)
    {
        moveCursorTo(coords.pins[i].x, coords.pins[i].y);
        printf("%c", PINE_UP_CHAR);
    }

    // printar a bola
    moveCursorTo(coords.ball.x, coords.ball.y);
    printf("%c", BALL_CHAR);

    resetCursorPos();
}

void multipleCollision(char board[SIZE_Y][SIZE_X], int xPine, int yPine, int ballSpeed)
{
    if (yPine != 2) // se for 2 entao eh um pino na ultima linha
    {
        if (randColisaoMult(ballSpeed)) // se a colisao vai acontecer
        {
            // verificar se ha pinos nas diagonais e usar essa mesma funcao como recursiva, depois dela acabar eu desenho o novo pino depois do if(yPine != 2)
        }
    }
}

void renderGame(char board[SIZE_Y][SIZE_X], boardCoord *bCoord)
{
    coordBall newBall;
    float delaySleep;
    int randColisaoMult;                                  // randomiza um numero para colisao multipla (quando um pino derruba outro)
    while (bCoord->ball.speed > 0 && bCoord->ball.y != 1) // enquanto a bola permanecer em movimento
    {
        // calcular a posicao e atributos da nova bola

        // teste // REVER ISSO - apagar depois, isso eh apenas para testes
        newBall.x = bCoord->ball.x;
        newBall.y = bCoord->ball.y - 1; // sobre um pra cima
        // calcular as novas coordenadas

        // colisao
        if (board[newBall.y - 1][newBall.x - 1] == PINE_UP_CHAR) // se colidiu o pino se abaixa e a bola passa por ele
        {
            // escreve o pino como caido
            board[newBall.y - 1][newBall.x - 1] == PINE_DOWN_CHAR;
            moveCursorTo(newBall.x, newBall.y);
            printf("%c", PINE_DOWN_CHAR);
            resetCursorPos();

            // colisao dupla

            // move a nova bola para depois do pino
            newBall.y--;
            // diminui a velocidade da bola porque ela bateu no pico // REVER ISSO - mexer para a velocidade diminuir mais
            bCoord->ball.speed = bCoord->ball.speed / 2;
        }
        else // se nao colidiu
        {
        }

        // desenha a nova bola e apaga a antiga
        swapBallPos(bCoord->ball.x, bCoord->ball.y, newBall.x, newBall.y);

        // teste
        bCoord->ball.x = newBall.x;
        bCoord->ball.y = newBall.y;

        resetCursorPos();
        delaySleep = (60.0 / (128 * bCoord->ball.speed)); // quanto maior o numero multiplicando o speed, mais rapido sera
        printf("%f", delaySleep);
        printf("\n");
        _sleep(delaySleep); // o calculo da velocidade, no pior caso (speed = 1) sleep(1) e no melhor caso (speed = 15) sleep(0,5) // REVER ISSO - da pra fazer ficar mais veloz, so mexer no 4 para 8 e etc
        // _sleep(1);
    }

    // test
    moveCursorTo(1, SIZE_Y + 1);
    printf("terminou o jogo\t speed - %i\n", bCoord->ball.speed);
}

// apenas para testes
int main()
{
    initiateConsole();
    char board[SIZE_Y][SIZE_X];
    boardCoord bCoord;

    // inicia e mostra a pista
    setBoard(board);
    showBoard(board);

    // inicia e mostra os items da pista (bola e pinos)
    setBoardItems(board, &bCoord);
    showBoardItems(bCoord);

    // inicia e mostra os controladores
    showControlLabels();
    bCoord.ball.speed = getControlLoad(LABELS_X, SPEED_Y + 1);
    bCoord.ball.direction = getControlLoad(LABELS_X, DIRECTION_Y + 1);
    bCoord.ball.effect = getControlLoad(LABELS_X, EFFECT_Y + 1);

    renderGame(board, &bCoord);

    // test vars
    // moveCursorTo(1, SIZE_Y + 1);
    printf("speed - %i\ndirection - %i\neffect - %i\n", bCoord.ball.speed, bCoord.ball.direction, bCoord.ball.effect);
    // printf("x - %i\ny - %i\n", bCoord.ball.x, bCoord.ball.y);

    // _sleep(5);

    return 0;
}