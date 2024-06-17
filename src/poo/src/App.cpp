#include "headers/App.hpp"

App::App() {
}

App::~App() {
}

void App::atualizarPontuacaoMax(int points) {
    FILE *arquivo;
    int pontuacaoMaxima;

    // Abrir o arquivo
    arquivo = fopen(FILENAME, "r");
    if (arquivo == NULL) {
        // Se o arquivo não existir, criar um novo com a pontuação atual
        arquivo = fopen(FILENAME, "w");
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo.\n");
            exit(1);
        }
        fprintf(arquivo, "%d", points);
        fclose(arquivo);
        printf("Nova pontuação máxima salva no arquivo.\n");
        return;
    }

    // Ler a pontuação máxima atual do arquivo
    fscanf(arquivo, "%d", &pontuacaoMaxima);
    fclose(arquivo);

    // Verificar se a pontuação atual é maior do que a pontuação máxima
    if (points > pontuacaoMaxima) {
        // Abrir o arquivo para escrita e atualizar a pontuação máxima
        arquivo = fopen(FILENAME, "w");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo para atualização.\n");
            exit(1);
        }
        fprintf(arquivo, "%d", points);
        fclose(arquivo);
        printf("Nova pontuação máxima salva no arquivo.\n");
    } else {
        printf("Pontuação não ultrapassou a pontuação máxima atual.\n");
    }
}

void App::run() {

}

void App::playGame() {
    this->pista = new Pista();
    this->bola = new Bola(0, 0);
    for (int i = 0; i < 10; i++) {
        this->pinos[i] = new Pino(0, 0);
    }

    this->pista->setPista();
    this->console->showBoard(this->pista);

    this->pista->setPistaItems(this->pinos, this->bola);
    this->console->showBoardItems(this->pinos, this->bola);

    this->console->showControlLabels();
    printf(" ");

    this->bola->setAtributos(this->console->getControlLoad(LABELS_X, SPEED_Y + 1), this->console->getControlLoad(LABELS_X, DIRECTION_Y + 1), this->console->getControlLoad(LABELS_X, EFFECT_Y + 1));

    this->console->renderGame(this->pista, this->pinos, this->bola);

    for (int i = 0; i < 10; i++) {
        this->pinos[i]->~Pino();
    }
    this->bola->~Bola();
    this->pista->~Pista();
}

void App::end() {
    this->console->~Console();
    this->pista->~Pista();
    for (int i = 0; i < 10; i++) {
        this->pinos[i]->~Pino();
    }

}
void App::start() {
    this->console = new Console();

    srand(time(NULL));
    this->console->clearConsole();

    this->console->exibirInstrucoes();
    this->console->pressEnterCord(1, 10);

    this->console->initConsole();
    this->playGame();
    this->console->showPoints();
    this->console->pressEnter();

    this->console->initConsole();
    this->playGame();
    this->console->showPoints();
    

}