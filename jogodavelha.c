#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.c>

//123	159	258
//456	357	369
//789	147

int mat[9][2] = {{11,2},{14,2},{17,2},{11,4},{14,4},{17,4},{11,6},{14,6},{17,6}};

int possibilidades[8][3] = {{1,2,3},{4,5,6},{7,8,9},{1,5,9},{3,5,7},{1,4,7},{2,5,8},{3,6,9}};

bool jogadasPlayer1[10] = {false,false,false,false,false,false,false,false,false,false};
bool jogadasPlayer2[10] = {false,false,false,false,false,false,false,false,false,false};

bool jogadas[10] = {false,false,false,false,false,false,false,false,false,false};
bool vencedor = false;
int prox = 1;

void inicializaVariaveis(){
    int i;
    for(i=0;i<10;i++){
        jogadasPlayer1[i] = false;
        jogadasPlayer2[i] = false;
        jogadas[i] = false;
    }
}
void imprimeJogo(){
    clrscr();
    textcolor(WHITE);
    int i,j,k;
    for(i=3;i<=5;i+=2){
        for(j=10;j<=16;j+=3){
            gotoxy(j,i);
            printf("--");
        }
        for(k=12;k<=15;k+=3){
            gotoxy(k,i);
            printf("|");
            gotoxy(k,i-1);
            printf("|");
            gotoxy(k,i+1);
            printf("|");
            //gotoxy(k,i+2);
            //printf("|");
        }
    }
    int n = 1;

    for(i=2;i<=6;i+=2){
        for(j=11;j<=17;j+=3){
            gotoxy(j,i);
            printf("%d",n);
            n++;
        }
    }
    inicializaVariaveis();
}
void log(){

    gotoxy(40,3);
    textcolor(RED);
    printf("Restam: %d jogadas       ",jogadasRestantes());
    textcolor(WHITE);
}

int verificaJogo(){

    int i;
    for(i=0;i<8;i++){
        if((jogadasPlayer1[possibilidades[i][0]] == true) &&(jogadasPlayer1[possibilidades[i][1]]==true) && (jogadasPlayer1[possibilidades[i][2]] == true) ){
            return 1;
        }
        if((jogadasPlayer2[possibilidades[i][0]] == true) &&(jogadasPlayer2[possibilidades[i][1]]==true) && (jogadasPlayer2[possibilidades[i][2]] == true) ){
            return 2;
        }
    }
    return 0;
}
int jogadasRestantes(){
    int i,j=0;
    for(i=0;i<10;i++){
        if(jogadas[i] == false){
            j++;
        }
    }
    return j-1;
}
int Jogo(){
    imprimeJogo();
    while(!vencedor){

        int jogada = 0;
        log();
        gotoxy(20,20);
        printf("Vez do Player %d",prox);
        gotoxy(20,21);
        printf("Faca sua jogada: ");
        scanf("%d",&jogada);
        jogada = jogada % 10;
        if(!jogadas[jogada] && jogada != 0){
            gotoxy(mat[jogada-1][0],mat[jogada-1][1]);
            if(prox == 1){
                printf("X");
                jogadasPlayer1[jogada] = true;
                prox = 2;
            }else if(prox == 2){
                printf("O");
                jogadasPlayer2[jogada] = true;
                prox = 1;
            }

            jogadas[jogada] = true;
        }else{
            gotoxy(30,10);
            textcolor(RED);
            printf("Opss, alguem já jogou ai! Tente novamente!");
            textcolor(WHITE);
            _sleep(2000);
            gotoxy(30,10);
            printf("                                                          ");
            continue;
        }
        switch(verificaJogo()){
        case 1:
            gotoxy(30,10);
            textcolor(GREEN);
            printf("Player 1 Ganhou!!!");
            textcolor(WHITE);
            vencedor = true;
            break;
        case 2:
            gotoxy(30,10);
            textcolor(GREEN);
            printf("Player 2 Ganhou!!!");
            textcolor(WHITE);
            vencedor = true;
            break;
        case 0:
            if(jogadasRestantes() <= 0){
                gotoxy(30,10);
                textcolor(GREEN);
                printf("O jogo deu velha!!!");
                textcolor(WHITE);
                vencedor = true;
            }
            break;
        }
        if(vencedor){
            gotoxy(30,5);
            printf("Jogar outra vez?[S/N]");
            char c = getch();
            if(c == 's'){
                vencedor = false;
                imprimeJogo();
                prox = 1;
            }else{
                return 0;
            }
        }
    }
    return 0;
}

int main(){

    Jogo();
    return 0;
}
