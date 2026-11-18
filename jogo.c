#include <stdio.h>
#include <stdlib.h>

void limparTela();
void exibirCabecalho(int jogadorAtual);
void inicializarTabuleiro(int tabuleiro[4][4]);
void inicializarPecas(int pecas[16], int usadas[16]);
void exibirTabuleiro(int tabuleiro[4][4]);
void exibirPecasEmTabela(int pecas[16], int usadas[16]);
void consultarTabuleiro(int tabuleiro[4][4]); 
int escolherPeca(int usadas[16], int tabuleiro[4][4]);
void posicionarPeca(int tabuleiro[4][4], int usadas[16], int peca);
int verificarVitoria(int tabuleiro[4][4]);
void imprimirLinhaAtributos(int p);

int main() {
    int tabuleiro[4][4];
    int pecas[16];
    int usadas[16];

    int jogadorAtual = 1;
    int outroJogador = 2;
    int pecaEmJogo;
    int jogadas = 0;
    int venceu = 0;

    inicializarTabuleiro(tabuleiro);
    inicializarPecas(pecas, usadas);

    limparTela();
    printf("\n");
    printf("              ======================================================\n");
    printf("                             BEM-VINDO AO JOGO QUARTO                \n");
    printf("              ======================================================\n\n");

    exibirTabuleiro(tabuleiro);
    exibirPecasEmTabela(pecas, usadas);

    printf("\n                         --- INICIO DO JOGO ---\n\n");
    printf("              Jogador %d, escolha a peca para o Jogador %d colocar:\n", jogadorAtual, outroJogador);
    pecaEmJogo = escolherPeca(usadas, tabuleiro);

    while (jogadas < 16) {
        int aux = jogadorAtual;
        jogadorAtual = outroJogador;
        outroJogador = aux;
        limparTela();
        exibirCabecalho(jogadorAtual);
        exibirTabuleiro(tabuleiro);

        printf("              >> Voce recebeu do Jogador %d a peca:\n", outroJogador);
        printf("              ---------------------------------------------------------\n");
        printf("               ID   |  Altura   |   Cor   |   Forma   | Consistencia\n");
        printf("              ---------------------------------------------------------\n");
        imprimirLinhaAtributos(pecaEmJogo);
        printf("\n              ---------------------------------------------------------\n\n");

        posicionarPeca(tabuleiro, usadas, pecaEmJogo);
        jogadas++;

        if (verificarVitoria(tabuleiro)) {
            limparTela();
            printf("\n");
            printf("              =========================================================\n");
            printf("                  PARABENS! O JOGADOR %d VENCEU O JOGO! \n", jogadorAtual);
            printf("              =========================================================\n\n");
            exibirTabuleiro(tabuleiro);
            venceu = 1;
            break;
        }

        if (jogadas == 16) break;

        limparTela();
        exibirCabecalho(jogadorAtual);
        exibirTabuleiro(tabuleiro);
        exibirPecasEmTabela(pecas, usadas);

        printf("\n              >> Excelente! Agora escolha a peca para o Jogador %d:\n", outroJogador);
        pecaEmJogo = escolherPeca(usadas, tabuleiro);
    }

    if (!venceu) {
        limparTela();
        printf("\n");
        printf("              =====================================================\n");
        printf("                     FIM DE JOGO! TABULEIRO CHEIO (EMPATE)             \n");
        printf("              =====================================================\n\n");
        exibirTabuleiro(tabuleiro);
    }

    return 0;
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void exibirCabecalho(int jogadorAtual) {
    printf("\n");
    printf("              =========================================================\n");
    printf("                         TURNO DO JOGADOR %d (Coloca a peca) \n", jogadorAtual);
    printf("              =========================================================\n");
}

void inicializarTabuleiro(int tabuleiro[4][4]) {
    int i, j;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            tabuleiro[i][j] = -1;
        }
    }
}

void inicializarPecas(int pecas[16], int usadas[16]) {
    int i;
    for(i = 0; i < 16; i++) {
        pecas[i] = i;
        usadas[i] = 0;
    }
}

void imprimirLinhaAtributos(int p) {
    int altura = (p >> 3) & 1;
    int cor = (p >> 2) & 1;
    int forma = (p >> 1) & 1;
    int topo = p & 1;

    printf("              [%02d]  | %-9s | %-7s | %-9s | %s",
           p,
           altura ? "Alta" : "Baixa",
           cor ? "Escura" : "Clara",
           forma ? "Quadrada" : "Redonda",
           topo ? "Solida" : "Oca");
}

void exibirTabuleiro(int tabuleiro[4][4]) {
    int i, j;
    printf("\n                         0    1    2    3\n");
    printf("                       --------------------\n");
    for(i = 0; i < 4; i++) {
        printf("                    %d  |", i);
        for(j = 0; j < 4; j++) {
            if(tabuleiro[i][j] == -1) {
                printf(" -- |");
            }
            else {
                printf(" %02d |", tabuleiro[i][j]);
            }
        }
        printf("\n                       --------------------\n");
    }
    printf("\n");
}

void exibirPecasEmTabela(int pecas[16], int usadas[16]) {
    int i;
    printf("              -----------------------------------------------------\n");
    printf("               ID   |  Altura   |   Cor   |   Forma   | Consistencia\n");
    printf("              -----------------------------------------------------\n");
    for(i = 0; i < 16; i++) {
        if(usadas[i] == 0) {
            imprimirLinhaAtributos(pecas[i]);
            printf("\n");
        }
    }
    printf("              ------------------------------------------------------\n");
}


void consultarTabuleiro(int tabuleiro[4][4]) {
    int i, j, encontrou = 0;
    printf("\n              --- PECAS JA POSICIONADAS NO TABULEIRO ---\n");
    printf("              Pos    | ID   |  Altura   |   Cor   |   Forma   | Consistencia\n");
    printf("              --------------------------------------------------------------\n");
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(tabuleiro[i][j] != -1) {
                printf("              (%d,%d)  |", i, j);
                
                int p = tabuleiro[i][j];
                printf(" [%02d] | %-9s | %-7s | %-9s | %s\n",
                       p,
                       ((p >> 3) & 1) ? "Alta" : "Baixa",
                       ((p >> 2) & 1) ? "Escura" : "Clara",
                       ((p >> 1) & 1) ? "Quadrada" : "Redonda",
                       (p & 1) ? "Solida" : "Oca");
                encontrou = 1;
            }
        }
    }
    if (!encontrou) {
        printf("              Nenhuma peca foi colocada no tabuleiro ainda.\n");
    }
    printf("              --------------------------------------------------------------\n\n");
}

int escolherPeca(int usadas[16], int tabuleiro[4][4]) {
    int escolha;
    while (1) {
        printf("              Digite o ID da peca (ou -1 para ver pecas no tabuleiro): ");
        scanf("%d", &escolha);

        if (escolha == -1) {
            consultarTabuleiro(tabuleiro);
            continue; 
        }

        if (escolha >= 0 && escolha <= 15 && usadas[escolha] == 0) {
            return escolha;
        }

        printf("              [!] Peca invalida ou ja usada! Tente novamente.\n");
    }
}

void posicionarPeca(int tabuleiro[4][4], int usadas[16], int peca) {
    int linha, coluna;

    while (1) {
        printf("              Digite a linha (0 a 3) ou -1 para consultar tabuleiro: ");
        scanf("%d", &linha);

        if (linha == -1) {
            consultarTabuleiro(tabuleiro);
            continue; 
        }

        printf("              Digite a coluna (0 a 3): ");
        scanf("%d", &coluna);

        if (linha >= 0 && linha <= 3 && coluna >= 0 && coluna <= 3 && tabuleiro[linha][coluna] == -1) {
            tabuleiro[linha][coluna] = peca;
            usadas[peca] = 1;
            break;
        }

        printf("\n              [!] Posicao invalida ou ja ocupada! Tente novamente.\n");
    }
}

int verificarVitoria(int tabuleiro[4][4]) {
    int i, j;

    for (i = 0; i < 4; i++) {
        if (tabuleiro[i][0] != -1 && tabuleiro[i][1] != -1 &&
            tabuleiro[i][2] != -1 && tabuleiro[i][3] != -1) {
            int p0 = tabuleiro[i][0], p1 = tabuleiro[i][1], p2 = tabuleiro[i][2], p3 = tabuleiro[i][3];
            if ((p0 & p1 & p2 & p3) != 0 || ((~p0 & 0xF) & (~p1 & 0xF) & (~p2 & 0xF) & (~p3 & 0xF)) != 0) return 1;
        }
    }

    for (j = 0; j < 4; j++) {
        if (tabuleiro[0][j] != -1 && tabuleiro[1][j] != -1 &&
            tabuleiro[2][j] != -1 && tabuleiro[3][j] != -1) {
            int p0 = tabuleiro[0][j], p1 = tabuleiro[1][j], p2 = tabuleiro[2][j], p3 = tabuleiro[3][j];
            if ((p0 & p1 & p2 & p3) != 0 || ((~p0 & 0xF) & (~p1 & 0xF) & (~p2 & 0xF) & (~p3 & 0xF)) != 0) return 1;
        }
    }

    if (tabuleiro[0][0] != -1 && tabuleiro[1][1] != -1 && tabuleiro[2][2] != -1 && tabuleiro[3][3] != -1) {
        int p0 = tabuleiro[0][0], p1 = tabuleiro[1][1], p2 = tabuleiro[2][2], p3 = tabuleiro[3][3];
        if ((p0 & p1 & p2 & p3) != 0 || ((~p0 & 0xF) & (~p1 & 0xF) & (~p2 & 0xF) & (~p3 & 0xF)) != 0) return 1;
    }

    if (tabuleiro[0][3] != -1 && tabuleiro[1][2] != -1 && tabuleiro[2][1] != -1 && tabuleiro[3][0] != -1) {
        int p0 = tabuleiro[0][3], p1 = tabuleiro[1][2], p2 = tabuleiro[2][1], p3 = tabuleiro[3][0];
        if ((p0 & p1 & p2 & p3) != 0 || ((~p0 & 0xF) & (~p1 & 0xF) & (~p2 & 0xF) & (~p3 & 0xF)) != 0) return 1;
    }
    return 0;
}
