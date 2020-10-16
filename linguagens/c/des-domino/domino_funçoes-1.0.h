#include <stdio.h>
#include <stdlib.h>

#define TAMAX 28

typedef struct domino* DOMPTR;

struct domino{
    int esquerda, direita, indice;
    DOMPTR prev;
    DOMPTR next;
} EXEMPLO;

//------------------------------    protótipos    -----------------------------------------------------------------------------------------

DOMPTR returnNULL();
void criarCaixa(DOMPTR *caixa);
void embaralhaCarta(DOMPTR *box);
void darAsCartas(DOMPTR *box ,DOMPTR *user1, DOMPTR *user2);
void imprimePagIni();
int imprimeMenu();
DOMPTR getPecaLista(DOMPTR point, int id);
int turnos(DOMPTR *user1, DOMPTR *user2, int FaceTail, DOMPTR *table, int *desistencia);
int checkIfPecaExiste(DOMPTR user, int id);
int checkWin(DOMPTR user1, DOMPTR user2, int vencedor);
void insereLista(int esq, int dir, int ind, DOMPTR *point);
void imprimeLista(DOMPTR point);
struct domino removePecaLista(DOMPTR *point, int id);
void imprimeTabuleiro(DOMPTR point);
int insereTop(int esq, int dir, DOMPTR *point);
int insereBottom(int esq, int dir, DOMPTR *point);

//------------------------------    funcoes do jogo    -----------------------------------------------------------------------------------------

DOMPTR returnNULL(){
	return NULL;
}

void criarCaixa(DOMPTR *caixa){
    int cont=0;
    for(int i=0; i<=6; i++)
		for(int j=i; j<=6; j++){
            insereLista(i, j, cont, &(*caixa));
			cont++;
		}
    return;
}

void embaralhaCarta(DOMPTR *box){
    DOMPTR busca = NULL;
    DOMPTR embaralhada = NULL;
    int n=TAMAX;
    while(n>0){
        busca = *box;
        int alvo = rand()%n, i=0;
        while((busca != NULL) && (i < alvo)){
            busca = busca->next;
            i++;
        }
        struct domino removido = removePecaLista(box, busca->indice);
        if(rand()%2){
            int aux=removido.direita;
            removido.direita=removido.esquerda;
            removido.esquerda=aux;
        }
        insereLista(removido.esquerda, removido.direita, removido.indice, &embaralhada);
        n--;
    }
    *box=embaralhada;
}

void darAsCartas(DOMPTR *box ,DOMPTR *user1, DOMPTR *user2){
    DOMPTR caixa= *box;
    struct domino removido1;
    struct domino removido2;
    int i=0;
    for(; i < TAMAX; i++){
        if(i%2==0){
            removido1 = removePecaLista(box, (*box)->indice);
            insereLista(removido1.esquerda, removido1.direita, removido1.indice, user1);
        }
        else {
            removido2 = removePecaLista(box, (*box)->indice);
            insereLista(removido2.esquerda, removido2.direita, removido2.indice, user2);
        }
    }
    return;
}

void imprimePagIni(){
    printf("|-----------------------------------------|\n");
    printf("|                                         |\n");
    printf("|                 DESDOMINÓ               |\n");
    printf("|                                         |\n");
    printf("|-----------------------------------------|\n");
    printf("\n\n");
    printf("Bem vindo ao jogo de DESdominó.\n");
    printf("Uma moeda decidirá qual jogador \n");
    printf("começará primeiro.\n\n");

    printf("Esse jogo foi feito para ser\n");
    printf("jogado com a janela maximizada, e\n");
    printf("alguns itens da tela podem não ser\n");
    printf("exibidos de maneira ideal, se não for.\n\n");

    printf("Para a introdução de um desafio maior\n");
    printf("as peças devem ser rotacionadas manualmente\n");
    printf("e custarão um turno para o jogador\n\n" );

    printf("pense bem antes de desistir,\n");
    printf("uma desistencia não intencional\n");
    printf("causa uma perda de turno para o jogador.\n\n");

    system("pause");
    system("cls");
}

int imprimeMenu(){
    int choice=0;
    do{
    printf("1 - Inserir uma peça no tabuleiro.\n");
    printf("2 - Rotacionar uma peça na sua mão.\n");
    printf("3 - Desistir.\n");
    printf("Qual o seu proximo movimento:");
    scanf("%d", &choice);
    printf("\n\n");
    }while(choice != 1 && choice != 2 && choice != 3);
    return(choice);
}

DOMPTR getPecaLista(DOMPTR point, int id){
    DOMPTR busca = point;
    while (busca->indice != id && busca != NULL )
        busca=busca->next;
    return(busca);
}

int turnos(DOMPTR *user1, DOMPTR *user2, int faceTail, DOMPTR *table, int *desistencia){
    int escolha1, escolha2=-1, peca= -1, is_valid_play = 0;
    DOMPTR currentUser = NULL;
    DOMPTR temporario;
    printf("JOGADOR %d ESCOLHA SUA AÇÃO\n", faceTail+1);
    if(faceTail)currentUser = *user2; else currentUser = *user1;
    imprimeLista(currentUser);
    escolha1=imprimeMenu();
    int giveup;
    switch(escolha1){
        case 1:
            do {
                do{
                    printf("\n\nQual peça deseja colocar? ");
                    scanf("%d", &peca);
                    if(!checkIfPecaExiste(currentUser, peca))
                        printf("PEÇA NÃO ENCONTRADA, TENTE NOVAMENTE!!!\n");
                } while(!checkIfPecaExiste(currentUser, peca));
                temporario = getPecaLista(currentUser, peca);
                do{
                    printf("\nEm qual extremidade deseja colocar sua peça? esquerda=0 direita=1 :");
                    scanf("%d", &escolha2);
                } while((escolha2 !=0)&&(escolha2 != 1));
                if(escolha2)
                    is_valid_play = insereTop(temporario->esquerda, temporario->direita, table);
                else
                    is_valid_play = insereBottom(temporario->esquerda, temporario->direita, table);
                if (!is_valid_play) {
                    printf("Essa peça não pode ser colocada nesta posição. Refaça sua jogada.\n");
                } else if(faceTail)
                    removePecaLista(&(*user2), peca);
                else removePecaLista(&(*user1), peca);
            } while (!is_valid_play);
        break;
        case 2:
            do{
                printf("\n\nQual peça deseja rotacionar? ");
                scanf("%d", &peca);
                if(!checkIfPecaExiste(currentUser, peca))
                    printf("PEÇA NÃO ENCONTRADA, TENTE NOVAMENTE!!!\n");
            } while(!checkIfPecaExiste(currentUser, peca));
            temporario = getPecaLista(currentUser, peca);
            int aux;
            aux = temporario->esquerda;
            temporario->esquerda = temporario->direita;
            temporario->direita = aux;
            printf("A peça [%d|%d] foi rotacionada para [%d|%d].\n", temporario->direita, temporario->esquerda, temporario->esquerda, temporario->direita);
            break;
        case 3:
            do {
            printf("tem certeza que deseja desistir? S=1 N=0\n");
            scanf("%d", &giveup);
            }  while((giveup !=0)&&(giveup != 1));
            *desistencia=giveup;
        break;
    }
    system("pause");
    system("cls");
    if(faceTail)return(0); else return(1);
}

int checkIfPecaExiste(DOMPTR user, int id){
    DOMPTR busca = user;
    if(busca->indice == id)
            return(1);
    while( busca->next != NULL && busca->indice != id ){
        busca = busca->next;
        if(busca->indice == id)
            return(1);
    }
    return(0);
}

int checkWin(DOMPTR user1, DOMPTR user2, int vencedor){
    if(user1 == NULL)
        return(1);
    if(user2 == NULL)
        return(2);
    else return(0);
}

//------------------------------    funcoes de lista    -----------------------------------------------------------------------------------------

void insereLista(int esq, int dir, int ind, DOMPTR *point){
    DOMPTR ptr=(DOMPTR) malloc(sizeof(EXEMPLO));
    if (ptr == NULL){
        printf("Erro na alocacao de memoria");
        return;
    }

    ptr->esquerda = esq;
    ptr->direita = dir;
    ptr->indice = ind;
    ptr->prev=NULL;
    ptr->next=NULL;

    if(*point == NULL)
        *point=ptr;
    else{
        DOMPTR busca = *point;
        while(busca->next != NULL)
            busca=busca->next;
        ptr->prev=busca;
        busca->next=ptr;
    }
    return;
}

void imprimeLista(DOMPTR point){
    if(point == NULL){
        printf("\na lista não existe.\n");
        system("pause");
        system("cls");
        return;
    }
    DOMPTR busc = point;
    while (busc != NULL ){
        printf("peça numero %2d: ( %2d | %2d )\n", busc->indice, busc->esquerda, busc->direita);
        busc=busc->next;
    }
    printf("\n\n");
    return;
}

struct domino removePecaLista(DOMPTR *point, int id){
    DOMPTR busca = *point;
    while (busca->indice != id )
        busca=busca->next;
    if(busca->prev != NULL)
        busca->prev->next=busca->next;
    else *point=busca->next;
    if(busca->next != NULL)
        busca->next->prev=busca->prev;
    struct domino Domino_temp = *busca;
    free(busca);
    return(Domino_temp);
}

//------------------------------    funcoes de deque    -----------------------------------------------------------------------------------------

void imprimeTabuleiro(DOMPTR point){
    if(point == NULL){
        printf("\nO tabuleiro ainda não foi criado.\n");
        system("pause");
        system("cls");
        return;
    }
    DOMPTR busc = point;
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------\n\n");
    while (busc != NULL ){
        printf("[%d|%d]", busc->esquerda, busc->direita);
        busc=busc->next;
    }
    printf("\n\n----------------------------------------------------------------------------------------------------------------------------------");
    printf("\n\n");
    return;
}

int insereTop(int esq, int dir, DOMPTR *point){
    DOMPTR ptr=(DOMPTR) malloc(sizeof(EXEMPLO));
    if (ptr == NULL){
        printf("Erro na alocacao de memoria");
        return(0);
    }

    ptr->esquerda = esq;
    ptr->direita = dir;
    ptr->indice = 0;
    ptr->prev=NULL;
    ptr->next=NULL;

    if(*point == NULL)
        *point=ptr;
    else{
        DOMPTR busca = *point;
        while(busca->next != NULL)
            busca=busca->next;
        if(busca->direita == ptr->esquerda){
            ptr->prev=busca;
            busca->next=ptr;
        }
        else return(0);
    }
    return(1);
}

int insereBottom(int esq, int dir, DOMPTR *point){
    DOMPTR ptr=(DOMPTR) malloc(sizeof(EXEMPLO));
    if (ptr == NULL){
        printf("Erro na alocacao de memoria");
        return 0;
    }

    ptr->esquerda = esq;
    ptr->direita = dir;
    ptr->indice = 0;
    ptr->prev=NULL;
    ptr->next=NULL;

    if(*point == NULL)
        *point=ptr;
    else{
        DOMPTR busca = *point;
        if(busca->esquerda == ptr->direita){
            ptr->next = busca;
            busca->prev = ptr;
            *point = ptr;
        }
        else return(0);
    }
    return(1);
}
