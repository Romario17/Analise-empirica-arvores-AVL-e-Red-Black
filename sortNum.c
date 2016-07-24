#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "sortNum.h"

/**
 * Procedimento que sorteia números
 * em um intervalo, de forma que ele não se repita,
 * e atribui um vetor com os valores ao ponteiro.
 * 
 * @param &ponteiro 
 * @param tamanho do vetor
 */
void sortearNum(int** vetor, int tam){
    
    *vetor = (int*)realloc(*vetor ,sizeof(int)*tam);
    
    srand(time(NULL));
    int i;
    int cont;
    int indice;
    int* vetAux;
    int MAX; 
    
    do {
        printf("\nDigite o valor maximo de um elemento sorteado >= %d : ", tam);
	scanf("%d", &MAX);
    } while (MAX < tam);
    
    vetAux = (int*)malloc(sizeof(int)*MAX);
    for(i=0; i<MAX; i++){
        vetAux[i] = i+1;
    }
    printf("Gerando chaves...\n");
    cont = MAX;
    for (i = 0; i < tam; i++) {
        indice = rand()%cont;
        vetor[0][i] = vetAux[indice];
        vetAux[indice] = vetAux[cont-1];
        cont--;
    }
    free(vetAux);
    printf("Chaves Geradas com sucesso!!!\n");
}

/**
 * Procedimento que gera uma matriz
 * de números em um arquivo.txt a partir de um vetor.
 * 
 * @param vetor
 * @param tamanho do vetor
 */
void gerarMatrizArquivoTxt(int vetor[], int tam){
    FILE *numSort = fopen("numSort.txt" , "w");
    
    if (numSort == NULL) {
    	printf("Falha ao abrir o arquivo!!!\n");
    	exit(EXIT_FAILURE);
    }
    
    int i;
    int MaxCol = sqrt(tam) == (int)sqrt(tam) ? (int)sqrt(tam) : (int)sqrt(tam) +1;
    
    printf("Gerando Arquivo...\n");
    
    fprintf(numSort,"%d\n",tam);
    for (i = 0; i < tam; i++) {
        fprintf(numSort,"%d ",vetor[i]);
        if ((i%MaxCol) == 0 && i!=0)
            fprintf(numSort,"\n");
    }
    
    fclose(numSort);
    printf("Arquivo gerado com sucesso!!!\n");
}

/**
 * Procedimento que gera um vetor
 * de números em um arquivo.bin.
 * 
 * @param vetor
 * @param tamanho do vetor
 */
void gerarVetorArquivoBin(struct vet v){
    FILE *numSort = fopen("numSort.bin" , "wb");
    
    if (numSort == NULL) {
    	printf("Falha ao abrir o arquivo!!!\n");
    	exit(EXIT_FAILURE);
    }
    
    if (fwrite(&v, sizeof(VET), 1, numSort) != 1 ){
        printf ( "Erro de escrita no arquivo!!!\n" );
    }
    
    fclose(numSort);
    printf("Arquivo gerado com sucesso!!!\n");
}


/**
 * Procedimento que lê um arquivo txt
 * de N números, que foram inseridos no
 * arquivo pelo procedimento "gerarMatrizArquivoTxt"
 * e insere N números em um vetor e atribui o endereço
 * da primeira posição ao ponteiro.
 * 
 * @param &ponteiro
 * @param tamanho do vetor  
 */
void lerVetorArquivoTxt(int** vetor, int* tam){
    
    FILE* numSort = fopen("numSort.txt" , "r");
    
    if (numSort == NULL) {
    	printf("Falha ao abrir o arquivo!!!\n");
    	return;
    }
    
    int i;
    int MAX;
    
    fscanf(numSort, "%d", &MAX);
    if(*tam>MAX){
        *tam = MAX;
        printf("\nO tamanho do vetor foi reduzido para %d,\npois, nao ha elementos suficientes!!!\n",*tam);
    }
    
    *vetor = (int*)realloc(*vetor ,sizeof(int) * (*tam));
    
    printf("Lendo...\n");
    
    fscanf(numSort,"%d", &vetor[0][0]);
    for(i=1; i< *tam; i++)
        fscanf(numSort,"%d",&vetor[0][i]);
    
    fclose(numSort);
    printf("Leitura realizada com sucesso!!!\n");
}

/**
 * Procedimento que lê um arquivo binário
 * de N números, que foram inseridos no
 * arquivo pelo procedimento "gerarVetorArquivoBin"
 * e insere os números em um vetor de tamanho N.
 * 
 * @param vetor
 * @param tamanho do vetor  
 */
void lerVetorArquivoBin(struct vet* v){
    FILE* numSort = fopen("numSort.bin" , "rb");
    
    if (numSort == NULL) {
    	printf("Falha ao abrir o arquivo!!!\n");
    	exit(EXIT_FAILURE);
    }
    if(fread(&v, sizeof(VET), 1, numSort)!=1);
        printf("Falha na leitura!\n");
        
    fclose(numSort);
    printf("Leitura realizada com sucesso!!!\n");
}

/**
 * imprime um vetor em forma de matriz.
 * 
 * @param vetor
 * @param tamanho do vetor  
 */
void imprimirVetorMatriz(int vetor[], int tam){
    int i;
    int MaxCol = sqrt(tam) == (int)sqrt(tam) ? (int)sqrt(tam) : (int)sqrt(tam) +1;

    for(i=0;i<tam;i++){
        printf("%d ", vetor[i]);
        
        if(i%MaxCol == 0 && i!=0)
            printf("\n");
    }
}