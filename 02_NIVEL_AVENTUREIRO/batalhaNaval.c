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

    // Variável de controle de sobreposição
    int sobreposicao = 0;

    // 2. Coordenadas dos navios
    // Navios horizontais/verticais
    int linhaH = 2, colunaH = 4; // horizontal
    int linhaV = 5, colunaV = 1; // vertical

    // Navios diagonais
    int linhaD1 = 0, colunaD1 = 0; // diagonal principal
    int linhaD2 = 0, colunaD2 = 9; // diagonal secundária

    // 3. Verifica se todos os navios cabem no tabuleiro
    if (
        colunaH + TAM_NAVIO <= TAM_TABULEIRO &&
        linhaV + TAM_NAVIO <= TAM_TABULEIRO &&
        linhaD1 + TAM_NAVIO <= TAM_TABULEIRO && colunaD1 + TAM_NAVIO <= TAM_TABULEIRO &&
        linhaD2 + TAM_NAVIO <= TAM_TABULEIRO && colunaD2 - (TAM_NAVIO - 1) >= 0
    ) {
        // 4. Verifica sobreposição para todos os navios
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (
                tabuleiro[linhaH][colunaH + i] != VALOR_AGUA || // horizontal
                tabuleiro[linhaV + i][colunaV] != VALOR_AGUA || // vertical
                tabuleiro[linhaD1 + i][colunaD1 + i] != VALOR_AGUA || // diagonal principal
                tabuleiro[linhaD2 + i][colunaD2 - i] != VALOR_AGUA    // diagonal secundária
            ) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // 5. Posiciona navio horizontal
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = VALOR_NAVIO;
            }

            // 6. Posiciona navio vertical
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = VALOR_NAVIO;
            }

            // 7. Posiciona navio diagonal principal
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaD1 + i][colunaD1 + i] = VALOR_NAVIO;
            }

            // 8. Posiciona navio diagonal secundária
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaD2 + i][colunaD2 - i] = VALOR_NAVIO;
            }
        } else {
            printf("Erro: sobreposição de navios detectada.\n");
            return 1;
        }

    } else {
        printf("Erro: coordenadas fora dos limites do tabuleiro.\n");
        return 1;
    }

    // 9. Exibe o tabuleiro formatado
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
