#include <stdio.h>
#include <string.h>

struct Territorio {
    char nome[30];     
    char cor[10];      
    int tropas;        
};

int main() {

    struct Territorio territorios[5];
    
    printf("=== SISTEMA DE CADASTRO DE TERRITORIOS ===\n\n");
    
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do Territorio %d:\n", i + 1);
        
        printf("Digite o nome do territorio: ");
        scanf("%29s", territorios[i].nome);
        
        printf("Digite a cor do exercito: ");
        scanf("%9s", territorios[i].cor);
        
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");
    }
    
    printf("=== DADOS DOS TERRITORIOS CADASTRADOS ===\n\n");
    
    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do exercito: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("----------------------------\n");
    }
    
    return 0;
}