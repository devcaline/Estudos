/******************************************************************************

Uma palavra é um palíndromo se a sequência de letras que a forma é a mesma, quer seja
lida da esquerda para a direita ou da direita para a esquerda (exemplo: raiar, ovo, ana,
mussum). Escreva um programa em C que reconheça se uma dada palavra é um palíndromo.

*******************************************************************************/
#include <stdio.h> 
#include <string.h>
#define MAX 100 

typedef struct{
    int topo;
    char itens[MAX];
} Pilha;


int main() { 
    Pilha p;
    p.topo = -1;
    int inicio, erro = 0;
    
    char palavra[MAX];
    
    printf("Digite uma palavra: ");
    scanf("%s", &palavra);
    
    int tamanho = strlen(palavra);
    
    for (int i = 0; i < tamanho/2; i++){
        p.topo++;
        p.itens[p.topo]=palavra[i];
    }
    
    if (tamanho %2 == 0){
        inicio = tamanho /2;
    } else {
        inicio = tamanho/2 + 1;
    }
    
    for (int i = inicio; i < tamanho; i++){
        for (int j = p.topo; j > -1; j--){
            if(palavra[i] != p.itens[p.topo]){
                erro++;
            }
        }
        
    }
    
    if(erro){
        printf("Não é palindromo");
    } else {
        printf("É palindromo");
    }
    
    return 0; 
}

