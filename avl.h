/* 
 * File:   avl.h
 * Author: Romário Fernando
 *
 * Created on 19 de Julho de 2016, 21:55
 */

#ifndef AVL_H
#define AVL_H

typedef struct No No;
typedef struct No* AVL;

//typedef struct{
    int rotacoesAVL;
//}AvlQuantRot;

//AvlQuantRot quant;

//int maior(int x, int y);

//No* novoNo(int chave);

int alturaNo(No* no);

//int fatorBalanceamento(No* no);

//void RotacaoLL(AVL *A);

//void RotacaoRR(AVL *A);

//void RotacaoLR(AVL *A);

//void RotacaoRL(AVL *A);

void inserirNoAVL(AVL* r, int chave);

//No* procuraMenor(No* atual);

void removerNoAVL(AVL* r, int chave);

int consultaAVL(AVL raiz, int chave);

void printTree(AVL raiz, int h);

void emOrdem_ArvAVL(AVL *raiz);

//void libera_NO(No* no);

void liberaAVL(AVL* raiz);

#endif /* AVL_H */