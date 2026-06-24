#include <stdio.h>
#include <string.h>

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
   BUSCAR POR ID
   Procura uma musica pelo seu id na playlist.

   Percorre o vetor e devolve a posicao da musica
   que tiver o id informado. Se nenhuma for
   encontrada, devolve -1.
   ================================================== */
int buscarPorId(int id) {
  for (int i = 0; i < quantidade; i++) {
    if (playlist[i].id == id) {
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
  if (quantidade >= MAX) {
    printf("  [!] Playlist cheia\n");
    return;
  }

  Musica m;
  m.id = proximoId; /* ID unico atribuido automaticamente */

  printf("\n  -- Cadastro de musica --\n");
  printf("  Titulo: ");
  lerTexto(m.titulo, 100);

  printf("  Artista: ");
  lerTexto(m.artista, 100);

  printf("  Duracao (em segundos): ");
  scanf("%d", &m.duracao);
  limparBuffer();

  printf("  Genero: ");
  lerTexto(m.genero, 50);

  playlist[quantidade] = m; /* mantem a ordem de cadastro */
  quantidade++;
  proximoId++;

  printf("  [OK] Musica cadastrada com sucesso! ID: %d\n", m.id);
}

/* ==================================================
   BUSCAR
   Busca e mostra uma musica a partir do id.

   Pede um id ao usuario, procura a musica na
   playlist e exibe a ficha dela. Avisa caso o id
   informado nao exista.
   ================================================== */
void buscar() {
  int id;
  printf("\n  ID da musica: ");
  scanf("%d", &id);
  limparBuffer();

  int pos = buscarPorId(id);
  if (pos == -1) {
    printf("  [!] Musica nao encontrada\n");
    return;
  }

  imprimirDetalhe(playlist[pos]);
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
  int id;
  printf("\n  ID da musica a editar: ");
  scanf("%d", &id);
  limparBuffer();

  int pos = buscarPorId(id);
  if (pos == -1) {
    printf("  [!] Musica nao encontrada\n");
    return;
  }

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
}

/* ==================================================
   EXCLUIR
   Remove uma musica da playlist pelo id.

   Localiza a musica e a apaga, deslocando as
   musicas seguintes uma posicao para tras para nao
   deixar buraco no vetor. Avisa se o id nao existir.
   ================================================== */
void excluir() {
  int id;
  printf("\n  ID da musica a excluir: ");
  scanf("%d", &id);
  limparBuffer();

  int pos = buscarPorId(id);
  if (pos == -1) {
    printf("  [!] Musica nao encontrada\n");
    return;
  }

  /* Desloca os elementos seguintes para nao deixar buraco no vetor */
  for (int i = pos; i < quantidade - 1; i++) {
    playlist[i] = playlist[i + 1];
  }
  quantidade--;

  printf("  [OK] Musica excluida com sucesso!\n");
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
    printf("\n  [!] A playlist esta vazia\n");
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
      cadastrar();
    } else if (op == 2) {
      buscar();
    } else if (op == 3) {
      editar();
    } else if (op == 4) {
      excluir();
    } else if (op == 5) {
      listar();
    } else if (op != 6) {
      printf("  [!] Opcao invalida\n");
    }
  } while (op != 6);

  printf("\n  Ate logo!\n");
  return 0;
}
