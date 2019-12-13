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
  char znak;
  size_t n_bajtova = 15;
  int br_klubova = 0;
  int poredak = 1;
  int j = 0;
  int dom_gol;
  int gost_gol;
  int x;
  int x1, y1;
  
  struct klub{
    
    char ime_kluba[15];
    int br_bodova;
    int br_datih_golova;
    int br_primljenih_golova;
    int br_odigranih_utakmica;

  };

  struct klub klubovi[10];

  struct klub temp;

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

      ime = strtok(ime, "\n");

      struct klub k1;

      strcpy(k1.ime_kluba, ime);

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

    // Pretraga po broju osvojenih bodova

    if(opcija[0] == '3'){

      printf("Pretrazi klubove po broju osvojenih bodova"
             " u formatu 'x,>' ili 'x,<': ");

      ime = (char*)malloc(n_bajtova);

      getline(&ime, &n_bajtova, stdin);

      sscanf(ime, "%d,%c", &x, &znak);

      free(ime);

      printf("\nTIM       BODOVI\n");

      if(znak == '<'){

        for(int i = 0; i < br_klubova; i++){

          if(klubovi[i].br_bodova < x){

            printf("%s      %d\n", klubovi[i].ime_kluba,
                                   klubovi[i].br_bodova);
          }

        }

      }

      if(znak == '>'){

        for(int i = 0; i < br_klubova; i++){

          if(klubovi[i].br_bodova > x){

            printf("%s      %d\n", klubovi[i].ime_kluba,
                                   klubovi[i].br_bodova);
          }

        }

      }

    }

    // Trenutno stanje tabele

    if(opcija[0] == '4'){

      poredak = 1;

      for(int i = 0; i < br_klubova - 1; i++){

        for(j = 0; j < br_klubova - i - 1; j++){

          x1 = klubovi[j].br_datih_golova - klubovi[j].br_primljenih_golova;
          y1 = klubovi[j+1].br_datih_golova - klubovi[j+1].br_primljenih_golova;

          if(x1 < y1){

            //Zameni(klubovi[j], klubovi[j+1]);
            
            temp = klubovi[j];
            klubovi[j] = klubovi[j+1];
            klubovi[j+1] = temp;

          }

        } 

      } 

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

      break;

    } // if(opcija[0] == '5')

    free(opcija);

  } // while()

} // main()
