#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    // Inicijalizacija programa

    FILE *fajl_tok;
    char ime_fajla[] = "tabela.txt";
    size_t n_bajtova = 100;
    char *ime_kluba;
    char *opcija;
    char *domaci;
    char *gostujuci;
    int bajtova_procitano;
    char broj_klubova = 1;
    char *pointer;
    char unos;
    char *gol_dom;
    char *gol_gos;
    char *rezultat;
    char *tab = NULL;

    fajl_tok = fopen(ime_fajla, "a+");

    if(fajl_tok == NULL){

      printf("Problem pri otvaranju fajla 'tabela.txt'\n");
    }

    fprintf(fajl_tok, "POREDAK     TIM     OS     G     B\n");

    if(fclose(fajl_tok)){

      printf("Problem pri zatvaranju fajla 'tabela.txt'\n");
    }

    while(1){

      // Opcije

      printf("\n(1) Unos novog tima\n");
      printf("(2) Korigovanje parametara kluba\n");
      printf("(3) Pretrazi tabelu *x,>* ili *x,<*\n");
      printf("(4) Trenutno stanje na tabeli\n");
      printf("(5) Izlaz\n\n");
      printf("Izaberite opciju: ");

      opcija = (char*)malloc(n_bajtova);

      getline(&opcija, &n_bajtova, stdin);

      // Unos novog kluba u tabelu

      if(opcija[0] == '1'){

        
        printf("Unesi ime novog tima: ");

        ime_kluba = (char*)malloc(n_bajtova);

        bajtova_procitano = getline(&ime_kluba, &n_bajtova, stdin);

        if(bajtova_procitano == -1){

          printf("Greska!\n");
        }

        pointer = strtok(ime_kluba, "\n");

        fajl_tok = fopen(ime_fajla, "a+");
      
        if(fajl_tok == NULL){

          printf("Problem pri otvaranju fajla 'tabela.txt'\n");
        }

        fprintf(fajl_tok, "%d.          %s"
                "   0"
                "   0:0"
                "   0\n", broj_klubova, pointer);

        broj_klubova++;

        if(fclose(fajl_tok)){

          printf("Problem pri zatvaranju 'tabela.txt'\n");
        }

        free(ime_kluba);
      }

      // Korigovanje parametara klubova

      if(opcija[2] == '2'){

        printf("Unesi domaci tim: ");

        domaci = (char*)malloc(n_bajtova);

        getline(&domaci, &n_bajtova, stdin);

        printf("Unesi gostujuci tim: ");

        gostujuci = (char*)malloc(n_bajtova);

        getline(&gostujuci, &n_bajtova, stdin);

        printf("Unesi rezultat utakmice *x:y* : ");

        rezultat = (char*)malloc(n_bajtova);

        getline(&rezultat, &n_bajtova, stdin);

        gol_dom = strtok(rezultat ,":");

        gol_gos = strtok(NULL, "\n");

        free(rezultat);

        free(gostujuci);

        free(domaci);
      }

      // Ispis trenututnog stanja tabele

      if(opcija[0] == '4'){

          fajl_tok = fopen(ime_fajla, "r");
      
          if(fajl_tok == NULL){

            printf("Problem pri otvaranju fajla 'tabela.txt'\n");
          }
          
          
          printf("\n");

          while(getline(&tab, &n_bajtova, fajl_tok) != -1){

            printf("%s", tab);
          }

          if(fclose(fajl_tok)){

            printf("Problem pri zatvaranju 'tabela.txt'\n");
          }

          free(tab);
      }

      // Izlaz

      if(opcija[0] == '5'){

        break;
      }

      free(opcija);

    }

}
