#ifndef TestBoard_h
#define TestBoard_h
#include <stdio.h>

#define SIZE_X 10
#define SIZE_X_LANE (SIZE_X - 4) // this exclude gutters and respective lines
#define SIZE_Y 64
#define SIZE_Y_LANE (SIZE_Y - 2) // this exclude top and bottom lines
#define SIDE_LINES '|'
#define TOP_LINES '_'
#define BOTTOM_LINES '='

// controls lines
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

void setBoard(char board[SIZE_X][SIZE_Y])
{
    int j;
    int i;
    // top line
    for (i = 0; i < SIZE_X; i++)
    {
        board[i][0] = TOP_LINES;
        printf("%c", TOP_LINES);
    }
    printf("\n");

    // middle
    for (j = 1; j < (SIZE_Y - 1); j++)
    {
        i = 0;
        board[i][j] = ' '; // left gutter space
        i++;
        board[i][j] = SIDE_LINES; // left gutter line
        i++;
        while (i < SIZE_X_LANE)
        {
            board[i][j] = ' ';
            i++;
        }
        board[i][j] = SIDE_LINES; // right gutter line
        i++;
        board[i][j] = ' '; // right gutter space
    }

    // bottom line
    i = 0;
    board[i][SIZE_Y - 1] = ' '; // left gutter space
    i++;
    board[i][SIZE_Y - 1] = SIDE_LINES; // left gutter line
    i++;
    while (i < SIZE_X_LANE)
    {
        board[i][j] = ' ';
        i++;
    }
    board[i][SIZE_Y - 1] = SIDE_LINES; // right gutter line
    i++;
    board[i][SIZE_Y - 1] = ' '; // right gutter space
}

void showSpeedLabel()
{
    printf("\t\t\t");
    printf("SPEED");
}

void showSpeedLoad(int speed)
{
    for (int i = 0; i < speed; i++)
    {
        printf("#");
    }
}

void showDirectionLabel()
{
    printf("\t\t\t");
    printf("DIRECTION");
}

void showDirectionLoad(float direction)
{
    float unit = 3 / 15; // how much value each direction charge (#) has
    float firstUnit = 1 + unit;
    for (float i = firstUnit; i <= direction; i += unit)
    {
        printf("#");
    }
}

void showEffectLabel()
{
    printf("\t\t\t");
    printf("EFFECT");
}

void showEffectLoad(float effect)
{
    float unit = 3 / 15; // how much value each effect charge (#) has
    float firstUnit = 1 + unit;
    for (float i = firstUnit; i <= effect; i += unit)
    {
        printf("#");
    }
}

void showBoard(char board[SIZE_X][SIZE_Y], ballStatus ballS)
{
    int line, collum;
    line = 0;
    while (line < (SPEED_Y - 1))
    { // write lines until line where controls show
        for (collum = 0; collum < SIZE_X; collum++)
        {
            printf("%c", board[line][collum]);
        }
        printf("\n");
        line++;
    }

    // write line with speed lable
    for (collum = 0; collum < SIZE_X; collum++)
    {
        printf("%c", board[line][collum]);
    }
    showSpeedLabel();
    printf("\n");
    line++;

    // write third line with speed load
    for (collum = 0; collum < SIZE_X; collum++)
    {
        printf("%c", board[line][collum]);
    }
    showSpeedLoad(ballS.speed);
    printf("\n");
    line++;

    // write four line, space between speed and direction
    for (collum = 0; collum < SIZE_X; collum++)
    {
        printf("%c", board[line][collum]);
    }
    printf("\n");
    line++;

    // write line with direction lable
    for (collum = 0; collum < SIZE_X; collum++)
    {
        printf("%c", board[line][collum]);
    }
    showDirectionLabel();
    printf("\n");
    line++;

    // write line with direction load
    for (collum = 0; collum < SIZE_X; collum++)
    {
        printf("%c", board[line][collum]);
    }
    showDirectionLoad(ballS.direction);
    printf("\n");
    line++;

    // write line, space between direction and effect
    for (collum = 0; collum < SIZE_X; collum++)
    {
        printf("%c", board[line][collum]);
    }
    printf("\n");
    line++;

    // write line with effect lable
    for (collum = 0; collum < SIZE_X; collum++)
    {
        printf("%c", board[line][collum]);
    }
    showEffectLabel();
    printf("\n");
    line++;

    // write line with effect load
    for (collum = 0; collum < SIZE_X; collum++)
    {
        printf("%c", board[line][collum]);
    }
    showEffectLoad(ballS.effect);
    printf("\n");
    line++;

    //...
}

void updateElements(char board[SIZE_X][SIZE_Y], boardCoord boardC, int typeUpdate) // typeUpdate - 1 (ball), 2 (pins), 3(two)
{
    if (typeUpdate == 2 || typeUpdate == 3) {
        // TODO percorre os pinos verificando posição e trocando se necessario
    }

    if (typeUpdate == 1 || typeUpdate == 3) {
        // TODO da um update na posição da bola
    }

    // TODO pensar se é legal ja mandar um renderizar aqui
}

// TODO fazer um update dos status (speed, direction, effect)

int main()
{

    return 1;
}

#endif