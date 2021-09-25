#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TAMANHO 10

// Codigo feito por mim, Thiago Bernardi, para a atividade A3
// da disciplina GRA1033 TÉCNICAS DE PROGRAMAÇÃO GR3342-212-9 - 202120
// do curso bacharelado de Ciencias da Computacao da FMU.

// declarando as funcoes implicitamente:
void listarClientes();
int contarClientes();
int inserirCliente();
void removerCliente(int posicaoCliente);
void atualizarGastosCliente(int posicaoCliente, double novoMontante);
void zerarTodosGastos();
int mostrarMelhorComprador();
void exibirGastosCliente (int idCliente);

typedef struct cliente {
    char nome[30];
    int ano;
    double gastos;
    int existe;
}TIPO_CLIENTE;

const int tamanhoArray = TAMANHO;
int tamanhoAtualArrayClientes = tamanhoArray;


// TIPO_CLIENTE listaClientes[tamanhoArray];
// line* array = malloc(number_of_elements * sizeof(*array));

// TIPO_CLIENTE* listaClientes = malloc(TAMANHO * sizeof(*listaClientes));

// int* myArray = calloc(16, sizeof(int));

TIPO_CLIENTE* listaClientes;


// funcao para colocar strings em formato minusculo e remover \n do final:

char *tratarString(char *str, int len) {
    char *str_l = calloc(len+1, sizeof(char));

    for (size_t i = 0; i < len; ++i) {
        str_l[i] = tolower((unsigned char)str[i]);
    }
    str_l[strcspn(str_l, "\n")] = 0;
    return str_l;
}

int mostrarMenu()
{

    // int opcao = 0;
    char opcao[20];
    char idBuffer[5];


    printf("\n#############\n");
    printf("Bem vindo!!\n");
    printf("#############\n\n");
    printf("Por favor selecione uma das opções desejadas:\n\n");
    printf("\t1. Incluir um novo cliente.\n");
    printf("\t2. Remover cliente.\n");
    printf("\t3. Atualizar o montante de compras do cliente realizadas no mês corrente.\n");
    printf("\t4. Zerar todos os montantes de compras por ocasião da virada de mês.\n");
    printf("\t5. Listar o cliente melhor comprador.\n");
    printf("\t6. Exibir um montante de compras de um cliente específico.\n\n");
    printf("Por favor digite o numero da opção desejada: ");

    // int itemLido = scanf("%d", &opcao);

    fgets(opcao,20,stdin);

    // if (itemLido == 1) {

    // printf("%s\n", opcao);

    if (strcmp("1\n",opcao) == 0 || strcmp("01\n",opcao) == 0)
    {

        printf("\n#############\n\n");
        printf("Incluir um novo cliente. \n");
        inserirCliente();
        mostrarMenu();


    }
    else if (strcmp("2\n",opcao) == 0 || strcmp("02\n",opcao) == 0)
    {
        listarClientes();
        printf("Escolha o ID do cliente a ser removido: ");

        fgets(idBuffer, 4, stdin);

        int idCliente = atoi(idBuffer);

        removerCliente(idCliente);

        listarClientes();
        printf("\n#############\n\n");

        mostrarMenu();

    }
    else if (strcmp("3\n",opcao) == 0 || strcmp("03\n",opcao) == 0)
    {
        listarClientes();
        printf("Escolha o ID do cliente a ter os seus gastos atualizados: ");

        fgets(idBuffer, 4, stdin);
        int idCliente = atoi(idBuffer);

        char bufferNovoMontante[10];
        double novoMontante;

        printf("Insira o novo montante deste cliente (Ex: 843,21): ");

        fgets(bufferNovoMontante, 10, stdin);
        sscanf(bufferNovoMontante, "%lf", &novoMontante);

        atualizarGastosCliente(idCliente, novoMontante);

        printf("\nListando novamente os clientes: \n");

        listarClientes();
        mostrarMenu();

    }
    else if (strcmp("4\n",opcao) == 0 || strcmp("04\n",opcao) == 0)
    {
        zerarTodosGastos();
        listarClientes();
        mostrarMenu();
    }
    else if (strcmp("5\n",opcao) == 0 || strcmp("05\n",opcao) == 0)
    {
        mostrarMelhorComprador();
        // listarClientes();
        mostrarMenu();

    } else if (strcmp("6\n",opcao) == 0 || strcmp("06\n",opcao) == 0) {

        int indiceCliente = 0;

        int numeroClientes = contarClientes();

        for (int i = 0; i < numeroClientes; i++) {
            indiceCliente++;
            printf("\nCliente ID #%i\n", indiceCliente);
            printf("Nome: %s\n", listaClientes[i].nome);
        }

        printf("\nEscolha o ID para exibir o montante de gastos: ");

        fgets(idBuffer, 4, stdin);
        int idCliente = atoi(idBuffer);
        exibirGastosCliente(idCliente);
        mostrarMenu();

    } else if (strcmp("99\n",opcao) == 0 || strcmp("98\n",opcao) == 0) {

        // tive que fazer isso pois senao receberia erro de all paths call itself
        printf("Testando");


    } else {
        // printf("%s", opcao);
        printf("\n#############");
        printf("\nOpcao Invalida!\n");
        printf("#############\n\n");
        mostrarMenu();
    }

    return 0;
}



int main()
{
    listaClientes = calloc(tamanhoArray, sizeof(TIPO_CLIENTE));

    mostrarMenu();
}

int contarClientes()
{
    // vamos contar quantos clientes já tem cadastrados
    int contagemClientes = 0;
    for (int i = 0; i < tamanhoAtualArrayClientes; i++){
        if (listaClientes[i].existe == 1) {
            contagemClientes++;
        }
    }
    return contagemClientes;
}

void listarClientes() {

    int indiceCliente = 0;
    int numeroClientes = contarClientes();

    for (int i = 0; i < numeroClientes; i++) {
        indiceCliente++;
        printf("\nCliente ID #%i\n", indiceCliente);
        printf("Nome: %s\n", listaClientes[i].nome);
        printf("Ano nascimento: %d\n", listaClientes[i].ano);
        printf("Gastos: $%.2f\n\n", listaClientes[i].gastos);

    } // final do for
}

int mostrarMelhorComprador() {

    int numeroClientes = contarClientes();

    // Se tiver clientes cadastrados verifique para evitar Segmentation Fault:

    if (numeroClientes > 0) {

        int indiceClienteMelhorComprador;

        double maiorGastosAtual = 0;

        for (int i = 0; i < numeroClientes; i++) {

            if (listaClientes[i].gastos > maiorGastosAtual) {
                maiorGastosAtual = listaClientes[i].gastos;
                indiceClienteMelhorComprador = i;
            }

        } // final do for

        if (maiorGastosAtual > 0) {
            printf("\n#############");
            printf("\nO cliente que mais gastou foi: \n");
            printf("Nome: %s\n", listaClientes[indiceClienteMelhorComprador].nome);
            printf("Gastos: %.2f\n", listaClientes[indiceClienteMelhorComprador].gastos);
            printf("#############\n\n");
        } else {
            printf("\n#############");
            printf("\nOs gatos estao zerados, por favor aguarde novas compras.\n");
            printf("#############\n\n");
        }



    } else {
        printf("\n\n#############");
        printf("\nAtencao!! Nao existem clientes cadastrados, por favor cadastre clientes antes de consultar esta opcao. \n");
        printf("#############\n\n");
    }



    return 0;
}

void aumentarMemoriaArray(TIPO_CLIENTE** lista)
{
    printf("\n\nAumentando Memoria\n Era: %d\n", tamanhoAtualArrayClientes);
    tamanhoAtualArrayClientes = tamanhoAtualArrayClientes + TAMANHO;
    printf("Ficou: %d\n\n", tamanhoAtualArrayClientes);
    *lista = realloc(*lista, tamanhoAtualArrayClientes * sizeof(TIPO_CLIENTE));
}

int inserirCliente(){

    int numeroClientes = contarClientes();

    // Verificando se o numero de veiculos já alcançou o limite.

    if (numeroClientes == tamanhoAtualArrayClientes){
        printf("Desculpe, o limite de %d clientes já foi atingido. Não é possível inserir mais clientes. Vamos realocar mais memoria. \n\n", tamanhoAtualArrayClientes);
        aumentarMemoriaArray(&listaClientes);
        // return 1;
    }

    char nome[30];
    char bufferAno[6];
    char bufferGastos[10];
    double gastos;
    int existe;

    printf("Insira o nome do cliente (max. 30 caract.): ");
    fgets(nome,30,stdin);
    // usando funcao customizada que criei para deixar em caixa baixa
    // e remover quebra de linha com strcspn
    int lenNome = strlen(nome);
    char *nomeTratado = tratarString(nome, lenNome);

    printf("Insira o ano de nascimento do cliente: ");
    fgets(bufferAno, 6, stdin);
    int ano = atoi(bufferAno);

    printf("Insira os gastos deste cliente (Ex: 843,21): ");
    fgets(bufferGastos, 10, stdin);
    // int gastos = atoi(bufferGastos);
    sscanf(bufferGastos, "%lf", &gastos);


    int indice;

    if (numeroClientes == 0) {
        indice = 0;
    } else {
        indice = numeroClientes;
    }

    strcpy(listaClientes[indice].nome, nomeTratado);
    listaClientes[indice].ano = ano;
    listaClientes[indice].gastos = gastos;
    listaClientes[indice].existe = 1;


    // numeroClientes = contarClientes();

    free(nomeTratado);

    return 0;
}

int pegarIndiceCliente(char nome[30]) {
    int indiceCliente = 0;
    int numeroClientes = contarClientes();

    for (int i = 0; i < numeroClientes; i++) {
        if (listaClientes[i].nome == nome) {
            return indiceCliente;
        } else {
            indiceCliente++;
        }
    }
    return 0;
}

void removerCliente(int posicaoCliente) {

    int numeroClientes = contarClientes();
    // int lenNome = strlen(nome);
    // char *nomeTratado = tratarString(nome, lenNome);

    // posicaoCliente = pegarIndiceCliente(*nomeTratado);


    listaClientes[posicaoCliente-1].existe = 0;

    for (int c = posicaoCliente - 1; c < numeroClientes - 1; c++) {
        listaClientes[c] = listaClientes[c+1];
        listaClientes[c+1].existe = 0;
    }
    printf("\n#############\n");
    printf("Cliente com ID #%d removido, listando novamente os clientes: \n", posicaoCliente);
    printf("#############\n");

}

void atualizarGastosCliente(int posicaoCliente, double novoMontante) {
    int posicaoCorrigida = posicaoCliente - 1;
    double gastosAnterior = listaClientes[posicaoCorrigida].gastos;
    listaClientes[posicaoCorrigida].gastos = novoMontante;
    printf("\n\n#############\n");
    printf("Gastos do cliente %s atualizado de $%.2f para $%.2f.", listaClientes[posicaoCorrigida].nome, gastosAnterior, listaClientes[posicaoCorrigida].gastos);
    printf("\n#############\n\n");
}

void zerarTodosGastos(){

    int numeroClientes = contarClientes();

    char confirmacao[3];

    printf("\n\nVocê tem certeza que deseja zerar os montantes de gastos de todos os clientes?\n\nResponda com S ou N : ");

    fgets(confirmacao, 3, stdin);

    int lenConfirmacao = strlen(confirmacao);
    char *confirmacaoTratado = tratarString(confirmacao, lenConfirmacao);

    if (strcmp("s",confirmacaoTratado) == 0) {

        for (int i=0; i < numeroClientes; i++) {
            listaClientes[i].gastos = 0;
        }
        printf("\n\n#############\n");
        printf("\n\nO montante de gastos de todos os clientes foi zerado.\n");
        printf("\n#############\n");

    } else {

        printf("\n\nCerto, voltando para o menu inicial.\n");

    }

}

void exibirGastosCliente (int idCliente) {
    int idCorrigido = idCliente - 1;
    printf("\n\n#############\n");
    printf("O total de gastos do cliente %s, cujo ID é %d é de $%.2f\n" ,listaClientes[idCorrigido].nome, idCliente, listaClientes[idCorrigido].gastos);
    printf("#############\n\n");

}