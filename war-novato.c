#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define TAM_STRING 100

// --- Estrutura do território ---
struct Territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função principal ---
int main() {
    struct Territorio mapa[MAX_TERRITORIOS];
    int totalTerritorios = 0;

    printf("====================================\n");
    printf("        JOGO WAR - MAPA MUNDIAL      \n");
    printf("====================================\n\n");

    // --- Preenchimento dos territórios ---
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("--- Cadastro do Território %d ---\n", i + 1);

        printf("Digite o nome do território: ");
        fgets(mapa[i].nome, TAM_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove '\n'

        printf("Digite a cor do exército (Ex: vermelho, azul, verde...): ");
        fgets(mapa[i].cor, TAM_STRING, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite o número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();

        printf("\n");
        totalTerritorios++;
    }

    // --- Exibição do mapa final ---
    printf("\n====================================\n");
    printf("       MAPA COMPLETO DO JOGO WAR     \n");
    printf("====================================\n\n");

    for (int i = 0; i < totalTerritorios; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("------------------------------------\n");
    }

    printf("\nMapa criado com sucesso! Boa sorte na conquista!\n");

    return 0;
}