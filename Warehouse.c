
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


struct plats_t{
  char hylla;
  int plats;
};

struct vara_t {
  bool exists;
  char *namn;
  char *besk;
  struct plats_t plats;
  int pris;
  int antal;
};

typedef struct db{
  struct vara_t vara[10];
  int antal;
}*db_t;


/**
 * @brief Clears the standard input.
 */

void clear() {
  while (getchar() != '\n'); // Clear stdin
}

/**
 * @brief
 */
void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

/**
 * @brief Prints a list of choices.
 */
void print_main_meny(){
  printf ("V�lkommen till lagerhantering 2.0\n");
  printf ("=================================\n");
  printf ("[L]�gga till en vara\n");
  printf ("[T]a bort en vara\n");
  printf ("[R]edigera en vara\n");
  printf ("�n[g]ra senaste �ndringen\n");
  printf ("Lista [h]ela varukatalogen\n");
  printf ("[A]vsluta\n");
  printf ("\n\n\n\n");
  printf ("Vad vill du g�ra idag?_\n");
}

/**
 * @brief Adds an item to the first available position in a given database.
 * @param db - The database in which the item will be added to.
 * @param varan - The item to be added to the database.
 */

void add_to_db(db_t db, struct vara_t varan) {
  db->vara [db->antal++] = varan;
}

/**
 * @brief Asks the user a question on which the user will
 */
char ask_char_question(char *question, char *alternative){

printf("%s [%s]\n",question, alternative);

while (true) {
    char reply;
    scanf("%c",&reply);

      if (strchr(alternative,reply)) {

	return tolower(reply);

      } else {

	printf ("Felaktigt svar, pr�va [%s] \n",alternative);
      }
 }
}

char* ask_string_question (char *question) {

  char buffer[128];
  printf("%s", question);
  readline(buffer, 128, stdin);
  char *svar = malloc(strlen(buffer) + 1);
  strcpy(svar, buffer);
  return svar;
}

int ask_int_question (char *question) {
  int svar;
  int sv;
  bool cont = false;
  printf("%s", question);
  scanf("%d", &svar);

  return svar;
}

void print_item(struct vara_t vara) {
  printf ("\nName: %s\nBeskrivning: %s\nPlats: %d\nPris: %d\nPlats: %d\nHylla: %s\n\n", vara.namn,vara.besk,vara.antal,vara.pris,vara->plats.plats,vara->plats.hylla);
    }


int delete_item(db_t db) {

  char* svar = ask_string_question("Vilken vara vill du ta bort?: ");
  int i = 0;
  while(db->antal > i) {
    if(strcmp(svar,db->vara[i].namn) == 0) {
      db->vara[i].exists = false;
      return i;
    }
    i++;
  }
  return i;
}




void regret(db_t database, db_t angralista, int index, int angracase) {

  switch (angracase) {
  case 1:
    printf("Du tog bort vara %s \n\n", angralista->vara[0].namn);
    database->vara[database->antal-1].exists = false;
    break;

  case 2:
    printf("Du tog tillbaka vara %s \n\n", angralista->vara[0].namn);
    angralista->vara[0].exists = true;
    database->vara[index] = angralista->vara[0];
   break;

 case 3:
   printf("Du �ngrade din �ndring p� vara %s \n\n", angralista->vara[0].namn);
   database->vara[index] = angralista->vara[0];
   break;
  default: printf("eh?");
  }


}


void Printeditlist() {

  printf ("[N]amn\n");
  printf ("[B]eskrivning\n");
  printf ("[P]ris\n");
  printf ("[L]agerhylla\n");
  printf ("An[T]al\n\n");
  printf ("V�lj rad eller [A]vbryt\n");
}

int returnTrueIndex(db_t db, int index) {
  int i = 0;
  int hidden = 0;
  if(index == 0 ) {return 0;}
  while(db->antal > i) {
    if(db->vara[hidden].exists == true) {
      i++;
      hidden++;

      if(index == i) {
	return hidden;
      }
    }
    else { hidden++; }
  }
  return hidden;
}

void listItems(db_t db) {
  int i = 1;
  int hidden = 0;
  int valvara;
  while(db->antal > hidden) {
    if(db->vara[hidden].exists == true) {
      printf("%d %s",i, db->vara[hidden].namn);
      printf("\n");
      i++;
      hidden++;
    } else {hidden++;}
  }
}

void showListItems(db_t db) {
  int i = 1;
  int hidden = 0;
  int valvara;
  while(db->antal > hidden) {
    if(db->vara[hidden].exists == true) {
      printf("%d %s",i, db->vara[hidden].namn);
      printf("\n");
      i++;
      hidden++;
    } else {hidden++;}
  }

  int index = ask_int_question("Vilken produkt vill du visa?: (ange siffra)\n");
  int realindex = returnTrueIndex(db, index);
  print_item(db->vara[realindex-1]);

}



int edit_item(db_t db, db_t regretlist) {
  bool s_continue = true;
  char val;
  int realindex;

  while(s_continue){

    listItems(db);

    if(ask_char_question("Vill du redigera en vara? ", "YyNn") == 'y') {
      int index = ask_int_question("Vilken produkt vill du redigera?: (ange siffra)\n");
      realindex = returnTrueIndex(db, index);

    }
    int nyttantal;
    int nyttpris;
    int nyplats;
    printf("Vad vill du �ndra? eller avbryt\n");
    Printeditlist();
    clear();
    scanf("%c",&val);
    clear();

    switch(tolower(val)) {
    case'n':
      printf("Nuvarande namn: %s\n", db->vara[realindex-1].namn);
      regretlist->vara[0] = db->vara[realindex-1];
      db->vara[realindex-1].namn = ask_string_question("Skriv in nytt namn: ");
      break;
    case'b':
      printf("Nuvarande beskrivning: %s \n", db->vara[realindex-1].besk);
      regretlist->vara[0] = db->vara[realindex-1];
      db->vara[realindex-1].besk = ask_string_question("Skriv in ny beskrivning: ");

      break;
    case'p':
      printf("Nuvarande pris: %d \n", db->vara[realindex-1].pris);
      printf("Skriv in ett nytt pris\n");
      scanf("%d", &nyttpris);
      regretlist->vara[0] = db->vara[realindex-1];
      db->vara[realindex-1].pris = nyttpris;
     break;
    case'l': //NYTT!
    	printf("Nuvarande lagerhylla: %c%d", db->vara[realindex-1]->plats.hylla, db->vara[realindex-1]->plats.plats);
    	regretlist->vara[0] = db->vara[realindex-1];
    	printf("Skriv in ny hylla: \n");
    	db->vara[realindex-1]->plats.hylla = scanf("%c", &val);
        clear();
        printf("Skriv in ny plats: \n");
        db->vara[realindex-1]->plats.plats = scanf("%d", &nyplats);
      break;
    case't':
      printf("Nuvarande antal: %d \n", db->vara[realindex-1].antal);
      printf("Skriv in ett nytt antal varor\n");
      scanf("%d", &nyttantal);
      regretlist->vara[0] = db->vara[realindex-1];
      db->vara[realindex-1].antal = nyttantal;
      clear();
      break;
    case'a':
      s_continue = false;
      break;
    default: printf("Felaktigt val!\n");
    }
  }
  return realindex-1;

}

void add_item(db_t db) {
  struct vara_t vara;
  vara.namn = ask_string_question("Namn: ");
  vara.besk = ask_string_question("Beskrivning: ");
  vara.antal = ask_int_question("Antal: ");
  vara.pris = ask_int_question("Pris: ");
  vara->plats.hylla = ask_char_question("Hylla: "); //HÄR!
  vara->plats.plats = ask_int_question("Plats: "); //HÄR!
  clear();


  if (ask_char_question("Spara till DB", "YyNn") == 'y')
  {
    vara.exists = true;
    add_to_db(db, vara);

  }
  clear();
}




int main(int argc, char *argv[]){
  char val;
  bool should_continue = true;
  int index;
  db_t regretlist = malloc(sizeof(struct vara_t)+1);
  db_t databas = malloc(sizeof(struct db));
  int angracase;

  while (should_continue) {
    print_main_meny();
    scanf("%c", &val);
    clear();

    switch (tolower(val)){
    case 'l':
      add_item(databas);
      regretlist->vara[0] = databas->vara[databas->antal-1];
      angracase = 1;
      break;
    case 't':
      index = delete_item(databas);
      regretlist->vara[0] = databas->vara[index];
      angracase = 2;
      break;
    case 'r':
      index = edit_item(databas, regretlist);
      angracase = 3;
      break;
    case 'g':
      regret(databas, regretlist, index, angracase);
      break;
    case 'h':
      showListItems(databas);
      break;
    case 'a':
      should_continue=false;
      break;
    default: printf("Fel inmatning,v�nligen f�rs�k igen\n");
    }



  }
  return 0;
}

