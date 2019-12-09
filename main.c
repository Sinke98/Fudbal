#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

  // Inicijalizacija

  FILE *fajl_tok;
  FILE *fajl_tok2;
  char ime_fajla[] = "tabela.txt";
  char ime_fajla2[] = "fajl2.txt";
  char *opcija;
  char *ime;
  char *pointer;
  char *domacin;
  char *gost;
  size_t n_bajtova = 100;
  int br_klubova = 0;
  int poredak = 1;
  int j = 0;
  int dom_gol;
  int gost_gol;
  
  struct klub{
    
    char ime_kluba[15];
    int br_bodova;
    int br_datih_golova;
    int br_primljenih_golova;
    int br_odigranih_utakmica;

  };

  struct klub klubovi[20];


  fajl_tok2 = fopen(ime_fajla2, "r");

  // Ako postoje fajlovi "tabela.txt" i "fajl2.txt"

  if(fajl_tok2 == NULL){

    printf("\nProblem pri otvaranju fajla 'fajl2.txt'\n");
  }
  else{

    ime = (char*)malloc(n_bajtova);

    getline(&ime, &n_bajtova, fajl_tok2);

    if(fclose(fajl_tok2)){

      printf("\nProblem pri zatvaranju fajla 'fajl2.txt'\n");
    }

    sscanf(ime, "%d,%d", &br_klubova, &poredak);

    free(ime);

    fajl_tok = fopen(ime_fajla, "r");

    if(fajl_tok == NULL){

      printf("\nProblem pri otvaranju fajla 'tabela.txt'\n");
    }
    else{

      ime = (char*)malloc(n_bajtova);

      while(getline(&ime, &n_bajtova, fajl_tok) != -1){

        sscanf(ime, "%s,%d,%d,%d,%d", klubovi[j].ime_kluba, &klubovi[j].br_bodova, &klubovi[j].br_datih_golova, &klubovi[j].br_primljenih_golova, &klubovi[j].br_odigranih_utakmica);

        j++;

        free(ime);
      }

      if(fclose(fajl_tok)){

        printf("\nProblem pri zatvaranju fajla 'tabela.txt'\n");
      }

    }

  }

  while(1){

    // Opcije

    printf("\n(1) Unos novog tima\n");
    printf("(2) Korigovanje parametara kluba\n");
    printf("(3) Pretrazi tabelu\n");
    printf("(4) Trenutno stanje na tabeli\n");
    printf("(5) Izlaz\n");
    printf("\nIzaberite opciju: ");

    opcija = (char*)malloc(n_bajtova);

    getline(&opcija, &n_bajtova, stdin);

    // Unos novog tima

    if(opcija[0] == '1'){

      printf("\nUnesi ime novog tima: ");

      ime = (char*)malloc(n_bajtova);

      getline(&ime, &n_bajtova, stdin);

      pointer = strtok(ime, "\n");

      struct klub k1;

      strcpy(k1.ime_kluba, pointer);

      k1.br_bodova = 0;
      k1.br_odigranih_utakmica = 0;
      k1.br_primljenih_golova = 0;
      k1.br_datih_golova = 0;

      klubovi[br_klubova] = k1;

      br_klubova++;

      free(ime);

    }

    // Korigovanje parametara kluba

    if(opcija[0] == '2'){

      printf("\nUnesi domaci tim: ");

      domacin = (char*)malloc(n_bajtova);

      getline(&domacin, &n_bajtova, stdin);

      domacin = strtok(domacin, "\n");

      printf("\nUnesi gostujuci tim: ");

      gost = (char*)malloc(n_bajtova);

      getline(&gost, &n_bajtova, stdin);

      gost = strtok(gost, "\n");

      printf("\nUnesi rezultat utakmice u formatu 'x:y': ");

      ime = (char*)malloc(n_bajtova);

      getline(&ime, &n_bajtova, stdin);

      sscanf(ime, "%d:%d", &dom_gol ,&gost_gol);

      free(ime);

      printf("%s i %s", domacin, gost);

      for(int i = 0; i < br_klubova; i++){

        // Domaci klub

        if(strcmp(domacin, klubovi[i].ime_kluba) == 0){

          klubovi[i].br_datih_golova += dom_gol;

          klubovi[i].br_primljenih_golova += gost_gol;

          klubovi[i].br_odigranih_utakmica++;

          if(dom_gol > gost_gol){

            klubovi[i].br_bodova += 3;
          }

          if(dom_gol == gost_gol){

            klubovi[i].br_bodova++;
          }

        }

        // Gostujuci klub

        if(strcmp(gost, klubovi[i].ime_kluba) == 0){

          klubovi[i].br_datih_golova += gost_gol;

          klubovi[i].br_primljenih_golova += dom_gol;

          klubovi[i].br_odigranih_utakmica++;

          if(gost_gol > dom_gol){

            klubovi[i].br_bodova += 3;
          }

          if(dom_gol == gost_gol){

            klubovi[i].br_bodova += 1;
          }

        }

      }

    }

    // Trenutno stanje tabele

    if(opcija[0] == '4'){

      printf("\nPOREDAK        TIM        OU        G        B\n");
      
      for(int i = 0; i < br_klubova; i++){
      
        printf("%d.             %s"
               "     %d"
               "        %d:%d"
               "      %d\n", poredak, klubovi[i].ime_kluba, klubovi[i].br_odigranih_utakmica, klubovi[i].br_datih_golova, klubovi[i].br_primljenih_golova, klubovi[i].br_bodova);

        poredak++;

      }

    }

    // Izlaz

    if(opcija[0] == '5'){

      fajl_tok = fopen(ime_fajla, "a+");

      if(fajl_tok == NULL){

        printf("Problem pri otvaranju fajla 'tabela.txt'\n");
      }

      for(int i = 0; i < br_klubova; i++){

        fprintf(fajl_tok, "%s,%d,%d,%d,%d\n", klubovi[i].ime_kluba, klubovi[i].br_bodova, klubovi[i].br_datih_golova, klubovi[i].br_primljenih_golova, klubovi[i].br_odigranih_utakmica);
      } // for()

      if(fclose(fajl_tok)){

        printf("Problem pri zatvaranju fajla 'tabela.txt'\n");
      }

      fajl_tok2 = fopen(ime_fajla2, "a+");

      if(fajl_tok2 == NULL){

        printf("Problem pri otvaranju fajla 'tabela.txt'\n");
      }

      fprintf(fajl_tok2, "%d,%d\n", br_klubova, poredak);

      if(fclose(fajl_tok2)){

        printf("Problem pri zatvaranju fajla 'fajl_tok2'\n");
      }

      break;

    } // if(opcija[0] == '5')

    free(opcija);

  } // while()

} // main()
