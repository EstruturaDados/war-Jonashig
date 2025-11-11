#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 100
#define MAX_TERRITORIOS 5

// --- Estrutura do território ---
typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} Territorio;

// --- Função para limpar buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função para rolar dado (1 a 6) ---
int rolarDado() {
    return (rand() % 6) + 1;
}

// --- Função principal ---
int main() {
    srand(time(NULL)); // inicializa o gerador de números aleatórios

    // --- Alocação dinâmica de territórios ---
    Territorio *mapa = (Territorio *) malloc(MAX_TERRITORIOS * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    int totalTerritorios = 0;
    int opcao;

    printf("====================================\n");
    printf("         JOGO WAR - MAPA MUNDIAL    \n");
    printf("====================================\n\n");

    // --- Cadastro dos territórios ---
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("--- Cadastro do Território %d ---\n", i + 1);
        printf("Digite o nome do território: ");
        fgets(mapa[i].nome, TAM_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Digite a cor (exército): ");
        fgets(mapa[i].cor, TAM_STRING, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite o número inicial de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();

        totalTerritorios++;
        printf("\n");
    }

    // --- Loop principal do jogo ---
    do {
        printf("\n====================================\n");
        printf("         MAPA ATUAL DO JOGO WAR     \n");
        printf("====================================\n");
        for (int i = 0; i < totalTerritorios; i++) {
            printf("%d - %-15s | Dono: %-10s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }

        printf("\n1 - Atacar\n2 - Pular turno\n0 - Sair do jogo\nEscolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        if (opcao == 1) {
            int atacante, defensor;

            printf("\nDigite o número do território ATACANTE: ");
            scanf("%d", &atacante);
            limparBufferEntrada();

            printf("Digite o número do território DEFENSOR: ");
            scanf("%d", &defensor);
            limparBufferEntrada();

            // Ajuste para índice (começa em 0)
            atacante--;
            defensor--;

            if (atacante < 0 || atacante >= totalTerritorios || defensor < 0 || defensor >= totalTerritorios) {
                printf("❌ Território inválido!\n");
                continue;
            }

            if (atacante == defensor) {
                printf("❌ Um território não pode atacar a si mesmo!\n");
                continue;
            }

            if (mapa[atacante].tropas < 2) {
                printf("❌ %s não tem tropas suficientes para atacar!\n", mapa[atacante].nome);
                continue;
            }

            printf("\n🎲 %s (atacante) lança o dado...\n", mapa[atacante].nome);
            int dadoAtacante = rolarDado();
            printf("Valor do dado atacante: %d\n", dadoAtacante);

            printf("🎲 %s (defensor) lança o dado...\n", mapa[defensor].nome);
            int dadoDefensor = rolarDado();
            printf("Valor do dado defensor: %d\n", dadoDefensor);

            // Resultado da batalha
            if (dadoAtacante > dadoDefensor) {
                mapa[defensor].tropas--;
                mapa[atacante].tropas--;

                printf("✅ Ataque bem-sucedido! %s perdeu 1 tropa!\n", mapa[defensor].nome);

                // Se defensor foi derrotado
                if (mapa[defensor].tropas <= 0) {
                    printf("🏴 Território %s foi CONQUISTADO por %s!\n",
                           mapa[defensor].nome, mapa[atacante].cor);
                    strcpy(mapa[defensor].cor, mapa[atacante].cor);
                    mapa[defensor].tropas = 1; // atacante deixa 1 tropa
                    mapa[atacante].tropas--;  // perdeu 1 ao avançar
                }
            } else {
                mapa[atacante].tropas--;
                printf("❌ O ataque falhou! %s defendeu com sucesso.\n", mapa[defensor].nome);
            }

        } else if (opcao == 2) {
            printf("\n⏭️  Turno pulado.\n");
        } else if (opcao == 0) {
            printf("\n🛑 Jogo encerrado.\n");
        } else {
            printf("❌ Opção inválida!\n");
        }

    } while (opcao != 0);

    // --- Liberação de memória ---
    free(mapa);
    return 0;
}
