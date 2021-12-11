#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
int harita[80][23]={0}; // konsol arayüz deðerleri
int kuyrukX[500];
int kuyrukY[500];
int maap[80][23]={0};
// SÜTUN=X SATIR=Y
void gotoxy(short x, short y) { //internetten aldýðým koordinatlara gitmemi saðlayan bir fonksiyon
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
        harita[i][yatay1] = tur; //1-0 2-0 3-0 4-0 olarak üst yatay çizgisi çekilir

        harita[i][yatay2] = tur; // 

    }
    for(i=yatay1; i<=yatay2;i++) //0-22
    {
        harita[dikey1][i] = tur;

        harita[dikey2][i] = tur;

    }
}

void ekranyazdir() //sütun ve satýrlarý dolaþýrken ==2(tur) ise belirlediðim karakter yazýlacak
{
    int x,y;
    for(x=0;x<80;x++)
    {


        for(y=0;y<23;y++)
        {
        gotoxy(x+1,y+1); //x ve y nin 1 fazlasýna imleci götürür
       
             if(harita[x][y]==2) // harita dizimin x ve y'nci indexleri 2 ye eþitse ascii tablosundaki 176 charýný çiz
            {
                printf("%c",176);
            }
     

        }
    }
}

int yemx,yemy; 
rastgeleyem()
{
    srand(time(NULL)); //zamana baðlý olarak sürekli farklý deðerler atayacak
    yemx=4+rand()%65; //69 farklý x koordinatýnda yem atayacak
    yemy=4+rand()%15; // 19 farklý y koordinatýnda yem atayacak


}

void main()
{
    rastgeleyem();
    cerceve(0,0,79,22,2);
    ekranyazdir();
    int yilanx=40,yilany=12;
    int ekley=0,eklex=0;
    unsigned char tus;
    int p=0; // hem puanýmýzý hem kuyruk uzunluðumuzu tutucak 
    int kontrol=0;




    do
    {
        if(kbhit()) //eðer tuþa basýlýrsa
        {
            tus=getch(); //tuþu hafýzaya al
            if(tus==224) //hafýzadaki tuþ yön tuþlarýndan biri mi?
            {
                tus=getch(); 
                switch(tus)
                {
                    case 72:ekley=-1; eklex=0; /* burdaki algoritma þu þekilde 
					yilany=12 demiþtik eðer '72' yani üst yön tuþuna basýlýrsa "yilany +=ekley;" ifadesiyle
					bu durumda 11e düþecektir
					bu da bizim yukarýya çýkmamýza sebep olur*/
                        break;
                    case 80:ekley=1; eklex=0; // aþaðý yön tuþu yilany= yilany+ekley; 12+1=13 aþaðý gider
                        break;
                    case 77: eklex=1; ekley=0; // sað yön tuþu  
                        break;
                    case 75: eklex=-1; ekley=0; // ascii tablosundaki sol yön tuþu
                    // saða doðru +1 sola doðru -1
                    // aþaðý doðru +1 üste doðru -1
                }
            }
        }
        //40-1 
        yilanx=yilanx+eklex; 
        yilany=yilany+ekley;
        
        if(yilanx>78)    
            yilanx=2;
        if(yilanx<2)   // üstte çerçevemizin boyutunu 2-78 2-22 olarak belirlemiþtik 
            yilanx=78; //ve yýlanýmýz bir kenardan çýktýðý zaman geri gelmesini istiyoruz 
        if(yilany>22)  //x koordinatý 78i aþarsa >>> yilanx=2 || 2nin altina girerse >>> yilanx =78
            yilany=2;  
        if(yilany<2)    // y koordinatý 22yi aþarsa > yilany=2 || y koordinatý 2nin altina girerse >> yilany=22
            yilany=22;

        kuyrukX[0]=yilanx;//kuyruky0 = yilanx
        kuyrukY[0]=yilany;//kuyruk
        int i;


        for(i=1;i<=p;i++) 
        {
            if((yilanx==kuyrukX[i] && yilany==kuyrukY[i])) /* 
			eðer yýlanýn sütun deðeri, kuyruðun sütun deðerine denk geldiyse
			ya da satýr deðerleri birbirine denk geldiyse oyunu bitir  	       */
            {
                gotoxy(yilanx,yilany);printf("<<OYUN BITTI>>"); 
                getch();
                kontrol=1;
            }


        }

        gotoxy(yilanx,yilany);printf("*"); //yilanx, yilany koordinatlarýnda * charýný oluþtur

        for(i=0;i<=p;i++) //0dan baþla, p'nýn uzunluðu kadar kuyrukX ve kuyrukY indexlerine git * koy (kuyruðu uzat)
        {
            gotoxy(kuyrukX[i],kuyrukY[i]);printf("*"); 

        }


        if(yilanx==yemx && yilany==yemy)
        {
            rastgeleyem(); //haritamýzýn içinde tekrardan bir yem ata
            p++; //kuyruk uzunluðunu ve puaný 1 arttýr
            gotoxy(2,2);printf("Puan: %d",p*10); //2,2 (en sol üst) koordinatlarýnda puanýmýzý dinamik olarak güncellesin.
        }

        gotoxy(yemx,yemy);printf("O"); // yemx,yemy koordinatlarýnda O charýný yani yemimizi oluþtursun

        Sleep(50); //ekran sürekli O ile dolmasýn diye 50 milisaniye beklesin

        gotoxy(yilanx,yilany);printf(" "); //yýlan gövdesi hareket ettikçe arkasýnýn silinmesi gerekiyor her taraf * olur yoksa


        for(i=0;i<=p;i++)
        {
            gotoxy(kuyrukX[i],kuyrukY[i]);printf(" "); //üsttekinin aynýsý, kuyruk için

        }


        for(i=p;i>0;i--) 
        {
            kuyrukX[i]=kuyrukX[i-1];//bir önceki kuyrukX indexini bi sonraki kuyrukX indexine ata örn: p=5 > 5-4-3-2-1 
            kuyrukY[i]=kuyrukY[i-1];
        }

    } while (kontrol==0);
}
