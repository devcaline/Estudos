# 🎓 Sistema de Gestão Acadêmica — AV3

> Trabalho da **Avaliação 3 (AV3)** da disciplina de **Algoritmo eLaboratório de Programação**.

Sistema de cadastro e gerenciamento acadêmico desenvolvido em **Linguagem C**, com interface de menus no terminal. O projeto aplica os conceitos vistos em sala: **structs**, **vetores de estruturas**, **funções**, **ponteiros**, **validação de entrada**, **algoritmos de busca e ordenação** e **relacionamento entre entidades (chaves primárias e estrangeiras)**.

---

## 📌 Sobre o Projeto

O sistema simula o controle acadêmico de uma instituição de ensino, gerenciando quatro entidades relacionadas entre si:

| Entidade | Chave Primária | Descrição |
|----------|----------------|-----------|
| **Aluno** | `pk_cpf` | Dados pessoais e escolares do aluno |
| **Curso** | `pk_codCurso` | Cursos oferecidos (carga horária, modalidade) |
| **Turma** | `pk_codTurma` | Turmas disponíveis (turno, quantidade de alunos) |
| **Matrícula** | `pk_ra` | Vincula um aluno a um curso e a uma turma |

A **Matrícula** funciona como uma tabela associativa, usando **chaves estrangeiras** para relacionar as demais entidades:

```
Matrícula
 ├── fk_cpf       → Aluno  (pk_cpf)
 ├── fk_codCurso  → Curso  (pk_codCurso)
 └── fk_codTurma  → Turma  (pk_codTurma)
```

---

## ✨ Funcionalidades

### Operações principais (menu)

| Opção | Funcionalidade | Descrição |
|:-----:|----------------|-----------|
| 1 | **Cadastrar** | Inclui alunos, cursos, turmas e matrículas, com validação de CPF, datas e duplicidade de chaves |
| 2 | **Consultar** | Busca um registro específico pela sua chave |
| 3 | **Alterar** | Edita os dados de um registro existente |
| 4 | **Excluir** | Remove um registro (com proteção de integridade: não exclui se houver matrícula vinculada) |
| 5 | **Ordenar** | Ordena qualquer entidade em ordem **crescente** ou **decrescente** |
| 6 | **Imprimir** | Lista todos os registros de uma entidade |
| 7 | **Relatórios** | Relatórios com totais por entidade e relatório geral do sistema |
| 8 | **Consulta Cruzada** | Consulta uma matrícula exibindo os **nomes** do aluno, curso e turma a partir das chaves estrangeiras |
| 9 | **Finalizar** | Encerra o programa |

---

## 🛡️ Validações e Regras de Integridade

- ✅ **CPF** no formato `000.000.000-00` (14 caracteres, pontos e traço nas posições corretas).
- ✅ **Datas** no formato `DD/MM/AAAA`.
- ✅ **Chaves únicas**: impede o cadastro de CPF, código ou RA já existentes.
- ✅ **Campos obrigatórios**: nome, escolaridade, modalidade e turno não podem ficar vazios.
- ✅ **Integridade referencial**: uma matrícula só aceita aluno, curso e turma já cadastrados; e um registro não pode ser excluído enquanto houver matrícula vinculada a ele.
- ✅ **Limite de capacidade**: até 50 registros por entidade.

---

## 🗂️ Estrutura do Código

O programa está organizado em blocos de funções com responsabilidades bem definidas:

- **Validação** — `validar_formato_cpf`, `validar_formato_data`
- **Menus** — `menu`, `subMenu`, `submenuOrdenar`, `submenuRelatorios`
- **Busca (exibição)** — `buscar_aluno`, `buscar_curso`, `buscar_turma`, `buscar_matricula`
- **Busca (verificação/índice)** — `buscar_*_pk_*`, `buscar_*_index`
- **Integridade** — `matricula_vinculada_aluno`, `matricula_vinculada_curso`, `matricula_vinculada_turma`
- **Ordenação** — `ordenar` (crescente/decrescente, por entidade e campo)
- **Saída de dados** — `imprimir`, `relatorio*`, `consulta_cruzada_matricula`

As melhorias reutilizam as funções de busca já existentes, evitando duplicação de lógica.

---

## ⚙️ Como Compilar e Executar

> O programa usa `system("clear")` e `sleep()`, sendo voltado a ambientes **Linux/macOS**.

```bash
# Compilar
gcc av3Jailson.c -o av3

# Executar
./av3
```

---

## 🧰 Tecnologias

- **Linguagem C** (padrão C99+)
- Bibliotecas: `stdio.h`, `string.h`, `stdlib.h`, `stdbool.h`, `locale.h`, `unistd.h`, `ctype.h`

---

## 📚 Contexto Acadêmico

| | |
|---|---|
| **Avaliação** | AV3 |
| **Disciplinas** | Algoritmo e Laboratório de Programação |
| **Linguagem** | C |
| **Tema** | Sistema de Gestão Acadêmica (CRUD com entidades relacionadas) |

---

> Projeto desenvolvido para fins acadêmicos. 🚀
