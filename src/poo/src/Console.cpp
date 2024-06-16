#include "headers/Console.hpp"

Console::Console() {
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
void Console::showBoard(char board[SIZE_Y][SIZE_X]) {
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}