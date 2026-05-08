/*
 * Batalha Naval - Nível Avançado
 * Habilidades especiais com áreas de efeito: Cone, Cruz e Octaedro
 *
 * Valores do tabuleiro:
 *   0 = Água
 *   3 = Navio
 *   5 = Área afetada pela habilidade
 */
 
#include <stdio.h>
 
/* Dimensões do tabuleiro principal */
#define TAM_TABULEIRO 10
 
/* Tamanho das matrizes de habilidade (5x5) */
#define TAM_HABILIDADE 5
 
/* Valores usados no tabuleiro */
#define AGUA      0
#define NAVIO     3
#define HABILIDADE 5
 
/* Exibe o tabuleiro no console usando caracteres distintos */
void exibir_tabuleiro(int tab[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n   ");
    for (int c = 0; c < TAM_TABULEIRO; c++) printf("%2d", c);
    printf("\n");
 
    for (int l = 0; l < TAM_TABULEIRO; l++) {
        printf("%2d ", l);
        for (int c = 0; c < TAM_TABULEIRO; c++) {
            if (tab[l][c] == AGUA)
                printf(" ~");          /* água */
            else if (tab[l][c] == NAVIO)
                printf(" N");          /* navio */
            else if (tab[l][c] == HABILIDADE)
                printf(" *");          /* área de efeito */
        }
        printf("\n");
    }
    printf("\nLegenda:  ~ = Água   N = Navio   * = Área de efeito\n\n");
}
 
/*
 * Constrói a habilidade CONE (5x5).
 * O cone aponta para baixo: na linha 0 há 1 célula afetada (centro),
 * e a largura aumenta a cada linha até cobrir toda a linha 4.
 *
 * Exemplo (5x5):
 *   0 0 1 0 0
 *   0 1 1 1 0
 *   1 1 1 1 1
 *   (apenas 3 linhas visíveis no enunciado, mas usamos 5 para melhor efeito)
 */
void construir_cone(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
 
    for (int l = 0; l < TAM_HABILIDADE; l++) {
        for (int c = 0; c < TAM_HABILIDADE; c++) {
            /*
             * Na linha l, a "meia-largura" afetada cresce de 0 até centro.
             * Uma célula é afetada se sua distância horizontal ao centro
             * for menor ou igual à linha atual.
             */
            int dist_horizontal = c - centro;
            if (dist_horizontal < 0) dist_horizontal = -dist_horizontal;
 
            if (dist_horizontal <= l)
                hab[l][c] = 1;
            else
                hab[l][c] = 0;
        }
    }
}
 
/*
 * Constrói a habilidade CRUZ (5x5).
 * A cruz tem o centro no meio da matriz e se expande
 * horizontalmente e verticalmente por toda a extensão.
 *
 * Exemplo (5x5):
 *   0 0 1 0 0
 *   0 0 1 0 0
 *   1 1 1 1 1
 *   0 0 1 0 0
 *   0 0 1 0 0
 */
void construir_cruz(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
 
    for (int l = 0; l < TAM_HABILIDADE; l++) {
        for (int c = 0; c < TAM_HABILIDADE; c++) {
            /* Afeta a linha central OU a coluna central */
            if (l == centro || c == centro)
                hab[l][c] = 1;
            else
                hab[l][c] = 0;
        }
    }
}
 
/*
 * Constrói a habilidade OCTAEDRO / LOSANGO (5x5).
 * Vista frontal de um octaedro resulta em um losango.
 * Uma célula é afetada se a soma das distâncias ao centro
 * (distância de Manhattan) for menor ou igual ao raio.
 *
 * Exemplo (5x5, raio=2):
 *   0 0 1 0 0
 *   0 1 1 1 0
 *   1 1 1 1 1
 *   0 1 1 1 0
 *   0 0 1 0 0
 */
void construir_octaedro(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    int raio   = TAM_HABILIDADE / 2;
 
    for (int l = 0; l < TAM_HABILIDADE; l++) {
        for (int c = 0; c < TAM_HABILIDADE; c++) {
            /* Distância de Manhattan até o centro */
            int dist_l = l - centro;
            int dist_c = c - centro;
            if (dist_l < 0) dist_l = -dist_l;
            if (dist_c < 0) dist_c = -dist_c;
 
            if (dist_l + dist_c <= raio)
                hab[l][c] = 1;
            else
                hab[l][c] = 0;
        }
    }
}
 
/*
 * Sobrepõe uma matriz de habilidade ao tabuleiro,
 * centrando-a na posição (orig_linha, orig_col).
 * Somente posições válidas (dentro do tabuleiro) são marcadas.
 * Navios (valor 3) não são sobrescritos.
 */
void aplicar_habilidade(int tab[TAM_TABULEIRO][TAM_TABULEIRO],
                        int hab[TAM_HABILIDADE][TAM_HABILIDADE],
                        int orig_linha, int orig_col) {
    int offset = TAM_HABILIDADE / 2; /* deslocamento do centro da matriz */
 
    for (int l = 0; l < TAM_HABILIDADE; l++) {
        for (int c = 0; c < TAM_HABILIDADE; c++) {
            if (hab[l][c] == 1) {
                /* Calcula a posição correspondente no tabuleiro */
                int tab_l = orig_linha + (l - offset);
                int tab_c = orig_col  + (c - offset);
 
                /* Verifica se está dentro dos limites do tabuleiro */
                if (tab_l >= 0 && tab_l < TAM_TABULEIRO &&
                    tab_c >= 0 && tab_c < TAM_TABULEIRO) {
                    /* Não sobrescreve navios */
                    if (tab[tab_l][tab_c] != NAVIO)
                        tab[tab_l][tab_c] = HABILIDADE;
                }
            }
        }
    }
}
 
int main(void) {
    /* ------------------------------------------------------------------ */
    /* 1. Inicializa o tabuleiro com água                                  */
    /* ------------------------------------------------------------------ */
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
 
    for (int l = 0; l < TAM_TABULEIRO; l++)
        for (int c = 0; c < TAM_TABULEIRO; c++)
            tabuleiro[l][c] = AGUA;
 
    /* ------------------------------------------------------------------ */
    /* 2. Posiciona navios no tabuleiro                                    */
    /*    (herdado dos níveis anteriores – posições fixas no código)       */
    /* ------------------------------------------------------------------ */
 
    /* Navio horizontal de tamanho 4 na linha 1, colunas 1-4 */
    for (int c = 1; c <= 4; c++)
        tabuleiro[1][c] = NAVIO;
 
    /* Navio vertical de tamanho 3 na coluna 7, linhas 3-5 */
    for (int l = 3; l <= 5; l++)
        tabuleiro[l][7] = NAVIO;
 
    /* Navio diagonal de tamanho 3 a partir de (7,0) */
    tabuleiro[7][0] = NAVIO;
    tabuleiro[8][1] = NAVIO;
    tabuleiro[9][2] = NAVIO;
 
    printf("=== BATALHA NAVAL - Habilidades Especiais ===\n");
    printf("\n--- Tabuleiro inicial (com navios) ---");
    exibir_tabuleiro(tabuleiro);
 
    /* ------------------------------------------------------------------ */
    /* 3. Cria as matrizes de habilidade                                   */
    /* ------------------------------------------------------------------ */
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
 
    construir_cone(cone);
    construir_cruz(cruz);
    construir_octaedro(octaedro);
 
    /* ------------------------------------------------------------------ */
    /* 4. Aplica as habilidades ao tabuleiro                               */
    /*    Pontos de origem definidos diretamente no código                 */
    /* ------------------------------------------------------------------ */
 
    /* Cone com origem em (2, 5) */
    aplicar_habilidade(tabuleiro, cone, 2, 5);
    printf("--- Apos habilidade CONE (origem: linha 2, col 5) ---");
    exibir_tabuleiro(tabuleiro);
 
    /* Reinicia apenas as marcas de habilidade para demonstrar a cruz */
    for (int l = 0; l < TAM_TABULEIRO; l++)
        for (int c = 0; c < TAM_TABULEIRO; c++)
            if (tabuleiro[l][c] == HABILIDADE)
                tabuleiro[l][c] = AGUA;
 
    /* Cruz com origem em (5, 4) */
    aplicar_habilidade(tabuleiro, cruz, 5, 4);
    printf("--- Apos habilidade CRUZ (origem: linha 5, col 4) ---");
    exibir_tabuleiro(tabuleiro);
 
    /* Reinicia novamente */
    for (int l = 0; l < TAM_TABULEIRO; l++)
        for (int c = 0; c < TAM_TABULEIRO; c++)
            if (tabuleiro[l][c] == HABILIDADE)
                tabuleiro[l][c] = AGUA;
 
    /* Octaedro com origem em (7, 7) */
    aplicar_habilidade(tabuleiro, octaedro, 7, 7);
    printf("--- Apos habilidade OCTAEDRO (origem: linha 7, col 7) ---");
    exibir_tabuleiro(tabuleiro);
 
    return 0;
}