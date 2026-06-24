#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Trabalho {
    int id;
    char arquivo[50];
    int paginas;
    char tipo;
    struct Trabalho* proximo;
} Trabalho;

typedef struct {
    Trabalho* inicio;
    Trabalho* fim;
} Fila;


/* ====================================================================
 * Método: limparBuffer
 * O que faz: Consome todos os caracteres restantes no buffer de entrada 
 * (stdin) até encontrar uma quebra de linha ('\n') ou o fim 
 * do arquivo (EOF).
 * Para que serve: Evitar que resíduos de digitação anterior (como a tecla 
 * 'Enter') quebrem ou pulem as próximas leituras via 'scanf'.
 * Condição: Deve ser chamado preferencialmente após o uso de 'scanf' para 
 * garantir a limpeza do estado da entrada do usuário.
 * ==================================================================== */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ====================================================================
 * Método: criarTrabalho
 * O que faz: Aloca dinamicamente a memória necessária para uma nova 
 * estrutura do tipo 'Trabalho' e inicializa seus atributos.
 * Para que serve: Criar o "nó" de dados que será posteriormente inserido 
 * em uma das filas de impressão.
 * Condição: Depende da disponibilidade de memória do sistema. Caso o 
 * 'malloc' falhe, exibe um erro crítico e retorna NULL.
 * ==================================================================== */
Trabalho* criarTrabalho(int id, char* arquivo, int paginas, char tipo) {
    Trabalho* novo = (Trabalho*) malloc(sizeof(Trabalho));
    if (novo == NULL) {
        printf("\nErro critico: Falha na alocacao de memoria!\n");
        return NULL;
    }
    novo->id = id;
    strcpy(novo->arquivo, arquivo);
    novo->paginas = paginas;
    novo->tipo = tipo;
    novo->proximo = NULL;
    return novo;
}

/* ====================================================================
 * Método: existeID
 * O que faz: Percorre tanto a fila prioritária quanto a normal buscando 
 * se o ID especificado já está cadastrado.
 * Para que serve: Garantir a integridade dos dados, impedindo que dois 
 * trabalhos possuam o mesmo identificador único (ID).
 * Condição: Retorna 1 (verdadeiro) se encontrar o ID em alguma fila, 
 * ou 0 (falso) caso o ID esteja livre. A busca na prioritária 
 * respeita a regra de parada da fila circular.
 * ==================================================================== */
int existeID(Fila* normal, Fila* prioritaria, int idBusca) {
    if (prioritaria->inicio != NULL) {
        Trabalho* atual = prioritaria->inicio;
        do {
            if (atual->id == idBusca) return 1;
            atual = atual->proximo;
        } while (atual != prioritaria->inicio);
    }
    Trabalho* atual = normal->inicio;
    while (atual != NULL) {
        if (atual->id == idBusca) return 1;
        atual = atual->proximo;
    }
    return 0;
}



/* ====================================================================
 * Método: enfileirarNormal
 * O que faz: Insere um novo trabalho na última posição da Fila Normal 
 * (fila encadeada simples).
 * Para que serve: Adicionar documentos de prioridade padrão à fila de 
 * espera de impressão.
 * Condição: Se a fila estiver vazia, ajusta o início e o fim para o 
 * novo elemento. Caso contrário, apenas anexa o novo elemento 
 * após o atual fim da fila.
 * ==================================================================== */
void enfileirarNormal(Fila* fila, Trabalho* novo) {
    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
    printf("\nTrabalho '%s' (ID: %d) enfileirado na Fila NORMAL com sucesso!\n", novo->arquivo, novo->id);
}

/* ====================================================================
 * Método: enfileirarPrioritaria
 * O que faz: Insere um novo trabalho na última posição da Fila Prioritária, 
 * mantendo a estrutura de lista encadeada circular.
 * Para que serve: Adicionar documentos urgentes na fila dedicada.
 * Condição: Se a fila estiver vazia, o novo elemento aponta para si 
 * mesmo (fechando o ciclo). Se não, é adicionado ao fim e 
 * seu ponteiro 'proximo' é direcionado para o início da fila.
 * ==================================================================== */
void enfileirarPrioritaria(Fila* fila, Trabalho* novo) {
    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
        novo->proximo = novo;
    } else {
        fila->fim->proximo = novo;
        novo->proximo = fila->inicio;
        fila->fim = novo;
    }
    printf("\nTrabalho '%s' (ID: %d) enfileirado na Fila PRIORITARIA com sucesso!\n", novo->arquivo, novo->id);
}

/* ====================================================================
 * Método: desenfileirarNormal
 * O que faz: Remove e retorna o primeiro elemento da Fila Normal.
 * Para que serve: Processar (imprimir) o documento de prioridade padrão 
 * que está há mais tempo aguardando (Regra FIFO).
 * Condição: Retorna NULL se a fila estiver vazia. Se remover o último 
 * elemento restante, o ponteiro de fim é atualizado para NULL 
 * para não deixar referências perdidas.
 * ==================================================================== */
Trabalho* desenfileirarNormal(Fila* fila) {
    if (fila->inicio == NULL) return NULL;
    Trabalho* removido = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    removido->proximo = NULL;
    return removido;
}

/* ====================================================================
 * Método: desenfileirarPrioritaria
 * O que faz: Remove e retorna o primeiro elemento da Fila Prioritária.
 * Para que serve: Processar (imprimir) o documento prioritário da vez.
 * Condição: Retorna NULL se vazia. Se houver apenas um elemento, limpa 
 * a fila (início e fim recebem NULL). Caso contrário, atualiza 
 * o início e refaz a ligação do fim para o novo início, 
 * mantendo a integridade circular.
 * ==================================================================== */
Trabalho* desenfileirarPrioritaria(Fila* fila) {
    if (fila->inicio == NULL) return NULL;
    Trabalho* removido = fila->inicio;
    if (fila->inicio == fila->fim) {
        fila->inicio = NULL;
        fila->fim = NULL;
    } else {
        fila->inicio = fila->inicio->proximo;
        fila->fim->proximo = fila->inicio;
    }
    removido->proximo = NULL;
    return removido;
}



/* ====================================================================
 * Método: listarFilas
 * O que faz: Percorre as duas filas de impressão e exibe no console 
 * os dados de todos os trabalhos na ordem de espera.
 * Para que serve: Fornecer ao usuário uma visualização clara do status 
 * atual de todas as requisições aguardando na impressora.
 * Condição: Verifica independentemente se as filas estão vazias antes 
 * de iniciar os laços de repetição, evitando falhas de leitura.
 * ==================================================================== */
void listarFilas(Fila* normal, Fila* prioritaria) {
    printf("\n========================================");
    printf("\n       STATUS DAS FILAS DE IMPRESSAO    ");
    printf("\n========================================\n");

    printf("--- FILA PRIORITARIA (Circular) ---\n");
    if (prioritaria->inicio == NULL) {
        printf(" [ Vazia ]\n");
    } else {
        Trabalho* atual = prioritaria->inicio;
        do {
            printf(" -> [ID: %d] %s (%d pags) - Tipo: %c\n",
                   atual->id, atual->arquivo, atual->paginas, atual->tipo);
            atual = atual->proximo;
        } while (atual != prioritaria->inicio);
    }

    printf("\n--- FILA NORMAL (Simples) ---\n");
    if (normal->inicio == NULL) {
        printf(" [ Vazia ]\n");
    } else {
        Trabalho* atual = normal->inicio;
        while (atual != NULL) {
            printf(" -> [ID: %d] %s (%d pags) - Tipo: %c\n",
                   atual->id, atual->arquivo, atual->paginas, atual->tipo);
            atual = atual->proximo;
        }
    }
    printf("========================================\n");
}

/* ====================================================================
 * Método: buscarTrabalhoPorID
 * O que faz: Recebe um ID e pesquisa sua existência nas duas filas, 
 * imprimindo as informações do trabalho correspondente.
 * Para que serve: Permitir a localização rápida de um trabalho sem a 
 * necessidade de listar toda a fila manualmente.
 * Condição: Exibe os dados do trabalho e encerra a função prematuramente 
 * (`return`) se achar. Se os laços terminarem sem encontrar, 
 * exibe mensagem informando o não comparecimento do ID.
 * ==================================================================== */
void buscarTrabalhoPorID(Fila* normal, Fila* prioritaria, int idBusca) {
    if (prioritaria->inicio != NULL) {
        Trabalho* atual = prioritaria->inicio;
        do {
            if (atual->id == idBusca) {
                printf("\n[ENCONTRADO NA PRIORITARIA] ID: %d | Arquivo: %s | Pags: %d\n",
                       atual->id, atual->arquivo, atual->paginas);
                return;
            }
            atual = atual->proximo;
        } while (atual != prioritaria->inicio);
    }

    if (normal->inicio != NULL) {
        Trabalho* atual = normal->inicio;
        while (atual != NULL) {
            if (atual->id == idBusca) {
                printf("\n[ENCONTRADO NA NORMAL] ID: %d | Arquivo: %s | Pags: %d\n",
                       atual->id, atual->arquivo, atual->paginas);
                return;
            }
            atual = atual->proximo;
        }
    }

    printf("\nTrabalho com ID %d nao encontrado em nenhuma fila.\n", idBusca);
}

/* ====================================================================
 * Método: cancelarNormal
 * O que faz: Localiza um trabalho pelo ID na Fila Normal, refaz os 
 * ponteiros de encadeamento para excluí-lo e libera sua memória.
 * Para que serve: Permitir o cancelamento de um documento antes que 
 * ele chegue ao processamento da impressora.
 * Condição: Rastrea o nó "anterior" para manter a lista coesa após a 
 * remoção. Retorna 1 se foi removido ou 0 se o ID não existir.
 * ==================================================================== */
int cancelarNormal(Fila* fila, int idCancela) {
    Trabalho* atual = fila->inicio;
    Trabalho* anterior = NULL;

    while (atual != NULL) {
        if (atual->id == idCancela) {
            if (anterior == NULL) {
                fila->inicio = atual->proximo;
                if (fila->inicio == NULL) fila->fim = NULL;
            } else {
                anterior->proximo = atual->proximo;
                if (atual == fila->fim) fila->fim = anterior;
            }
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0;
}

/* ====================================================================
 * Método: cancelarPrioritaria
 * O que faz: Exclui um nó específico por ID da Fila Prioritária (circular), 
 * liberando a memória.
 * Para que serve: Permitir a exclusão de um trabalho prioritário.
 * Condição: Exige lógica específica por ser uma fila circular. O "anterior" 
 * começa apontando para o 'fim'. Lida com o caso especial de ser 
 * o único nó na fila, garantindo que o ciclo se mantenha intacto 
 * nos demais casos. Retorna 1 (sucesso) ou 0 (falha).
 * ==================================================================== */
int cancelarPrioritaria(Fila* fila, int idCancela) {
    if (fila->inicio == NULL) return 0;

    Trabalho* atual = fila->inicio;
    Trabalho* anterior = fila->fim;

    do {
        if (atual->id == idCancela) {
            if (atual == fila->inicio && atual == fila->fim) {
                fila->inicio = NULL;
                fila->fim = NULL;
            } else {
                anterior->proximo = atual->proximo;
                if (atual == fila->inicio) fila->inicio = atual->proximo;
                if (atual == fila->fim) fila->fim = anterior;
            }
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    } while (atual != fila->inicio);

    return 0;
}



/* ====================================================================
 * Método: salvarCSV
 * O que faz: Abre o arquivo "impressao.csv" em modo de escrita ("w") e 
 * exporta os dados atuais de ambas as filas formatados em texto.
 * Para que serve: Persistência de dados (backup), permitindo que os 
 * trabalhos na fila não se percam quando o programa fecha.
 * Condição: Se houver erro de permissão para criar o arquivo, a função 
 * aborta. Os prioritários são salvos primeiro, seguidos dos normais.
 * ==================================================================== */
void salvarCSV(Fila* normal, Fila* prioritaria) {
    FILE* arquivo = fopen("impressao.csv", "w"); 
    
    if (arquivo == NULL) {                       
        printf("\nErro ao abrir o arquivo para salvar!\n"); 
        return;                                  
    }

    fprintf(arquivo, "id;arquivo;paginas;tipo\n"); 

    if (prioritaria->inicio != NULL) {           
        Trabalho* atual = prioritaria->inicio;   
        do {
            
            fprintf(arquivo, "%d;%s;%d;%c\n", atual->id, atual->arquivo, atual->paginas, atual->tipo);
            atual = atual->proximo;              
        } while (atual != prioritaria->inicio);  
    }

    if (normal->inicio != NULL) {                
        Trabalho* atual = normal->inicio;        
        while (atual != NULL) {                  
            
            fprintf(arquivo, "%d;%s;%d;%c\n", atual->id, atual->arquivo, atual->paginas, atual->tipo);
            atual = atual->proximo;              
        }
    }

    fclose(arquivo);                             
    printf("\nDados salvos com sucesso no arquivo 'impressao.csv'!\n"); 
}

/* ====================================================================
 * Método: carregarCSV
 * O que faz: Abre o arquivo "impressao.csv" em modo leitura ("r") e 
 * reconstrói as filas Prioritária e Normal com base nos dados.
 * Para que serve: Recuperar o estado da aplicação de execuções anteriores, 
 * inserindo todos os trabalhos de volta na memória.
 * Condição: Ignora o cabeçalho inicial. Durante a leitura, checa via 
 * 'existeID' se o trabalho já está na fila para evitar duplicatas 
 * (evita anomalias em múltiplas cargas).
 * ==================================================================== */
void carregarCSV(Fila* normal, Fila* prioritaria) {
    FILE* arquivo = fopen("impressao.csv", "r"); 
    
    if (arquivo == NULL) {                       
        printf("\n[Aviso] Arquivo 'impressao.csv' nao encontrado. Iniciando com filas vazias.\n");
        return;                                  
    }

    char linha[256];                             
    if (fgets(linha, sizeof(linha), arquivo) == NULL) { 
        fclose(arquivo);                         
        return;                                  
    }

    int id, paginas;                             
    char nomeArquivo[50];
    char tipo;
    int contador = 0;                            

    
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\r\n")] = 0;       

        
        if (sscanf(linha, "%d;%49[^;];%d;%c", &id, nomeArquivo, &paginas, &tipo) == 4) {
            if (existeID(normal, prioritaria, id)) { 
                continue;                        
            }

            
            Trabalho* novo = (Trabalho*) malloc(sizeof(Trabalho));
            if (novo != NULL) {                  
                novo->id = id;                   
                strcpy(novo->arquivo, nomeArquivo);
                novo->paginas = paginas;
                novo->tipo = tipo;
                novo->proximo = NULL;

                
                if (tipo == 'N') {
                    if (normal->inicio == NULL) { normal->inicio = novo; normal->fim = novo; }
                    else { normal->fim->proximo = novo; normal->fim = novo; }
                } else if (tipo == 'P') {
                    if (prioritaria->inicio == NULL) { prioritaria->inicio = novo; prioritaria->fim = novo; novo->proximo = novo; }
                    else { prioritaria->fim->proximo = novo; novo->proximo = prioritaria->inicio; prioritaria->fim = novo; }
                }
                contador++;                      
            }
        }
    }

    fclose(arquivo);                             
    if (contador > 0) {                          
        printf("\n[Sucesso] %d trabalhos foram carregados do arquivo 'impressao.csv' para a memoria!\n", contador);
    }
}

/* ====================================================================
 * Método: liberarMemoria
 * O que faz: Percorre todos os nós de ambas as filas acionando a função 
 * 'free' para desalocar a estrutura do Trabalho da RAM.
 * Para que serve: Prevenir problemas de vazamento de memória (Memory Leak) 
 * ao encerrar a aplicação.
 * Condição: Para a fila prioritária circular, é necessário quebrar o link 
 * final (`prioritaria->fim->proximo = NULL`) convertendo-a 
 * em uma lista simples momentaneamente para conseguir liberar.
 * ==================================================================== */
void liberarMemoria(Fila* normal, Fila* prioritaria) {
    Trabalho* atual = normal->inicio;            
    while (atual != NULL) {                      
        Trabalho* proximoNode = atual->proximo;  
        free(atual);                             
        atual = proximoNode;                     
    }

    if (prioritaria->inicio != NULL) {           
        atual = prioritaria->inicio;             
        prioritaria->fim->proximo = NULL;        
        while (atual != NULL) {                  
            Trabalho* proximoNode = atual->proximo; 
            free(atual);                         
            atual = proximoNode;                 
        }
    }
}


/* ====================================================================
 * Método: main
 * O que faz: Controla o ponto de entrada principal do programa, gerindo 
 * o loop do menu interativo e processando os comandos do terminal.
 * Para que serve: Atuar como a interface central do sistema de impressão, 
 * coordenando a leitura do CSV, inserções, buscas e remoções.
 * Condição: Inicia carregando os dados salvos em disco e roda continuamente 
 * até que o utilizador selecione a opção 6, realizando a limpeza 
 * completa da memória RAM antes de retornar 0.
 * ==================================================================== */
int main(void) {
    Fila filaNormal = {NULL, NULL};              
    Fila filaPrioritaria = {NULL, NULL};         
    
    int opcao = -1;                              

    
    carregarCSV(&filaNormal, &filaPrioritaria);  

    do {                                         
        
        printf("\n========================================\n");
        printf("       SISTEMA DE FILA DE IMPRESSAO       \n");
        printf("========================================\n");
        
        
        if (filaPrioritaria.inicio != NULL) {    
            printf("[PROXIMO A SER IMPRESSO]: ID %d | %s (%d pags) [PRIORITARIO]\n", 
                   filaPrioritaria.inicio->id, filaPrioritaria.inicio->arquivo, filaPrioritaria.inicio->paginas);
        } else if (filaNormal.inicio != NULL) {  
            printf("[PROXIMO A SER IMPRESSO]: ID %d | %s (%d pags) [NORMAL]\n", 
                   filaNormal.inicio->id, filaNormal.inicio->arquivo, filaNormal.inicio->paginas);
        } else {                                 
            printf("[PROXIMO A SER IMPRESSO]: Nao ha trabalhos na fila.\n");
        }
        printf("----------------------------------------\n");
        
        
        printf("1. Enfileirar novo trabalho\n");
        printf("2. Processar proximo trabalho\n");
        printf("3. Listar ambas as filas\n");
        printf("4. Buscar trabalho por ID\n");
        printf("5. Cancelar trabalho\n");
        printf("6. Salvar e Sair\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");           
        
        if (scanf("%d", &opcao) != 1) {          
            opcao = -1;                          
        }
        limparBuffer();                          

        switch (opcao) {                         
            case 1: {                            
                int id, paginas;                 
                char arquivo[50], tipo;
                
                printf("\n--- NOVO TRABALHO ---\n");
                printf("ID do trabalho: ");      
                scanf("%d", &id);                
                limparBuffer();                  

                if (existeID(&filaNormal, &filaPrioritaria, id)) { 
                    printf("\nErro: Ja existe um trabalho com o ID %d na fila! Cadastre com outro ID.\n", id);
                    break;                       
                }
                
                printf("Nome do arquivo: ");     
                scanf(" %49[^\n]", arquivo);     
                limparBuffer();                  
                
                printf("Quantidade de paginas: "); 
                scanf("%d", &paginas);           
                limparBuffer();                  
                
                printf("Tipo (N - Normal / P - Prioritario): "); 
                scanf(" %c", &tipo);             
                limparBuffer();                  
                
                if (tipo >= 'a' && tipo <= 'z') { 
                    tipo = tipo - 32;            
                }
                
                
                Trabalho* novoTrabalho = criarTrabalho(id, arquivo, paginas, tipo);
                
                if (novoTrabalho != NULL) {      
                    if (tipo == 'N') {           
                        enfileirarNormal(&filaNormal, novoTrabalho); 
                    } else if (tipo == 'P') {    
                        enfileirarPrioritaria(&filaPrioritaria, novoTrabalho); 
                    } else {                     
                        printf("\nTipo invalido! Digite apenas N ou P.\n");
                        free(novoTrabalho);      
                    }
                }
                break;                           
            }
            case 2: {                            
                Trabalho* processado = NULL;     
                
                if (filaPrioritaria.inicio != NULL) { 
                    processado = desenfileirarPrioritaria(&filaPrioritaria);
                    
                    printf("\n[PRIORIDADE] Imprimindo trabalho ID: %d | Arquivo: %s | Paginas: %d\n", 
                           processado->id, processado->arquivo, processado->paginas);
                } 
                else if (filaNormal.inicio != NULL) { 
                    processado = desenfileirarNormal(&filaNormal);
                    printf("\n[NORMAL] Imprimindo trabalho ID: %d | Arquivo: %s | Paginas: %d\n", 
                           processado->id, processado->arquivo, processado->paginas);
                } 
                else {                           
                    printf("\nNao ha trabalhos na fila de impressao no momento.\n");
                }
                
                if (processado != NULL) {        
                    free(processado);            
                }
                break;                           
            }
            case 3:                              
                listarFilas(&filaNormal, &filaPrioritaria); 
                break;                           
            case 4: {                            
                int idBusca;                     
                printf("\n--- BUSCAR TRABALHO ---\n");
                printf("Digite o ID do trabalho que deseja buscar: ");
                scanf("%d", &idBusca);           
                limparBuffer();                  
                
                
                buscarTrabalhoPorID(&filaNormal, &filaPrioritaria, idBusca);
                break;                           
            }
            case 5: {                            
                int idCancela;                   
                printf("\n--- CANCELAR TRABALHO ---\n");
                printf("Digite o ID do trabalho que deseja cancelar: ");
                scanf("%d", &idCancela);         
                limparBuffer();                  
                
                
                if (cancelarPrioritaria(&filaPrioritaria, idCancela)) {
                    printf("\nTrabalho ID %d cancelado com sucesso da Fila Prioritaria!\n", idCancela);
                } 
                
                else if (cancelarNormal(&filaNormal, idCancela)) {
                    printf("\nTrabalho ID %d cancelado com sucesso da Fila Normal!\n", idCancela);
                } 
                
                else {
                    printf("\nErro: Trabalho com ID %d nao encontrado em nenhuma fila.\n", idCancela);
                }
                break;                           
            }
            case 6:                              
                printf("\nEncerrando o sistema...\n");
                salvarCSV(&filaNormal, &filaPrioritaria); 
                liberarMemoria(&filaNormal, &filaPrioritaria); 
                printf("Memoria liberada com sucesso. Ate logo!\n\n"); 
                break;                           
            default:                             
                printf("\nOpcao invalida! Tente novamente.\n"); 
        }                                        
    } while (opcao != 6);                        

    return 0;                                    
}                                                