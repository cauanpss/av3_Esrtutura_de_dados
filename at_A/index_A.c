#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MUSICAS 100
#define MAX_TITULO 50
#define MAX_ARTISTA 50
#define MAX_GENERO 30

// Define o comando correto para limpar a tela dependendo do sistema operacional
#ifdef _WIN32
#define LIMPAR_TELA "cls"
#else
#define LIMPAR_TELA "clear"
#endif

// Estrutura para armazenar os dados de uma música
typedef struct
{
    int id;
    char titulo[MAX_TITULO];
    char artista[MAX_ARTISTA];
    int duracao;
    char genero[MAX_GENERO];
} Musica;

// Variáveis globais
Musica playlist[MAX_MUSICAS];
int quantidade = 0;

// Protótipos das funções
void limparBuffer();
void exibirMenu();
void cadastrarMusica();
void listarMusicas();
void buscarPorId();
void editarMusica();
void excluirMusica();
int validarId(int id);
void salvarEmArquivo();
void carregarDoArquivo();
void exibirMusica(Musica m);
int lerInteiro();
void lerString(char *destino, int tamanho);

int main()
{

    carregarDoArquivo();

    int opcao;
    do
    {
        exibirMenu();
        printf("Escolha uma opção: ");
        opcao = lerInteiro();

        switch (opcao)
        {
        case 1:
            cadastrarMusica();
            break;
        case 2:
            listarMusicas();
            break;
        case 3:
            buscarPorId();
            break;
        case 4:
            editarMusica();
            break;
        case 5:
            excluirMusica();
            break;
        case 6:
            salvarEmArquivo();
            printf("Dados salvos com sucesso!\n");
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }

        if (opcao != 0)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while (opcao != 0);

    return 0;
}

// Função para limpar o buffer do teclado
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Função para exibir o menu
void exibirMenu()
{
    system(LIMPAR_TELA);
    printf("====================================\n");
    printf("        PLAYLIST MUSICAL\n");
    printf("====================================\n");
    printf("1. Cadastrar música\n");
    printf("2. Listar todas as músicas\n");
    printf("3. Buscar música por ID\n");
    printf("4. Editar música\n");
    printf("5. Excluir música\n");
    printf("6. Salvar dados\n");
    printf("0. Sair\n");
    printf("====================================\n");
}

// Função para ler um inteiro com validação
int lerInteiro()
{
    int valor;
    while (scanf("%d", &valor) != 1)
    {
        printf("Entrada inválida! Digite um número: ");
        limparBuffer();
    }
    limparBuffer();
    return valor;
}

// Função para ler uma string com segurança
void lerString(char *destino, int tamanho)
{
    fgets(destino, tamanho, stdin);
    size_t len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n')
    {
        destino[len - 1] = '\0';
    }
}

// Função para validar se o ID já existe
int validarId(int id)
{
    for (int i = 0; i < quantidade; i++)
    {
        if (playlist[i].id == id)
        {
            return 0; // ID já existe
        }
    }
    return 1; // ID disponível
}

// Função para cadastrar uma nova música
void cadastrarMusica()
{
    if (quantidade >= MAX_MUSICAS)
    {
        printf("Playlist cheia! Não é possível cadastrar mais músicas.\n");
        return;
    }

    Musica nova;

    printf("\n--- CADASTRO DE MÚSICA ---\n");

    do
    {
        printf("ID (número inteiro): ");
        nova.id = lerInteiro();
        if (!validarId(nova.id))
        {
            printf("ID já cadastrado! Por favor, escolha outro ID.\n");
        }
    } while (!validarId(nova.id));

    printf("Título: ");
    lerString(nova.titulo, MAX_TITULO);

    printf("Artista: ");
    lerString(nova.artista, MAX_ARTISTA);

    printf("Duração em segundos: ");
    nova.duracao = lerInteiro();

    printf("Gênero musical: ");
    lerString(nova.genero, MAX_GENERO);

    playlist[quantidade] = nova;
    quantidade++;

    printf("\nMúsica cadastrada com sucesso!\n");
}

// Função para exibir os dados de uma música
void exibirMusica(Musica m)
{
    printf("ID: %d\n", m.id);
    printf("Título: %s\n", m.titulo);
    printf("Artista: %s\n", m.artista);
    printf("Duração: %d segundos\n", m.duracao);
    printf("Gênero: %s\n", m.genero);
    printf("-------------------\n");
}

// Função para listar todas as músicas
void listarMusicas()
{
    if (quantidade == 0)
    {
        printf("\nPlaylist vazia!\n");
        return;
    }

    printf("\n--- PLAYLIST ---\n");
    printf("Total de músicas: %d\n\n", quantidade);

    for (int i = 0; i < quantidade; i++)
    {
        printf("Música #%d:\n", i + 1);
        exibirMusica(playlist[i]);
    }
}

// Função para buscar música por ID
void buscarPorId()
{
    if (quantidade == 0)
    {
        printf("\nPlaylist vazia!\n");
        return;
    }

    printf("\n--- BUSCAR POR ID ---\n");
    printf("Digite o ID da música: ");
    int id = lerInteiro();

    for (int i = 0; i < quantidade; i++)
    {
        if (playlist[i].id == id)
        {
            printf("\nMúsica encontrada:\n");
            exibirMusica(playlist[i]);
            return;
        }
    }

    printf("\nMúsica com ID %d não encontrada!\n", id);
}

// Função para editar uma música
void editarMusica()
{
    if (quantidade == 0)
    {
        printf("\nPlaylist vazia!\n");
        return;
    }

    printf("\n--- EDITAR MÚSICA ---\n");
    printf("Digite o ID da música a ser editada: ");
    int id = lerInteiro();

    for (int i = 0; i < quantidade; i++)
    {
        if (playlist[i].id == id)
        {
            printf("\nMúsica encontrada. Dados atuais:\n");
            exibirMusica(playlist[i]);

            printf("\nNovos dados (deixe em branco para manter o valor atual):\n");

            char novoTitulo[MAX_TITULO];
            char novoArtista[MAX_ARTISTA];
            char novoGenero[MAX_GENERO];
            int novaDuracao;

            printf("Título [%s]: ", playlist[i].titulo);
            lerString(novoTitulo, MAX_TITULO);
            if (strlen(novoTitulo) > 0)
            {
                strcpy(playlist[i].titulo, novoTitulo);
            }

            printf("Artista [%s]: ", playlist[i].artista);
            lerString(novoArtista, MAX_ARTISTA);
            if (strlen(novoArtista) > 0)
            {
                strcpy(playlist[i].artista, novoArtista);
            }

            printf("Duração em segundos [%d]: ", playlist[i].duracao);
            char entrada[10];
            lerString(entrada, 10);
            if (strlen(entrada) > 0)
            {
                playlist[i].duracao = atoi(entrada);
            }

            printf("Gênero [%s]: ", playlist[i].genero);
            lerString(novoGenero, MAX_GENERO);
            if (strlen(novoGenero) > 0)
            {
                strcpy(playlist[i].genero, novoGenero);
            }

            printf("\nMúsica atualizada com sucesso!\n");
            return;
        }
    }

    printf("\nMúsica com ID %d não encontrada!\n", id);
}

// Função para excluir uma música
void excluirMusica()
{
    if (quantidade == 0)
    {
        printf("\nPlaylist vazia!\n");
        return;
    }

    printf("\n--- EXCLUIR MÚSICA ---\n");
    printf("Digite o ID da música a ser excluída: ");
    int id = lerInteiro();

    for (int i = 0; i < quantidade; i++)
    {
        if (playlist[i].id == id)
        {
            printf("\nMúsica a ser excluída:\n");
            exibirMusica(playlist[i]);

            printf("Tem certeza que deseja excluir? (S/N): ");
            char confirmacao;
            scanf("%c", &confirmacao);
            limparBuffer();

            if (toupper(confirmacao) == 'S')
            {
                // Deslocar os elementos posteriores para ocupar o espaço vazio
                for (int j = i; j < quantidade - 1; j++)
                {
                    playlist[j] = playlist[j + 1];
                }
                quantidade--;
                printf("\nMúsica excluída com sucesso!\n");
            }
            else
            {
                printf("\nOperação cancelada.\n");
            }
            return;
        }
    }

    printf("\nMúsica com ID %d não encontrada!\n", id);
}

// Função para salvar dados em arquivo CSV
void salvarEmArquivo()
{
    FILE *arquivo = fopen("playlist.csv", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    // Escrever cabeçalho
    fprintf(arquivo, "ID,TITULO,ARTISTA,DURACAO,GENERO\n");

    // Escrever dados das músicas
    for (int i = 0; i < quantidade; i++)
    {
        fprintf(arquivo, "%d,%s,%s,%d,%s\n",
                playlist[i].id,
                playlist[i].titulo,
                playlist[i].artista,
                playlist[i].duracao,
                playlist[i].genero);
    }

    fclose(arquivo);
}

// Função para carregar dados do arquivo CSV
void carregarDoArquivo()
{
    FILE *arquivo = fopen("playlist.csv", "r");
    if (arquivo == NULL)
    {
        printf("Arquivo de dados não encontrado. Iniciando com playlist vazia.\n");
        return;
    }

    // Pular cabeçalho
    char linha[200];
    fgets(linha, sizeof(linha), arquivo);

    quantidade = 0;
    while (fgets(linha, sizeof(linha), arquivo) != NULL && quantidade < MAX_MUSICAS)
    {
        Musica m;

        // Remover quebra de linha
        linha[strcspn(linha, "\n")] = 0;

        // Parse da linha CSV
        char *token = strtok(linha, ",");
        if (token)
            m.id = atoi(token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(m.titulo, token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(m.artista, token);

        token = strtok(NULL, ",");
        if (token)
            m.duracao = atoi(token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(m.genero, token);

        playlist[quantidade] = m;
        quantidade++;
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso! %d músicas encontradas.\n", quantidade);
}