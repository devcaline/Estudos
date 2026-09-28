# Tema A1 — Playlist de Músicas

Projeto da **AV3** de Estrutura de Dados — UNIJORGE, Turma A.

**Responsável:** Victória Caroline Bittencourt Costa

## Descrição

Programa de console em C que gerencia uma **playlist de músicas** usando um
**vetor de structs**. Cada música guarda um identificador único e os seus dados,
e o programa oferece um menu com as operações básicas de um cadastro (CRUD).

Cada música é representada pela struct `Musica`:

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `id` | `int` | Identificador único, gerado automaticamente |
| `titulo` | `char[100]` | Nome da música |
| `artista` | `char[100]` | Nome do artista |
| `duracao` | `int` | Duração em segundos (exibida como `min:seg`) |
| `genero` | `char[50]` | Gênero musical |

## Funcionalidades

A partir do menu principal, o usuário pode:

1. **Cadastrar música** — adiciona uma nova música; o ID é atribuído
   automaticamente e nunca se repete.
2. **Buscar música** — localiza uma música pelo ID e mostra a ficha detalhada.
3. **Editar música** — altera os dados de uma música existente. Para cada campo,
   basta apertar **ENTER** (deixar em branco) para **manter o valor atual**; só é
   alterado o que for realmente preenchido. O ID nunca muda.
4. **Excluir música** — remove uma música pelo ID, deslocando as seguintes para
   não deixar buraco no vetor.
5. **Listar músicas** — exibe todas as músicas em uma tabela formatada.
6. **Sair** — encerra o programa.

## Estrutura de dados utilizada

- **Vetor estático de structs** (`Musica playlist[MAX]`, com `MAX = 100`).
- Variável de controle `quantidade` com o total de músicas cadastradas.
- Gerador de ID sequencial (`proximoId`) que sempre cresce, garantindo
  identificadores únicos mesmo após exclusões.

## Como compilar e executar

Pré-requisito: ter o compilador **gcc** instalado.

Dentro desta pasta (`playlist-de-musicas/`):

```bash
# Compilar
gcc playlist.c -o playlist

# Executar
./playlist
```

No Windows (com MinGW), o executável é `playlist.exe`:

```bash
gcc playlist.c -o playlist.exe
playlist.exe
```

## Arquivos

- [`playlist.c`](playlist.c) — código-fonte completo do programa.
