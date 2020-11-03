#ifndef MACROS_CONSTANTES_H_INCLUDED
#define MACROS_CONSTANTES_H_INCLUDED

// Dificuldades
#define PERSON  0
#define FACIL   1
#define MEDIO   2
#define DIFICIL 3
#define EXTREMO 4

// Dimensoes do campo por dificuldade
#define QUANT_LIN_FACIL   9
#define QUANT_COL_FACIL   9

#define QUANT_LIN_MEDIO   16
#define QUANT_COL_MEDIO   16

#define QUANT_LIN_DIFICIL 24
#define QUANT_COL_DIFICIL 20

#define QUANT_LIN_EXTREMO 30
#define QUANT_COL_EXTREMO 24

// Constantes auxiliares (serao removidas)
#ifdef AUX
    #define Dimensoes_Facil   QUANT_LIN_FACIL, QUANT_COL_FACIL
    #define Dimensoes_Medio   QUANT_LIN_MEDIO, QUANT_COL_MEDIO
    #define Dimensoes_Dificil QUANT_LIN_DIFICIL, QUANT_COL_DIFICIL
    #define Dimensoes_Extremo QUANT_LIN_EXTREMO, QUANT_COL_EXTREMO
#endif

// Dimensoes maximas para o modo personalizado
#define MAX_LIN_PERSON 30
#define MAX_COL_PERSON 30

// Quantidade de Bombas por dificuldade
#define QUANT_BOMBAS_FACIL   10
#define QUANT_BOMBAS_MEDIO   40
#define QUANT_BOMBAS_DIFICIL 99
#define QUANT_BOMBAS_EXTREMO 180

// Quantidade maxima de Bombas para o modo personalizado
#define MAX_BOMBAS_PERSON 270

// Constantes importantes
#define PAREDE  -1

#define OCULTO   0
#define EXIBINDO 1

#define VAZIO    0
#define BOMBA    9

// Constantes de acesso a estrutura

// Constantes de acesso as dimensoes maximas das matrizes
#define ALTURA campoMinado->dimensoes.altura
#define LARGURA campoMinado->dimensoes.largura

// Macros de acesso a campo e visualizacao
#define campo(lin,col)        campoMinado->campo[lin][col]
#define visualizacao(lin,col) campoMinado->visualizacao[lin][col]

// Constante de acesso a dificuldade do jogo
#define DIFICULDADE campoMinado->dificuldade

// Constante de acesso a quantidade de bombas do jogo
#define QUANT_BOMBAS campoMinado->quantBombas

#endif /* MACROS_CONSTANTES_H_INCLUDED */