/* 
 * File:   sortNum.h
 * Author: Romário Fernando
 *
 * Created on 19 de Julho de 2016, 17:38
 */

#ifndef SORTNUM_H
#define SORTNUM_H

struct vet{
    int* vetor;
    int tam;
};
typedef struct vet VET;

void sortearNum(int**, int);
void gerarMatrizArquivoTxt(int*, int);
void gerarVetorArquivoBin(struct vet);
void lerVetorArquivoTxt(int**, int*);
void lerVetorArquivoBin(struct vet*);
void imprimirVetorMatriz(int*, int);

#endif /* SORTNUM_H */

