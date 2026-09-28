/******************************************************************************

Faça um programa em C para ler um número inteiro maior que zero, converter este número
de decimal para binário, usando pilha e apresentar na tela o resultado da conversão.

*******************************************************************************/
#include <stdio.h> 
#define MAX 100 

typedef struct{ 
    int itens[MAX]; 
    int topo; 
} Pilha; 

void push(Pilha *p, int resto){ 
    if(p->topo < MAX -1){ 
        p->topo = p->topo+1; 
        p->itens[p->topo] = resto; 
    } 
} 

int main() { 
    int numero; 
    Pilha p; 
    
    p.topo = -1; 
    do{ 
        printf("Digite um numero inteiro maior que zero: "); 
        scanf("%d", &numero); 
    } while(numero<=0); 
    
    while(numero>0){ 
        push(&p, numero %2); 
        numero /= 2; 
    } 
    
    printf("Número em binário: "); 
    
    for(int i = p.topo; i > -1; i--){ 
        printf("%i ", p.itens[i]); 
    } 
    return 0; 
}

