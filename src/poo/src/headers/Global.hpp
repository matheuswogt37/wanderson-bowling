
//* pinos
const char PINO_ERQUIDO = '|';
const char PINO_CAIDO = '$';

//* bola
const char BOLA = '*';

//* pista
const char LINHAS_LATERAIS = '|';
const char LINHAS_SUPERIORES = '_';
const char LINHAS_INFERIORES = '=';

#define SIZE_X 13
#define SIZE_X_LANE (SIZE_X - 4)  // this exclude gutters and respective lines // REVER ISSO
#define SIZE_Y 16
#define SIZE_Y_LANE (SIZE_Y - 2)  // this exclude top and bottom lines // REVER ISSO
#define LABELS_X (SIZE_X + 10)
#define SLEEP_MOD 128  // quanto maior, mais rapido o sleep sera
#define FILENAME "pontuacao.txt"