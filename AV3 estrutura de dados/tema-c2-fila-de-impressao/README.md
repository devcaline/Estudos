# Tema C2 — Fila de Impressão

Projeto da **AV3** de Estrutura de Dados — UNIJORGE, Turma A.

**Responsável:** Pedro Henrique Oliveira do Nascimento

## Descrição

Programa de console em C que simula uma **fila de impressão** com duas filas
distintas: uma **fila prioritária** (lista encadeada **circular**) e uma **fila
normal** (lista encadeada **simples**). Trabalhos prioritários são sempre
impressos antes dos normais. O estado das filas é persistido em um arquivo CSV.

Cada trabalho de impressão é representado pela struct `Trabalho`:

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `id` | `int` | Identificador único do trabalho |
| `arquivo` | `char[50]` | Nome do arquivo a ser impresso |
| `paginas` | `int` | Quantidade de páginas |
| `tipo` | `char` | `N` (Normal) ou `P` (Prioritário) |
| `proximo` | `Trabalho*` | Ponteiro para o próximo nó da fila |

## Funcionalidades

A partir do menu principal, o usuário pode:

1. **Enfileirar novo trabalho** — cadastra um trabalho na fila normal ou
   prioritária conforme o tipo; o ID não pode se repetir entre as filas.
2. **Processar próximo trabalho** — imprime (desenfileira) o próximo trabalho,
   sempre respeitando a prioridade: a fila prioritária é esvaziada antes da normal.
3. **Listar ambas as filas** — exibe todos os trabalhos aguardando em cada fila.
4. **Buscar trabalho por ID** — localiza um trabalho pelo ID em qualquer das filas.
5. **Cancelar trabalho** — remove um trabalho específico pelo ID antes da impressão.
6. **Salvar e Sair** — grava as filas no arquivo `impressao.csv`, libera a memória
   e encerra o programa.

Ao iniciar, o programa carrega automaticamente os trabalhos salvos em
`impressao.csv` (se existir), evitando duplicar IDs já carregados.

## Estruturas de dados utilizadas

- **Fila prioritária:** lista encadeada **circular** (o último nó aponta de volta
  para o início), com ponteiros de `inicio` e `fim`.
- **Fila normal:** lista encadeada **simples** (FIFO), com ponteiros de `inicio` e `fim`.
- **Persistência em CSV** (`impressao.csv`) com cabeçalho `id;arquivo;paginas;tipo`.
- Gerenciamento manual de memória com `malloc`/`free`, liberando todos os nós ao sair.

## Como compilar e executar

Pré-requisito: ter o compilador **gcc** instalado.

Dentro desta pasta (`tema-c2-fila-de-impressao/`):

```bash
# Compilar
gcc -std=c99 -Wall -pedantic main.c -o impressao

# Executar
./impressao
```

No Windows (com MinGW), o executável é `impressao.exe`:

```bash
gcc -std=c99 -Wall -pedantic main.c -o impressao.exe
impressao.exe
```

## Arquivos

- [`main.c`](main.c) — código-fonte completo do programa.
- [`impressao.csv`](impressao.csv) — arquivo de persistência das filas (gerado/lido pelo programa).
- [`comandoCompilacao`](comandoCompilacao) — anotações de compilação e execução.
