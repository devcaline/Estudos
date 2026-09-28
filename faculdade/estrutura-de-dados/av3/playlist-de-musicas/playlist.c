#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define MAX 100
#define LARG 40 /* largura interna do menu */

/* Cada musica da playlist e armazenada nesta struct */
typedef struct {
  int id;
  char titulo[100];
  char artista[100];
  int duracao;
  char genero[50];
} Musica;

/* Vetor de struct + variavel de controle com a quantidade cadastrada */
Musica playlist[MAX];
int quantidade = 0;

/* Gerador de ID unico: sempre cresce, nunca repete */
int proximoId = 1;

/* ---------- Funcoes de desenho da tela ---------- */

/* ==================================================
   REPETIR
   Imprime uma mesma string varias vezes seguidas.

   Recebe o texto e quantas vezes ele deve aparecer.
   E usada para montar as bordas e os espacos das
   tabelas e do menu sem precisar escrever tudo na mao.
   ================================================== */
void repetir(const char *s, int n) {
  for (int i = 0; i < n; i++) {
    printf("%s", s);
  }
}

/* ==================================================
   LIMPAR TELA
   Apaga tudo o que esta na tela do terminal.

   Usa codigos de escape ANSI para levar o cursor ao
   topo e limpar o conteudo, deixando a tela pronta
   para a proxima sessao do programa.
   ================================================== */
void limparTela() { printf("\033[H\033[J"); }

/* ==================================================
   CABECALHO
   Desenha o cabecalho da sessao atual do programa.

   Recebe o nome da sessao (ex.: "BUSCAR MUSICA") e o
   mostra dentro de uma caixa centralizada, para o
   usuario saber sempre em que parte do sistema esta.
   ================================================== */
void cabecalho(const char *titulo) {
  int n = (int)strlen(titulo);
  int esq = (LARG - n) / 2;
  int dir = LARG - n - esq;
  printf("\n╔");
  repetir("═", LARG);
  printf("╗\n");
  printf("║");
  repetir(" ", esq);
  printf("%s", titulo);
  repetir(" ", dir);
  printf("║\n");
  printf("╚");
  repetir("═", LARG);
  printf("╝\n");
}

/* ==================================================
   LINHA CENTRAL
   Imprime uma linha do menu com o texto centralizado.

   Calcula quantos espacos colocar na esquerda e na
   direita para que o texto fique no meio da caixa,
   sempre fechando as bordas laterais do menu.
   ================================================== */
void linhaCentral(const char *texto) {
  int n = (int)strlen(texto);
  int esq = (LARG - n) / 2;
  int dir = LARG - n - esq;
  printf("║");
  repetir(" ", esq);
  printf("%s", texto);
  repetir(" ", dir);
  printf("║\n");
}

/* ==================================================
   LINHA ITEM
   Imprime uma linha do menu com um item da lista.

   O texto fica alinhado a esquerda e a funcao
   completa o resto com espacos para manter a borda
   direita sempre no mesmo lugar.
   ================================================== */
void linhaItem(const char *texto) { printf("║  %-*s║\n", LARG - 2, texto); }

/* ==================================================
   BORDA TABELA
   Desenha uma linha de borda da tabela de musicas.

   Recebe os simbolos dos cantos/divisorias (esquerda,
   meio e direita) e monta a borda respeitando a
   largura de cada coluna da listagem.
   ================================================== */
void bordaTabela(const char *esq, const char *meio, const char *dir) {
  int larg[] = {6, 26, 18, 9, 14};
  printf("%s", esq);
  for (int i = 0; i < 5; i++) {
    repetir("─", larg[i]);
    printf("%s", i < 4 ? meio : dir);
  }
  printf("\n");
}

/* ==================================================
   MENU
   Desenha na tela o menu principal do programa.

   Mostra o titulo e todas as opcoes disponiveis
   (cadastrar, buscar, editar, excluir, listar e sair)
   e pede para o usuario digitar uma opcao.
   ================================================== */
void menu() {
  printf("\n╔");
  repetir("═", LARG);
  printf("╗\n");
  linhaCentral("PLAYLIST DE MUSICAS");
  printf("╠");
  repetir("═", LARG);
  printf("╣\n");
  linhaItem("[1]  Cadastrar musica");
  linhaItem("[2]  Buscar musica");
  linhaItem("[3]  Editar musica");
  linhaItem("[4]  Excluir musica");
  linhaItem("[5]  Listar musicas");
  linhaItem("[6]  Sair");
  printf("╚");
  repetir("═", LARG);
  printf("╝\n");
  printf(" » Opcao: ");
}

/* ==================================================
   IMPRIMIR DETALHE
   Mostra uma musica em formato de ficha detalhada.

   Recebe uma musica e exibe todos os seus dados
   (id, titulo, artista, duracao e genero) de forma
   organizada. E usada na busca e na edicao.
   ================================================== */
void imprimirDetalhe(Musica m) {
  printf("\n  ┌─ Musica encontrada ");
  repetir("─", 18);
  printf("┐\n");
  printf("  │ ID:      %d\n", m.id);
  printf("  │ Titulo:  %s\n", m.titulo);
  printf("  │ Artista: %s\n", m.artista);
  printf("  │ Duracao: %d:%02d\n", m.duracao / 60, m.duracao % 60);
  printf("  │ Genero:  %s\n", m.genero);
  printf("  └");
  repetir("─", 37);
  printf("┘\n");
}

/* ---------- Funcoes de logica ---------- */

/* ==================================================
   LER TEXTO
   Le uma linha de texto digitada pelo usuario.

   Aceita espacos no meio do texto e remove o '\n'
   que o ENTER deixa no final, devolvendo a string
   ja limpa no destino informado.
   ================================================== */
void lerTexto(char *destino, int tamanho) {
  fgets(destino, tamanho, stdin);
  destino[strcspn(destino, "\n")] = '\0';
}

/* ==================================================
   LIMPAR BUFFER
   Limpa o que sobra no teclado depois de um scanf.

   O scanf deixa o '\n' do ENTER guardado no buffer.
   Esta funcao descarta esses caracteres para nao
   atrapalhar a proxima leitura de texto.
   ================================================== */
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

/* ==================================================
   LER DURACAO
   Le a duracao aceitando apenas numeros inteiros.

   Mostra o texto de pedido e le a resposta como
   linha. Se o usuario digitar algo que nao seja
   composto so por numeros, avisa e pergunta de novo,
   ate receber uma duracao valida em segundos.
   ================================================== */
int lerDuracao(const char *prompt) {
  char buffer[100];

  while (1) {
    printf("%s", prompt);
    lerTexto(buffer, 100);

    /* Valida: nao pode ser vazio e todo caractere deve ser digito */
    int valido = strlen(buffer) > 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
      if (buffer[i] < '0' || buffer[i] > '9') {
        valido = 0;
        break;
      }
    }

    if (valido) {
      int valor;
      sscanf(buffer, "%d", &valor);
      return valor;
    }

    printf("  [!] Duracao invalida. Digite apenas numeros (segundos).\n");
  }
}

/* ==================================================
   PAUSAR E LIMPAR
   Espera alguns segundos e depois limpa a tela.

   Da tempo para o usuario ler o que esta na tela
   (uma mensagem ou uma ficha) antes de apagar tudo
   e devolver o controle para o menu principal.
   ================================================== */
void pausarELimpar() {
  fflush(stdout); /* garante que tudo aparece antes da pausa */
  sleep(3);
  limparTela();
}

/* ==================================================
   MENSAGEM ERRO
   Mostra um aviso e pausa antes de voltar ao menu.

   Exibe o texto de erro, espera alguns segundos para
   o usuario conseguir ler e entao limpa a tela,
   devolvendo o controle para o menu principal.
   ================================================== */
void mensagemErro(const char *texto) {
  printf("\n  [!] %s\n", texto);
  pausarELimpar();
}

/* ==================================================
   BUSCAR POR NOME
   Procura uma musica pelo seu titulo na playlist.

   Percorre o vetor e devolve a posicao da primeira
   musica cujo titulo seja igual ao informado (sem
   diferenciar maiusculas de minusculas). Se nenhuma
   for encontrada, devolve -1.
   ================================================== */
int buscarPorNome(const char *nome) {
  for (int i = 0; i < quantidade; i++) {
    if (strcasecmp(playlist[i].titulo, nome) == 0) {
      return i;
    }
  }
  return -1;
}

/* ==================================================
   CADASTRAR
   Cadastra uma nova musica na playlist.

   Pede ao usuario titulo, artista, duracao e genero,
   atribui um id unico automatico e guarda a musica
   no vetor. Avisa se a playlist estiver cheia.
   ================================================== */
void cadastrar() {
  char resposta[10];

  do {
    if (quantidade >= MAX) {
      mensagemErro("Playlist cheia");
      return;
    }

    Musica m;
    m.id = proximoId; /* ID unico atribuido automaticamente */

    printf("\n  Titulo: ");
    lerTexto(m.titulo, 100);

    printf("  Artista: ");
    lerTexto(m.artista, 100);

    m.duracao = lerDuracao("  Duracao (em segundos): ");

    printf("  Genero: ");
    lerTexto(m.genero, 50);

    playlist[quantidade] = m; /* mantem a ordem de cadastro */
    quantidade++;
    proximoId++;

    printf("  [OK] Musica cadastrada com sucesso!\n");

    /* Permite cadastrar varias musicas em sequencia */
    printf("\n  Cadastrar outra musica? (s/n): ");
    lerTexto(resposta, 10);

    /* Prepara uma tela limpa para o proximo cadastro */
    if (resposta[0] == 's' || resposta[0] == 'S') {
      limparTela();
      cabecalho("CADASTRAR MUSICA");
    }
  } while (resposta[0] == 's' || resposta[0] == 'S');

  /* Ao sair do cadastro, limpa a tela antes de voltar ao menu */
  limparTela();
}

/* ==================================================
   BUSCAR
   Busca e mostra uma musica a partir do id.

   Pede um id ao usuario, procura a musica na
   playlist e exibe a ficha dela. Avisa caso o id
   informado nao exista.
   ================================================== */
void buscar() {
  if (quantidade == 0) {
    mensagemErro("A playlist esta vazia. Cadastre uma musica primeiro.");
    return;
  }

  char nome[100];
  printf("\n  Titulo da musica: ");
  lerTexto(nome, 100);

  int pos = buscarPorNome(nome);
  if (pos == -1) {
    mensagemErro("Musica nao encontrada");
    return;
  }

  imprimirDetalhe(playlist[pos]);
  pausarELimpar();
}

/* ==================================================
   EDITAR
   Altera os dados de uma musica ja cadastrada.

   Localiza a musica pelo id e mostra os dados atuais.
   Para cada campo, basta apertar ENTER (deixar em
   branco) para manter o valor antigo; so muda o que
   for realmente preenchido. O id nunca muda,
   garantindo que ele continue unico.
   ================================================== */
void editar() {
  if (quantidade == 0) {
    mensagemErro("A playlist esta vazia. Cadastre uma musica primeiro.");
    return;
  }

  char nome[100];
  printf("\n  Titulo da musica a editar: ");
  lerTexto(nome, 100);

  int pos = buscarPorNome(nome);
  if (pos == -1) {
    mensagemErro("Musica nao encontrada");
    return;
  }

  /* Tela limpa para comecar a edicao dos dados */
  limparTela();
  cabecalho("EDITAR MUSICA");

  printf("  Editando a musica:\n");
  imprimirDetalhe(playlist[pos]);

  /* Buffer temporario: so atualiza o campo se algo for digitado */
  char buffer[100];
  printf("\n  Deixe o campo VAZIO e aperte ENTER para nao alterar a informacao.\n\n");

  /* O ID nao muda, garantindo que continue unico */
  printf("  Novo titulo (ENTER para manter): ");
  lerTexto(buffer, 100);
  if (strlen(buffer) > 0) {
    strcpy(playlist[pos].titulo, buffer);
  }

  printf("  Novo artista (ENTER para manter): ");
  lerTexto(buffer, 100);
  if (strlen(buffer) > 0) {
    strcpy(playlist[pos].artista, buffer);
  }

  printf("  Nova duracao em segundos (ENTER para manter): ");
  lerTexto(buffer, 100);
  if (strlen(buffer) > 0) {
    sscanf(buffer, "%d", &playlist[pos].duracao);
  }

  printf("  Novo genero (ENTER para manter): ");
  lerTexto(buffer, 50);
  if (strlen(buffer) > 0) {
    strcpy(playlist[pos].genero, buffer);
  }

  printf("  [OK] Musica atualizada com sucesso!\n");
  pausarELimpar();
}

/* ==================================================
   EXCLUIR
   Remove uma musica da playlist pelo id.

   Localiza a musica e a apaga, deslocando as
   musicas seguintes uma posicao para tras para nao
   deixar buraco no vetor. Avisa se o id nao existir.
   ================================================== */
void excluir() {
  if (quantidade == 0) {
    mensagemErro("A playlist esta vazia. Cadastre uma musica primeiro.");
    return;
  }

  char nome[100];
  printf("\n  Titulo da musica a excluir: ");
  lerTexto(nome, 100);

  int pos = buscarPorNome(nome);
  if (pos == -1) {
    mensagemErro("Musica nao encontrada");
    return;
  }

  /* Desloca os elementos seguintes para nao deixar buraco no vetor */
  for (int i = pos; i < quantidade - 1; i++) {
    playlist[i] = playlist[i + 1];
  }
  quantidade--;

  printf("  [OK] Musica excluida com sucesso!\n");
  pausarELimpar();
}

/* ==================================================
   LISTAR
   Mostra todas as musicas em forma de tabela.

   Imprime uma tabela com id, titulo, artista,
   duracao e genero de cada musica cadastrada.
   Avisa caso a playlist esteja vazia.
   ================================================== */
void listar() {
  if (quantidade == 0) {
    mensagemErro("A playlist esta vazia");
    return;
  }

  printf("\n  Playlist - %d musica(s)\n", quantidade);
  bordaTabela("┌", "┬", "┐");
  printf("│ %-4s │ %-24s │ %-16s │ %-7s │ %-12s │\n", "ID", "Titulo", "Artista",
         "Duracao", "Genero");
  bordaTabela("├", "┼", "┤");
  for (int i = 0; i < quantidade; i++) {
    Musica m = playlist[i];
    char dur[12];
    sprintf(dur, "%d:%02d", m.duracao / 60, m.duracao % 60);
    printf("│ %-4d │ %-24.24s │ %-16.16s │ %7s │ %-12.12s │\n", m.id, m.titulo,
           m.artista, dur, m.genero);
  }
  bordaTabela("└", "┴", "┘");
}

/* ==================================================
   MAIN
   Funcao principal que controla o programa.

   Mostra o menu em repeticao, le a opcao escolhida
   e chama a funcao correspondente. O laco so termina
   quando o usuario escolhe a opcao de sair.
   ================================================== */
int main() {
  int op;

  do {
    menu();
    scanf("%d", &op);
    limparBuffer();

    if (op == 1) {
      limparTela();
      cabecalho("CADASTRAR MUSICA");
      cadastrar();
    } else if (op == 2) {
      limparTela();
      cabecalho("BUSCAR MUSICA");
      buscar();
    } else if (op == 3) {
      limparTela();
      cabecalho("EDITAR MUSICA");
      editar();
    } else if (op == 4) {
      limparTela();
      cabecalho("EXCLUIR MUSICA");
      excluir();
    } else if (op == 5) {
      limparTela();
      cabecalho("LISTAR MUSICAS");
      listar();
    } else if (op != 6) {
      limparTela();
      mensagemErro("Opcao invalida");
    }
  } while (op != 6);

  printf("\n  Ate logo!\n");
  return 0;
}
