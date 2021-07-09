#ifndef CAMPOMINADO_H_INCLUDED
#define CAMPOMINADO_H_INCLUDED

// Bibliotecas incluidas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "macros-constantes.h"

/**
 * @author: David Gomesh
 * @author: Lucas Nadler 
 * 
 * Documentação: https://github.com/DavidGomesh/campo-minado-c
*/

// Declaracao de estruturas

// Estrutura de coordenadas
typedef struct tipo_coordenadas{
    int lin;
    int col;
}Coordenadas;

// 
typedef struct tipo_dimensoes{
    int altura;
    int largura;
}Dimensoes;

// Estrutura do jogo
typedef struct tipo_jogo{
    int campo[30][30];          //Armazenas as bombas e os numeros
    int visualizacao[30][30];   //Controla o que sera exibido
    int dificuldade;            //Controla a dificuldade do jogo
    int quantBombas;            //Controla a quantidade de bombas no jogo
    bool fimDeJogo;             //Controla se o jogo foi encerrado 
    bool jogoGanho;             //Controla se o jogo foi ganho ou perdido
    Coordenadas posicaoConsole; //Define onde o campo estara no console
    Dimensoes dimensoes;        //Define o tamanho do jogo
}Jogo;

// Declaração de funcoes

// Define a dificuldade do jogo
void definirDificuldade(Jogo * campoMinado, int dificuldade);
void definirDificuldadePerson(Jogo * campoMinado, Dimensoes dimensoes, int quantBombas); //Modo personalizado

// Preparacao das matrizes pra receber valores
void inicializarVisualizacao(Jogo * campoMinado); //Usada pra reiniciar o jogo
void inicializarMatrizes    (Jogo * campoMinado);
void gerarParedes           (Jogo * campoMinado);

// Alimentacao do campo com os valores do jogo
void gerarBombas (Jogo * campoMinado);
void gerarNumeros(Jogo * campoMinado);

// Controladora da inicializacao: inicializa as variaveis do jogo
void incializarCampoMinado(Jogo * campoMinado);
void reincializarCampoMinado(Jogo * campoMinado); //Reinicia o jogo

// Trabalham com a visualizacao do jogo
void exibirCampo    (Jogo * campoMinado);
void revelarBombas  (Jogo * campoMinado);
void analisarEspacos(Jogo * campoMinado, Coordenadas coord);

int fazerJogada(Jogo * campoMinado);

#endif /*CAMPOMINADO_H_INCLUDED */