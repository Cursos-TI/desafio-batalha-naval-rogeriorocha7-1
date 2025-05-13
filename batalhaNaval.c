#include <stdio.h>

// Constantes
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

int main() {
    // 1. Inicializa o tabuleiro 10x10 com valor 0 (água)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }

    // 2. Declaraçao e inicialização dos navios como vetores unidimensionais
    int navioHorizontal[TAM_NAVIO] = {VALOR_NAVIO, VALOR_NAVIO, VALOR_NAVIO};
    int navioVertical[TAM_NAVIO] = {VALOR_NAVIO, VALOR_NAVIO, VALOR_NAVIO};

    // 3. Coordenadas iniciais dos navios (definidas no código)
    int linhaH = 2;
    int colunaH = 4;

    int linhaV = 5;
    int colunaV = 1;

    // 4. Verificaçao se os navios cabem no tabuleiro
    if (colunaH + TAM_NAVIO <= TAM_TABULEIRO && linhaV + TAM_NAVIO <= TAM_TABULEIRO) {
        
        // 5. Verificaçao de sobreposiçao
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaH][colunaH + i] != VALOR_AGUA || 
                tabuleiro[linhaV + i][colunaV] != VALOR_AGUA) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // 6. Posiciona o navio horizontal copiando os valores do vetor
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
            }

            // 7. Posiciona o navio vertical copiando os valores do vetor
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = navioVertical[i];
            }
        } else {
            printf("Erro: sobreposição de navios detectada.\n");
            return 1;
        }

    } else {
        printf("Erro: coordenadas fora dos limites do tabuleiro.\n");
        return 1;
    }

    // 8. Exibe o tabuleiro formatado
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
