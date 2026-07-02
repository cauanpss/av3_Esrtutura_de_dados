# Trabalho A1/B2/C2 - Estruturas de Dados em C

## Integrantes

Cauan Pereira Santos

Daniel Ribeiro Madureira Rocha

Davi Seguchi Carneiro Dias

Ericsson dos Santos 

## Vídeo de apresentação

https://www.youtube.com/watch?v=AtDdzBgGewo

## Turma

**Turma:**
Ciência da Computação, C, matutino - 3º semestre.

---

# Temas dos Trabalhos

## Trabalho A (A1)

**Tema:** Playlist de Música

## Trabalho B (B2)

**Tema:** Chamadas de Emergência

## Trabalho C (C2)

**Tema:** Fila de Impressão

---

# Descrição dos Programas

## A1 – Playlist de Música

Sistema de gerenciamento de uma playlist musical desenvolvido em linguagem C. O programa permite cadastrar, listar, buscar, editar e excluir músicas por meio de um menu interativo. Também realiza validações de entrada, impede IDs duplicados e salva os dados em um arquivo CSV para que as informações permaneçam disponíveis entre diferentes execuções do programa.

### Funcionalidades

* Cadastro de músicas;
* Listagem de todas as músicas;
* Busca por ID;
* Edição de registros;
* Exclusão de músicas;
* Salvamento em arquivo CSV;
* Carregamento automático dos dados ao iniciar o programa.

---

## B2 – Chamadas de Emergência

Sistema de gerenciamento de chamadas de emergência desenvolvido utilizando a mesma estrutura do Trabalho A. O programa realiza o cadastro, consulta, edição, exclusão e armazenamento das ocorrências por meio de um menu interativo, permitindo organizar e controlar as chamadas registradas.

### Funcionalidades

* Registro de chamadas de emergência;
* Atendimento da última chamada registrada;
* Consulta da última chamada pendente;
* Listagem de todas as chamadas;
* Validação de protocolo único;
* Validação de horário no formato HH:MM;
* Validação de entradas do usuário;
* Salvamento em arquivo CSV;
* Carregamento automático dos dados ao iniciar o programa.
---

## C2 – Fila de Impressão

Sistema para gerenciamento de uma fila de impressão. Permite cadastrar documentos para impressão, listar os documentos pendentes, buscar registros, editar informações, remover documentos da fila e armazenar os dados em arquivo para preservar as informações entre as execuções.

### Funcionalidades

* Cadastro de trabalhos de impressão;
* Separação entre filas Normal e Prioritária;
* Processamento de trabalhos respeitando a prioridade;
* Listagem de todos os trabalhos pendentes;
* Busca de trabalhos por ID;
* Cancelamento de trabalhos da fila;
* Validação das entradas do usuário;
* Validação do tipo de impressão (Normal ou Prioritária);
* Salvamento em arquivo CSV;
* Carregamento automático dos dados ao iniciar o programa.

---

# Compilação

O projeto pode ser compilado utilizando o compilador GCC.

### Linux

```bash
gcc arquivo.c -o programa
```

### Windows (MinGW)

```bash
gcc arquivo.c -o programa.exe
```

Substitua **arquivo.c** pelo nome do arquivo correspondente ao programa que deseja compilar.

---

# Execução

### Linux

```bash
./programa
```

### Windows

```bash
programa.exe
```

---

# Observações sobre o Funcionamento

* Os programas utilizam menus interativos para facilitar a navegação.
* As entradas numéricas são validadas para evitar erros de digitação.
* Cada registro possui um identificador (ID) único, impedindo duplicidade.
* Os dados permanecem armazenados em arquivos CSV mesmo após o encerramento do programa, sendo carregados automaticamente na próxima execução.
* Todos os programas seguem uma organização modular utilizando funções específicas para cada operação, facilitando a manutenção e reutilização do código.

---

# Dificuldades Encontradas

Durante o desenvolvimento dos projetos foram encontradas algumas dificuldades, principalmente relacionadas à manipulação de arquivos e persistência de dados.

A principal funcionalidade adicionada foi o salvamento e carregamento das informações utilizando arquivos no formato CSV. Foi necessário estudar as funções da biblioteca padrão da linguagem C para abertura, leitura, escrita e fechamento de arquivos, além da conversão entre texto e dados armazenados nas estruturas do programa.

Também foram enfrentados desafios relacionados à:

* validação das entradas do usuário;
* controle de IDs duplicados;
* manipulação de strings;
* organização do código em funções independentes;

Essas dificuldades contribuíram para um melhor entendimento sobre manipulação de arquivos, modularização do código, estruturas de dados e desenvolvimento de aplicações em linguagem C.

## Considerações sobre o Desenvolvimento

Durante o desenvolvimento dos três projetos, foram utilizadas ferramentas de Inteligência Artificial baseadas em Modelos de Linguagem de Grande Escala (LLMs) como apoio à implementação de partes do código. Essas ferramentas foram empregadas principalmente para auxiliar na escrita de trechos específicos, sugerir melhorias de sintaxe e esclarecer dúvidas pontuais relacionadas à linguagem C.

Entretanto, a definição da arquitetura dos programas, a escolha das estruturas de dados, a modularização das funcionalidades e a integração entre os diferentes componentes foram realizadas pelo grupo. Todo o código gerado passou por análise, revisão e adaptação para atender aos requisitos da disciplina e às decisões de projeto adotadas pelos integrantes.

Também houve preocupação em manter um código organizado, legível e modular, utilizando funções com responsabilidades bem definidas, validação de entradas, gerenciamento adequado dos dados e aplicação das estruturas estudadas em sala de aula. Cada programa foi desenvolvido utilizando a estrutura de dados mais adequada ao problema proposto (lista, pilha ou fila), buscando refletir os conceitos apresentados na disciplina tanto na organização do código quanto no gerenciamento das informações.

Dessa forma, a utilização de LLMs ocorreu exclusivamente como ferramenta de apoio ao processo de desenvolvimento. O planejamento, a implementação, a revisão, os testes, a depuração e a versão final dos programas foram de responsabilidade do grupo.