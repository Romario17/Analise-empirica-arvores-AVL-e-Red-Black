/* 
 * File:   ArvoreLLRB.h
 * Author: Romário Fernando
 *
 * Created on 24 de Julho de 2016, 07:13
 */

#ifndef ARVORELLRB1_H
#define ARVORELLRB1_H

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct NO* ArvLLRB;

    // ABB RUBRO NEGRO 2-3
    ArvLLRB* cria_ArvLLRB();
    void libera_ArvLLRB(ArvLLRB* raiz);
    int insere_ArvLLRB(ArvLLRB* raiz, int valor);
    int remove_ArvLLRB(ArvLLRB *raiz, int valor);
    int estaVazia_ArvLLRB(ArvLLRB *raiz);
    int totalNO_ArvLLRB(ArvLLRB *raiz);
    int altura_ArvLLRB(ArvLLRB *raiz);
    int consulta_ArvLLRB(ArvLLRB *raiz, int valor);
    void preOrdem_ArvLLRB(ArvLLRB *raiz, int H);
    void emOrdem_ArvLLRB(ArvLLRB *raiz, int H);
    void posOrdem_ArvLLRB(ArvLLRB *raiz, int H);

#ifdef __cplusplus
}
#endif

#endif /* ARVORELLRB_H */

