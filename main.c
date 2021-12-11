#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
int harita[80][23]={0}; // konsol aray�z de�erleri
int kuyrukX[500];
int kuyrukY[500];
int maap[80][23]={0};
// S�TUN=X SATIR=Y
void gotoxy(short x, short y) { //internetten ald���m koordinatlara gitmemi sa�layan bir fonksiyon
	HANDLE hConsoleOutput;
	COORD Cursor_Pos = {x-1, y-1};

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void cerceve(int dikey1, int yatay1, int dikey2, int yatay2,int tur)
{
    int i;
    for(i=dikey1; i<=dikey2;i++) // 0-79 
    {    
        harita[i][yatay1] = tur; //1-0 2-0 3-0 4-0 olarak �st yatay �izgisi �ekilir

        harita[i][yatay2] = tur; // 

    }
    for(i=yatay1; i<=yatay2;i++) //0-22
    {
        harita[dikey1][i] = tur;

        harita[dikey2][i] = tur;

    }
}

void ekranyazdir() //s�tun ve sat�rlar� dola��rken ==2(tur) ise belirledi�im karakter yaz�lacak
{
    int x,y;
    for(x=0;x<80;x++)
    {


        for(y=0;y<23;y++)
        {
        gotoxy(x+1,y+1); //x ve y nin 1 fazlas�na imleci g�t�r�r
       
             if(harita[x][y]==2) // harita dizimin x ve y'nci indexleri 2 ye e�itse ascii tablosundaki 176 char�n� �iz
            {
                printf("%c",176);
            }
     

        }
    }
}

int yemx,yemy; 
rastgeleyem()
{
    srand(time(NULL)); //zamana ba�l� olarak s�rekli farkl� de�erler atayacak
    yemx=4+rand()%65; //69 farkl� x koordinat�nda yem atayacak
    yemy=4+rand()%15; // 19 farkl� y koordinat�nda yem atayacak


}

void main()
{
    rastgeleyem();
    cerceve(0,0,79,22,2);
    ekranyazdir();
    int yilanx=40,yilany=12;
    int ekley=0,eklex=0;
    unsigned char tus;
    int p=0; // hem puan�m�z� hem kuyruk uzunlu�umuzu tutucak 
    int kontrol=0;




    do
    {
        if(kbhit()) //e�er tu�a bas�l�rsa
        {
            tus=getch(); //tu�u haf�zaya al
            if(tus==224) //haf�zadaki tu� y�n tu�lar�ndan biri mi?
            {
                tus=getch(); 
                switch(tus)
                {
                    case 72:ekley=-1; eklex=0; /* burdaki algoritma �u �ekilde 
					yilany=12 demi�tik e�er '72' yani �st y�n tu�una bas�l�rsa "yilany +=ekley;" ifadesiyle
					bu durumda 11e d��ecektir
					bu da bizim yukar�ya ��kmam�za sebep olur*/
                        break;
                    case 80:ekley=1; eklex=0; // a�a�� y�n tu�u yilany= yilany+ekley; 12+1=13 a�a�� gider
                        break;
                    case 77: eklex=1; ekley=0; // sa� y�n tu�u  
                        break;
                    case 75: eklex=-1; ekley=0; // ascii tablosundaki sol y�n tu�u
                    // sa�a do�ru +1 sola do�ru -1
                    // a�a�� do�ru +1 �ste do�ru -1
                }
            }
        }
        //40-1 
        yilanx=yilanx+eklex; 
        yilany=yilany+ekley;
        
        if(yilanx>78)    
            yilanx=2;
        if(yilanx<2)   // �stte �er�evemizin boyutunu 2-78 2-22 olarak belirlemi�tik 
            yilanx=78; //ve y�lan�m�z bir kenardan ��kt��� zaman geri gelmesini istiyoruz 
        if(yilany>22)  //x koordinat� 78i a�arsa >>> yilanx=2 || 2nin altina girerse >>> yilanx =78
            yilany=2;  
        if(yilany<2)    // y koordinat� 22yi a�arsa > yilany=2 || y koordinat� 2nin altina girerse >> yilany=22
            yilany=22;

        kuyrukX[0]=yilanx;//kuyruky0 = yilanx
        kuyrukY[0]=yilany;//kuyruk
        int i;


        for(i=1;i<=p;i++) 
        {
            if((yilanx==kuyrukX[i] && yilany==kuyrukY[i])) /* 
			e�er y�lan�n s�tun de�eri, kuyru�un s�tun de�erine denk geldiyse
			ya da sat�r de�erleri birbirine denk geldiyse oyunu bitir  	       */
            {
                gotoxy(yilanx,yilany);printf("<<OYUN BITTI>>"); 
                getch();
                kontrol=1;
            }


        }

        gotoxy(yilanx,yilany);printf("*"); //yilanx, yilany koordinatlar�nda * char�n� olu�tur

        for(i=0;i<=p;i++) //0dan ba�la, p'n�n uzunlu�u kadar kuyrukX ve kuyrukY indexlerine git * koy (kuyru�u uzat)
        {
            gotoxy(kuyrukX[i],kuyrukY[i]);printf("*"); 

        }


        if(yilanx==yemx && yilany==yemy)
        {
            rastgeleyem(); //haritam�z�n i�inde tekrardan bir yem ata
            p++; //kuyruk uzunlu�unu ve puan� 1 artt�r
            gotoxy(2,2);printf("Puan: %d",p*10); //2,2 (en sol �st) koordinatlar�nda puan�m�z� dinamik olarak g�ncellesin.
        }

        gotoxy(yemx,yemy);printf("O"); // yemx,yemy koordinatlar�nda O char�n� yani yemimizi olu�tursun

        Sleep(50); //ekran s�rekli O ile dolmas�n diye 50 milisaniye beklesin

        gotoxy(yilanx,yilany);printf(" "); //y�lan g�vdesi hareket ettik�e arkas�n�n silinmesi gerekiyor her taraf * olur yoksa


        for(i=0;i<=p;i++)
        {
            gotoxy(kuyrukX[i],kuyrukY[i]);printf(" "); //�sttekinin ayn�s�, kuyruk i�in

        }


        for(i=p;i>0;i--) 
        {
            kuyrukX[i]=kuyrukX[i-1];//bir �nceki kuyrukX indexini bi sonraki kuyrukX indexine ata �rn: p=5 > 5-4-3-2-1 
            kuyrukY[i]=kuyrukY[i-1];
        }

    } while (kontrol==0);
}
