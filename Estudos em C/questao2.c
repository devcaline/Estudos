/******************************************************************************

Construa um programa em C que use a estrutura pilha e verifique se o número de abre
parênteses é igual ao número de fecha parênteses.

*******************************************************************************/
#include <stdio.h> 
#include <string.h>
#define MAX 100 

typedef struct{
    int topo;
    char itens[MAX];
} Pilha;


int main() { 
    char expressao[MAX];
    Pilha p;
    int erro =0;
    
    p.topo = -1;
    
    printf("Digite uma expressão: ");
    fgets(expressao, sizeof(expressao), stdin);
    
    for (int i = 0; expressao[i] != '\0'; i++){
        if (expressao[i]=='('){
            p.topo++;
            p.itens[p.topo]='(';
        } else if (expressao[i] == ')'){
            if (p.topo == -1){
            erro ++;
            }
           p.topo--;
        }
    }
    
    if(erro != 0){
        printf("Foi encontrado um ')' sem '(' correspondente");
    }
    else if(p.topo == -1){
        printf("A abertura e fechamento de parenteses está correta");
    } else if (p.topo >= 0){
        printf("Há %i parenteses abertos que não foram fechados", p.topo+1);
    }
    
    
    return 0; 
}

