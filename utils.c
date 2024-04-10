
functCalcEffect(int effect) { //esquerda para direita
    /*
    effect = 1 vai da esquerda para direita
    effect = 2 fica no meio até o final (sem nenhum efeito)
    effect = 3 vai da direita para esquerda
    //0,34 para o effect -> 0,34 + 0,34 + 0,34 = 1,02
    */
    float calcEffect;
    if (effect == 1) //vai da esquerda para direita
    {
        calcEffect = effect + 0,34
        coords->ball.x = SIZE_X / 2 + calcEffect;
        coords->ball.y = SIZE_Y - 2;
        board[coords->ball.x][coords->ball.y] = BALL_CHAR;
    } else if(effect == 2) //fica sem efeito
    {
        coords->ball.x = SIZE_X / 2 + 1;
        coords->ball.y = SIZE_Y - 2;
        board[coords->ball.x][coords->ball.y] = BALL_CHAR;
    } else(effect == 3) //vai da direita para esquerda
    {
        coords->ball.x = SIZE_X / 2 - calcEffect; 
        coords->ball.y = SIZE_Y - 2;
        board[coords->ball.x][coords->ball.y] = BALL_CHAR;
    }
}

functCalcDirection(int direction) {

    if(direction == 1) //left
    {
        coords->ball.x = SIZE_X / 2 - 3;
        coords->ball.y = SIZE_Y - 2;
        board[coords->ball.x][coords->ball.y] = BALL_CHAR;
    }

    if(direction == 2) //middle
    {
        coords->ball.x = SIZE_X / 2 + 1;
        coords->ball.y = SIZE_Y - 2;
        board[coords->ball.x][coords->ball.y] = BALL_CHAR;
    }

    if(direction == 3) //right
    {
        coords->ball.x = SIZE_X / 2 + 3;
        coords->ball.y = SIZE_Y - 2;
        board[coords->ball.x][coords->ball.y] = BALL_CHAR;
    }

}