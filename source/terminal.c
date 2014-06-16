#include "biblioteki.h"

/*Struktura gracza*/
typedef struct{
char imie[MAX_IM];
char nazwisko [MAX_NA];
int wynik;
}gracz;


/*Tabela struktur*/
gracz spis_gracz[IL_GRACZ];

/*Sprawdzanie czy baza istnieje i jej ewentualne utworzenie+dodanie nowego gracza*/
void utworz_baze()
    {
        FILE* plik;
             plik=fopen("baza.txt","r");
             if(plik==NULL)
               {
                fclose(plik);
                printf("Brak bazy Graczy, nastapilo jej utworzenie\n");
                plik=fopen("baza.txt","w");
                     char imiee[MAX_IM];
                     char spacja=' ';
                     char brejk='\n';
                     char nazwiskoo[MAX_NA];
                     int wynikk=0;
                        printf("Podaj imie:   ");
                        scanf("%s",&imiee);
                            fprintf(plik,"%s", &imiee);
                            fprintf(plik,"%c", spacja);
                        printf("Podaj nazwisko:   ");
                        scanf("%s",&nazwiskoo);
                            fprintf(plik,"%s", &nazwiskoo);
                            fprintf(plik,"%c", spacja);
                            fprintf(plik,"%i", wynikk);
                            fprintf(plik,"%c", brejk);

               }
             else
                printf("jest plik\n");
                printf("\n");

         fclose(plik);
    }

    /*Wczytywanie spisu graczy z bazy do GRY*/
   int wczyt_spis()
    {
     int i=0,sukces;
  FILE* plik =
    plik=fopen("baza.txt","r");
  if (plik == NULL){
        printf("\n ZLE\n\n");
                   }else
            {
do
        {
           sukces=fscanf(plik, "%s %s %i", &spis_gracz[i].imie, &spis_gracz[i].nazwisko, &spis_gracz[i].wynik);
                                     i++;
                                     }
                               while(sukces!=EOF);

                        }

  fclose(plik);
  int ile=i-1;
  return ile;
}
/*dodanie gracza*/
void dod_gr(int a)
{
    FILE * plik;
    plik=fopen("baza.txt","a");

}
/*Wypisywanie tabeli z graczami*/
void tb_wyn()
{
    FILE* plik;
    plik=fopen("baza.txt","r");
    int i=0;
    for(i=0;i<10;i++)
    {
        printf(" %s %s %i \n",spis_gracz[i].imie, spis_gracz[i].nazwisko, spis_gracz[i].wynik);
    }
    fclose(plik);
}

/*MENU gry*/
void menu_podstawa()
{
printf("--RIVER_RIDE!!--");
printf("\n");
printf("-----POWODZENIA-----");
printf("\n");
printf("        MENU        ");
printf("\n");
printf(" Dodaj gracza [1]\n Tabela Najlepszych Wynikow [2]\n Nowa Gra [3]\n Wyjscie [4]\n");
}

void menu_glowne(int ile)
{
    int k;
    scanf("%i",&k);
    int q=1;
    switch(k)
    {
    case 1:dod_gr(ile);

    case 2:tb_wyn();

    case 3: break;
    case 4: exit(-1);
    }
}

