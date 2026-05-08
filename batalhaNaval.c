#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    /*//declaração de variaveis e arrays
    char colunas[10] = {'A','B','C','D','E','F','G','H','I','J'};
    int tabuleiro[10][10];
    int navioH[3] = {3,3,3};
    int navioV[3] = {3,3,3};

    //inicialização do tabuleiro com os valores de "água"
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            tabuleiro[i][j] = 0;
        }
    }

    //posicionamento dos navios na matriz do tabuleiro
    for (int i = 0; i < 10; i++){
        for (int j = 0; j<10; j++){
            if (i == 0 && j < 3){
                tabuleiro[i][j] = navioH[j];
            }

            if (j == 9 && i < 3){
                tabuleiro[i][j] = navioV[i];
            }
        }
    }

    //print do tabuleiro no console
    for (int i = 0; i <= 10; i++){
        printf("  %c ", colunas[i]);
    }
    printf("\n");
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (j == 0){
                printf("%d ", i + 1);
            }
            printf("[%d] ", tabuleiro[i][j]);
        }
        printf("\n");
    }*/

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

     //declaração de variaveis e arrays
    char colunas[10] = {'A','B','C','D','E','F','G','H','I','J'};
    int tabuleiro[10][10];

    //inicialização do tabuleiro com os valores de "água"
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            tabuleiro[i][j] = 0;
        }
    }

    //posicionamento dos navios na matriz do tabuleiro
    for (int i = 0; i < 10; i++){
        for (int j = 0; j<10; j++){
            //primeiro navio diagonal (b2,c3,d4)
            if (i == j && i > 0 && i< 4){
                //validação de sobreposição dos navios
                if( tabuleiro[i][j] == 0 ){
                    tabuleiro[i][j] = 3;
                } else {
                    printf("Posição inválida os navios se sobrepõem");
                }
                
            }

            //segundo navio diagonal(c8,b9,a10)
            if (i + j == 9 && i > 6){
                if( tabuleiro[i][j] == 0 ){
                    tabuleiro[i][j] = 3;
                } else {
                    printf("Posição inválida os navios se sobrepõem");
                }
            }

            //navio horizontal (g4,h4,i4)
            if (i == 4 && j > 5 && j < 9){
                if( tabuleiro[i][j] == 0 ){
                    tabuleiro[i][j] = 3;
                } else {
                    printf("Posição inválida os navios se sobrepõem");
                }
            }

             //navio vertical (j7,j8,j9)
            if (j == 9 && i > 6){
                if( tabuleiro[i][j] == 0 ){
                    tabuleiro[i][j] = 3;
                } else {
                    printf("Posição inválida os navios se sobrepõem");
                }
            }
        }
    }

    //print do tabuleiro no console
    for (int i = 0; i <= 10; i++){
        printf("  %c ", colunas[i]);
    }
    printf("\n");
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (j == 0){
                printf("%d ", i + 1);
            }
            printf("[%d] ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    return 0;
}
