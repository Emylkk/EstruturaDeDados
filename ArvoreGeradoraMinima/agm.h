#ifndef _AGM_H_
#define  _AGM_H_

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<strings.h>
/*arestas = segmento,caminho ou linha*/
/*vertices = pontas ou elementos*/

/*ARESTA*/
    typedef struct Caminho{
        int status;
        int peso;
        struct elemento *destino;
        struct Caminho *proximo;
        struct Caminho *reverso;
    }C;

/*LISTA DE ARESTAS DE UM ELEMENTO*/
    typedef struct ListaDeCaminhos{
        C *primeiro;
    }LC;

/*VERTICES OU PONTAS*/
    typedef struct elemento{
         struct elemento *proximo;
         char pontaID;
         char *pai;
         LC* caminhos_disponiveis;
    }E;
/*LISTA DE ARESTAS DE UM ELEMENTO*/
    typedef struct ListaDeElementos{
        E *primeiro;
    }LE;


/*ALOCA MEMORIA PRA UMA LISTA  DE VERTICES*/
    LC* listMemAlloc(){
        LC *lista;
        lista = (LC*) malloc(sizeof(LC));
        lista->primeiro=NULL;
        return(lista);
    }

/*ALOCA MEMORIA PRA UMA LISTA  DE ARESTAS*/
    C*  alocaMemCaminho(){
        C *caminho;
        caminho = (C*) malloc(sizeof(C));
        caminho->destino=NULL;
        caminho->peso=NULL;
        caminho->status=-1;
        caminho->proximo=NULL;
        caminho->reverso=NULL;
        return(caminho);
    }
/*ALOCA MEMORIA PARA UM ELEMENTO*/
    E* elmntMemAlloc(char verticeID){
        E* novoElemento;
        novoElemento = (E*) malloc(sizeof(E));
        novoElemento->pontaID = verticeID;
        novoElemento->pai = novoElemento->pontaID;
        novoElemento->proximo = NULL;
        novoElemento->caminhos_disponiveis = listMemAlloc();
        return(novoElemento);
    }
    void listarElementos(E *ini){
        printf("\nElementos: \n");
        while(ini){
            printf("%c",ini->pontaID);
            ini = ini->proximo;
        }
    }
    void listarPais(E *ini){
        printf("\nPais: \n");
        while(ini){
            printf("%c",ini->pai);
            ini = ini->proximo;
        }
    }
    void listarcaminhos(E *ini){
        C *c;
        char nome_Destino;
        c = ini->caminhos_disponiveis->primeiro;
        printf("Caminhos do elemento %c",ini->pontaID);
        while(c){
            printf("\nPeso: %d",c->peso);
            printf("\t\tDestino: %c\n",c->destino->pontaID);
            c=c->proximo;
        }
        system("pause");
    }
    C* geradora_Minima_Filhos(E *e){
        C *caminho,*menorCaminho,*comp;
        comp = NULL;
        menorCaminho = NULL;
        caminho= e->caminhos_disponiveis->primeiro;

        while(caminho){
            if(caminho->status == 1 && caminho->destino->caminhos_disponiveis->primeiro->proximo != NULL){
                comp = geradora_Minima_Filhos(caminho->destino);
                if(comp != NULL) {
                    if(menorCaminho){
                        if(comp->peso < menorCaminho->peso){
                            menorCaminho = comp;
                        }
                    }

                }
            }
            if(caminho->destino->pai == e->pai && caminho->status < 0){

                caminho->status == 0;

            }
            if(menorCaminho){
              if( (caminho->peso < menorCaminho->peso) && (caminho->status < 0) && (caminho->destino->pai != e->pai)){
                menorCaminho=caminho;
              }
            }else if( caminho->status < 0  && (caminho->destino->pai != e->pai)) {

                menorCaminho = caminho;
            }

            caminho = caminho->proximo;
        }

        return(menorCaminho);
    }
#endif
