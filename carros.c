#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Codigo feito por mim, Thiago Bernardi, para a atividade A1
// da disciplina GRA1033 TÉCNICAS DE PROGRAMAÇÃO GR3342-212-9 - 202120
// do curso bacharelado de Ciencias da Computacao da FMU.

// declarando as funcoes implicitamente:
int listarCarros();
int contarCarros();
int inserirVeiculo();

typedef struct carro {
    char marca[30];
    char modelo[30];
    int ano;
    char placa[9];
    int existe;
}TIPO_CARRO;

const int tamanhoArray = 11;

// const int max_candidates = 5;

TIPO_CARRO listaCarros[tamanhoArray];

// funcao para colocar strings em formato minusculo e remover \n do final:

char *tratarString(char *str, int len)
{
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


    printf("\nBem vindo\n");
    printf("Por favor selecione uma das opções desejadas:\n");
    printf("\t1. Listar os veículos cadastrados.\n");
    printf("\t2. Inserir um novo veículo.\n");
    printf("\t3. Listar os veículos filtrando-se por ano de fabricação.\n");
    printf("\t4. Listar os veículos a partir de determinado ano.\n");
    printf("\t5. Listar os veículos filtrando-se pelo modelo.\n");
    printf("Por favor digite o numero da opção desejada: ");

    // int itemLido = scanf("%d", &opcao);

    fgets(opcao,20,stdin);

    // if (itemLido == 1) {

    // printf("%s\n", opcao);

    if (strcmp("1\n",opcao) == 0 || strcmp("01\n",opcao) == 0)
    {
        printf("Escolheu 1\n");
        listarCarros("todos", "todos");
        mostrarMenu();

    }
    else if (strcmp("2\n",opcao) == 0 || strcmp("02\n",opcao) == 0)
    {
        // printf("Escolheu 2\n");
        printf("Insira um veículo: \n");
        inserirVeiculo();
        mostrarMenu();
    }
    else if (strcmp("3\n",opcao) == 0 || strcmp("03\n",opcao) == 0)
    {
        // printf("Escolheu 3\n");

        char anoBuffer[6];

        printf("Insira o ano: ");

        fgets(anoBuffer, 6, stdin);

        listarCarros("ano", anoBuffer);
        mostrarMenu();

    }
    else if (strcmp("4\n",opcao) == 0 || strcmp("04\n",opcao) == 0)
    {
        // printf("Escolheu 4\n");
        char anoApartirBuffer[6];

        printf("Pesquisar a partir do ano: ");

        fgets(anoApartirBuffer, 6, stdin);

        listarCarros("partir", anoApartirBuffer);
        mostrarMenu();
    }
    else if (strcmp("5\n",opcao) == 0 || strcmp("05\n",opcao) == 0)
    {
        // printf("Escolheu 5\n");
        char modeloBuffer[30];

        printf("Insira o modelo: ");

        fgets(modeloBuffer, 30, stdin);

        listarCarros("modelo", modeloBuffer);
        mostrarMenu();
    } else if (strcmp("99\n",opcao) == 0 || strcmp("98\n",opcao) == 0) {

        // tive que fazer isso pois senao receberia erro de all paths call itself
        printf("Testing");

    } else {
        printf("%s", opcao);
        printf("\nOpcao Invalida!\n");
        mostrarMenu();
    }

    return 0;
}



int main()
{

    mostrarMenu();
}

int contarCarros()
{
    // vamos contar quantos carros já tem cadastrados
    int contagemCarros = 0;
    for (int i = 0; i < tamanhoArray; i++){
        if (listaCarros[i].existe == 1) {
            contagemCarros++;
        }
    }
    return contagemCarros;
}

int listarCarros(char filtro[10], char dado[30])
{

        printf("\nTemos %d carros\n\n", contarCarros());
        // int tamanho = sizeof(listaCarros)/sizeof(TIPO_CARRO);
        // printf("%d\n", size);
        for (int i = 0; i < tamanhoArray; i++) {

                if (listaCarros[i].existe == 1 ) {
                    if (strcmp("todos",filtro) == 0 && strcmp("todos",dado ) == 0 ) {
                        printf("Carro #%d\n", i);
                        printf("Marca: %s\n", listaCarros[i].marca);
                        printf("Modelo: %s\n", listaCarros[i].modelo);
                        printf("Ano: %d\n", listaCarros[i].ano);
                        printf("Placa: %s\n", listaCarros[i].placa);
                    }
                    if (strcmp("ano",filtro) == 0 ) {

                        int dadoInt = atoi(dado);

                        if (listaCarros[i].ano == dadoInt) {
                            printf("Carro #%d\n", i);
                            printf("Marca: %s\n", listaCarros[i].marca);
                            printf("Modelo: %s\n", listaCarros[i].modelo);
                            printf("Ano: %d\n", listaCarros[i].ano);
                            printf("Placa: %s\n", listaCarros[i].placa);
                        }

                    }
                    if (strcmp("partir",filtro) == 0) {

                        int dadoInt = atoi(dado);

                        if (listaCarros[i].ano >= dadoInt) {
                            printf("Carro #%d\n", i);
                            printf("Marca: %s\n", listaCarros[i].marca);
                            printf("Modelo: %s\n", listaCarros[i].modelo);
                            printf("Ano: %d\n", listaCarros[i].ano);
                            printf("Placa: %s\n", listaCarros[i].placa);
                        }

                    }
                    if (strcmp("modelo",filtro) == 0 ) {

                        // usando funcao customizada que criei para deixar em caixa baixa
                        // e remover quebra de linha com strcspn
                        int lenDado = strlen(dado);
                        char *dadoTratado = tratarString(dado, lenDado);

                        if (strcmp(listaCarros[i].modelo,dadoTratado) == 0) {
                            printf("Carro #%d\n", i);
                            printf("Marca: %s\n", listaCarros[i].marca);
                            printf("Modelo: %s\n", listaCarros[i].modelo);
                            printf("Ano: %d\n", listaCarros[i].ano);
                            printf("Placa: %s\n", listaCarros[i].placa);
                        }

                    }


                } // final do if .existe 1


        } // final do for

    return 0;
}

int inserirVeiculo(){

    int numeroVeiculos = contarCarros();

    // Verificando se o numero de veiculos já alcançou o limite de 10.

    if (numeroVeiculos == 10){
        printf("Desculpe, o limite de 10 veículos já foi atingido. Não é possível inserir mais veículos.");
        return 1;
    }

    char marca[30];
    char modelo[30];
    char bufferAno[6];
    char placa[9];
    int existe;

    printf("Insira a marca do veículo (max. 30 caract.): ");
    fgets(marca,30,stdin);
    // usando funcao customizada que criei para deixar em caixa baixa
    // e remover quebra de linha com strcspn
    int lenMarca = strlen(marca);
    char *marcaTratado = tratarString(marca, lenMarca);

    printf("Insira o modelo do veículo (max. 30 caract.): ");
    fgets(modelo,30,stdin);
    // usando funcao customizada que criei para deixar em caixa baixa
    // e remover quebra de linha com strcspn
    int lenModelo = strlen(modelo);
    char *modeloTratado = tratarString(modelo, lenModelo);

    printf("Insira o ano de fabricacao do veículo (max. 4 caract.): ");
    fgets(bufferAno, 6, stdin);
    int ano = atoi(bufferAno);
    // scanf("%d", &ano);
    // printf("Ano: %d\n", ano);

    printf("Insira a placa do veículo: ");
    fgets(placa,10,stdin);
    // printf("Recebemos o valor da placa: %s", placa);
    // usando strcspn para remover quebra de linha
    // usando funcao customizada que criei para deixar em caixa baixa
    // e remover quebra de linha com strcspn
    int lenPlaca = strlen(placa);
    char *placaTratado = tratarString(placa, lenPlaca);

    int indice;

    if (numeroVeiculos == 0) {
        indice = 0;
    } else {
        indice = numeroVeiculos + 1;
    }
    strcpy(listaCarros[indice].marca, marcaTratado);
    strcpy(listaCarros[indice].modelo, modeloTratado);
    // strcpy(listaCarros[indice].ano, ano);
    listaCarros[indice].ano = ano;
    strcpy(listaCarros[indice].placa, placaTratado);
    listaCarros[indice].existe = 1;

    // ordenando depois de inserir

    numeroVeiculos = contarCarros();

    for (int i = 0; i < numeroVeiculos; i++) {

        for (int j = i + 1; j <= numeroVeiculos; j++) {

            if (listaCarros[j].ano < listaCarros[i].ano) {

                // printf("%d eh menor que %d\n", listaCarros[j].ano, listaCarros[i].ano);

                TIPO_CARRO copiaTemp = listaCarros[i];
                listaCarros[i] = listaCarros[j];
                listaCarros[j] = copiaTemp;
            }

        }

    }

    free(marcaTratado);
    free(modeloTratado);
    free(placaTratado);


    return 0;
}