#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

/*  inclui a biblioteca windows.h apenas quando o código está sendo compilado no Windows.
  do console para forçar o codigo para UTF-8. 
  Sem isso, os acentos aparecem como caracteres 
  estranhos quando o programa roda no cmd. */
  
#ifdef _WIN32
    #include <windows.h>
#endif

/* Tamanho máximo da pilha */
#define MAX 100

/* Estrutura que representa uma chamada de emergência */
typedef struct {
    int protocolo;      // Identificador único da chamada
    char local[50];     // Local da ocorrência
    char tipo[30];      // Tipo da emergência
    char horario[20];   // Horário da chamada
} Chamada;

/* Vetor utilizado para armazenar a pilha */
Chamada pilha[MAX];

/* Controle do topo da pilha */
int topo = -1;

/* Próximo protocolo disponível */
int proxProtocolo = 1001;

/* Quantidade de chamadas atendidas */
int chamadasAtendidas = 0;

/* ==================================================
   CONFIGURAR CONSOLE
   Ajusta o terminal para exibir corretamente os
   acentos da língua portuguesa.
   ================================================== */
void configurarConsole() {

#ifdef _WIN32
    /* 65001 = UTF-8. Força a saída e a entrada do
       console do Windows a usarem UTF-8. */
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    /* Mantém o locale do sistema (útil para funções
       que dependem de idioma, como ordenação). */
    setlocale(LC_ALL, "");
}

/* ==================================================
   LIMPAR TELA
   Limpa a tela do terminal.

   - No Windows o comando  é "cls".
   - No Linux/Mac o comando é "clear".

   ================================================== */
void limparTela() {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* ==================================================
   PAUSAR
   Pausa a execução até o usuário apertar ENTER.

   Serve para o usuário conseguir ler as informações
   na tela antes do programa voltar para o menu e
   limpar tudo.
   ================================================== */
void pausar() {

    int c;

    printf("\nAperte ENTER para prosseguir...");

    /* Lê e descarta tudo até encontrar a quebra de
       linha (o ENTER) ou o fim de arquivo. */
    while((c = getchar()) != '\n' && c != EOF);
}

/* ==================================================
   Valida se o horário está no formato HH:MM
   Retorna:
   1 -> válido
   0 -> inválido
   ================================================== */
int validarHorario(char horario[]) {

    /* Verifica tamanho da string */
    if(strlen(horario) != 5)
        return 0;

    /* Verifica presença dos dois pontos */
    if(horario[2] != ':')
        return 0;

    /* Verifica se os demais caracteres são números */
    if(!isdigit(horario[0]) ||
       !isdigit(horario[1]) ||
       !isdigit(horario[3]) ||
       !isdigit(horario[4]))
        return 0;

    /* Converte a parte da hora */
    int hora =
        (horario[0] - '0') * 10 +
        (horario[1] - '0');

    /* Converte a parte dos minutos */
    int minuto =
        (horario[3] - '0') * 10 +
        (horario[4] - '0');

    /* Verifica limites válidos */
    return (hora >= 0 &&
            hora <= 23 &&
            minuto >= 0 &&
            minuto <= 59);
}

/* ==================================================
   PUSH
   Adiciona uma nova chamada no topo da pilha.
   ================================================== */
void registrarChamada(char local[],
                      char tipo[],
                      char horario[]) {

    /* Verifica se a pilha está cheia */
    if(topo == MAX - 1) {
        printf("\nPilha cheia!\n");
        return;
    }

    /* Avança para a próxima posição */
    topo++;

    /* Gera protocolo automático */
    pilha[topo].protocolo = proxProtocolo++;

    /* Copia os dados para a pilha */
    strcpy(pilha[topo].local, local);
    strcpy(pilha[topo].tipo, tipo);
    strcpy(pilha[topo].horario, horario);

    printf("\nChamada registrada com sucesso!\n");
    printf("Protocolo: %d\n",
           pilha[topo].protocolo);
}

/* ==================================================
   POP
   Remove a chamada do topo da pilha.
   ================================================== */
void atenderChamada() {

    /* Verifica se existem chamadas */
    if(topo == -1) {
        printf("\nPilha vazia!\n");
        return;
    }

    printf("\nAtendendo chamada...\n");

    printf("Protocolo: %d\n",
           pilha[topo].protocolo);

    /* Incrementa estatística */
    chamadasAtendidas++;

    /* Remove elemento do topo */
    topo--;
}

/* ==================================================
   PEEK
   Exibe a chamada do topo sem removê-la.
   ================================================== */
void consultarChamada() {

    /* Verifica se a pilha está vazia */
    if(topo == -1) {
        printf("\nNenhuma chamada registrada!\n");
        return;
    }

    printf("\n===== ÚLTIMA CHAMADA =====\n");

    printf("Protocolo: %d\n",
           pilha[topo].protocolo);

    printf("Local: %s\n",
           pilha[topo].local);

    printf("Tipo: %s\n",
           pilha[topo].tipo);

    printf("Horário: %s\n",
           pilha[topo].horario);
}

/* ==================================================
   LISTAR
   Exibe todas as chamadas da pilha do topo
   para a base.
   ================================================== */
void listarChamadas() {

    /* Verifica se existem elementos */
    if(topo == -1) {
        printf("\nNenhuma chamada registrada.\n");
        return;
    }

    printf("\n===== PILHA DE CHAMADAS =====\n");

    /* Percorre do topo para a base */
    for(int i = topo; i >= 0; i--) {

        printf("\n-------------------------\n");

        printf("Protocolo: %d\n",
               pilha[i].protocolo);

        printf("Local: %s\n",
               pilha[i].local);

        printf("Tipo: %s\n",
               pilha[i].tipo);

        printf("Horário: %s\n",
               pilha[i].horario);
    }
}

/* ==================================================
   SALVAR CSV
   Grava todas as chamadas no arquivo CSV.
   ================================================== */
void salvarCSV() {

    /* Cria ou sobrescreve o arquivo */
    FILE *arq =
        fopen("chamadas.csv", "w");

    if(!arq) {
        printf("\nErro ao criar arquivo.\n");
        return;
    }

    /* Cabeçalho do CSV */
    fprintf(arq,
            "protocolo;local;tipo;horario\n");

    /* Salva todos os registros */
    for(int i = 0; i <= topo; i++) {

        fprintf(arq,
                "%d;%s;%s;%s\n",
                pilha[i].protocolo,
                pilha[i].local,
                pilha[i].tipo,
                pilha[i].horario);
    }

    fclose(arq);

    printf("\nArquivo salvo com sucesso!\n");
}

/* ==================================================
   CARREGAR CSV
   Lê os registros do arquivo chamadas.csv e
   reconstrói a pilha preservando sua ordem.
   ================================================== */
void carregarCSV() {

    /* Abre o arquivo para leitura */
    FILE *arq =
        fopen("chamadas.csv", "r");

    /* Verifica se o arquivo existe */
    if(!arq) {
        printf("\nArquivo não encontrado.\n");
        return;
    }

    /* Reinicia a pilha antes do carregamento */
    topo = -1;

    char linha[200];

    /* Ignora o cabeçalho do CSV */
    fgets(linha, sizeof(linha), arq);

    /* Lê cada linha do arquivo */
    while(fgets(linha, sizeof(linha), arq)) {

        /* Verifica limite da pilha */
        if(topo == MAX - 1) {

            printf(
                "\nArquivo excede a capacidade da pilha.\n"
            );

            break;
        }

        topo++;

        /* Extrai os dados da linha */
        if(sscanf(
            linha,
            "%d;%49[^;];%29[^;];%19[^\n]",
            &pilha[topo].protocolo,
            pilha[topo].local,
            pilha[topo].tipo,
            pilha[topo].horario
        ) != 4) {

            topo--;
            continue;
        }

        /* Atualiza o próximo protocolo */
        if(pilha[topo].protocolo >= proxProtocolo)
            proxProtocolo =
                pilha[topo].protocolo + 1;
    }

    fclose(arq);

    printf("\nDados carregados com sucesso!\n");
}

/* ==================================================
   RELATÓRIO
   Exibe estatísticas do sistema.
   ================================================== */
void gerarRelatorio() {

    printf("\n===== RELATÓRIO =====\n");

    /* Quantidade de elementos na pilha */
    printf("Chamadas atualmente na pilha: %d\n",
           topo + 1);

    /* Quantidade total atendida */
    printf("Chamadas atendidas: %d\n",
           chamadasAtendidas);

    /* Mostra a última chamada registrada */
    if(topo != -1) {

        printf("\nÚltima chamada registrada:\n");

        printf("Protocolo: %d\n",
               pilha[topo].protocolo);

        printf("Local: %s\n",
               pilha[topo].local);
    }
}

/* ==================================================
   EXPORTAR RELATÓRIO TXT
   Salva as estatísticas em um arquivo texto.
   ================================================== */
void exportarRelatorioTXT() {

    /* Cria o arquivo relatório */
    FILE *arq =
        fopen("relatorio.txt", "w");

    if(!arq) {
        printf("\nErro ao gerar relatório.\n");
        return;
    }

    fprintf(arq,
            "===== RELATORIO =====\n\n");

    fprintf(arq,
            "Chamadas na pilha: %d\n",
            topo + 1);

    fprintf(arq,
            "Chamadas atendidas: %d\n",
            chamadasAtendidas);

    fclose(arq);

    printf(
        "\nRelatório exportado para relatorio.txt\n"
    );
}

/* ==================================================
   LIMPAR PILHA
   Remove todas as chamadas da pilha mediante
   confirmação do usuário.
   ================================================== */
void limparPilha() {

    char op;

    printf(
        "\nDeseja realmente apagar todas as chamadas? (S/N): "
    );

    scanf(" %c", &op);

    /* Limpa o restante da linha (incluindo o ENTER)
       para não atrapalhar a próxima leitura/pausa. */
    while(getchar() != '\n');

    /* Confirma a operação */
    if(toupper(op) == 'S') {

        topo = -1;

        printf(
            "\nPilha limpa com sucesso!\n"
        );
    }
    else {

        printf(
            "\nOperação cancelada.\n"
        );
    }
}

/* ==================================================
   MENU
   Exibe as opções disponíveis para o usuário.
   ================================================== */
void menu() {

    printf("\n====================================\n");
    printf("   SISTEMA DE CHAMADAS EMERGÊNCIA\n");
    printf("====================================\n");

    printf("1 - Registrar chamada\n");
    printf("2 - Atender chamada\n");
    printf("3 - Consultar última chamada\n");
    printf("4 - Listar chamadas\n");
    printf("5 - Salvar CSV\n");
    printf("6 - Carregar CSV\n");
    printf("7 - Gerar relatório\n");
    printf("8 - Exportar relatório TXT\n");
    printf("9 - Limpar pilha\n");
    printf("0 - Sair\n");
}

/* ==================================================
   MAIN
   Função principal do programa.

   Responsável por:
   - Configurar o console (acentos).
   - Limpar a tela e exibir o menu.
   - Ler a opção do usuário.
   - Direcionar para a função correspondente.
   - Pausar a tela para o usuário ler o resultado.
   - Manter o sistema em execução até a saída.
   ================================================== */
int main() {

    /* Configura acentuação e codificação do console */
    configurarConsole();

    int op;

    char local[50];
    char tipo[30];
    char horario[20];

    /* Loop principal do sistema */
    do {

        /* Limpa a tela antes de mostrar o menu */
        limparTela();

        menu();

        printf("\nOpção: ");

        /* Valida entrada numérica */
        if(scanf("%d", &op) != 1) {

            printf("\nDigite apenas números!\n");

            /* Limpa o buffer de entrada inválida */
            while(getchar() != '\n');

            /* Pausa para o usuário ler o aviso */
            pausar();

            continue;
        }

        /* Consome o ENTER deixado pelo scanf */
        getchar();

        switch(op) {

        /* Registrar chamada */
        case 1:

            printf("\nLocal: ");
            fgets(local, sizeof(local), stdin);
            local[strcspn(local, "\n")] = '\0';

            printf("Tipo: ");
            fgets(tipo, sizeof(tipo), stdin);
            tipo[strcspn(tipo, "\n")] = '\0';

            /* Solicita horário válido */
            do {

                printf("Horário (HH:MM): ");

                fgets(horario,
                      sizeof(horario),
                      stdin);

                horario[
                    strcspn(
                        horario,
                        "\n"
                    )
                ] = '\0';

                if(!validarHorario(horario))
                    printf(
                        "Horário inválido!\n"
                    );

            } while(!validarHorario(horario));

            registrarChamada(
                local,
                tipo,
                horario
            );

            break;

        /* Atender chamada */
        case 2:
            atenderChamada();
            break;

        /* Consultar topo */
        case 3:
            consultarChamada();
            break;

        /* Listar pilha */
        case 4:
            listarChamadas();
            break;

        /* Salvar CSV */
        case 5:
            salvarCSV();
            break;

        /* Carregar CSV */
        case 6:
            carregarCSV();
            break;

        /* Relatório */
        case 7:
            gerarRelatorio();
            break;

        /* Exportar relatório */
        case 8:
            exportarRelatorioTXT();
            break;

        /* Limpar pilha */
        case 9:
            limparPilha();
            break;

        /* Encerrar sistema */
        case 0:
            printf("\nSistema encerrado.\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }

        /* Pausa a tela (exceto ao sair) para o usuário
           conseguir ler o resultado antes de voltar
           ao menu, que vai limpar a tela. */
        if(op != 0)
            pausar();

    } while(op != 0);

    return 0;
}
