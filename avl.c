#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

struct No {
    int chave;
    int altura;
    struct No* esq;
    struct No* dir;
};

int maior(int x, int y) {
    if (y > x)
        return y;

    return x;
}

No* novoNo(int chave) {
    No *r = (No*) malloc(sizeof (No));
    if (r != NULL) {
        r->altura = 0;
        r->chave = chave;
        r->dir = r->esq = NULL;
    }
    return r;
}

/** 
 *  Função que analisa a altura dos filhos de um nó.
 *  Se o nó for diferente de nulo a função retornará sua altura,
 *  senão retornará -1.
 */
int alturaNo(No* no) {
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

/**
 * Retorna o módulo da diferença de altura
 * entre dois nós. 
 */
int fatorBalanceamento(No* no) {
    return labs(alturaNo(no->esq) - alturaNo(no->dir));
}

/*.        
 *         _A  |      _B_
 *       _|    |    _|   |_
 *     _B      |  C         A
 *   _|        |
 * C           |
 */
void RotacaoLL(AVL *A) {
    //printf("RotacaoLL\n");
    No *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(alturaNo((*A)->esq), alturaNo((*A)->dir)) + 1;
    B->altura = maior(alturaNo(B->esq), (*A)->altura) + 1;
    *A = B;
    
    rotacoesAVL ++;
}

/* A _          |    _B_
 *    |_        |  _|   |_
 *      B_      | A       C
 *        |_    |
 *           C  | 
 */
void RotacaoRR(AVL *A) {
    //printf("RotacaoRR\n");
    No *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(alturaNo((*A)->esq), alturaNo((*A)->dir)) + 1;
    B->altura = maior(alturaNo(B->dir), (*A)->altura) + 1;
    (*A) = B;
    
    rotacoesAVL ++;
}

/*.
 *    _ A |         _ A  |     _C_      
 *  _|    |       _|     |   _|   |_ 
 * B_     |     _C       | B         A
 *   |_   |   _|         |
 *      C | B            | 
 */
void RotacaoLR(AVL *A) {
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

/* A _    | A _          |     _C_
 *    |_  |    |_        |   _|   |_
 *     _B |      C_      | A         B
 *   _|   |        |_    |
 * C      |           B  | 
 */
void RotacaoRL(AVL *A) {
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

void inserirNoAVL(AVL* r, int chave) {
    if (*r == NULL) {
        if ((*r = novoNo(chave)) == NULL) {
            printf("Memoria cheia!!!\n");
            return;
        }
    }
    else {
        if (chave > (*r)->chave)
            inserirNoAVL(&(*r)->dir, chave);

        else if (chave < (*r)->chave)
            inserirNoAVL(&(*r)->esq, chave);

        else if (chave == (*r)->chave){
            printf("Insercao de chave repetida nao autorizada!!!\n");
            return;
        }

        //Balanceando a AVL
        if (fatorBalanceamento(*r) >= 2) {

           /*        _ A
            *      _|  
            * chave   
            */
            if ((*r)->chave > chave) {

                /*            _ A
                 *          _|  
                 *        _B  
                 *      _|
                 * chave
                 */
                if (chave < (*r)->esq->chave) {
                    RotacaoLL(r);
                }

                /*    _ A
                 *  _|  
                 * B_  
                 *   |_ 
                 *     chave  
                 */
                else if (chave > (*r)->esq->chave) {
                    RotacaoLR(r);
                }
            }
        
            /* A _
             *    |_  
             *      chave   
             */
            else if ((*r)->chave < chave) {

                /* A _
                 *     |_
                 *       B_
                 *         |_
                 *           chave   
                 */
                if ((*r)->dir->chave < chave) {
                    RotacaoRR(r);
                }    
            
                /*    A _
                 *       |_
                 *        _B
                 *      _|
                 * chave   
                 */
                else if ((*r)->dir->chave > chave) {
                    RotacaoRL(r);
                }
            }
        }
        //Calculando altura do Nó
        (*r)->altura = maior(alturaNo((*r)->dir), alturaNo((*r)->esq)) + 1;
    }
}

/* Procura o nó de chave de menor valor
 * a partir da direita, descendo para esquerda até encontrar.
 * 
 *           A_
 *             |_
 *              _B
 *  procura..._|    
 */
No* procuraMenor(No* atual) {
    No* no1 = atual;
    No* no2 = atual->esq;

    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

void removerNoAVL(AVL* r, int chave) {
    if (*r == NULL) {
        printf("Chave nao encontrada ou Arvore Vazia!!!\n");
        return;
    }
    else {
        if (chave > (*r)->chave)
            removerNoAVL(&(*r)->dir, chave);

        else if (chave < (*r)->chave)
            removerNoAVL(&(*r)->esq, chave);

        else if (chave == (*r)->chave){
        
            //O Nó a ser removido possui somente um filho ou nenhum.
            if ((*r)->dir == NULL || (*r)->esq == NULL) {
                No* aux = (*r);

                if ((*r)->esq != NULL)
                   *r = (*r)->esq;
                else
                   *r = (*r)->dir;

                free(aux);
                
            //Se o Nó a ser removido possui dois filhos.    
            } else {
                No* menor = procuraMenor((*r)->dir);
                (*r)->chave = menor->chave;
                   
                /* Chamando novamente a si mesma, com a intenção de
                 * encontrar a chave de menor valor a partir do nó a direita,
                 * para que logo após possa subir a Árvore pelo caminho percorrido
                 * balanceando os nós. 
                 */ 
                removerNoAVL(&(*r)->dir, menor->chave);
            }
        }
        
        /* Na primeira vez que esta condição for verificada o nó em questão será nulo, se,
         * a proposição : "O Nó a ser removido possui somente um filho ou nenhum."
         * tiver sido verificada como verdadeira e o nó for uma folha, pois, o espaço de memória referente ao nó terá sido 
         * liberado, e logo após, será verificado esta condição para iniciar o balanceamento bottom-up. 
         */
        if(*r != NULL){
            //Calculando altura do No
            (*r)->altura = maior(alturaNo((*r)->dir), alturaNo((*r)->esq)) + 1;
            
            //Balanceando a AVL
            if (fatorBalanceamento(*r) >= 2) {
               
                /*     _ A
                 *   _|  
                 * B   
                 */
                if (alturaNo((*r)->esq) > alturaNo((*r)->dir)) {

                    /*         _ A
                     *       _|  
                     *     _B  
                     *   _|
                     * C 
                     */
                    if (alturaNo((*r)->esq->esq) >= alturaNo((*r)->esq->dir)) {
                        RotacaoLL(r);
                    } 
            
                    /*    _ A
                     *  _|  
                     * B_  
                     *   |_ 
                     *      C  
                     */
                    else if (alturaNo((*r)->esq->esq) < alturaNo((*r)->esq->dir)) {
                        RotacaoLR(r);
                    }
                }  
        
                /* A _
                 *    |_  
                 *      B   
                 */
                else if (alturaNo((*r)->dir) > alturaNo((*r)->esq)) {

                    /* A _
                     *    |_
                     *      B_
                     *        |_
                     *          C   
                     */
                    if (alturaNo((*r)->dir->dir) >= alturaNo((*r)->dir->esq)) {
                        RotacaoRR(r);
                    }               
            
                    /* A _
                     *    |_
                     *     _B
                     *   _|
                     * C   
                     */
                    else if (alturaNo((*r)->dir->dir) < alturaNo((*r)->dir->esq)) {
                        RotacaoRL(r);
                    }
                }
            }
        }    
    }
}

/* Consulta um elemento na árvore
 * 
 * @param ponteiro raiz
 * @param chave
 * @return true->(chave existe) false->(chave não existe) 
 */
int consultaAVL(AVL raiz, int chave){
    if(raiz == NULL)
        return 0;
    
    if(raiz != NULL){
        if(chave == raiz->chave){
            return 1;
        }
        if(chave > raiz->chave)
            consultaAVL(raiz->dir, chave);
        else
            consultaAVL(raiz->esq, chave);
    }
    return 0;
}

void printTree(AVL raiz, int h) {
    if (raiz != NULL) {
        printTree(raiz->dir, h + 1);
        printf("%*d\n", h * 5, raiz->chave);
        printTree(raiz->esq, h + 1);
    }
}

void emOrdem_ArvAVL(AVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->chave);
        printf("No %d: H(%d) fb(%d)\n",(*raiz)->chave, alturaNo(*raiz),fatorBalanceamento(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void libera_NO(No* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void liberaAVL(AVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}
