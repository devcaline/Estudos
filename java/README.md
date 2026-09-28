# ☕ Projetos em Java

Projetinhos pessoais para praticar Java. Cada projeto fica na sua própria pasta, numerada na ordem em que foi feito.

## Projetos

| # | Projeto | O que pratiquei |
|:-:|---------|-----------------|
| — | *em breve* | |

## Como adicionar um projeto novo

1. Crie uma pasta com número + nome em minúsculas separado por hífen: `01-calculadora`, `02-agenda-de-contatos`.
2. Dentro dela, coloque o código em `src/` e um `README.md` explicando:
   - o que o projeto faz;
   - como compilar e executar;
   - o que você aprendeu com ele.
3. Adicione uma linha na tabela acima.

Estrutura sugerida:

```text
01-calculadora/
├── README.md
└── src/
    └── Main.java
```

Para rodar um projeto simples, sem Maven/Gradle:

```bash
cd 01-calculadora
javac -d out src/*.java
java -cp out Main
```
