/******************************************************************************

Escreva um programa em C que calcule o valor de uma expressão em notação polonesa
reversa (notação pós-fixa). Considere as 4 operações matemáticas e que se está trabalhando
apenas com dígitos (valores de 0 a 9).

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct{
    int topo;
    int itens[MAX];
} Pilha;

void push(Pilha *p, int valor){
    if(p->topo < MAX - 1){
        p->itens[++p->topo] = valor;
    }
}

int pop(Pilha *p){
    if(p->topo > -1){
        return p->itens[p->topo--];
    }
    return -1;
}

int main(){

    char expressao[MAX];
    Pilha p;

    p.topo = -1;

    printf("Digite a expressao pos-fixa: ");
    scanf("%s", expressao);

    for(int i = 0; expressao[i] != '\0'; i++){

        if(isdigit(expressao[i])){

            push(&p, expressao[i] - '0');

        } else {

            int op2 = pop(&p);
            int op1 = pop(&p);

            int resultado;

            switch(expressao[i]){

                case '+':
                    resultado = op1 + op2;
                    break;

                case '-':
                    resultado = op1 - op2;
                    break;

                case '*':
                    resultado = op1 * op2;
                    break;

                case '/':
                    resultado = op1 / op2;
                    break;
            }

            push(&p, resultado);
        }
    }

    printf("Resultado: %d\n", pop(&p));

    return 0;
}