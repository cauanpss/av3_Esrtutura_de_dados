#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Necessário para a função isdigit()

#define MAX 100

// Define o comando correto para limpar a tela dependendo do sistema operacional
#ifdef _WIN32
#define LIMPAR_TELA "cls"
#else
#define LIMPAR_TELA "clear"
#endif

// Definição do Registro para Chamadas de Emergência
typedef struct
{
    int protocolo;
    char local[50];
    char tipo[30];
    char horario[20];
} Registro;

// Variáveis Globais da Pilha
Registro pilha[MAX];
int topo = -1;

// --- FUNÇÕES DE AUXÍLIO E VALIDAÇÃO ---

int estaVazia()
{
    return topo == -1;
}

int estaCheia()
{
    return topo == MAX - 1;
}

int protocoloExiste(int prot)
{
    for (int i = 0; i <= topo; i++)
    {
        if (pilha[i].protocolo == prot)
        {
            return 1;
        }
    }
    return 0;
}

void aguardarUsuario()
{
    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
}

// Nova função: Ler string garantindo que não fique vazia
void lerStringNaoVazia(char *destino, int max, const char *prompt)
{
    do
    {
        printf("%s", prompt);
        fgets(destino, max, stdin);
        destino[strcspn(destino, "\n")] = 0; // Remove quebra de linha
        if (strlen(destino) == 0)
        {
            printf("[ERRO] Este campo nao pode ficar vazio!\n");
        }
    } while (strlen(destino) == 0);
}

// Nova função: Ler protocolo blindado contra letras
int lerProtocoloBlindado()
{
    char buffer[50];
    int valido = 0;
    int protocolo = -1;

    while (!valido)
    {
        printf("Digite o numero do protocolo (Apenas numeros): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0)
        {
            printf("[ERRO] O protocolo nao pode ser vazio!\n");
            continue;
        }

        int apenasNumeros = 1;
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            if (!isdigit(buffer[i]))
            { // Verifica caractere por caractere se é dígito
                apenasNumeros = 0;
                break;
            }
        }

        if (apenasNumeros)
        {
            protocolo = atoi(buffer); // Converte a string limpa para int
            valido = 1;
        }
        else
        {
            printf("[ERRO] Formato invalido! Digite APENAS NUMEROS.\n");
        }
    }
    return protocolo;
}

// Nova função: Ler e validar formato de hora (HH:MM)
void lerHorario(char *destino)
{
    int valido = 0;
    while (!valido)
    {
        printf("Horario (HH:MM): ");
        fgets(destino, 20, stdin);
        destino[strcspn(destino, "\n")] = 0;

        // Verifica o tamanho da string e se os dois pontos (:) estão na posição certa
        if (strlen(destino) == 5 &&
            isdigit(destino[0]) && isdigit(destino[1]) &&
            destino[2] == ':' &&
            isdigit(destino[3]) && isdigit(destino[4]))
        {

            // Converte os caracteres separados para inteiros lógicos
            int hh = (destino[0] - '0') * 10 + (destino[1] - '0');
            int mm = (destino[3] - '0') * 10 + (destino[4] - '0');

            // Valida as horas lógicas (0 a 23h, 0 a 59 min)
            if (hh >= 0 && hh <= 23 && mm >= 0 && mm <= 59)
            {
                valido = 1;
            }
            else
            {
                printf("[ERRO] Hora ou minuto invalido! Use de 00:00 a 23:59.\n");
            }
        }
        else
        {
            printf("[ERRO] Formato invalido! Use EXATAMENTE o formato HH:MM (Ex: 09:30).\n");
        }
    }
}

// --- OPERAÇÕES DA PILHA ---

void push()
{
    if (estaCheia())
    {
        printf("\n[ERRO] Pilha cheia! Nao e possivel registrar mais chamadas.\n");
        aguardarUsuario();
        return;
    }

    Registro novaChamada;

    printf("\n--- REGISTRAR CHAMADA ---\n");

    // Looping para garantir protocolo único
    int prot;
    do
    {
        prot = lerProtocoloBlindado();
        if (protocoloExiste(prot))
        {
            printf("[ERRO] Ja existe uma chamada com esse protocolo! Tente outro.\n");
        }
        else
        {
            novaChamada.protocolo = prot;
            break;
        }
    } while (1);

    // Usa os ajudantes para ler textos e hora
    lerStringNaoVazia(novaChamada.local, 50, "Local da emergencia: ");
    lerStringNaoVazia(novaChamada.tipo, 30, "Tipo da ocorrencia: ");
    lerHorario(novaChamada.horario);

    topo++;
    pilha[topo] = novaChamada;
    printf("[SUCESSO] Chamada %d registrada!\n", novaChamada.protocolo);
    aguardarUsuario();
}

void pop()
{
    if (estaVazia())
    {
        printf("\n[AVISO] Nao ha chamadas na fila de emergencia.\n");
        aguardarUsuario();
        return;
    }

    Registro atendida = pilha[topo];
    topo--;

    printf("\n--- ATENDENDO CHAMADA ---\n");
    printf("Protocolo: %d\n", atendida.protocolo);
    printf("Tipo: %s\n", atendida.tipo);
    printf("Local: %s\n", atendida.local);
    printf("Horario: %s\n", atendida.horario);
    printf("[SUCESSO] Chamada encerrada.\n");
    aguardarUsuario();
}

void peek()
{
    if (estaVazia())
    {
        printf("\n[AVISO] Nao ha chamadas para consultar.\n");
        aguardarUsuario();
        return;
    }

    printf("\n--- PROXIMA CHAMADA A SER ATENDIDA ---\n");
    printf("Protocolo: %d\n", pilha[topo].protocolo);
    printf("Tipo: %s\n", pilha[topo].tipo);
    printf("Local: %s\n", pilha[topo].local);
    printf("Horario: %s\n", pilha[topo].horario);
    aguardarUsuario();
}

void listarPilha()
{
    if (estaVazia())
    {
        printf("\n[AVISO] Nenhuma chamada pendente.\n");
        aguardarUsuario();
        return;
    }

    printf("\n=== LISTA DE CHAMADAS PENDENTES ===\n");
    for (int i = topo; i >= 0; i--)
    {
        printf("[%d] Protocolo: %d | Tipo: %s | Local: %s | Horario: %s\n",
                i, pilha[i].protocolo, pilha[i].tipo, pilha[i].local, pilha[i].horario);
    }
    printf("===================================\n");
    aguardarUsuario();
}

// --- ARQUIVOS CSV ---

void salvarCSV(int exibirMensagem)
{
    // Agora o if mata a função imediatamente se não houver dados,
    // independente se é salvamento manual (exibirMensagem=1) ou fechamento de tela.
    if (estaVazia())
    {
        if (exibirMensagem)
        {
            printf("\n[AVISO] Nao ha dados para salvar.\n");
            aguardarUsuario();
        }
        return;
    }

    FILE *arquivo = fopen("chamadas.csv", "w");
    if (arquivo == NULL)
    {
        if (exibirMensagem)
        {
            printf("\n[ERRO] Nao foi possivel criar o arquivo CSV.\n");
            aguardarUsuario();
        }
        return;
    }

    fprintf(arquivo, "protocolo,local,tipo,horario\n");

    for (int i = 0; i <= topo; i++)
    {
        fprintf(arquivo, "%d,%s,%s,%s\n",
                pilha[i].protocolo, pilha[i].local, pilha[i].tipo, pilha[i].horario);
    }

    fclose(arquivo);
    if (exibirMensagem)
    {
        printf("\n[SUCESSO] Dados salvos com sucesso!\n");
        aguardarUsuario();
    }
}

void carregarCSV()
{
    FILE *arquivo = fopen("chamadas.csv", "r");
    if (arquivo == NULL)
    {
        return;
    }

    char linha[200];
    if (fgets(linha, sizeof(linha), arquivo) == NULL)
    {
        fclose(arquivo);
        return;
    }

    topo = -1;

    while (fgets(linha, sizeof(linha), arquivo) && !estaCheia())
    {
        Registro c;

        linha[strcspn(linha, "\n")] = 0;

        char *token = strtok(linha, ",");
        if (token != NULL)
            c.protocolo = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL)
            strcpy(c.local, token);

        token = strtok(NULL, ",");
        if (token != NULL)
            strcpy(c.tipo, token);

        token = strtok(NULL, ",");
        if (token != NULL)
            strcpy(c.horario, token);

        topo++;
        pilha[topo] = c;
    }

    fclose(arquivo);
}

// --- MENU PRINCIPAL ---
int main()
{
    int opcao;
    char bufferOpcao[20];

    carregarCSV();

    do
    {
        system(LIMPAR_TELA);
        printf("\n--- SISTEMA DE CHAMADAS DE EMERGENCIA ---\n");
        printf("1. Registrar Chamada\n");
        printf("2. Atender Chamada\n");
        printf("3. Consultar Ultima Chamada\n");
        printf("4. Listar Todas as Chamadas\n");
        printf("5. Salvar Dados\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        // Proteção também no menu principal contra letras!
        fgets(bufferOpcao, sizeof(bufferOpcao), stdin);
        opcao = atoi(bufferOpcao);

        switch (opcao)
        {
        case 1:
            push();
            break;
        case 2:
            pop();
            break;
        case 3:
            peek();
            break;
        case 4:
            listarPilha();
            break;
        case 5:
            salvarCSV(1);
            break;
        case 0:
            salvarCSV(0);
            printf("\nEncerrando programa.\n");
            break;
        default:
            // Evita disparo se o usuário só bater ENTER no menu
            if (bufferOpcao[0] != '\n')
            {
                printf("\nOpcao invalida! Tente novamente.\n");
                aguardarUsuario();
            }
        }
    } while (opcao != 0);

    return 0;
}