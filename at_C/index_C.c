#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// =========================
// LIMPAR TELA
// =========================
void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// =========================
// STRUCT
// =========================
typedef struct
{
    int id;
    char arquivo[50];
    int paginas;
    char tipo; // N ou P
} Trabalho;

// =========================
// PROTÓTIPOS DAS FUNÇÕES
// =========================

int lerInteiro(const char *msg);
char lerTipo();
int cheiaNormal();
int vaziaNormal();
int cheiaP();
int vaziaP();
void enfileirar(Trabalho t);
void processar();
void listar();
void buscar(int id);
void cancelar(int id);
void carregarDoArquivo();
void salvarNoArquivo();

// =========================
// MAIN
// =========================
int main()
{
    int op, id;
    Trabalho t;

    carregarDoArquivo();

    do
    {
        printf("\n--- FILA DE IMPRESSAO ---\n");
        printf("1 - Enfileirar\n");
        printf("2 - Processar\n");
        printf("3 - Listar\n");
        printf("4 - Buscar por ID\n");
        printf("5 - Cancelar item\n");
        printf("0 - Sair\n");

        op = lerInteiro("Opcao: ");

        switch (op)
        {
        case 1:
            t.id = lerInteiro("ID: ");

            printf("Arquivo: ");
            fgets(t.arquivo, 50, stdin);
            t.arquivo[strcspn(t.arquivo, "\n")] = 0;

            t.paginas = lerInteiro("Paginas: ");
            t.tipo = lerTipo();

            enfileirar(t);

            printf("\nPressione ENTER para continuar...");
            getchar();
            limparTela();
            break;

        case 2:
            processar();

            printf("\nPressione ENTER para continuar...");
            getchar();
            limparTela();
            break;

        case 3:
            listar();

            printf("\nPressione ENTER para continuar...");
            getchar();
            limparTela();
            break;

        case 4:
            id = lerInteiro("ID: ");
            buscar(id);

            printf("\nPressione ENTER para continuar...");
            getchar();
            limparTela();
            break;

        case 5:
            id = lerInteiro("ID: ");
            cancelar(id);

            printf("\nPressione ENTER para continuar...");
            getchar();
            limparTela();
            break;

        case 0:
            salvarNoArquivo();
            printf("Encerrando o sistema...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }
    } while (op != 0);

    return 0;
}

// =========================
// FILAS
// =========================

// NORMAL
Trabalho filaNormal[MAX];
int iniN = 0, fimN = 0, qtdN = 0;

// PRIORITÁRIA (circular)
Trabalho filaP[MAX];
int iniP = 0, fimP = 0, qtdP = 0;

// =========================
// VALIDAÇÃO
// =========================
int lerInteiro(const char *msg)
{
    int valor;
    char buffer[100];

    while (1)
    {
        printf("%s", msg);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &valor) == 1)
        {
            return valor;
        }

        printf("Entrada invalida! Digite apenas numeros.\n");
    }
}

char lerTipo()
{
    char tipo;
    char buffer[10];

    while (1)
    {
        printf("Tipo (Normal[N]/Preferencial[P]): ");
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, " %c", &tipo) == 1)
        {
            if (tipo == 'N' || tipo == 'n' || tipo == 'P' || tipo == 'p')
            {
                return toupper(tipo);
            }
        }

        printf("Digite apenas N ou P!\n");
    }
}

// =========================
// VERIFICAÇÕES
// =========================
int cheiaNormal() { return qtdN == MAX; }
int vaziaNormal() { return qtdN == 0; }

int cheiaP() { return qtdP == MAX; }
int vaziaP() { return qtdP == 0; }

// =========================
// INSERIR
// =========================
void enfileirar(Trabalho t)
{
    if (t.tipo == 'P')
    {
        if (cheiaP())
        {
            printf("Fila prioritaria cheia!\n");
            return;
        }
        filaP[fimP] = t;
        fimP = (fimP + 1) % MAX;
        qtdP++;
    }
    else
    {
        if (cheiaNormal())
        {
            printf("Fila normal cheia!\n");
            return;
        }
        filaNormal[fimN] = t;
        fimN++;
        qtdN++;
    }

    printf("Trabalho adicionado!\n");
}

// =========================
// PROCESSAR
// =========================
void processar()
{
    if (!vaziaP())
    {
        Trabalho t = filaP[iniP];
        printf("\n[P] Processando PRIORITARIO:\n");
        printf("ID: %d | Arquivo: %s | Paginas: %d\n", t.id, t.arquivo, t.paginas);

        iniP = (iniP + 1) % MAX;
        qtdP--;
    }
    else if (!vaziaNormal())
    {
        Trabalho t = filaNormal[iniN];
        printf("\n[N] Processando NORMAL:\n");
        printf("ID: %d | Arquivo: %s | Paginas: %d\n", t.id, t.arquivo, t.paginas);

        iniN++;
        qtdN--;
    }
    else
    {
        printf("Nenhum trabalho na fila!\n");
    }
}

// =========================
// LISTAR
// =========================
void listar()
{
    int i, pos;

    printf("\n=============================\n");
    printf("   FILA DE IMPRESSAO\n");
    printf("=============================\n");

    // PRIORITÁRIA
    printf("\n--- PRIORITARIOS (P) ---\n");
    if (vaziaP())
    {
        printf("Nenhum trabalho prioritario\n");
    }
    else
    {
        pos = iniP;
        for (i = 0; i < qtdP; i++)
        {
            printf("[P] ID:%d | %s | %d pags\n",
                   filaP[pos].id,
                   filaP[pos].arquivo,
                   filaP[pos].paginas);
            pos = (pos + 1) % MAX;
        }
    }

    // NORMAL
    printf("\n--- NORMAIS (N) ---\n");
    if (vaziaNormal())
    {
        printf("Nenhum trabalho normal\n");
    }
    else
    {
        for (i = iniN; i < fimN; i++)
        {
            printf("[N] ID:%d | %s | %d pags\n",
                   filaNormal[i].id,
                   filaNormal[i].arquivo,
                   filaNormal[i].paginas);
        }
    }

    printf("\n=============================\n");
}

// =========================
// BUSCAR
// =========================
void buscar(int id)
{
    int i, pos;

    pos = iniP;
    for (i = 0; i < qtdP; i++)
    {
        if (filaP[pos].id == id)
        {
            printf("Encontrado na fila PRIORITARIA\n");
            return;
        }
        pos = (pos + 1) % MAX;
    }

    for (i = iniN; i < fimN; i++)
    {
        if (filaNormal[i].id == id)
        {
            printf("Encontrado na fila NORMAL\n");
            return;
        }
    }

    printf("Trabalho nao encontrado!\n");
}

// =========================
// CANCELAR
// =========================
void cancelar(int id)
{
    int i, j, pos;

    // PRIORITÁRIA
    pos = iniP;
    for (i = 0; i < qtdP; i++)
    {
        if (filaP[pos].id == id)
        {
            int k = pos;
            while (k != fimP)
            {
                int prox = (k + 1) % MAX;
                filaP[k] = filaP[prox];
                k = prox;
            }
            fimP = (fimP - 1 + MAX) % MAX;
            qtdP--;
            printf("Cancelado da fila PRIORITARIA\n");
            return;
        }
        pos = (pos + 1) % MAX;
    }

    // NORMAL
    for (i = iniN; i < fimN; i++)
    {
        if (filaNormal[i].id == id)
        {
            for (j = i; j < fimN - 1; j++)
            {
                filaNormal[j] = filaNormal[j + 1];
            }
            fimN--;
            qtdN--;
            printf("Cancelado da fila NORMAL\n");
            return;
        }
    }

    printf("Trabalho nao encontrado!\n");
}

// =========================
// CARREGAR DO ARQUIVO CSV
// =========================
void carregarDoArquivo()
{
    FILE *arquivo = fopen("trabalhos.csv", "r");
    if (arquivo == NULL)
    {
        printf("Arquivo de dados não encontrado. Iniciando com filas vazias.\n");
        return;
    }

    // Pular cabeçalho
    char linha[200];
    fgets(linha, sizeof(linha), arquivo);

    // Contar quantos foram carregados
    int carregados = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        Trabalho t;

        // Remover quebra de linha
        linha[strcspn(linha, "\n")] = 0;

        // Parse da linha CSV (formato: id,arquivo,paginas,tipo)
        char *token = strtok(linha, ",");
        if (token)
            t.id = atoi(token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(t.arquivo, token);

        token = strtok(NULL, ",");
        if (token)
            t.paginas = atoi(token);

        token = strtok(NULL, ",");
        if (token)
        {
            // Converter para maiúsculo e pegar primeiro caractere
            char tipo = toupper(token[0]);
            t.tipo = (tipo == 'P') ? 'P' : 'N';
        }

        // Verificar se as filas não estão cheias antes de enfileirar
        if (t.tipo == 'P')
        {
            if (!cheiaP())
            {
                filaP[fimP] = t;
                fimP = (fimP + 1) % MAX;
                qtdP++;
                carregados++;
            }
            else
            {
                printf("Fila prioritária cheia! Não foi possível carregar o trabalho ID %d.\n", t.id);
            }
        }
        else
        {
            if (!cheiaNormal())
            {
                filaNormal[fimN] = t;
                fimN++;
                qtdN++;
                carregados++;
            }
            else
            {
                printf("Fila normal cheia! Não foi possível carregar o trabalho ID %d.\n", t.id);
            }
        }
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso! %d trabalhos encontrados.\n", carregados);
}

void salvarNoArquivo()
{
    FILE *arquivo = fopen("trabalhos.csv", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao salvar arquivo!\n");
        return;
    }

    // Escrever cabeçalho
    fprintf(arquivo, "id,arquivo,paginas,tipo\n");

    int i, pos;

    // Salvar fila PRIORITÁRIA
    pos = iniP;
    for (i = 0; i < qtdP; i++)
    {
        fprintf(arquivo, "%d,%s,%d,%c\n",
                filaP[pos].id,
                filaP[pos].arquivo,
                filaP[pos].paginas,
                filaP[pos].tipo);
        pos = (pos + 1) % MAX;
    }

    // Salvar fila NORMAL
    for (i = iniN; i < fimN; i++)
    {
        fprintf(arquivo, "%d,%s,%d,%c\n",
                filaNormal[i].id,
                filaNormal[i].arquivo,
                filaNormal[i].paginas,
                filaNormal[i].tipo);
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}