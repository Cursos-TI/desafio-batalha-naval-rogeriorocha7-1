#include <stdio.h>
#include <stdlib.h> // Para abs

// Constantes
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5

// Inicializa matriz de habilidade com zeros
void inicializarHabilidade(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
}

// Cria habilidade em forma de cone (ajustado para exemplo 3x5 do professor)
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    inicializarHabilidade(habilidade);
    // Cone apontando para baixo, origem na linha 0, coluna central
    habilidade[0][2] = 1; // Topo (1 célula)
    habilidade[1][1] = 1; habilidade[1][2] = 1; habilidade[1][3] = 1; // Meio (3 células)
    habilidade[2][0] = 1; habilidade[2][1] = 1; habilidade[2][2] = 1; habilidade[2][3] = 1; habilidade[2][4] = 1; // Base (5 células)
}

// Cria habilidade em forma de cruz
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    inicializarHabilidade(habilidade);
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        habilidade[i][centro] = 1; // Vertical
        habilidade[centro][i] = 1; // Horizontal
    }
}

// Cria habilidade em forma de octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    inicializarHabilidade(habilidade);
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Exibe matriz de habilidade para verificação
void exibirHabilidade(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], const char* nome) {
    printf("\nMatriz de habilidade %s:\n", nome);
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            printf("%d ", habilidade[i][j]);
        }
        printf("\n");
    }
}

// Aplica habilidade ao tabuleiro com verificação rigorosa de limites
int aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], 
                     int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], 
                     int linhaOrigem, int colunaOrigem) {
    int offset = TAM_HABILIDADE / 2;
    // Verifica se toda a área da habilidade está dentro do tabuleiro
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = linhaOrigem - offset + i;
                int colTab = colunaOrigem - offset + j;
                if (linhaTab < 0 || linhaTab >= TAM_TABULEIRO || 
                    colTab < 0 || colTab >= TAM_TABULEIRO) {
                    return 0; // Fora dos limites
                }
            }
        }
    }

    // Aplica a habilidade
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = linhaOrigem - offset + i;
                int colTab = colunaOrigem - offset + j;
                // Marca se é água ou área de habilidade (preserva navios)
                if (tabuleiro[linhaTab][colTab] == VALOR_AGUA || 
                    tabuleiro[linhaTab][colTab] == VALOR_HABILIDADE) {
                    tabuleiro[linhaTab][colTab] = VALOR_HABILIDADE;
                }
            }
        }
    }
    return 1;
}

// Exibe o tabuleiro com caracteres distintos
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro:\n  ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == VALOR_AGUA) {
                printf("~  "); // Água
            } else if (tabuleiro[i][j] == VALOR_NAVIO) {
                printf("N  "); // Navio
            } else if (tabuleiro[i][j] == VALOR_HABILIDADE) {
                printf("*  "); // Habilidade
            }
        }
        printf("\n");
    }
}

int main() {
    // 1. Inicializa o tabuleiro
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }

    // 2. Coordenadas dos navios
    int linhaH = 2, colunaH = 4; // Horizontal
    int linhaV = 5, colunaV = 1; // Vertical
    int linhaD1 = 0, colunaD1 = 0; // Diagonal principal
    int linhaD2 = 0, colunaD2 = 9; // Diagonal secundária

    // 3. Verifica se navios cabem
    if (
        colunaH + TAM_NAVIO <= TAM_TABULEIRO &&
        linhaV + TAM_NAVIO <= TAM_TABULEIRO &&
        linhaD1 + TAM_NAVIO <= TAM_TABULEIRO && colunaD1 + TAM_NAVIO <= TAM_TABULEIRO &&
        linhaD2 + TAM_NAVIO <= TAM_TABULEIRO && colunaD2 - (TAM_NAVIO - 1) >= 0
    ) {
        // 4. Verifica sobreposição
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (
                tabuleiro[linhaH][colunaH + i] != VALOR_AGUA ||
                tabuleiro[linhaV + i][colunaV] != VALOR_AGUA ||
                tabuleiro[linhaD1 + i][colunaD1 + i] != VALOR_AGUA ||
                tabuleiro[linhaD2 + i][colunaD2 - i] != VALOR_AGUA
            ) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // 5. Posiciona navios
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = VALOR_NAVIO; // Horizontal
                tabuleiro[linhaV + i][colunaV] = VALOR_NAVIO; // Vertical
                tabuleiro[linhaD1 + i][colunaD1 + i] = VALOR_NAVIO; // Diagonal principal
                tabuleiro[linhaD2 + i][colunaD2 - i] = VALOR_NAVIO; // Diagonal secundária
            }
        } else {
            printf("Erro: sobreposicao de navios detectada.\n");
            return 1;
        }
    } else {
        printf("Erro: coordenadas fora dos limites do tabuleiro.\n");
        return 1;
    }

    // 6. Cria habilidades
    int habilidadeCone[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeCruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int habilidadeOctaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);

    // 7. Exibe matrizes de habilidade
    exibirHabilidade(habilidadeCone, "Cone");
    exibirHabilidade(habilidadeCruz, "Cruz");
    exibirHabilidade(habilidadeOctaedro, "Octaedro");

    // 8. Aplica habilidades
    int origemConeL = 4, origemConeC = 4;
    int origemCruzL = 7, origemCruzC = 7;
    int origemOctaedroL = 2, origemOctaedroC = 7;

    if (!aplicarHabilidade(tabuleiro, habilidadeCone, origemConeL, origemConeC)) {
        printf("Aviso: Habilidade cone fora dos MNIST do tabuleiro.\n");
    }
    if (!aplicarHabilidade(tabuleiro, habilidadeCruz, origemCruzL, origemCruzC)) {
        printf("Aviso: Habilidade cruz fora dos limites do tabuleiro.\n");
    }
    if (!aplicarHabilidade(tabuleiro, habilidadeOctaedro, origemOctaedroL, origemOctaedroC)) {
        printf("Aviso: Habilidade octaedro fora dos limites do tabuleiro.\n");
    }

    // 9. Exibe tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}