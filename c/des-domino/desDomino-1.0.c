#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "domino_funçoes-1.0.h"

int main(){
    setlocale(LC_ALL,"portuguese");
    srand( (unsigned)time(NULL) );

    DOMPTR caixa=returnNULL();   //lista
    DOMPTR usuario1=returnNULL();//duplamente
    DOMPTR usuario2=returnNULL();//encadeada
	DOMPTR tabuleiro=returnNULL();          //deque

	int isWinner=0, moeda=rand()%2, escolha, aux=0;
	criarCaixa(&caixa);
    embaralhaCarta(&caixa);
    darAsCartas(&caixa, &usuario1, &usuario2);
    imprimePagIni();
    while(!isWinner){
        isWinner=checkWin(usuario1, usuario2, isWinner);

        if(aux)imprimeTabuleiro(tabuleiro);
        else aux=1;

        moeda=turnos(&usuario1, &usuario2, moeda, &tabuleiro, &isWinner);

	}
	printf("\n\no jogador %d é o vencedor\n\n", isWinner);


}
