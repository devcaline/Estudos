#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <unistd.h>
#include <ctype.h>

#define max 50
int op = 0, sop = 0, ida = 0, idc = 0, idt = 0, idm = 0, idgc = 0, cont, idx, id_busca;
char resp, nome1[30], nome2[30], cpf[15];
_Bool enc=false, enc_fk=false;

struct aluno{
    char pk_cpf[15];
    char nome[max];
    char admissao[11]; //Data de admissao
    char dtNasc[11];
    char escolaridade[max];
};

struct curso{
    int pk_codCurso;
    char nome[max];
    int cargaHoraria;
    char modalidade[20];// Presencial, Semi-Precial, Online
};

struct turma{
    int pk_codTurma;
    char nomeTurma[max];
    int qtdAlunos;
    char turno[20];
};

struct matricula{
    int pk_ra;
    char fk_cpf[15];
    int fk_codTurma;
    int fk_codCurso;
};

struct aluno a;
struct curso c;
struct turma t;
struct matricula m;
struct aluno tbaluno[max];
struct curso tbcurso[max];
struct turma tbturma[max];
struct matricula tbmatricula[max];


// --- FUNÇÕES DE VALIDAÇÃO ---
_Bool validar_formato_cpf(char cpf[]) {
    if (strlen(cpf) != 14) return false;
    if (cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-') return false;
    return true;
}

_Bool validar_formato_data(char data[]) {
    if (strlen(data) != 10) return false;
    if (data[2] != '/' || data[5] != '/') return false;
    return true;
}



void subMenu(){
    printf("***********************************\n");
    printf("*            SUBMENU              *\n");
    printf("***********************************\n");
    printf("*   1 - ALUNO                     *\n");
    printf("*   2 - CURSO                     *\n");
    printf("*   3 - TURMA                     *\n");
    printf("*   4 - MATRICULA                 *\n");
    printf("*   5 - RETORNAR                  *\n");
    printf("***********************************\n\n");
}

void menu(){
    printf("***********************************\n");
    printf("*         MENU PRINCIPAL          *\n");
    printf("***********************************\n");
    printf("*   1 - CADASTRAR                 *\n");
    printf("*   2 - CONSULTAR                 *\n");
    printf("*   3 - ALTERAR                   *\n");
    printf("*   4 - EXCLUIR                   *\n");
    printf("*   5 - ORDENAR                   *\n");
    printf("*   6 - IMPRIMIR                  *\n");
    printf("*   7 - RELATÓRIOS                *\n");
    printf("*   8 - CONSULTA CRUZADA          *\n");
    printf("*   9 - FINALIZAR                 *\n");
    printf("***********************************\n\n");
}

void submenuOrdenar(){
    printf("***********************************\n");
    printf("*             ORDENAR             *\n");
    printf("***********************************\n");
    printf("*   1 - CRESCENTE                 *\n");
    printf("*   2 - DECRESCENTE               *\n");
    printf("*   3 - RETORNAR                  *\n");
    printf("***********************************\n\n");
}

void submenuOpcaoOrdenar(int opcao){
    switch(opcao){
        case 1:
            strcpy(nome1,"CPF");
            strcpy (nome2,"Nome");
            break;
        case 2:
            strcpy (nome1,"Codigo do Curso");
            strcpy (nome2,"Nome do curso");
            break;
        case 3:
            strcpy (nome1,"Código da Turma");
            strcpy (nome2,"Nome da Turma");
            break;
        case 4:
            strcpy (nome1,"Registro do aluno");
            strcpy (nome2,"CPF do aluno");
            break;
        default:
            if ((opcao<1) ||(opcao>4)){
                system("clear");
                printf("Opçã o inválida!\n");
                sleep(3);
            }
            break;
    }
    if ((opcao>0) && (opcao<5)){
        printf("***********************************\n");
        printf("             ORDENAR               \n");
        printf("***********************************\n");
        printf("   1 - %s                    \n",nome1);
        printf("   2 - %s                    \n",nome2);
        printf("   3 - RETORNAR                    \n");
        printf("***********************************\n\n");
    }
}

void buscar_aluno(char cpf[15]){
    _Bool enc=false;
    int i=0;
    while((i<ida)&&(enc==false)){
        if (strcmp(tbaluno[i].pk_cpf,cpf)==0){
            enc=true;
            system("clear");
            printf("CPF: %s ",tbaluno[i].pk_cpf);
            printf("\nNome: %s ",tbaluno[i].nome);
            printf("\nAdmissão: %s ",tbaluno[i].admissao);
            printf("\nData de Nascimento: %s ",tbaluno[i].dtNasc);
            printf("\nEscolaridade: %s \n\n",tbaluno[i].escolaridade);
            
        }else{
            i++;
        } 
    }
    if (enc==false) printf("Registro não encontrado!\n");
    sleep(5);
}


// FUNÇÃO DE VALIDAÇÃO
void buscar_curso(int codCurso){
    _Bool enc=false;
    int i=0;
    while((i<idc)&&(enc==false)){
        if (tbcurso[i].pk_codCurso==codCurso){
            enc=true;
            system("clear");
            printf("Código do Curso: %d ",tbcurso[i].pk_codCurso);
            printf("\nNome: %s ",tbcurso[i].nome);
            printf("\nCarga Horária: %d ",tbcurso[i].cargaHoraria);
            printf("\nModalidade: %s \n\n",tbcurso[i].modalidade);
        }else{
            i++;
        } 
    }
    if (enc==false) printf("Registro não encontrado!\n");
    sleep(5);
}

void buscar_turma(int codTurma){
    _Bool enc=false;
    int i=0;
    while((i<idt)&&(enc==false)){
        if (tbturma[i].pk_codTurma==codTurma){
            enc=true;
            system("clear");
            printf("Código da Turma: %d ",tbturma[i].pk_codTurma);
            printf("\nNome da Turma: %s ",tbturma[i].nomeTurma);
            printf("\nQuantidade de Alunos: %d ",tbturma[i].qtdAlunos);
            printf("\nTurno: %s \n\n",tbturma[i].turno);
        }else{
            i++;
        } 
    }
    if (enc==false) printf("Registro não encontrado!\n");
    sleep(5);
}

void buscar_matricula(int ra){
    _Bool enc=false;
    int i=0;
    while((i<idm)&&(enc==false)){
        if (tbmatricula[i].pk_ra==ra){
            enc=true;
            system("clear");
            printf("Registro do Aluno: %d ",tbmatricula[i].pk_ra);
            printf("\nCPF do Aluno: %s ",tbmatricula[i].fk_cpf);
            printf("\nCódigo da Turma: %d ",tbmatricula[i].fk_codTurma);
            printf("\nCódigo do Curso: %d \n\n",tbmatricula[i].fk_codCurso);
        }else{
            i++;
        } 
    }
    if (enc==false) printf("Registro não encontrado!\n");
    sleep(5);
}

//----------------

_Bool buscar_aluno_pk_cpf(char cpf[15]){
    _Bool enc=false;
    int i=0;
    while((i<ida)&&(enc==false)){
        if (strcmp(tbaluno[i].pk_cpf,cpf)==0){
           enc=true; 
        }else{
            i++;
        } 
    }
    return enc;
}

_Bool buscar_curso_pk_codCurso(int codCurso){
    _Bool enc=false;
    int i=0;
    while((i<idc)&&(enc==false)){
        if (tbcurso[i].pk_codCurso==codCurso){
           enc=true; 
        }else{
            i++;
        } 
    }
    return enc;
}

_Bool buscar_turma_pk_codTurma(int codTurma){
    _Bool enc=false;
    int i=0;
    while((i<idt)&&(enc==false)){
        if (tbturma[i].pk_codTurma==codTurma){
           enc=true; 
        }else{
            i++;
        } 
    }
    return enc;
}

_Bool buscar_matricula_pk_ra(int ra){
    _Bool enc=false;
    int i=0;
    while((i<idm)&&(enc==false)){
        if (tbmatricula[i].pk_ra==ra){
           enc=true;
        }else{
            i++;
        }
    }
    return enc;
}

void limparBuffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

int buscar_aluno_index(char cpf[15]){
    for(int i=0;i<ida;i++){
        if (strcmp(tbaluno[i].pk_cpf,cpf)==0) return i;
    }
    return -1;
}

int buscar_curso_index(int codCurso){
    for(int i=0;i<idc;i++){
        if (tbcurso[i].pk_codCurso==codCurso) return i;
    }
    return -1;
}

int buscar_turma_index(int codTurma){
    for(int i=0;i<idt;i++){
        if (tbturma[i].pk_codTurma==codTurma) return i;
    }
    return -1;
}

int buscar_matricula_index(int ra){
    for(int i=0;i<idm;i++){
        if (tbmatricula[i].pk_ra==ra) return i;
    }
    return -1;
}

_Bool matricula_vinculada_aluno(char cpf[15]){
    for(int i=0;i<idm;i++){
        if (strcmp(tbmatricula[i].fk_cpf,cpf)==0) return true;
    }
    return false;
}

_Bool matricula_vinculada_curso(int codCurso){
    for(int i=0;i<idm;i++){
        if (tbmatricula[i].fk_codCurso==codCurso) return true;
    }
    return false;
}

_Bool matricula_vinculada_turma(int codTurma){
    for(int i=0;i<idm;i++){
        if (tbmatricula[i].fk_codTurma==codTurma) return true;
    }
    return false;
}

void ordenar(int ident, int entidade, int subop){
   int id=0;
   switch(entidade){
    case 1:
        id = ida;
        break;
    case 2:
        id = idc;
        break;
    case 3:
        id = idt;
        break;
    case 4:
        id = idm;
        break;
   }
   if (ident==1){
       for(int i=0;i<id-1;i++){
          for(int y=i+1;y<id;y++){
             if (entidade==1){
                switch(subop) {
                    case 1:
                        if(strcmp(tbaluno[i].pk_cpf, tbaluno[y].pk_cpf) > 0){
                            a=tbaluno[i];// a da struct de aluno
                            tbaluno[i]=tbaluno[y];
                            tbaluno[y]=a;
                        }
                        break;
                     case 2:
                        if(strcmp(tbaluno[i].nome, tbaluno[y].nome) > 0){
                            a=tbaluno[i];
                            tbaluno[i]=tbaluno[y];
                            tbaluno[y]=a;
                        }
                        break;
                }
             }else if (entidade==2){
                switch(subop) {
                    case 1:
                        if(tbcurso[i].pk_codCurso>tbcurso[y].pk_codCurso){
                            c=tbcurso[i];
                            tbcurso[i]=tbcurso[y];
                            tbcurso[y]=c;
                        }
                        break;
                    case 2:
                        if(strcmp(tbcurso[i].nome, tbcurso[y].nome) > 0){
                            c=tbcurso[i];
                            tbcurso[i]=tbcurso[y];
                            tbcurso[y]=c;
                        }
                        break;
                 }
             }else if (entidade==3){
                switch(subop) {
                    case 1:
                        if(tbturma[i].pk_codTurma>tbturma[y].pk_codTurma){
                            t=tbturma[i];
                            tbturma[i]=tbturma[y];
                            tbturma[y]=t;
                        }
                        break;
                    case 2:
                        if(strcmp(tbturma[i].nomeTurma, tbturma[y].nomeTurma) > 0){
                            t=tbturma[i];
                            tbturma[i]=tbturma[y];
                            tbturma[y]=t;
                        }
                        break;
                 }
             }else if (entidade==4){
                switch(subop) {
                    case 1:
                        if(tbmatricula[i].pk_ra>tbmatricula[y].pk_ra){
                            m=tbmatricula[i];
                            tbmatricula[i]=tbmatricula[y];
                            tbmatricula[y]=m;
                        }
                        break;
                    case 2:
                        if(strcmp(tbmatricula[i].fk_cpf, tbmatricula[y].fk_cpf) > 0){
                            m=tbmatricula[i];
                            tbmatricula[i]=tbmatricula[y];
                            tbmatricula[y]=m;
                        }
                        break;
                    }
                }
            } 
        }
    }else if (ident==2){
       for(int i=0;i<id-1;i++){
          for(int y=i+1;y<id;y++){
            if (entidade==1){
                switch(subop) {
                    case 1:
                        if(strcmp(tbaluno[i].pk_cpf, tbaluno[y].pk_cpf) < 0){
                            a=tbaluno[i];
                            tbaluno[i]=tbaluno[y];
                            tbaluno[y]=a;
                        }
                        break;
                     case 2:
                        if(strcmp(tbaluno[i].nome, tbaluno[y].nome) < 0){
                            a=tbaluno[i];
                            tbaluno[i]=tbaluno[y];
                            tbaluno[y]=a;
                        }
                        break;
                }
            }else if (entidade==2){
                switch(subop) {
                    case 1:
                        if(tbcurso[i].pk_codCurso>tbcurso[y].pk_codCurso){
                            c=tbcurso[i];
                            tbcurso[i]=tbcurso[y];
                            tbcurso[y]=c;
                        }
                        break;
                    case 2:
                        if(strcmp(tbcurso[i].nome, tbcurso[y].nome) < 0){
                            c=tbcurso[i];
                            tbcurso[i]=tbcurso[y];
                            tbcurso[y]=c;
                        }
                        break;
                 }
             }else if (entidade==3){
                switch(subop) {
                    case 1:
                        if(tbturma[i].pk_codTurma<tbturma[y].pk_codTurma){
                            t=tbturma[i];
                            tbturma[i]=tbturma[y];
                            tbturma[y]=t;
                        }
                        break;
                    case 2:
                        if(strcmp(tbturma[i].nomeTurma, tbturma[y].nomeTurma) < 0){
                            t=tbturma[i];
                            tbturma[i]=tbturma[y];
                            tbturma[y]=t;
                        }
                        break;
                 }
             }else if (entidade==4){
                switch(subop) {
                    case 1:
                        if(tbmatricula[i].pk_ra<tbmatricula[y].pk_ra){
                            m=tbmatricula[i];
                            tbmatricula[i]=tbmatricula[y];
                            tbmatricula[y]=m;
                        }
                        break;
                    case 2:
                        if(strcmp(tbmatricula[i].fk_cpf, tbmatricula[y].fk_cpf) < 0){
                            m=tbmatricula[i];
                            tbmatricula[i]=tbmatricula[y];
                            tbmatricula[y]=m;
                        }
                        break;
                    }
                }
            } 
        }
    }
}

void imprimir(int entidade){
    system("clear");
    switch(entidade){
        case 1:
            if (ida>0){
                for (int i=0;i<ida;i++){
                    printf("CPF: %s ",tbaluno[i].pk_cpf);
                    printf("\nNome: %s ",tbaluno[i].nome);
                    printf("\nAdmissão: %s ",tbaluno[i].admissao);
                    printf("\nData de Nascimento: %s ",tbaluno[i].dtNasc);
                    printf("\nEscolaridade: %s \n\n",tbaluno[i].escolaridade);
                }
            }else{
                printf("Cadastre primeiro o(s) aluno(s)!\n");
            }
            break;
        case 2:
            if (idc>0){
                for (int i=0;i<idc;i++){
                    printf("Código do Curso: %d ",tbcurso[i].pk_codCurso);
                    printf("\nNome: %s ",tbcurso[i].nome);
                    printf("\nCarga Horária: %d ",tbcurso[i].cargaHoraria);
                    printf("\nModalidade: %s \n\n",tbcurso[i].modalidade);
                }
            }else{
                printf("Cadastre primeiro o(s) curso(s)!\n");
            }
            break;
        case 3:
            if (idt>0){
                for (int i=0;i<idt;i++){
                    printf("Código da Turma: %d ",tbturma[i].pk_codTurma);
                    printf("\nNome da Turma: %s ",tbturma[i].nomeTurma);
                    printf("\nQuantidade de Alunos: %d ",tbturma[i].qtdAlunos);
                    printf("\nTurno: %s \n\n",tbturma[i].turno);
                }
            }else{
                printf("Cadastre primeiro a(s) turma(s)!\n");
            }
            break;
        case 4:
            if (idm>0){
                for (int i=0;i<idm;i++){
                    printf("Registro do Aluno: %d ",tbmatricula[i].pk_ra);
                    printf("\nCPF do Aluno: %s ",tbmatricula[i].fk_cpf);
                    printf("\nCódigo do Turma: %d ",tbmatricula[i].fk_codTurma);
                    printf("\nCódigo do Curso: %d \n\n",tbmatricula[i].fk_codCurso);
                }
            }else{
                printf("Cadastre primeiro a(s) matricula(s)!\n");
            }
            break;
    }
}

// --- RELATÓRIOS ---
void submenuRelatorios(){
    printf("***********************************\n");
    printf("*           RELATÓRIOS            *\n");
    printf("***********************************\n");
    printf("*   1 - ALUNOS                    *\n");
    printf("*   2 - CURSOS                    *\n");
    printf("*   3 - TURMAS                    *\n");
    printf("*   4 - MATRÍCULAS                *\n");
    printf("*   5 - GERAL                     *\n");
    printf("*   6 - RETORNAR                  *\n");
    printf("***********************************\n\n");
}

void relatorioAlunos(){
    printf("========== RELATÓRIO DE ALUNOS CADASTRADOS ==========\n");
    printf("Total de alunos cadastrados: %d\n\n", ida);
    if (ida>0){
        for (int i=0;i<ida;i++){
            printf("CPF: %s ",tbaluno[i].pk_cpf);
            printf("\nNome: %s ",tbaluno[i].nome);
            printf("\nAdmissão: %s ",tbaluno[i].admissao);
            printf("\nData de Nascimento: %s ",tbaluno[i].dtNasc);
            printf("\nEscolaridade: %s \n\n",tbaluno[i].escolaridade);
        }
    }else{
        printf("Nenhum aluno cadastrado!\n\n");
    }
}

void relatorioCursos(){
    printf("========== RELATÓRIO DE CURSOS CADASTRADOS ==========\n");
    printf("Total de cursos cadastrados: %d\n\n", idc);
    if (idc>0){
        for (int i=0;i<idc;i++){
            printf("Código do Curso: %d ",tbcurso[i].pk_codCurso);
            printf("\nNome: %s ",tbcurso[i].nome);
            printf("\nCarga Horária: %d ",tbcurso[i].cargaHoraria);
            printf("\nModalidade: %s \n\n",tbcurso[i].modalidade);
        }
    }else{
        printf("Nenhum curso cadastrado!\n\n");
    }
}

void relatorioTurmas(){
    printf("========== RELATÓRIO DE TURMAS CADASTRADAS ==========\n");
    printf("Total de turmas cadastradas: %d\n\n", idt);
    if (idt>0){
        for (int i=0;i<idt;i++){
            printf("Código da Turma: %d ",tbturma[i].pk_codTurma);
            printf("\nNome da Turma: %s ",tbturma[i].nomeTurma);
            printf("\nQuantidade de Alunos: %d ",tbturma[i].qtdAlunos);
            printf("\nTurno: %s \n\n",tbturma[i].turno);
        }
    }else{
        printf("Nenhuma turma cadastrada!\n\n");
    }
}

void relatorioMatriculas(){
    printf("========== RELATÓRIO DE MATRÍCULAS CADASTRADAS ==========\n");
    printf("Total de matrículas cadastradas: %d\n\n", idm);
    if (idm>0){
        for (int i=0;i<idm;i++){
            printf("Registro do Aluno: %d ",tbmatricula[i].pk_ra);
            printf("\nCPF do Aluno: %s ",tbmatricula[i].fk_cpf);
            printf("\nCódigo da Turma: %d ",tbmatricula[i].fk_codTurma);
            printf("\nCódigo do Curso: %d \n\n",tbmatricula[i].fk_codCurso);
        }
    }else{
        printf("Nenhuma matrícula cadastrada!\n\n");
    }
}

void relatorioGeral(){
    printf("############### RELATÓRIO GERAL DO SISTEMA ###############\n\n");
    relatorioAlunos();
    relatorioCursos();
    relatorioTurmas();
    relatorioMatriculas();
}

// --- CONSULTA CRUZADA ---
void consulta_cruzada_matricula(int ra){
    int idx = buscar_matricula_index(ra);
    if (idx == -1){
        system("clear");
        printf("Matrícula não encontrada!\n");
        sleep(5);
        return;
    }
    int ia = buscar_aluno_index(tbmatricula[idx].fk_cpf);
    int ic = buscar_curso_index(tbmatricula[idx].fk_codCurso);
    int it = buscar_turma_index(tbmatricula[idx].fk_codTurma);

    system("clear");
    printf("========== CONSULTA CRUZADA DA MATRÍCULA ==========\n\n");
    printf("Registro do Aluno (RA): %d\n\n", tbmatricula[idx].pk_ra);

    printf("CPF do Aluno (fk_cpf): %s\n", tbmatricula[idx].fk_cpf);
    printf("Nome do Aluno: %s\n\n", (ia != -1) ? tbaluno[ia].nome : "(aluno não encontrado)");

    printf("Código do Curso (fk_codCurso): %d\n", tbmatricula[idx].fk_codCurso);
    printf("Nome do Curso: %s\n\n", (ic != -1) ? tbcurso[ic].nome : "(curso não encontrado)");

    printf("Código da Turma (fk_codTurma): %d\n", tbmatricula[idx].fk_codTurma);
    printf("Nome da Turma: %s\n\n", (it != -1) ? tbturma[it].nomeTurma : "(turma não encontrada)");
    sleep(5);
}

// --- DADOS DE TESTE ---
void popularDados(){
    // 5 ALUNOS
    strcpy(tbaluno[0].pk_cpf,"111.111.111-11"); strcpy(tbaluno[0].nome,"Ana Souza");      strcpy(tbaluno[0].admissao,"01/02/2023"); strcpy(tbaluno[0].dtNasc,"15/05/2000"); strcpy(tbaluno[0].escolaridade,"Ensino Medio");
    strcpy(tbaluno[1].pk_cpf,"222.222.222-22"); strcpy(tbaluno[1].nome,"Bruno Lima");      strcpy(tbaluno[1].admissao,"10/03/2023"); strcpy(tbaluno[1].dtNasc,"20/08/1999"); strcpy(tbaluno[1].escolaridade,"Superior Incompleto");
    strcpy(tbaluno[2].pk_cpf,"333.333.333-33"); strcpy(tbaluno[2].nome,"Carla Dias");      strcpy(tbaluno[2].admissao,"05/04/2023"); strcpy(tbaluno[2].dtNasc,"30/11/2001"); strcpy(tbaluno[2].escolaridade,"Ensino Medio");
    strcpy(tbaluno[3].pk_cpf,"444.444.444-44"); strcpy(tbaluno[3].nome,"Diego Alves");     strcpy(tbaluno[3].admissao,"12/05/2023"); strcpy(tbaluno[3].dtNasc,"02/02/1998"); strcpy(tbaluno[3].escolaridade,"Superior Completo");
    strcpy(tbaluno[4].pk_cpf,"555.555.555-55"); strcpy(tbaluno[4].nome,"Elena Castro");    strcpy(tbaluno[4].admissao,"20/06/2023"); strcpy(tbaluno[4].dtNasc,"25/12/2002"); strcpy(tbaluno[4].escolaridade,"Ensino Medio");
    ida = 5;

    // 5 CURSOS
    tbcurso[0].pk_codCurso=101; strcpy(tbcurso[0].nome,"Logica de Programacao"); tbcurso[0].cargaHoraria=60;  strcpy(tbcurso[0].modalidade,"Presencial");
    tbcurso[1].pk_codCurso=102; strcpy(tbcurso[1].nome,"Banco de Dados");        tbcurso[1].cargaHoraria=80;  strcpy(tbcurso[1].modalidade,"Online");
    tbcurso[2].pk_codCurso=103; strcpy(tbcurso[2].nome,"Desenvolvimento Web");   tbcurso[2].cargaHoraria=120; strcpy(tbcurso[2].modalidade,"Semi-Presencial");
    tbcurso[3].pk_codCurso=104; strcpy(tbcurso[3].nome,"Redes de Computadores"); tbcurso[3].cargaHoraria=90;  strcpy(tbcurso[3].modalidade,"Presencial");
    tbcurso[4].pk_codCurso=105; strcpy(tbcurso[4].nome,"Inteligencia Artificial"); tbcurso[4].cargaHoraria=100; strcpy(tbcurso[4].modalidade,"Online");
    idc = 5;

    // 5 TURMAS
    tbturma[0].pk_codTurma=1; strcpy(tbturma[0].nomeTurma,"Turma A"); tbturma[0].qtdAlunos=30; strcpy(tbturma[0].turno,"Manha");
    tbturma[1].pk_codTurma=2; strcpy(tbturma[1].nomeTurma,"Turma B"); tbturma[1].qtdAlunos=25; strcpy(tbturma[1].turno,"Tarde");
    tbturma[2].pk_codTurma=3; strcpy(tbturma[2].nomeTurma,"Turma C"); tbturma[2].qtdAlunos=40; strcpy(tbturma[2].turno,"Noite");
    tbturma[3].pk_codTurma=4; strcpy(tbturma[3].nomeTurma,"Turma D"); tbturma[3].qtdAlunos=20; strcpy(tbturma[3].turno,"Manha");
    tbturma[4].pk_codTurma=5; strcpy(tbturma[4].nomeTurma,"Turma E"); tbturma[4].qtdAlunos=35; strcpy(tbturma[4].turno,"Noite");
    idt = 5;

    // 5 MATRICULAS (FKs consistentes com os dados acima)
    tbmatricula[0].pk_ra=1001; strcpy(tbmatricula[0].fk_cpf,"111.111.111-11"); tbmatricula[0].fk_codTurma=1; tbmatricula[0].fk_codCurso=101;
    tbmatricula[1].pk_ra=1002; strcpy(tbmatricula[1].fk_cpf,"222.222.222-22"); tbmatricula[1].fk_codTurma=2; tbmatricula[1].fk_codCurso=102;
    tbmatricula[2].pk_ra=1003; strcpy(tbmatricula[2].fk_cpf,"333.333.333-33"); tbmatricula[2].fk_codTurma=3; tbmatricula[2].fk_codCurso=103;
    tbmatricula[3].pk_ra=1004; strcpy(tbmatricula[3].fk_cpf,"444.444.444-44"); tbmatricula[3].fk_codTurma=4; tbmatricula[3].fk_codCurso=104;
    tbmatricula[4].pk_ra=1005; strcpy(tbmatricula[4].fk_cpf,"555.555.555-55"); tbmatricula[4].fk_codTurma=5; tbmatricula[4].fk_codCurso=105;
    idm = 5;
}

void main()
{
    setlocale(LC_ALL, "");
    popularDados();
    do{
        system("clear");
        menu();
        printf("Escolha a opção desejada: ");
        scanf("%d",&op);
        system("clear");
        switch(op){
            case 1:
                subMenu();
                printf("Escolha a opção desejada: ");
                scanf("%d",&sop);
                system("clear");
                switch(sop){
                    case 1:
                        if (ida >= max) {
                            printf("Limite máximo de alunos cadastrados atingido!\n");
                            sleep(3);
                            break;
                        }
                        do{
                            do{
                                do{
                                    system("clear");
                                    printf("Exemplo: 000.000.000-00\nCPF: ");
                                    getchar();
                                    scanf("%s",&a.pk_cpf);
                                    a.pk_cpf[strcspn(a.pk_cpf,"\n")] ='\0';
                                    cont=strlen(a.pk_cpf);
                                }while(cont!=14 || validar_formato_cpf(a.pk_cpf) == false);
                                if (ida>0) enc=buscar_aluno_pk_cpf(a.pk_cpf);
                                if (enc==true) {
                                    printf("CPF já cadastrado!\n");
                                    sleep(3);
                                }
                            }while(enc==true);
                            
                            getchar();
                            do {
                                printf("Nome do Aluno (obrigatório): ");
                                fgets(a.nome,sizeof(a.nome),stdin);
                                a.nome[strcspn(a.nome,"\n")] ='\0';
                            } while (strlen(a.nome) == 0);
                            
                            do {
                                printf("Admissão (DD/MM/AAAA): ");
                                scanf("%s",a.admissao);
                                a.admissao[strcspn(a.admissao,"\n")] ='\0';
                            } while (validar_formato_data(a.admissao) == false);
                            
                            do {
                                printf("Data de Nascimento (DD/MM/AAAA): ");
                                getchar();
                                scanf("%s",a.dtNasc);
                                a.dtNasc[strcspn(a.dtNasc,"\n")] ='\0';
                            } while (validar_formato_data(a.dtNasc) == false);
                            
                            getchar();
                            do {
                                printf("Escolaridade (obrigatório): ");
                                fgets(a.escolaridade,sizeof(a.escolaridade),stdin);
                                a.escolaridade[strcspn(a.escolaridade,"\n")] ='\0';
                            } while (strlen(a.escolaridade) == 0);
                            
                            tbaluno[ida]=a;
                            ida++;
                            printf("\nDeseja continuar cadastrando [s/n]: ");
                            scanf(" %c",&resp);
                        }while((ida<max) && (tolower(resp)=='s'));
                        break;
                    case 2:
                        if (idc >= max) {
                            printf("Limite máximo de cursos cadastrados atingido!\n");
                            sleep(3);
                            break;
                        }
                        do{
                            do{
                                system("clear");
                                printf("codCurso: ");
                                scanf("%d",&c.pk_codCurso);
                                if (idc>0) enc=buscar_curso_pk_codCurso(c.pk_codCurso);
                                if (enc==true) {
                                    printf("Código já cadastrado!\n");
                                    sleep(3);
                                }
                            }while(enc==true);
                            
                            getchar();
                            do {
                                printf("Nome do Curso (obrigatório): ");
                                fgets(c.nome,sizeof(c.nome),stdin);
                                c.nome[strcspn(c.nome,"\n")] ='\0';
                            } while (strlen(c.nome) == 0);
                            
                            printf("cargaHoraria: ");
                            scanf("%d",&c.cargaHoraria);
                            
                            do {
                                printf("modalidade (obrigatório): ");
                                scanf("%s",&c.modalidade);
                            } while (strlen(c.modalidade) == 0);
                            
                            tbcurso[idc]=c;
                            idc++;
                            printf("\nDeseja continuar cadastrando [s/n]: ");
                            scanf(" %c",&resp);
                        }while((idc<max) && (tolower(resp)=='s'));
                        break;
                    case 3:
                        if (idt >= max) {
                            printf("Limite máximo de turmas cadastradas atingido!\n");
                            sleep(3);
                            break;
                        }
                        do{
                            do{
                                system("clear");
                                printf("Código da Turma: ");
                                scanf("%d",&t.pk_codTurma);
                                if (idt>0) enc=buscar_turma_pk_codTurma(t.pk_codTurma);
                                if (enc==true) {
                                    printf("Código já cadastrado!\n");
                                    sleep(3);
                                }
                            }while(enc==true);
                            
                            getchar();
                            do {
                                printf("Nome da Turma (obrigatório): ");
                                fgets(t.nomeTurma,sizeof(t.nomeTurma),stdin);
                                t.nomeTurma[strcspn(t.nomeTurma,"\n")] ='\0';
                            } while(strlen(t.nomeTurma) == 0);
                            
                            printf("Quantidade de Alunos: ");
                            scanf("%d",&t.qtdAlunos);
                            
                            do {
                                printf("Turno (obrigatório): ");
                                scanf("%s",&t.turno);
                            } while(strlen(t.turno) == 0);
                            
                            tbturma[idt]=t;
                            idt++;
                            printf("\nDeseja continuar cadastrando [s/n]: ");
                            scanf(" %c",&resp);
                        }while((idt<max) && (tolower(resp)=='s'));
                        break;
                    case 4:
                        if (idm >= max) {
                            printf("Limite máximo de matrículas cadastradas atingido!\n");
                            sleep(3);
                            break;
                        }
                        if ((ida>0)&&(idc>0)&&(idt>0)){
                            do{
                                do{
                                    system("clear");
                                    printf("Registro do Aluno: ");
                                    scanf("%d",&m.pk_ra);
                                    if (idm>0) enc=buscar_matricula_pk_ra(m.pk_ra);
                                    if (enc==true) {
                                        printf("Registro do aluno já foi cadastrado!\n");
                                        sleep(3);
                                    }
                                }while(enc==true);
                                
                                do{
                                    system("clear");
                                    printf("CPF: ");
                                    scanf("%s",&m.fk_cpf);
                                    if (ida>0) enc_fk=buscar_aluno_pk_cpf(m.fk_cpf);
                                    if (enc_fk==false) {
                                        printf("CPF não cadastrado!\n");
                                        sleep(3);
                                    }
                                }while(enc_fk==false);
                                
                                do{
                                    system("clear");
                                    printf("codTurma: ");
                                    scanf("%d",&m.fk_codTurma);
                                    if (idt>0) enc_fk=buscar_turma_pk_codTurma(m.fk_codTurma);
                                    if (enc_fk==false) {
                                        printf("Código não cadastrado!\n");
                                        sleep(3);
                                    }
                                }while(enc_fk==false);
                                
                                do{
                                    system("clear");
                                    printf("codCurso: ");
                                    scanf("%d",&m.fk_codCurso);
                                    if (idc>0) enc_fk=buscar_curso_pk_codCurso(m.fk_codCurso);
                                    if (enc_fk==false) {
                                        printf("Código não cadastrado!\n");
                                        sleep(3);
                                    }
                                }while(enc_fk==false);
                                
                                tbmatricula[idm]=m;
                                idm++;
                                printf("\nDeseja continuar cadastrando [s/n]: ");
                                scanf(" %c",&resp);
                            }while((idt<max) && (tolower(resp)=='s'));
                        }else{
                            printf("Relação de dependência ainda consta sem cadastro\n");
                            sleep(3);
                        }
                        break;
                    default:
                        if (sop!=5) {
                            printf("Opção inválida!");
                            sleep(3);
                        }
                        break;
                    }
                    break;
            case 2: // CONSULTAR COMPLETO
                subMenu();
                printf("Escolha a opção desejada: ");
                scanf("%d",&sop);
                system("clear");
                switch(sop){
                    case 1:
                        printf("Digite o CPF: ");
                        scanf("%s",&cpf);
                        buscar_aluno(cpf);
                        break;
                    case 2:
                        printf("Digite o Código do Curso: ");
                        scanf("%d",&id_busca);
                        buscar_curso(id_busca);
                        break;
                    case 3:
                        printf("Digite o Código da Turma: ");
                        scanf("%d",&id_busca);
                        buscar_turma(id_busca);
                        break;
                    case 4:
                        printf("Digite o RA: ");
                        scanf("%d",&id_busca);
                        buscar_matricula(id_busca);
                        break;
                }
                break;
            case 3: // ALTERAR
                subMenu();
                printf("Escolha a opção desejada: ");
                scanf("%d", &sop);
                limparBuffer();
                system("clear");

                if (sop == 1) {
                    printf("Digite o CPF do Aluno a ser alterado: ");
                    scanf("%14s", cpf); limparBuffer();
                    idx = buscar_aluno_index(cpf);
                    if (idx != -1) {
                        printf("Novo Nome (Atual: %s): ", tbaluno[idx].nome);
                        fgets(tbaluno[idx].nome, max, stdin); tbaluno[idx].nome[strcspn(tbaluno[idx].nome, "\n")] = '\0';
                        printf("Nova Admissão (Atual: %s): ", tbaluno[idx].admissao);
                        scanf("%10s", tbaluno[idx].admissao); limparBuffer();
                        printf("Nova Data de Nascimento (Atual: %s): ", tbaluno[idx].dtNasc);
                        scanf("%10s", tbaluno[idx].dtNasc); limparBuffer();
                        printf("Nova Escolaridade (Atual: %s): ", tbaluno[idx].escolaridade);
                        fgets(tbaluno[idx].escolaridade, max, stdin); tbaluno[idx].escolaridade[strcspn(tbaluno[idx].escolaridade, "\n")] = '\0';
                        printf("Dados alterados com sucesso!\n");
                    } else printf("Aluno não encontrado.\n");
                } else if (sop == 2) {
                    printf("Digite o Código do Curso a ser alterado: ");
                    scanf("%d", &id_busca); limparBuffer();
                    idx = buscar_curso_index(id_busca);
                    if (idx != -1) {
                        printf("Novo Nome do Curso (Atual: %s): ", tbcurso[idx].nome);
                        fgets(tbcurso[idx].nome, max, stdin); tbcurso[idx].nome[strcspn(tbcurso[idx].nome, "\n")] = '\0';
                        printf("Nova Carga Horária (Atual: %d): ", tbcurso[idx].cargaHoraria);
                        scanf("%d", &tbcurso[idx].cargaHoraria); limparBuffer();
                        printf("Nova Modalidade (Atual: %s): ", tbcurso[idx].modalidade);
                        scanf("%19s", tbcurso[idx].modalidade); limparBuffer();
                        printf("Dados alterados com sucesso!\n");
                    } else printf("Curso não encontrado.\n");
                } else if (sop == 3) {
                    printf("Digite o Código da Turma a ser alterada: ");
                    scanf("%d", &id_busca); limparBuffer();
                    idx = buscar_turma_index(id_busca);
                    if (idx != -1) {
                        printf("Novo Nome da Turma (Atual: %s): ", tbturma[idx].nomeTurma);
                        fgets(tbturma[idx].nomeTurma, max, stdin); tbturma[idx].nomeTurma[strcspn(tbturma[idx].nomeTurma, "\n")] = '\0';
                        printf("Nova Quantidade de Alunos (Atual: %d): ", tbturma[idx].qtdAlunos);
                        scanf("%d", &tbturma[idx].qtdAlunos); limparBuffer();
                        printf("Novo Turno (Atual: %s): ", tbturma[idx].turno);
                        scanf("%19s", tbturma[idx].turno); limparBuffer();
                        printf("Dados alterados com sucesso!\n");
                    } else printf("Turma não encontrada.\n");
                } else if (sop == 4) {
                    printf("Digite o RA da Matrícula a ser alterada: ");
                    scanf("%d", &id_busca); limparBuffer();
                    idx = buscar_matricula_index(id_busca);
                    if (idx != -1) {
                        do {
                            printf("Novo CPF do Aluno Existente: "); scanf("%14s", tbmatricula[idx].fk_cpf); limparBuffer();
                            enc_fk = buscar_aluno_pk_cpf(tbmatricula[idx].fk_cpf);
                            if (!enc_fk) printf("CPF não cadastrado!\n");
                        } while(!enc_fk);
                        do {
                            printf("Novo Código da Turma Existente: "); scanf("%d", &tbmatricula[idx].fk_codTurma); limparBuffer();
                            enc_fk = buscar_turma_pk_codTurma(tbmatricula[idx].fk_codTurma);
                            if (!enc_fk) printf("Código não cadastrado!\n");
                        } while(!enc_fk);
                        do {
                            printf("Novo Código do Curso Existente: "); scanf("%d", &tbmatricula[idx].fk_codCurso); limparBuffer();
                            enc_fk = buscar_curso_pk_codCurso(tbmatricula[idx].fk_codCurso);
                            if (!enc_fk) printf("Código não cadastrado!\n");
                        } while(!enc_fk);
                        printf("Matrícula alterada com sucesso!\n");
                    } else printf("Matrícula não encontrada.\n");
                }
                sleep(2);
                break;

            case 4: // EXCLUIR
                subMenu();
                printf("Escolha a opção desejada: ");
                scanf("%d", &sop);
                limparBuffer();
                system("clear");

                if (sop == 1) {
                    printf("Digite o CPF do Aluno a ser excluído: ");
                    scanf("%14s", cpf); limparBuffer();
                    idx = buscar_aluno_index(cpf);
                    if (idx != -1) {
                        if (matricula_vinculada_aluno(cpf)) {
                            printf("Não é possível excluir: existe matrícula vinculada a este aluno!\n");
                        } else {
                            for(int i = idx; i < ida - 1; i++) tbaluno[i] = tbaluno[i+1];
                            ida--; printf("Aluno excluído com sucesso!\n");
                        }
                    } else printf("Aluno não encontrado.\n");
                } else if (sop == 2) {
                    printf("Digite o Código do Curso a ser excluído: ");
                    scanf("%d", &id_busca); limparBuffer();
                    idx = buscar_curso_index(id_busca);
                    if (idx != -1) {
                        if (matricula_vinculada_curso(id_busca)) {
                            printf("Não é possível excluir: existe matrícula vinculada a este curso!\n");
                        } else {
                            for(int i = idx; i < idc - 1; i++) tbcurso[i] = tbcurso[i+1];
                            idc--; printf("Curso excluído com sucesso!\n");
                        }
                    } else printf("Curso não encontrado.\n");
                } else if (sop == 3) {
                    printf("Digite o Código da Turma a ser excluída: ");
                    scanf("%d", &id_busca); limparBuffer();
                    idx = buscar_turma_index(id_busca);
                    if (idx != -1) {
                        if (matricula_vinculada_turma(id_busca)) {
                            printf("Não é possível excluir: existe matrícula vinculada a esta turma!\n");
                        } else {
                            for(int i = idx; i < idt - 1; i++) tbturma[i] = tbturma[i+1];
                            idt--; printf("Turma excluída com sucesso!\n");
                        }
                    } else printf("Turma não encontrada.\n");
                } else if (sop == 4) {
                    printf("Digite o RA da Matrícula a ser excluída: ");
                    scanf("%d", &id_busca); limparBuffer();
                    idx = buscar_matricula_index(id_busca);
                    if (idx != -1) {
                        for(int i = idx; i < idm - 1; i++) tbmatricula[i] = tbmatricula[i+1];
                        idm--; printf("Matrícula excluída com sucesso!\n");
                    } else printf("Matrícula não encontrada.\n");
                }
                sleep(2);
                break;
            case 5:
                system("clear");
                submenuOrdenar();
                printf("Escolha a opção desejada: ");
                scanf("%d",&sop);
                system("clear");
                int idop=sop;
                switch(idop){
                   case 1 ... 2:
                      subMenu();
                      printf("Escolha a opção desejada: ");
                      scanf("%d",&sop);
                      int entidade = sop;
                      switch(entidade){
                         case 1 ... 4:
                            submenuOpcaoOrdenar(entidade);
                            printf("Escolha a opção desejada: ");
                            scanf("%d",&sop);
                            if (sop>0 && sop<3){
                                ordenar(idop,entidade,sop);
                                printf("Lista ordenada com sucesso! \n");
                            }else{
                                if (sop!=3) printf("Opção inválida!\n");
                            }
                            if (sop!=3) sleep(3);
                            break;
                      }
                      break;
                   default:
                        if (sop!=3) {
                            printf("Opção inválida!");
                            sleep(3);
                        }
                        break;
                }
                break;
            case 6:
                subMenu();
                printf("Escolha a opção desejada: ");
                scanf("%d",&sop);
                if ((sop>0)&&(sop<5)){
                    imprimir(sop);
                    sleep(5);
                }
                break;
            case 7: // RELATÓRIOS
                submenuRelatorios();
                printf("Escolha a opção desejada: ");
                scanf("%d",&sop);
                system("clear");
                switch(sop){
                    case 1:
                        relatorioAlunos();
                        sleep(5);
                        break;
                    case 2:
                        relatorioCursos();
                        sleep(5);
                        break;
                    case 3:
                        relatorioTurmas();
                        sleep(5);
                        break;
                    case 4:
                        relatorioMatriculas();
                        sleep(5);
                        break;
                    case 5:
                        relatorioGeral();
                        sleep(5);
                        break;
                    default:
                        if (sop!=6) {
                            printf("Opção inválida!");
                            sleep(3);
                        }
                        break;
                }
                break;
            case 8: // CONSULTA CRUZADA
                printf("Digite o RA da Matrícula: ");
                scanf("%d",&id_busca);
                consulta_cruzada_matricula(id_busca);
                break;
        }
    }while(op!=9);
    system("clear");
    printf("Sistema finalizado com sucesso!");
}