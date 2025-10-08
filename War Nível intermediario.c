#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];      
    char cor[10];       
    int tropas;        
};

struct Territorio* cadastrarTerritorios(int quantidade);
void exibirTerritorios(struct Territorio* territorios, int quantidade);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);
void menuAtaque(struct Territorio* territorios, int quantidade);

int main() {
    srand(time(NULL));
    
    int quantidade;
    
    printf("=== SISTEMA WAR ESTRUTURADO ===\n\n");
    
    printf("Digite o numero total de territorios: ");
    scanf("%d", &quantidade);
    
    struct Territorio* territorios = cadastrarTerritorios(quantidade);
    
    if (territorios == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }
    
    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Realizar ataque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                exibirTerritorios(territorios, quantidade);
                break;
            case 2:
                menuAtaque(territorios, quantidade);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    
    liberarMemoria(territorios);
    
    return 0;
}

struct Territorio* cadastrarTerritorios(int quantidade) {
    // Alocação dinâmica do vetor de territórios
    struct Territorio* territorios = (struct Territorio*)malloc(quantidade * sizeof(struct Territorio));
    
    if (territorios == NULL) {
        return NULL;
    }
    
    printf("\n=== CADASTRO DE %d TERRITORIOS ===\n", quantidade);
    
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        
        printf("Digite o nome: ");
        scanf("%29s", territorios[i].nome);
        
        printf("Digite a cor do exercito: ");
        scanf("%9s", territorios[i].cor);
        
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
    
    return territorios;
}

void exibirTerritorios(struct Territorio* territorios, int quantidade) {
    printf("\n=== TERRITORIOS CADASTRADOS ===\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("  Endereco: %p\n", (void*)&territorios[i]);
    }
}

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n=== SIMULACAO DE ATAQUE ===\n");
    printf("Atacante: %s (%s) - %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
    
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("\nDado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("\n>>> VITORIA DO ATACANTE! <<<\n");
        
        printf("O territorio %s agora pertence ao exercito %s!\n", defensor->nome, atacante->cor);
        
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        
        int tropasPerdidas = atacante->tropas / 4;
        atacante->tropas -= tropasPerdidas;
        printf("Atacante perdeu %d tropas na batalha.\n", tropasPerdidas);
        
    } else if (dadoAtacante < dadoDefensor) {
        printf("\n>>> VITORIA DO DEFENSOR! <<<\n");
        
        atacante->tropas--;
        printf("Atacante perdeu 1 tropa na batalha.\n");
        
        defensor->tropas++;
        printf("Defensor recebeu 1 tropa de reforco.\n");
        
    } else {
        printf("\n>>> EMPATE! <<<\n");
        printf("Nenhum territorio mudou de dono.\n");
        
        atacante->tropas--;
        defensor->tropas--;
        printf("Ambos os exercitos perderam 1 tropa.\n");
    }
    
    printf("\nSituacao apos a batalha:\n");
    printf("Atacante: %s (%s) - %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
}

void menuAtaque(struct Territorio* territorios, int quantidade) {
    int idxAtacante, idxDefensor;
    
    exibirTerritorios(territorios, quantidade);
    
    printf("\n=== SELECAO DE ATAQUE ===\n");
    
    printf("Digite o numero do territorio ATACANTE: ");
    scanf("%d", &idxAtacante);
    
    if (idxAtacante < 1 || idxAtacante > quantidade) {
        printf("Territorio invalido!\n");
        return;
    }
    
    printf("Digite o numero do territorio DEFENSOR: ");
    scanf("%d", &idxDefensor);
    
    if (idxDefensor < 1 || idxDefensor > quantidade) {
        printf("Territorio invalido!\n");
        return;
    }
    
    idxAtacante--;
    idxDefensor--;

    if (idxAtacante == idxDefensor) {
        printf("Um territorio nao pode atacar a si mesmo!\n");
        return;
    }
    
    if (strcmp(territorios[idxAtacante].cor, territorios[idxDefensor].cor) == 0) {
        printf("Nao e possivel atacar um territorio da mesma cor!\n");
        return;
    }
    
    if (territorios[idxAtacante].tropas <= 1) {
        printf("O territorio atacante nao tem tropas suficientes para atacar!\n");
        return;
    }
    
    atacar(&territorios[idxAtacante], &territorios[idxDefensor]);
}

void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}