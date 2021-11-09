/**
 * @file main.c
 */

#include <stdio.h>
#include <stdbool.h>


/**
 * Creando variabili globali costanti che rappresentano il numero di colonne e righe, il valore
 * che ogni casella contiene, il giocatore, le pedine e le coordinate delle colonne
 */

const int rows=7;
const int cols=7;
const int vuoto=0;
const int player1=1;
const int player2=10;
int choice;
char col_coor[8]="abcdefg";

/**
 * La funzione posizionamento pedine serve a posizionare le pedine dei rispettivi giocatore
 * sulla scacchiera, assegnando ad ogni casella un valore specifico.
 */

/**
 *
 * @param board
 */

void posizionamento_pedine(int *board){
    int i,j;
    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            if(i==3){
                board[i*cols+j]=vuoto;
            }
            if(i>3){
                if((i*cols+j)%2==0){board[i*cols+j]=player1;}
                else board[i*cols+j]=vuoto;
            }
            if(i<3){
                if((i*cols+j)%2==0){board[i*cols+j]=player2;}
                else board[i*cols+j]=vuoto;
            }
        }
    }
}

/**
 * Dopo aver assegnato ad ogni casella un valore che rappresenta la pedina
 * la funzione stampa scacchiera assegna ad ogni valore una rappresentazione grafica
 * Ho aggiunto la variabile k che parte in modo decrescente rispetto alla i e rappresenta le coordinate delle righe
 * mentre per le coordinate delle colonne ho usato l'array globale e la variabile j
 */

/**
 *
 * @param board
 */

void stampa_scacchiera(int *board){
    int i,j,k=0;
    printf("  +---+---+---+---+---+---+---+\n");
    for(i=7;i>=1;i--){
        printf("%d |", i);
        for(j=0;j<cols;j++) {
            if(board[k*cols+j]==vuoto){
                printf("   |");}
            else if(board[k*cols+j]==player1){
                printf(" x |");}
            else if(board[k*cols+j]==player1*2){
                printf("x x|");}
            else if(board[k*cols+j]==player1*3){
                printf("xxx|");}
            else if(board[k*cols+j]==player2){
                printf(" o |");}
            else if(board[k*cols+j]==player2*2){
                printf("o o|");}
            else if(board[k*cols+j]==player2*3){
                printf("ooo|");}
        }
        k++;
        printf("\n");
        printf("  +---+---+---+---+---+---+---+\n");
    }
    printf("    %c",col_coor[0]);
    for(int l=1;l<cols;l++){
        printf("   %c",col_coor[l]);}
    printf("\n");
}

//le coordinate stampate attorno alla scacchiera vanno da 1 a 7 mentre le coordinate vere vanno da 0 a 6, inoltre le coordinate dei
//numeri di fianco vanno in ordine decrescente mentre la i deve andare in ordine crescente

/** La funzione mosse possibili analizza tutte le pedine nella scacchiera e le possibili mosse che possono compiere
 *  ho fatto analizzare diagonalmente le posizioni rispetto alla pedina che si prende in considerazione sia di un posto
 *  nel caso la casella successiva fosse piena sia di due posti nel caso la prima casela fosse piena o vuota.
 *  Per le pedine del player 1 ossia l x ho fatto analizzare solo i movimenti che andavano in alto.
 *  Per le pedine del player 2 ossia le o ho fatto analizzare solo i movimenti che andavano in basso.
 */

void mosse_possibili (int *board, int turno){
    int i,j,k=rows;
    choice=0;
    if(turno==player1){
        printf("Mosse disponibili per il giocatore 1:\n");

        for(i=0;i<rows;i++){
            for(j=0;j<cols;j++){

                if(board[i*cols+j]==player1 || board[i*cols+j]==player1*2 || board[i*cols+j]==player1*3){

                    if(k>=0 && k<=rows)

                        if(j+2<cols && k+2<=rows){
                            if(board[(i-1)*cols+j+1]==vuoto && board[(i-2)*cols+j+2]!=vuoto){
                                choice++;
                                printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j+1], k+1);
                            }
                            else if(board[(i-1)*cols+j+1]!=player1 && board[(i-2)*cols+j+2]==vuoto){
                                choice++;
                                printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j+2], k+2);

                            }}

                    if(j-2>=0 && k+2<=rows){
                        if(board[(i-1)*cols+j-1]==vuoto && board[(i-2)*cols+j-2]!=vuoto){
                            choice++;
                            printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j-1], k+1);
                        }
                        else if(board[(i-1)*cols+j-1]!=player1 && board[(i-2)*cols+j-2]==vuoto){
                            choice++;
                            printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j-2], k+2);
                        }}

                    if(j+2==cols && k+1<=rows){  //>= perchÃ¨ col_coor arriva fino a 7 ([8]) mentre cols Ã¨ [7] ossia 6
                        if(board[(i-1)*cols+j+1]==vuoto){
                            choice++;
                            printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j+1], k+1);
                        }}

                    if(j-2<0 && k+1<=rows){
                        if(board[(i-1)*cols+j-1]==vuoto && j-1==0){
                            choice++;
                            printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j-1], k+1);
                        }}

                }

            }

            k--;

        }

    }else if(turno==player2){
        printf("Mosse disponibili per il giocatore 2:\n");
        for(i=0;i<rows;i++){
            for(j=0;j<cols;j++){

                if(board[i*cols+j]==player2 || board[i*cols+j]==player2*2 || board[i*cols+j]==player2*3){

                    if(j+2<cols && k-2>=0){
                        if(board[(i+1)*cols+j+1]==vuoto && board[(i+2)*cols+j+2]!=vuoto){
                            choice++;
                            printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j+1], k-1);
                        }
                        else if(board[(i+1)*cols+j+1]!=player2 && board[(i+2)*cols+j+2]==vuoto){
                            choice++;
                            printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j+2], k-2);
                        }}

                    if(j-2>=0 && k-2>=0){
                        if(board[(i+1)*cols+j-1]==vuoto && board[(i+2)*cols+j-2]!=vuoto){
                            choice++;
                            printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j-1], k-1);
                        }
                        else if(board[(i+1)*cols+j-1]!=player2 && board[(i+2)*cols+j-2]==vuoto){
                            choice++;
                            printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j-2], k-2);
                        }}

                    if(j+2==cols && k-1>=0){
                        if(board[(i+1)*cols+j+1]==vuoto){
                            choice++;
                            printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j+1], k-1);
                        }}

                    if(j-2<0 && k-1>=0){
                        if(board[(i+1)*cols+j-1]==vuoto && j-1==0){
                            choice++;
                            printf("%d) %c%d-%c%d  \n",choice, col_coor[j], k, col_coor[j-1], k-1);
                        }}

                }

            }

            k--;

        }

    }
}

//inserimento delle coordinate
/** La funzione scegli mossa chiede in input prima la colonna e la riga della pedina che si vuole spostare poi richiede
 *  la colonna e la riga su cui si vuole spostare la pedina, se si inserisce una coordinata sbagliata si salta il turno
 * Una volta che la pedina raggiunge la fine della scacchiera non si potrÃ  piÃ¹ muovere
 */

/**
 *
 * @param board
 * @param turno
 */

void scegli_mossa(int *board, int turno){
    int i,j,k=rows;
    char a;
    int b;

    if(turno==player1){
        printf("Turno del giocatore 1\n");
    }else if(turno==player2){
        printf("Turno del giocatore 2\n");
    }

    printf("Scegli la pedina da muovere:\n");
    printf("-Inserisci la colonna\n");
    scanf(" %c",&a);
    printf("-Inserisci la riga\n");
    scanf("%d",&b);

    for(i=0;i<=rows;i++){
        for(j=0;j<cols;j++){
            if(k==b && col_coor[j]==a){
                if(board[i*cols+j]!=turno && board[i*cols+j]!=turno*2 && board[i*cols+j]!=turno*3){
                    printf("La casella non contiene la tua pedina\n");
                    break;
                }

                if(board[i*cols+j]==player1){
                    char colonna;
                    int riga;
                    printf("Inserisci le coordinate della casella su cui vuoi spostare la pedina:\n");
                    printf("-Inserisci la colonna\n");
                    scanf(" %c", &colonna);
                    printf("-Inserisci la riga\n");
                    scanf("%d", &riga);

                    if(riga==k+1 && col_coor[j+1]==colonna){
                        if(board[(i-1)*cols+j+1]==vuoto && board[(i-2)*cols+j+2]!=vuoto){
                            board[(i-1)*cols+j+1]=player1;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k+1 && col_coor[j-1]==colonna){
                        if(board[(i-1)*cols+j-1]==vuoto && board[(i-2)*cols+j-2]!=vuoto){
                            board[(i-1)*cols+j-1]=player1;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k+2 && col_coor[j+2]==colonna){
                        if(board[(i-1)*cols+j+1]==player2 && board[(i-2)*cols+j+2]==vuoto){
                            board[(i-2)*cols+j+2]=player1*2;
                            board[(i-1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i-1)*cols+j+1]==player2*2 || board[(i-1)*cols+j+1]==player2*3) && board[(i-2)*cols+j+2]==vuoto){
                            board[(i-2)*cols+j+2]=player1*3;
                            board[(i-1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i-1)*cols+j+1]==vuoto && board[(i-2)*cols+j+2]==vuoto){
                            board[(i-2)*cols+j+2]=player1;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k+2 && col_coor[j-2]==colonna){
                        if(board[(i-1)*cols+j-1]==player2 && board[(i-2)*cols+j-2]==vuoto){
                            board[(i-2)*cols+j-2]=player1*2;
                            board[(i-1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i-1)*cols+j-1]==player2*2 || board[(i-1)*cols+j-1]==player2*3) && board[(i-2)*cols+j-2]==vuoto){
                            board[(i-2)*cols+j-2]=player1*3;
                            board[(i-1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i-1)*cols+j-1]==vuoto && board[(i-2)*cols+j-2]==vuoto){
                            board[(i-2)*cols+j-2]=player1;
                            board[(i)*cols+j]=vuoto;
                        }
                    }

                }else if(board[i*cols+j]==player2){
                    char colonna;
                    int riga;
                    printf("Inserisci le coordinate della casella su cui vuoi spostare la pedina:\n");
                    printf("-Inserisci la colonna\n");
                    scanf(" %c", &colonna);
                    printf("-Inserisci la riga\n");
                    scanf("%d", &riga);

                    if(riga==k-1 && col_coor[j+1]==colonna){
                        if(board[(i+1)*cols+j+1]==vuoto && board[(i+2)*cols+j+2]!=vuoto){
                            board[(i+1)*cols+j+1]=player2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k-1 && col_coor[j-1]==colonna){
                        if(board[(i+1)*cols+j-1]==vuoto && board[(i+2)*cols+j-2]!=vuoto){
                            board[(i+1)*cols+j-1]=player2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k-2 && col_coor[j+2]==colonna){
                        if(board[(i+1)*cols+j+1]==player1 && board[(i+2)*cols+j+2]==vuoto){
                            board[(i+2)*cols+j+2]=player2*2;
                            board[(i+1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i+1)*cols+j+1]==player1*2 || board[(i+1)*cols+j+1]==player1*3) && board[(i+2)*cols+j+2]==vuoto){
                            board[(i+2)*cols+j+2]=player2*3;
                            board[(i+1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i+1)*cols+j+1]==vuoto && board[(i+2)*cols+j+2]==vuoto){
                            board[(i+2)*cols+j+2]=player2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k-2 && col_coor[j-2]==colonna){
                        if(board[(i+1)*cols+j-1]==player1 && board[(i+2)*cols+j-2]==vuoto){
                            board[(i+2)*cols+j-2]=player2*2;
                            board[(i+1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i+1)*cols+j-1]==player1*2 || board[(i+1)*cols+j-1]==player1*3) && board[(i+2)*cols+j-2]==vuoto){
                            board[(i+2)*cols+j-2]=player2*3;
                            board[(i+1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i+1)*cols+j-1]==vuoto && board[(i+2)*cols+j-2]==vuoto){
                            board[(i+2)*cols+j-2]=player2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }

                }

                else if(board[i*cols+j]==player2*2){
                    char colonna;
                    int riga;
                    printf("Inserisci le coordinate della casella su cui vuoi spostare la pedina:\n");
                    printf("-Inserisci la colonna\n");
                    scanf(" %c", &colonna);
                    printf("-Inserisci la riga\n");
                    scanf("%d", &riga);

                    if(riga==k-1 && col_coor[j+1]==colonna){
                        if(board[(i+1)*cols+j+1]==vuoto && board[(i+2)*cols+j+2]!=vuoto){
                            board[(i+1)*cols+j+1]=player2*2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k-1 && col_coor[j-1]==colonna){
                        if(board[(i+1)*cols+j-1]==vuoto && board[(i+2)*cols+j-2]!=vuoto){
                            board[(i+1)*cols+j-1]=player2*2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k-2 && col_coor[j+2]==colonna){
                        if(board[(i+1)*cols+j+1]==player1 && board[(i+2)*cols+j+2]==vuoto){
                            board[(i+2)*cols+j+2]=player2*3;
                            board[(i+1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i+1)*cols+j+1]==player1*2 || board[(i+1)*cols+j+1]==player1*3) && board[(i+2)*cols+j+2]==vuoto){
                            board[(i+2)*cols+j+2]=player2*3;
                            board[(i+1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i+1)*cols+j+1]==vuoto && board[(i+2)*cols+j+2]==vuoto){
                            board[(i+2)*cols+j+2]=player2*2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k-2 && col_coor[j-2]==colonna){
                        if(board[(i+1)*cols+j-1]==player1 && board[(i+2)*cols+j-2]==vuoto){
                            board[(i+2)*cols+j-2]=player2*3;
                            board[(i+1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i+1)*cols+j-1]==player1*2 || board[(i+1)*cols+j-1]==player1*3) && board[(i+2)*cols+j-2]==vuoto){
                            board[(i+2)*cols+j-2]=player2*3;
                            board[(i+1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i+1)*cols+j-1]==vuoto && board[(i+2)*cols+j-2]==vuoto){
                            board[(i+2)*cols+j-2]=player2*2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }

                }

                else if(board[i*cols+j]==player1*2){

                    char colonna;
                    int riga;
                    printf("Inserisci le coordinate della casella su cui vuoi spostare la pedina:\n");
                    printf("-Inserisci la colonna\n");
                    scanf(" %c", &colonna);
                    printf("-Inserisci la riga\n");
                    scanf("%d", &riga);

                    if(riga==k+1 && col_coor[j+1]==colonna){
                        if(board[(i-1)*cols+j+1]==vuoto && board[(i-2)*cols+j+2]!=vuoto){
                            board[(i-1)*cols+j+1]=player1*2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k+1 && col_coor[j-1]==colonna){
                        if(board[(i-1)*cols+j-1]==vuoto && board[(i-2)*cols+j-2]!=vuoto){
                            board[(i-1)*cols+j-1]=player1*2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k+2 && col_coor[j+2]==colonna){
                        if(board[(i-1)*cols+j+1]==player2 && board[(i-2)*cols+j+2]==vuoto){
                            board[(i-2)*cols+j+2]=player1*3;
                            board[(i-1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i-1)*cols+j+1]==player2*2 || board[(i-1)*cols+j+1]==player2*3) && board[(i-2)*cols+j+2]==vuoto){
                            board[(i-2)*cols+j+2]=player1*3;
                            board[(i-1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i-1)*cols+j+1]==vuoto && board[(i-2)*cols+j+2]==vuoto){
                            board[(i-2)*cols+j+2]=player1*2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k+2 && col_coor[j-2]==colonna){
                        if(board[(i-1)*cols+j-1]==player2 && board[(i-2)*cols+j-2]==vuoto){
                            board[(i-2)*cols+j-2]=player1*3;
                            board[(i-1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i-1)*cols+j-1]==player2*2 || board[(i-1)*cols+j-1]==player2*3) && board[(i-2)*cols+j-2]==vuoto){
                            board[(i-2)*cols+j-2]=player1*3;
                            board[(i-1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i-1)*cols+j-1]==vuoto && board[(i-2)*cols+j-2]==vuoto){
                            board[(i-2)*cols+j-2]=player1*2;
                            board[(i)*cols+j]=vuoto;
                        }
                    }

                }else if(board[i*cols+j]==player1*3){

                    char colonna;
                    int riga;
                    printf("Inserisci le coordinate della casella su cui vuoi spostare la pedina:\n");
                    printf("-Inserisci la colonna\n");
                    scanf(" %c", &colonna);
                    printf("-Inserisci la riga\n");
                    scanf("%d", &riga);

                    if(riga==k+1 && col_coor[j+1]==colonna){
                        if(board[(i-1)*cols+j+1]==vuoto && board[(i-2)*cols+j+2]!=vuoto){
                            board[(i-1)*cols+j+1]=player1*3;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k+1 && col_coor[j-1]==colonna){
                        if(board[(i-1)*cols+j-1]==vuoto && board[(i-2)*cols+j-2]!=vuoto){
                            board[(i-1)*cols+j-1]=player1*3;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k+2 && col_coor[j+2]==colonna){
                        if(board[(i-1)*cols+j+1]==player2 && board[(i-2)*cols+j+2]==vuoto){
                            board[(i-2)*cols+j+2]=player1*3;
                            board[(i-1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i-1)*cols+j+1]==player2*2 || board[(i-1)*cols+j+1]==player2*3) && board[(i-2)*cols+j+2]==vuoto){
                            board[(i-2)*cols+j+2]=player1*3;
                            board[(i-1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i-1)*cols+j+1]==vuoto && board[(i-2)*cols+j+2]==vuoto){
                            board[(i-2)*cols+j+2]=player1*3;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k+2 && col_coor[j-2]==colonna){
                        if(board[(i-1)*cols+j-1]==player2 && board[(i-2)*cols+j-2]==vuoto){
                            board[(i-2)*cols+j-2]=player1*3;
                            board[(i-1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i-1)*cols+j-1]==player2*2 || board[(i-1)*cols+j-1]==player2*3) && board[(i-2)*cols+j-2]==vuoto){
                            board[(i-2)*cols+j-2]=player1*3;
                            board[(i-1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i-1)*cols+j-1]==vuoto && board[(i-2)*cols+j-2]==vuoto){
                            board[(i-2)*cols+j-2]=player1*3;
                            board[(i)*cols+j]=vuoto;
                        }
                    }

                }

                else if(board[i*cols+j]==player2*3){
                    char colonna;
                    int riga;
                    printf("Inserisci le coordinate della casella su cui vuoi spostare la pedina:\n");
                    printf("-Inserisci la colonna\n");
                    scanf(" %c", &colonna);
                    printf("-Inserisci la riga\n");
                    scanf("%d", &riga);

                    if(riga==k-1 && col_coor[j+1]==colonna){
                        if(board[(i+1)*cols+j+1]==vuoto && board[(i+2)*cols+j+2]!=vuoto){
                            board[(i+1)*cols+j+1]=player2*3;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k-1 && col_coor[j-1]==colonna){
                        if(board[(i+1)*cols+j-1]==vuoto && board[(i+2)*cols+j-2]!=vuoto){
                            board[(i+1)*cols+j-1]=player2*3;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k-2 && col_coor[j+2]==colonna){
                        if(board[(i+1)*cols+j+1]==player1 && board[(i+2)*cols+j+2]==vuoto){
                            board[(i+2)*cols+j+2]=player2*3;
                            board[(i+1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i+1)*cols+j+1]==player1*2 || board[(i+1)*cols+j+1]==player1*3) && board[(i+2)*cols+j+2]==vuoto){
                            board[(i+2)*cols+j+2]=player2*3;
                            board[(i+1)*cols+j+1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i+1)*cols+j+1]==vuoto && board[(i+2)*cols+j+2]==vuoto){
                            board[(i+2)*cols+j+2]=player2*3;
                            board[(i)*cols+j]=vuoto;
                        }
                    }else if(riga==k-2 && col_coor[j-2]==colonna){
                        if(board[(i+1)*cols+j-1]==player1 && board[(i+2)*cols+j-2]==vuoto){
                            board[(i+2)*cols+j-2]=player2*3;
                            board[(i+1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if((board[(i+1)*cols+j-1]==player1*2 || board[(i+1)*cols+j-1]==player1*3) && board[(i+2)*cols+j-2]==vuoto){
                            board[(i+2)*cols+j-2]=player2*3;
                            board[(i+1)*cols+j-1]=vuoto;
                            board[(i)*cols+j]=vuoto;
                        }else if(board[(i+1)*cols+j-1]==vuoto && board[(i+2)*cols+j-2]==vuoto){
                            board[(i+2)*cols+j-2]=player2*3;
                            board[(i)*cols+j]=vuoto;
                        }
                    }

                }

            }
        }
        k--;
    }

}

/** Nella funzione main si utilizzano tutte le funzioni e per determinare la fine del gioco ci si basa sul turno e sulla
 *  variabile globale choice che determina quante mosse disponibili ha un giocatore
 */

int main(){
    int board[rows][cols];
    int turno;
    printf("Premi qualsiasi pulsante per iniziare il gioco\n");
    getchar();
    bool endgame;

    posizionamento_pedine(&board[0][0]);

    turno=player1;
    printf("Turno del giocatore 1:\n");
    while(endgame!=true){

        stampa_scacchiera(&board[0][0]);
        mosse_possibili(&board[0][0],turno);
        if(choice==0){
            if(turno==player1){
                printf("Il giocatore 1 ha perso\n");
            }else if(turno==player2){
                printf("Il giocatore 2 ha perso\n");
            }
            endgame=true;
            break;
        }
        scegli_mossa(&board[0][0],turno);
        if(turno==player1) {turno=player2;}
        else {turno=player1;}
    }
}