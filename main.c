#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

int giocatore, movx, movy, gameover, zeri, campo[7][7], chiudi=0;
enum direzione{STOP, SIN, DES, SU, GIU, SPAZIO};
direzione dir;


void start(){

    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
               campo[i][j]=0;
        }
    }

    movx=3;
    movy=3;
    giocatore=1;
    gameover=0;
    dir=STOP;

}

void disegna(){

    Sleep(100);

    system("cls");

    cout << "                                       TrisEVO" << endl << endl;

    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(j==0)
                cout << "                                       ";

            if((i%2==0 && j%2==0) || (i%2==0 && j%2!=0) || (i%2!=0 && j%2==0)){
                cout << "+";
                if(j==6)
                    cout << endl;
                }
            else{
                if((i==movy && j==movx)){
                    if(giocatore==1)
                        cout << "1";
                    else
                        cout << "2";
                }
                else if(campo[i][j]==1)
                        cout << "X";
                else if(campo[i][j]==2)
                        cout << "O";
                else
                cout << " ";
            }

        }

    }


    cout << endl;
    cout << "                     Usa i comandi WASD per muovere il cursore" << endl;
    cout << "                e spazio per inserire una pedina nello spazio vuoto." << endl;

}

void comandi(){

    dir=STOP;

    if(_kbhit()){
        switch(_getch()){
            case 'a':
                dir=SIN;
            break;

            case 'd':
                dir=DES;
            break;

            case 'w':
                dir=SU;
            break;

            case 's':
                dir=GIU;
            break;

            case ' ':
                dir=SPAZIO;
            break;

            case 'l':
                gameover=true;
            break;

            default:
            break;
        }
    }
}

void logica(){

    switch(dir){
        case SIN:
            if(movx-2>0)
                movx-=2;
        break;

        case DES:
            if(movx+2<6)
                movx+=2;
        break;

        case SU:
            if(movy-2>0)
                movy-=2;
        break;

        case GIU:
            if(movy+2<6)
                movy+=2;
        break;

        case SPAZIO:
            if(campo[movy][movx]==0){
                if(giocatore==1){
                    campo[movy][movx]=1;
                    giocatore=2;
                }
                else{
                    campo[movy][movx]=2;
                    giocatore=1;
                }
            }
        break;

        default:
        break;
    }

}

void vittoria(){

    zeri=49;

    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            if(campo[i][j]!=0)
                zeri--;
        }
    }

    for(int i=1; i<6; i++){
        for(int j=1; j<6; j++){
            if(i%2!=0 && j%2!=0){
                if((campo[i][j]==1 && campo[i+2][j]==1 && campo[i+4][j]==1) ||
                   (campo[i][j]==1 && campo[i][j+2]==1 && campo[i][j+4]==1) ||
                   (campo[i][j]==1 && campo[i+2][j+2]==1 && campo[i+4][j+4]==1) ||
                   (campo[i][j]==1 && campo[i+2][j-2]==1 && campo[i+4][j-4]==1)){
                    gameover=1;
                    cout << endl << "                               Vincitore: Giocatore 1." << endl << endl;
                }

                else if((campo[i][j]==2 && campo[i+2][j]==2 && campo[i+4][j]==2) ||
                        (campo[i][j]==2 && campo[i][j+2]==2 && campo[i][j+4]==2) ||
                        (campo[i][j]==2 && campo[i+2][j+2]==2 && campo[i+4][j+4]==2) ||
                        (campo[i][j]==2 && campo[i+2][j-2]==2 && campo[i+4][j-4]==2)){
                    gameover=2;
                    cout << endl << "                               Vincitore: Giocatore 2." << endl << endl;
                }
            }
        }
    }

    if(zeri==40 && gameover==0){
        gameover=3;
        cout << endl << "                                   Nessun vincitore." << endl << endl;
    }

    if(gameover!=0){
        cout << "Premi Y per iniziare una nuova partita o un tasto qualunque per uscire dal programma. ";
        switch(_getch()){
            case 'y':
                gameover=0;
                start();
            break;

            default:

            break;
        }
    }
}



int main(){

    start();

    while(gameover==0){

        disegna();
        comandi();
        logica();
        vittoria();

        /*cout << endl;
        for(int i=0; i<7; i++){
            for(int j=0; j<7; j++){
                cout << campo[i][j];
                if(j==6)
                cout << endl;
            }
        }*/
    }
    return 0;
}
