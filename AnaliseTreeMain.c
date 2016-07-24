/* 
 * File:   AnaliseTreeMain.c
 * Author: Romário Fernando
 *
 * Created on 19 de Julho de 2016, 22:04
 */

#include "ArvoreLLRB.h"
#include "avl.h"
#include "sortNum.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

//==============================================================================

#define arvAVL "AVL"
#define arvRB "Red Black"
#define insercao "insercao"
#define remocao "remocao"

//==============================================================================

//estrutura para armazenar data e hora.
struct tm *DataAtual;
time_t Segundos;

int getDia();
int getMes();
int getAno();

struct DATA {
    int dia;
    int mes;
    int ano;
};
typedef struct DATA Data;

struct dados {
    char* nomeArv;
    char* tipoOperacao;
    int numChaves;
    int rotacoes;
    int altura;
    float secondsTime;
};
typedef struct dados DADOS;

struct ANALISE {
    DADOS* dadosAVL;
    DADOS* dadosRB;
    int quantDadosAVL;
    int quantDadosRB;
};
typedef struct ANALISE Analise;

typedef struct {
    Analise* analise;
    Data* data;
    int quantAnalise;
} GerenAnalise;

//==============================================================================

void menu();
void menuGerenciamentoChaves();
void menuArv();
void pause();
void limparTela();

//==============================================================================

void newGerenAnalise(GerenAnalise* gerenAnalise);

void addDadosArv(GerenAnalise* gerenAnalise, char* nomeArv, char* operacao,
        int quantChaves, int quantRotacoes, int altura, float time);

//Ainda em desenvolvimento
//bool lerDadosArquivoAnalise(GerenAnalise* gerenAnalise);
//bool gravarDadosArquivoAnalise(GerenAnalise* gerenAnalise);

//==============================================================================

void gravarDadosArquivoTxt(Analise analise, Data data);
void imprimirDadosArv(Analise analise);

//==============================================================================

/* Programa que faz análise empírica nas árvores AVL e RedBlack
 */
int main(int argc, char** argv) {

    //Declaração da estrutura que conterá os dados de análise
    GerenAnalise gerenAnalise;

    //Desenvolvimento
    //if (lerDadosArquivoAnalise(&gerenAnalise) == false)

    newGerenAnalise(&gerenAnalise);

    //Declaração da raiz da árvore AVL
    //AVL* raizAVL = (AVL*) malloc(sizeof (AVL));
    AVL* raizAVL;
    *raizAVL = NULL;

    //Declaração da raiz da Árvore Red Black

    //Declaração das variáveis que receberão o tempo do clock do processador
    clock_t iniTime, fimTime;

    //contador
    int i;

    //variáveis que conterá as opcoes escolhidas pelo usuário
    int opcao, opcaoCase1, opcaoCase5;

    //variáveis relacionadas ao vetor que conterá as chaves geradas
    int quantChaves;
    int* vetor = NULL;
    int tamVetor = 0;

    //roracoes da arvore AVL variável global 
    rotacoesAVL = 0;

    do {
        menu();

        scanf("%d", &opcao);

        limparTela();

        switch (opcao) {

            case 1:

                do {
                    menuGerenciamentoChaves();

                    scanf("%d", &opcaoCase1);

                    limparTela();

                    switch (opcaoCase1) {

                        case 1:

                            printf("Digite a quantidade de chaves a serem geradas: ");
                            do {
                                limparTela();
                                printf("Digite a quantidade de chaves a serem geradas > 0: ");
                                scanf("%d", &quantChaves);
                            } while (quantChaves <= 0);

                            tamVetor = quantChaves;

                            sortearNum(&vetor, tamVetor);
                            pause();

                            break;

                        case 2:

                            gerarMatrizArquivoTxt(vetor, tamVetor);
                            pause();

                            break;

                        case 3:

                            printf("Digite a quantidade de chaves a serem lidas: ");
                            do {
                                limparTela();
                                printf("Digite a quantidade de chaves a serem lidas > 0: ");
                                scanf("%d", &tamVetor);
                            } while (tamVetor <= 0);
                            lerVetorArquivoTxt(&vetor, &tamVetor);
                            pause();

                            break;

                        case 4:

                            imprimirVetorMatriz(vetor, tamVetor);
                            printf("\n\n");
                            pause();

                            break;

                        case 5:
                            break;

                        default:
                            printf("Opcao invalida!!!\n");
                            pause();
                    }

                    limparTela();

                } while (opcaoCase1 != 5);

                break;

            case 2:

                if (tamVetor == 0) {
                    printf("Nao ha chaves para serem inseridas!!!\n");
                    pause();
                    break;
                }

                do {
                    printf("Quantidade de chaves a serem inseridas <= %d: ", tamVetor);
                    scanf("%d", &quantChaves);
                    limparTela();
                } while (quantChaves > tamVetor);

                //==============================================================

                printf("Iniciando insercao na Arvore AVL!\n");

                rotacoesAVL = 0;

                iniTime = clock();

                for (i = 0; i < quantChaves; i++) {
                    inserirNoAVL(raizAVL, vetor[i]);
                    //printf("\n\n");
                    //printTree(*raizAVL, 0);
                }

                fimTime = clock();

                printf("insercao na Arvore AVL Terminada!\n\n");

                addDadosArv(&gerenAnalise, arvAVL, insercao,
                        quantChaves, rotacoesAVL, alturaNo(*raizAVL),
                        (float) (fimTime - iniTime) / CLOCKS_PER_SEC);

                //==============================================================

                //printf("Iniciando insercao na Arvore Red Black!\n");

                /*
                dadosRB[n-1].nomeArv = redBlack;
                dadosRB[n-1].tipoOperacao = insercao;
                dadosRB[n-1].numChaves = quantChaves;
                dadosRB[n-1].rotacoes = 0;
                dadosRB[n-1].secondsTime = (float)(fimTime-iniTime)/CLOCKS_PER_SEC;
                 */
                //printf("Remocao na Arvore Red Black Terminada!\n\n");

                //addDadosArv(&gerenAnalise , arvRB, insercao, quantChaves, quantRotacoes, (float) (fimTime - iniTime) / CLOCKS_PER_SEC);

                pause();

                break;

            case 3:

                if (tamVetor == 0) {
                    printf("Nao ha chaves para serem removidas!!!\n");
                    pause();
                    break;
                }

                if (*raizAVL == NULL) {
                    printf("Arvores vazias!!!\n");
                    pause();
                    break;
                }

                do {
                    printf("Quantidade de chaves a serem removidas <= %d: ", tamVetor);
                    scanf("%d", &quantChaves);
                    limparTela();
                } while (quantChaves > tamVetor);

                //==============================================================

                printf("Iniciando remocao na Arvore AVL!\n");

                //teste
                rotacoesAVL = 0;
                //printf("\nRotacoes: %d\n", rotacoesAVL);

                //printTree(*raizAVL, 0);

                iniTime = clock();

                for (i = 0; i < quantChaves; i++) {
                    removerNoAVL(raizAVL, vetor[i]);
                    //printf("\n\nremovendo: %d\n\n", vetor[i]);
                    //printTree(*raizAVL, 0);
                }

                fimTime = clock();

                printf("Remocao na Arvore AVL Terminada!\n\n");

                //printTree(*raizAVL, 0);

                addDadosArv(&gerenAnalise, arvAVL, remocao,
                        quantChaves, rotacoesAVL, alturaNo(*raizAVL),
                        (float) (fimTime - iniTime) / CLOCKS_PER_SEC);

                //==============================================================

                /*printf("Iniciando remocao na Arvore Red Black!\n");
                
                addDadosArv(&gerenAnalise , arvRB, remocao, quantChaves, quantRotacoes, (float) (fimTime - iniTime) / CLOCKS_PER_SEC);
                
                printf("Remocao na Arvore Red Black Terminada!\n\n");*/

                pause();

                break;

            case 4:

                do {

                    menuArv();

                    scanf("%d", &opcaoCase5);

                    limparTela();

                    switch (opcaoCase5) {

                        case 1:

                            printf("\n\n");
                            printTree(*raizAVL, 0);
                            printf("\n\n");

                            pause();

                            break;

                        case 2:

                            printf("\n\n");
                            printTree(*raizAVL, 0);
                            printf("\n\n");

                            pause();

                            break;

                        case 3:
                            break;

                        default:
                            printf("Opcao invalida!!!\n");
                            pause();
                    }

                    limparTela();

                } while (opcaoCase5 != 3);

                break;

            case 5:

                imprimirDadosArv(gerenAnalise.analise[gerenAnalise.quantAnalise - 1]);
                pause();

                break;

            case 6:

                if (gerenAnalise.analise[gerenAnalise.quantAnalise - 1].quantDadosAVL == 0) {
                    printf("Nao ha dados a serem gravados!!!\n");
                    pause();
                    break;
                }

                gravarDadosArquivoTxt(gerenAnalise.analise[gerenAnalise.quantAnalise - 1], gerenAnalise.data[gerenAnalise.quantAnalise - 1]);
                pause();

                break;

            case 7:
                break;

            default:
                printf("Opcao invalida!!!\n");
                pause();
        }

        limparTela();

    } while (opcao != 7);

    //gravarDadosArquivoAnalise(&gerenAnalise);

    liberaAVL(raizAVL);
    free(vetor);

    printf("\n");
    //getchar();
    //system("pause");
    return (EXIT_SUCCESS);
}

void menu() {
    printf("1_Gerenciamento de chaves\n");
    printf("2_Inserir chaves\n");
    printf("3_Remover chaves\n");
    printf("4_Imprimir Arvore\n");
    printf("5_Imprimir dados de analise\n");
    printf("6_Gravar Dados Analise em arquivo txt\n");
    printf("7_Sair\n: ");
}

void menuArv() {
    printf("1_Imprimir Arvore -> AVL\n");
    printf("2_Imprimir Arvore -> Red Black\n");
    printf("3_Sair\n: ");
}

void menuGerenciamentoChaves() {
    printf("1_Sortear chaves\n");
    printf("2_Gravar chaves em arquivo txt\n");
    //printf("3_Gravar chaves em arquivo binario\n");
    printf("3_Ler chaves em arquivo txt\n");
    //printf("4_Ler chaves em arquivo binario (ira ler todas as chaves do arquivo)\n");
    printf("4_Imprimir chaves\n");
    printf("5_Sair\n: ");
}

void newGerenAnalise(GerenAnalise* gerenAnalise) {

    gerenAnalise->data = (Data*) malloc(sizeof (Data));
    gerenAnalise->data->dia = getDia();
    gerenAnalise->data->mes = getMes();
    gerenAnalise->data->ano = getAno();
    gerenAnalise->quantAnalise = 1;

    gerenAnalise->analise = (Analise*) malloc(sizeof (Analise));
    gerenAnalise->analise->dadosAVL = NULL;
    gerenAnalise->analise->dadosRB = NULL;
    gerenAnalise->analise->quantDadosAVL = 0;
    gerenAnalise->analise->quantDadosRB = 0;

}

void addDadosArv(GerenAnalise* gerenAnalise, char* nomeArv, char* operacao,
        int quantChaves, int quantRotacoes, int altura, float time) {

    /*
    int dia = gerenAnalise->data[gerenAnalise->quantAnalise - 1] . dia;
    int mes = gerenAnalise->data[gerenAnalise->quantAnalise - 1] . mes;
    int ano = gerenAnalise->data[gerenAnalise->quantAnalise - 1] . ano;

    int diaAtual = getDia();
    int mesAtual = getMes();
    int anoAtual = getAno();

    if (dia != diaAtual || mes != mesAtual || ano != anoAtual) {
        gerenAnalise->quantAnalise++;
        gerenAnalise->analise = (Analise*) realloc(gerenAnalise->analise, sizeof (Analise) * gerenAnalise->quantAnalise);

        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosAVL = 0;
        //gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosRB = 0;

        gerenAnalise->data[gerenAnalise->quantAnalise - 1] . dia = getDia();
        gerenAnalise->data[gerenAnalise->quantAnalise - 1] . mes = getMes();
        gerenAnalise->data[gerenAnalise->quantAnalise - 1] . ano = getAno();
    }
     */
    gerenAnalise->analise[gerenAnalise->quantAnalise - 1] . quantDadosAVL++;

    gerenAnalise->analise[gerenAnalise->quantAnalise - 1] . dadosAVL =
            (DADOS*) realloc(gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosAVL,
            sizeof (DADOS) * gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosAVL);

    /*
    
    gerenAnalise->analise[gerenAnalise->quantAnalise - 1] . quantDadosRB++; 
      
    gerenAnalise->analise[gerenAnalise->quantAnalise - 1] . dadosRB =
            (DADOS*) realloc(gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosRB,
            sizeof (DADOS) * gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosRB);
     */
    if (strcmp(nomeArv, arvAVL) == 0) {
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosAVL [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosAVL - 1] . nomeArv = nomeArv;
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosAVL [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosAVL - 1] . tipoOperacao = operacao;
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosAVL [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosAVL - 1] . numChaves = quantChaves;
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosAVL [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosAVL - 1] . rotacoes = quantRotacoes;
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosAVL [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosAVL - 1] . altura = altura;
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosAVL [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosAVL - 1] . secondsTime = time;
    }/* else if (strcmp(nomeArv, arvRB) == 0) {
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosRB [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosRB - 1] . nomeArv = nomeArv;
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosRB [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosRB - 1] . tipoOperacao = operacao;
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosRB [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosRB - 1] . numChaves = quantChaves;
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosRB [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosRB - 1] . rotacoes = quantRotacoes;
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosRB [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosRB - 1] . altura = altura;
        gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . dadosRB [gerenAnalise->analise [gerenAnalise->quantAnalise - 1] . quantDadosRB - 1] . secondsTime = time;
    }*/
}

bool criarArquivoAnalise() {
    FILE* arquivo = fopen("analise.bin", "wb");

    if (arquivo == NULL)
        return false;

    fclose(arquivo);

    return true;
}

void gravarDadosArquivoTxt(Analise analise, Data data) {
    int i;

    FILE* arquivo = fopen("DadosAnalise.txt", "a");

    if (arquivo == NULL) {
        arquivo = fopen("DadosAnalise.txt", "w");

        if (arquivo == NULL) {
            printf("Falha na abertura do arquivo!!!\n");
            return;
        }
    }

    fprintf(arquivo, "Data: %d / %d / %d\n", data.dia, data.mes, data.ano);

    for (i = 0; i < analise.quantDadosAVL; i++) {
        fprintf(arquivo, "\nArvore: %s\n", analise.dadosAVL[i].nomeArv);
        fprintf(arquivo, "Tipo da operacao: %s\n", analise.dadosAVL[i].tipoOperacao);
        fprintf(arquivo, "Quantidade de Chaves: %d\n", analise.dadosAVL[i].numChaves);
        fprintf(arquivo, "Quantidade de rotacoes: %d\n", analise.dadosAVL[i].rotacoes);
        fprintf(arquivo, "Altura: %d\n", analise.dadosAVL[i].altura);
        fprintf(arquivo, "Tempo em Segundos: %f\n", analise.dadosAVL[i].secondsTime);
    }

    fprintf(arquivo, "\n");

    printf("Arquivo de texto gerado com sucesso!!!\n");

    fclose(arquivo);
}

void pause() {
#ifdef _linux_
    getchar();
    //printf("Sistema Operacional: LINUX\n");
#endif

#ifdef _WIN32
    system("pause");
    //printf("Sistema Operacional: WINDOWS\n");
#endif
}

void imprimirDadosArv(Analise analise) {
    int i;

    if (analise.quantDadosAVL == 0) {
        printf("Nao ha dados!!!\n");
        return;
    }

    for (i = 0; i < analise.quantDadosAVL; i++) {
        printf("%s\n", analise.dadosAVL[i].nomeArv);
        printf("Tipo de Operacao: %s\n", analise.dadosAVL[i].tipoOperacao);
        printf("Numero de chaves: %d\n", analise.dadosAVL[i].numChaves);
        printf("Rotacoes: %d\n", analise.dadosAVL[i].rotacoes);
        printf("Altura: %d\n", analise.dadosAVL[i].altura);
        printf("Tempo em segundos: %f\n\n", analise.dadosAVL[i].secondsTime);

        /*
        printf("%s\n",analise.dadosRB[i].nomeArv);
        printf("Tipo de Operacao: %s\n",analise.dadosRB[i].tipoOperacao);
        printf("Numero de chaves: %d\n",analise.dadosRB[i].numChaves);
        printf("Rotacoes: %d\n",analise.dadosRB[i].rotacoes);
        printf("Tempo em segundos: %f\n\n",analise.dadosRB[i].secondsTime);
         */
    }
}

bool gravarDadosArquivoAnalise(GerenAnalise* gerenAnalise) {

    if (gerenAnalise->analise[gerenAnalise->quantAnalise - 1] . quantDadosAVL == 0) {
        printf("Nao ha dados ha serem gravados!!!\n");
        return false;
    }

    FILE* arquivo = fopen("analise.bin", "wb");

    if (fwrite(&gerenAnalise, sizeof (GerenAnalise), 1, arquivo) != 1) {
        printf("Falha ao gravar os dados no arquivo!!!\n");
        pause();
        return false;
    }

    fclose(arquivo);

    return true;
}

bool lerDadosArquivoAnalise(GerenAnalise* gerenAnalise) {
    FILE* arquivo = fopen("analise.bin", "rb");

    if (arquivo == NULL)
        return false;

    if (fread(gerenAnalise, sizeof (GerenAnalise), 1, arquivo) != 1) {
        printf("Arquivo de Analise Vazio!!!\n");
        pause();
    }

    fclose(arquivo);

    return true;
}

int getDia() {
    time(&Segundos); //obtém a hora em segundos.
    DataAtual = localtime(&Segundos); //converte horas em segundos.
    return (DataAtual->tm_mday); //retorna os dias de 1 a 31.
}

int getMes() {
    time(&Segundos); //obtém a hora em segundos.
    DataAtual = localtime(&Segundos); //converte horas em segundos.
    return (DataAtual->tm_mon + 1); //retorna os meses de 0 a 11.
}

int getAno() {
    time(&Segundos); //obtém a hora em segundos.
    DataAtual = localtime(&Segundos); //converte horas em segundos.
    return (DataAtual->tm_year + 1900); //retorna o ano atual.
}

void limparTela() {
#ifdef _linux_
    system("clear");
    //printf("Sistema Operacional: LINUX\n");
#endif

#ifdef _WIN32
    system("cls");
    //printf("Sistema Operacional: WINDOWS\n");
#endif
}