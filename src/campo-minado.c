#ifndef CAMPO_MINADO_C_INCLUDED
#define CAMPO_MINADO_C_INCLUDED

#include "campo-minado.h"
#include "console.h"

// Define a dificuldade, no modo padrao de definicao
void definirDificuldade(Jogo * campoMinado, int dificuldade){
    DIFICULDADE = dificuldade;

    switch(dificuldade){
        case FACIL:
            ALTURA  = QUANT_LIN_FACIL;
            LARGURA = QUANT_COL_FACIL;

            QUANT_BOMBAS = QUANT_BOMBAS_FACIL;
            break;

        case MEDIO:
            ALTURA  = QUANT_LIN_MEDIO;
            LARGURA = QUANT_COL_MEDIO;

            QUANT_BOMBAS = QUANT_BOMBAS_MEDIO;
            break;

        case DIFICIL:
            ALTURA  = QUANT_LIN_DIFICIL;
            LARGURA = QUANT_COL_DIFICIL;

            QUANT_BOMBAS = QUANT_BOMBAS_DIFICIL;
            break;

        case EXTREMO:
            ALTURA  = QUANT_LIN_EXTREMO;
            LARGURA = QUANT_COL_EXTREMO;

            QUANT_BOMBAS = QUANT_BOMBAS_EXTREMO;
            break;
        
        default:
            ALTURA  = QUANT_LIN_FACIL;
            LARGURA = QUANT_COL_FACIL;

            DIFICULDADE = FACIL;
            QUANT_BOMBAS = QUANT_BOMBAS_FACIL;
            printf("Erro ao definir a dificuldade!\nDificuldade 'FACIL' atribudia!\n");
            break;
    }
}

// Define a dificuldade, no modo personalizado de definicao 
void definirDificuldadePerson(Jogo * campoMinado, Dimensoes dimensoes, int quantBombas){
    DIFICULDADE = PERSON;

    ALTURA = dimensoes.altura;
    LARGURA = dimensoes.largura;

    QUANT_BOMBAS = quantBombas;
}

// Zera todas as posicoes da visualizacao
void inicializarVisualizacao(Jogo * campoMinado){
    for(int lin=1; lin<ALTURA-1; lin++){
        for(int col=1; col<LARGURA-1; col++){
            visualizacao(lin, col) = OCULTO;
        }
    }
}

// Zera todas as posicoes das matrizes
void inicializarMatrizes(Jogo * campoMinado){
    for(int lin=1; lin<ALTURA-1; lin++){
        for(int col=1; col<LARGURA-1; col++){
            campo(lin, col)        = VAZIO;
            visualizacao(lin, col) = OCULTO;
        }
    }
}

// Colocas as paredes nas matrizes
void gerarParedes(Jogo * campoMinado){
    for(int lin=0; lin<ALTURA; lin++){ //Percorrera todas as linhas
        if(lin==0 || lin==ALTURA-1){ //Se for a primeira ou a ultima, coloca as paredes em toda linha
            for(int col=0; col<LARGURA; col++){
                campo(lin, col)          = PAREDE;
                visualizacao(lin, col)   = PAREDE;
            }
        }
        else{ //Senao, coloca as paredes apenas na primeira e na ultima coluna
            campo(lin, 0)                = PAREDE;
            visualizacao(lin, 0)         = PAREDE;

            campo(lin, LARGURA-1)        = PAREDE;
            visualizacao(lin, LARGURA-1) = PAREDE;
        }
    }    
}

// Gera as bombas do jogo
void gerarBombas(Jogo * campoMinado){
    int quantBombas=0, numAleatorio;
    int lin, col;

    while(quantBombas < QUANT_BOMBAS){
        //Gera posicoes aleatorias entre 1 e a posicao maxima
        lin = 1 + rand() % ALTURA-2;
        col = 1 + rand() % LARGURA-2;

        if(campo(lin, col) == VAZIO){ //Se nao tiver bomba, coloca uma bomba
            campo(lin, col) = BOMBA; //9 == Bomba
            quantBombas++;
        }
    }
}

// Gera os numeros que indicam a quantidade de bombas ao redor deles
void gerarNumeros(Jogo * campoMinado){
    int quantBombas;

    //Percorre todo o campo
    for(int lin=1; lin<ALTURA-1; lin++){
        for(int col=1; col<LARGURA-1; col++){

            if(campo(lin, col) != BOMBA){ //Se nao tiver bombas
                quantBombas=0;

                //Percorre em volta do local selecionado
                for(int i=lin-1; i<=lin+1; i++){
                    for(int j=col-1; j<=col+1; j++){

                        if(campo(i, j) == BOMBA){ //Se no local atual tiver bombas
                            quantBombas++; //Aumenta a quantidade de bombas encontradas
                        }

                    }
                }

                //Coloca a quantidade de bombas encontradas no local selecionado
                campo(lin, col) = quantBombas;
            }

        }
    }
}

// Faz todos os procedimentos necessarios para inicializar o jogo
void incializarCampoMinado(Jogo * campoMinado){
    inicializarMatrizes(campoMinado);
    gerarParedes(campoMinado);
    gerarBombas(campoMinado);
    gerarNumeros(campoMinado);

    campoMinado->jogoGanho = false;
    campoMinado->fimDeJogo = false;

    campoMinado->posicaoConsole.lin = 5;
    campoMinado->posicaoConsole.col = 15;
}

// Faz todos os procedimentos necessarios para reiniciar o jogo
void reincializarCampoMinado(Jogo * campoMinado){
    inicializarVisualizacao(campoMinado);

    campoMinado->jogoGanho = false;
    campoMinado->fimDeJogo = false;
}

// Exibe o campo minado todo formatado/personalizado
void exibirCampo(Jogo * campoMinado){
    //Percorre toda a matriz do campo
    //Tera uma linha a mais na exibicao, pois deve haver espacos para os numeros
    //E
    for(int lin=-1; lin<ALTURA; lin++){
        for(int col=0; col<LARGURA; col++){

            // Sleep(100);

            //Coloca o cursor na posicoes que o campo minado deve estar
            if(col==0){
                if(lin==-1){
                    gotoxy(
                        campoMinado->posicaoConsole.col, 
                        campoMinado->posicaoConsole.lin
                    );
                }
                else{
                    gotoxy(
                        campoMinado->posicaoConsole.col, 
                        campoMinado->posicaoConsole.lin + lin+1
                    );
                }
            }

            //Caso o numero de linhas fique maior que 9, move uma casa para a esquerda para caber as dezenas
            if(lin>9 && col==0 && lin != ALTURA-1){
                gotoxy(
                    campoMinado->posicaoConsole.col-1, 
                    campoMinado->posicaoConsole.lin + lin+1
                );
            }

            //Coloca os numeros das colunas na primeira linha da exibicao
            if(lin==-1){
                if(col>0&&col<LARGURA-1){
                    printf("%i ", col);
                }
                else{
                    printf("   ");
                }

                continue;
            }
            
            /* BORDAS */
            //Canto superior esquerdo
            if(lin==0 && col==0){
                printf(" %c%c", 201, 205);
                continue;
            }

            //Canto superior direito
            if(lin==0 && col==LARGURA-1){
                printf("%c", 187);
                continue;
            }

            //Canto inferior direito
            if(lin==ALTURA-1 && col==LARGURA-1){ 
                printf("%c", 188);
                continue;
            }

            //Canto inferior esquerdo
            if(lin==ALTURA-1 && col==0){ 
                printf(" %c%c", 200, 205);
                continue;
            }
            
            /* BARRAS */
            // Barras horizontais
            if((col>0 && col<LARGURA-1) && (lin==0 || lin==ALTURA-1)){
                printf("%c%c", 205, 205);
                continue;
            }

            // Barras verticais
            if((lin>0 && lin<ALTURA-1) && (col==0 || col==LARGURA-1)){ 
                if(col==LARGURA-1){
                    printf("%c ", 186);
                }
                else{
                    //Aproveita para colocar o numero das linhas
                    printf("%i%c ", lin, 186);
                }

                continue;
            }

            /* CONTEUDO DA MATRIZ */
            //Se estiver aberto para mostrar
            if(visualizacao(lin, col) == EXIBINDO){

                //Se tiver bomba
                if(campo(lin, col)==BOMBA){
                    textcolor(RED);
                    printf("%c ", 207);
                    textcolor(LIGHTGREEN);
                }
                // Se tiver numeros
                else{
                    printf("%i ", campo(lin, col));
                }

                continue;
            }

            //Se estiver oculto
            if(visualizacao(lin, col)==OCULTO){
                printf("%c ", 254);
                continue;
            }
        }

        printf("\n");
    }
}

// Revela a posicao de todas as bombas do jogo
void revelarBombas(Jogo * campoMinado){
    //Percorre toda a matrix procurando as bombas
    for(int lin=1; lin<ALTURA; lin++){
        for(int col=1; col<LARGURA; col++){

            if(campo(lin, col)==BOMBA){
                visualizacao(lin, col) = EXIBINDO;
            }
        }
    }
}

// Analisa os espacos a serem exibidos apos uma jogada
void analisarEspacos(Jogo * campoMinado, Coordenadas coord){
    int i, j;
    //Percorre em volta do local selecionado
    for(i=coord.lin-1; i<=coord.lin+1; i++){
        for(j=coord.col-1; j<=coord.col+1; j++){
            //Se o local atual estiver vazio
            if(campo(i, j)==VAZIO){
                //Se a visualizacao estiver oulta
                if(visualizacao(i, j)==OCULTO){
                    visualizacao(i, j) = EXIBINDO;

                    Coordenadas novasCoord;
                    novasCoord.lin = i;
                    novasCoord.col = j;

                    //Chama novamente, para um nova analise em um nova posicao
                    analisarEspacos(campoMinado, novasCoord);
                }
            }
            //Apenas exibe se nao for uma bomba ou um numero diferente de zero
            else if(campo(i, j)!=BOMBA){
                visualizacao(i, j) = EXIBINDO;
            }
        }
    }
}

// Inicia uma nova jogada e retorna algo com base na jogada
int fazerJogada(Jogo * campoMinado){
    int lin, col;

    printf("Informe a linha: ");
    scanf("%i", &lin);

    printf("Informe a coluna: ");
    scanf("%i", &col);

    //Verifica se foi digitado as posicoes de saida
    if(lin==0 && col==0){
        revelarBombas(campoMinado);
        return -2;
    }

    //Verifica se eh uma coordenada invalida
    if(lin <= 0 || col <= 0 || lin >= ALTURA-1 || col >= LARGURA-1){
        return -1;
    }

    //Verifica se eh uma bomba
    if(campo(lin, col) == BOMBA){
        revelarBombas(campoMinado);
        return 0;
    }

    //Verifica se o local esta vazio
    if(campo(lin, col) == VAZIO){
        visualizacao(lin, col) = EXIBINDO;

        //Cria variaveis para enviar as coordenadas
        Coordenadas coord;
        coord.lin = lin;
        coord.col = col;

        //Envia as coordenadas para analise
        analisarEspacos(campoMinado, coord);
        return 1;
    }

    //Verifica se tem um numero diferente de zero
    if(campo(lin, col) >= 1 || campo(lin, col) <= 8){
        visualizacao(lin, col) = EXIBINDO;
        return 1;
    }

}

#endif /* CAMPO_MINADO_C_INCLUDED */