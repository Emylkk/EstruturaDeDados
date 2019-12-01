#include"agm.h"


E* criaElemento(char verticeID, LE *elmntIniL){
/*SE O PRIMEIRO ELEMENTO EXISTIR CHECA SE A LETRA INSERIDA JA EXISTE*/
    if(elmntIniL->primeiro){
        E* percorreElemento;
        percorreElemento=elmntIniL->primeiro;
        while(percorreElemento){
            if(percorreElemento->pontaID != verticeID){
                if(percorreElemento->proximo == NULL){
                    percorreElemento->proximo = elmntMemAlloc(verticeID);
                    return(percorreElemento->proximo);
                }
                percorreElemento = percorreElemento->proximo;
            }else{
                return(percorreElemento);
            }

        }
/*SE O PRIMEIRO ELEMENTO NAO EXISTIR, O CRIA*/
    }else{
        elmntIniL->primeiro = elmntMemAlloc(verticeID);
        return(elmntIniL->primeiro);
    }
}

C* percorrerListaDeCaminhos(LC* caminho){
    if(caminho->primeiro){
        C* percorreCaminho;
        percorreCaminho=caminho->primeiro;
        while(percorreCaminho){
             if(percorreCaminho->proximo == NULL){
                percorreCaminho->proximo = alocaMemCaminho();
                return(percorreCaminho->proximo);
            }
            percorreCaminho = percorreCaminho->proximo;
        }

    }else{

        caminho->primeiro = alocaMemCaminho();
        return(caminho->primeiro);
    }
}

void inserecaminho(char origem,char destino,int peso,LE *elmntIniL){
    E *o,*d;
    LC *lc1,*lc2;
    C *c1,*c2;
    o = criaElemento(origem,elmntIniL);
    d = criaElemento(destino,elmntIniL);
    lc1 = o->caminhos_disponiveis;
    lc2 = d->caminhos_disponiveis;
    c1 = percorrerListaDeCaminhos(lc1);
    c2 = percorrerListaDeCaminhos(lc2);
    c1->destino=d;
    c1->peso=peso;
    c2->reverso=c1;
    c2->destino=o;
    c2->peso=peso;
    c1->reverso=c2;
}

void guiainsercao(LE *eInicial){
    int p;
    char o,d;
    system("cls");
    printf("\n\t\tINSIRA OS VALORES: \n\n\nOrigem: ");
    fflush(stdin);
    scanf("%c",&o);
    CharUpper(&o);
    printf("%c",o);
    printf("\nDestino: ");
    fflush(stdin);
    scanf("%c",&d);
    CharUpper(&d);
    printf("%c",d);
    printf("\nPeso: ");
    scanf("%d",&p);
    if(o != '\n' && o != ' '&& d != '\n' && d != ' '){
        if(o!=d){
            inserecaminho(o,d,p,eInicial);
        }else{
            system("cls");
            system("color fc");
            printf("\n\n\n\t\t\tDESTINO E ORIGEM NAO DEVEM SER IGUAIS\n\n\n\n\n\n\n\n\n");
            system("pause");
            system("color 0f");
        }
    }else{
        system("cls");
        system("color fc");
        printf("\n\n\n\t\t\tNAO ACEITO CARACTERE VAZIO OU ESPACO\n\n\n\n\n\n\n\n\n");
        system("pause");
        system("color 0f");
    }
}

C* geradora_Minima(E *ref,E *e,E *pai){
    C *caminho,*menorCaminho,*comp;
    comp = NULL;
    char orig =NULL;
    menorCaminho = NULL;
    caminho= e->caminhos_disponiveis->primeiro;

    while(caminho){
        if(caminho->status == 1 && caminho->destino->caminhos_disponiveis->primeiro->proximo != NULL && caminho->destino != pai){
            comp = geradora_Minima(ref, caminho->destino, e);
            if(comp != NULL){
               if(menorCaminho){
                    if(comp->peso < menorCaminho->peso){
                        menorCaminho = comp;
                        orig= caminho->destino->pontaID;
                    }
               }else{
               menorCaminho = comp;
               orig= caminho->destino->pontaID;
               }
            }
        }
        if(caminho->destino->pai == e->pai && caminho->status < 0){

            caminho->status == 0;

        }
        if(menorCaminho){
          if( (caminho->peso < menorCaminho->peso) && (caminho->status < 0) && (caminho->destino->pai != e->pai)){
            menorCaminho=caminho;
            orig =NULL;
          }
        }else if( caminho->status < 0  && (caminho->destino->pai != e->pai)) {

            menorCaminho = caminho;
            orig=NULL;
        }

        caminho = caminho->proximo;
    }
    if(ref == e){
        if(menorCaminho){
            if(menorCaminho->status != 0){
                menorCaminho->status = 1;
                menorCaminho->destino->pai = e->pai;
                if(menorCaminho->reverso->status)
                    menorCaminho->reverso->status = 1;

                if(orig){
                    printf("Origem: %c\t",orig);
                }else{
                    printf("\n\nOrigem: %c\t",e->pontaID);
                }
                printf("Peso %d\tDestino %c\n\n",menorCaminho->peso,menorCaminho->destino->pontaID);
                Sleep(1000);
            }
        }
    }
    return(menorCaminho);
}

void exibe(E *ini){
    C *way;
    while(ini){
        way = ini->caminhos_disponiveis->primeiro;
        printf("__________________________________________\nCaminhos do Vertice: %c\n",ini->pontaID);
        while(way){

            if(way->status ==1)
            printf("\tOrigem: %c  Destino %c  Peso: %d\n",ini->pontaID,way->destino->pontaID,way->peso);

            way= way->proximo;
        }
        ini=ini->proximo;
    }
    printf("\n\n\n");
    system("pause");
 }

int main(){
    system("mode con cols=100 lines=15");
    system("color f0");
    char op;
    C* gerando;
    LE *elementoInicial;
    elementoInicial= (LE*) malloc(sizeof(LE));
    elementoInicial->primeiro=NULL;
    while(GetAsyncKeyState(VK_ESCAPE) == 0){
        system("cls");
        listarElementos(elementoInicial->primeiro);
        listarPais(elementoInicial->primeiro);
        printf("\n\n\n\t\t\t1-Adicionar Caminho.\n\t\t\t2-Teste de Caminhos do Primeiro Elemento.\n\t\t\t3-Gerar Arvore Mínima\n\t\t\t4-Exibir Arvore Geradora Minima");
        op = getch();
        fflush(stdin);
        switch(op){
            case'1':
                guiainsercao(elementoInicial);
            break;

            case'2':
                listarcaminhos(elementoInicial->primeiro);
            break;

            case'3':
                do{
                    gerando = geradora_Minima(elementoInicial->primeiro, elementoInicial->primeiro, NULL);
                }while(gerando!=NULL);
                system("CLS");
                printf("\n\n\n\t\t\tArvore Minima Gerada Com Sucesso");
                system("color 0a");
                Sleep(2000);
                system("color f0");
            break;

            case'4':
                system("mode con cols=100 lines=400");
                exibe(elementoInicial->primeiro);
            break;
        }
    }
}
