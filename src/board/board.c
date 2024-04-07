#include <stdio.h>

// variaveis globais
#define SIZE_X 12
#define SIZE_X_LANE (SIZE_X - 4) // this exclude gutters and respective lines // REVER ISSO
#define SIZE_Y 32
#define SIZE_Y_LANE (SIZE_Y - 2) // this exclude top and bottom lines // REVER ISSO

char SIDE_LINES = '|';
char TOP_LINES = '_';
char BOTTOM_LINES = '=';

// posicoes para controladores
#define SPEED_Y 3
#define DIRECTION_Y 6
#define EFFECT_Y 9

typedef struct
{
    int x, y;
} coord;

typedef struct
{
    coord ball;
    coord pins[10];
} boardCoord;

typedef struct
{
    int speed;       // 1 (low) - 15 (high)
    float direction; // 1 (left) - 2 (middle) - 3(right)
    float effect;    // 1 (leftToRight) - 2 (noEffect) - 3 (rightToLeft)
} ballStatus;

// verificações para o sistema operacional
#ifdef linux // se o sistema operacional for um linux

// kbhit function
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
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
    printf("\033[%i;%iH", x, y);
};

void writeStringIn(int x, int y, char *str)
{
    moveCursorTo(x, y);
    printf("%s", str);
};

void swapStringPos(int x, int y, int newX, int newY, char *str, char *newStr)
{
    moveCursorTo(newX, newY);
    printf("%s", newStr);
    moveCursorTo(x, y);
    printf("%s", str);
};

void _sleep(float seconds)
{
    usleep(1000000 * seconds);
}

#endif

#ifndef _WIN32 // se o sistema operacional for windows

// ter as mesmas funcoes que no linux

#endif

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

// apenas para testes
int main()
{
    initiateConsole();
    char board[SIZE_Y][SIZE_X];
    setBoard(board);

    // showBoard(board);

    // test
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }

    while (!_kbhit())
    {
    }

    return 0;
}