#include <stdio.h> 

void inicia_tabuleiro(int tabuleiro[4][4]);
void inicia_pecas(int pecas[16], int usadas[16]);
void exibir_tabuleiro(int tabuleiro[4][4]);
void exibir_pecas(int pecas[16], int usadas[16]);

int main (){
    int tabuleiro [4][4], pecas[16], usadas [16];

    inicia_tabuleiro(tabuleiro);
    inicia_pecas(pecas, usadas);

    printf("JOGO QUARTO \n");

    exibir_tabuleiro(tabuleiro);
    exibir_pecas(pecas, usadas);

    return 0;

}

void inicia_tabuleiro(int tabuleiro[4][4]) {
    int i, j;

    for ( int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tabuleiro [i][j] = -1;
        }
    }
}
void inicia_pecas(int pecas[16], int usadas[16]) {
    int i;
    for (int i = 0; i < 16; i++) {
        pecas [i] = i;
        usadas [i] = 0;
    }
}

void exibir_tabuleiro(int tabuleiro[4][4]) {
    int i, j;
    printf("\n0   1   2   3\n");

    for (int i = 0; i < 4; i++) {
        printf("%d ", i)
    }
}
