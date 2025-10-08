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
void exibirMapa(struct Territorio* mapa, int tamanho);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa, char** missoesJogadores, int numJogadores);
void menuAtaque(struct Territorio* territorios, int quantidade, char** missoesJogadores, int jogadorAtual);

void inicializarMissoes(char* missoes[]);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
void exibirMissao(char* missao, int jogador);
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho, char corJogador[]);

int main() {
    srand(time(NULL));
    
    int quantidade, numJogadores;
    
    printf("=== SISTEMA WAR ESTRUTURADO COM MISSOES ===\n\n");
    
    printf("Digite o numero total de territorios: ");
    scanf("%d", &quantidade);
    
    printf("Digite o numero de jogadores: ");
    scanf("%d", &numJogadores);
    
    char* missoes[5];
    inicializarMissoes(missoes);
    
    char** missoesJogadores = (char**)malloc(numJogadores * sizeof(char*));
    char** coresJogadores = (char**)malloc(numJogadores * sizeof(char*));
    
    for (int i = 0; i < numJogadores; i++) {
        missoesJogadores[i] = (char*)malloc(100 * sizeof(char));
        coresJogadores[i] = (char*)malloc(10 * sizeof(char));
        
        printf("\nJogador %d, digite sua cor: ", i + 1);
        scanf("%9s", coresJogadores[i]);
        
        atribuirMissao(missoesJogadores[i], missoes, 5);
        printf("Missao atribuida: ");
        exibirMissao(missoesJogadores[i], i + 1);
    }
    
    struct Territorio* territorios = cadastrarTerritorios(quantidade);
    
    if (territorios == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }
    
    int jogadorAtual = 0;
    int vencedor = -1;
    
    while (vencedor == -1) {
        printf("\n=== TURNO DO JOGADOR %d (%s) ===\n", jogadorAtual + 1, coresJogadores[jogadorAtual]);
        
        int opcao;
        do {
            printf("\n1 - Exibir mapa\n");
            printf("2 - Realizar ataque\n");
            printf("3 - Consultar missao\n");
            printf("4 - Finalizar turno\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            
            switch (opcao) {
                case 1:
                    exibirMapa(territorios, quantidade);
                    break;
                case 2:
                    menuAtaque(territorios, quantidade, missoesJogadores, jogadorAtual);
                    break;
                case 3:
                    exibirMissao(missoesJogadores[jogadorAtual], jogadorAtual + 1);
                    break;
                case 4:
                    printf("Finalizando turno...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
            }
        } while (opcao != 4);
        
        if (verificarMissao(missoesJogadores[jogadorAtual], territorios, quantidade, coresJogadores[jogadorAtual])) {
            vencedor = jogadorAtual;
            printf("\n🎉🎉🎉 PARABENS JOGADOR %d! 🎉🎉🎉\n", jogadorAtual + 1);
            printf("Voce cumpriu sua missao e venceu o jogo!\n");
            printf("Missao cumprida: %s\n", missoesJogadores[jogadorAtual]);
        }

        jogadorAtual = (jogadorAtual + 1) % numJogadores;
    }
    
    liberarMemoria(territorios, missoesJogadores, numJogadores);
    
    for (int i = 0; i < numJogadores; i++) {
        free(coresJogadores[i]);
    }
    free(coresJogadores);
    
    return 0;
}

void inicializarMissoes(char* missoes[]) {
    missoes[0] = "Conquistar 3 territorios seguidos";
    missoes[1] = "Eliminar todas as tropas da cor Vermelha";
    missoes[2] = "Controlar pelo menos 5 territorios";
    missoes[3] = "Destruir o exercito Azul completamente";
    missoes[4] = "Manter 10 tropas em um unico territorio";
}

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

void exibirMissao(char* missao, int jogador) {
    printf("Jogador %d - Missao: %s\n", jogador, missao);
}

int verificarMissao(char* missao, struct Territorio* mapa, int tamanho, char corJogador[]) {
    if (strstr(missao, "3 territorios seguidos") != NULL) {
        int consecutivos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                consecutivos++;
                if (consecutivos >= 3) return 1;
            } else {
                consecutivos = 0;
            }
        }
        return 0;
    }
    
    else if (strstr(missao, "cor Vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    
    else if (strstr(missao, "5 territorios") != NULL) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                count++;
            }
        }
        return count >= 5;
    }
    
    else if (strstr(missao, "exercito Azul") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    
    else if (strstr(missao, "10 tropas") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 10) {
                return 1;
            }
        }
        return 0;
    }
    
    return 0; 
}

struct Territorio* cadastrarTerritorios(int quantidade) {
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

void exibirMapa(struct Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ATUAL ===\n");
    
    for (int i = 0; i < tamanho; i++) {
        printf("Territorio %d: %s | Cor: %s | Tropas: %d\n", 
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n=== SIMULACAO DE ATAQUE ===\n");
    printf("Atacante: %s (%s) - %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
    
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("\n>>> VITORIA DO ATACANTE! <<<\n");
        
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        
        int tropasPerdidas = atacante->tropas / 4;
        atacante->tropas -= tropasPerdidas;
        printf("Atacante perdeu %d tropas. Defensor agora e %s.\n", tropasPerdidas, atacante->cor);
        
    } else if (dadoAtacante < dadoDefensor) {
        printf("\n>>> VITORIA DO DEFENSOR! <<<\n");
        
        atacante->tropas--;
        defensor->tropas++;
        printf("Atacante perdeu 1 tropa. Defensor ganhou 1 tropa de reforco.\n");
        
    } else {
        printf("\n>>> EMPATE! <<<\n");
        atacante->tropas--;
        defensor->tropas--;
        printf("Ambos os exercitos perderam 1 tropa.\n");
    }
}

void menuAtaque(struct Territorio* territorios, int quantidade, char** missoesJogadores, int jogadorAtual) {
    int idxAtacante, idxDefensor;
    
    exibirMapa(territorios, quantidade);
    
    printf("\n=== SELECAO DE ATAQUE - Jogador %d ===\n", jogadorAtual + 1);
    
    printf("Digite o numero do territorio ATACANTE: ");
    scanf("%d", &idxAtacante);
    
    printf("Digite o numero do territorio DEFENSOR: ");
    scanf("%d", &idxDefensor);
    
    if (idxAtacante < 1 || idxAtacante > quantidade || idxDefensor < 1 || idxDefensor > quantidade) {
        printf("Territorio invalido!\n");
        return;
    }
    
    idxAtacante--;
    idxDefensor--;
    
    if (idxAtacante == idxDefensor) {
        printf("Nao pode atacar a si mesmo!\n");
        return;
    }
    
    if (strcmp(territorios[idxAtacante].cor, territorios[idxDefensor].cor) == 0) {
        printf("Nao pode atacar territorio da mesma cor!\n");
        return;
    }
    
    if (territorios[idxAtacante].tropas <= 1) {
        printf("Tropas insuficientes para atacar!\n");
        return;
    }
    
    atacar(&territorios[idxAtacante], &territorios[idxDefensor]);
}

void liberarMemoria(struct Territorio* mapa, char** missoesJogadores, int numJogadores) {
    free(mapa);
    
    for (int i = 0; i < numJogadores; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
    
    printf("\nMemoria liberada com sucesso!\n");
}