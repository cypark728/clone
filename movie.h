#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIES 5 // The maximum number that can be stored in memory.

//Define the type of movie record, and compose the contents of that type.

typedef struct st_movie{
    char title[30];
    char genre[30];
    char distri[30];
    char age[30];
    char state[30];
} T_Movie;

int mv_is_available();
int mv_firste_available();
void mv_init();
int mv_count();

//Below fuctions are used in (1)create menu. (First using place)

T_Movie* mv_search_by_title(char *t);

int mv_valid_about_genre(char *g);
int mv_valid_about_age(int a);
int mv_valid_about_age_file(char* a);
int mv_valid_about_state(int s);
int mv_valid_about_state_file(char* s);

void mv_create(char *t, char *g, char *d, int a, int s);
void mv_create_by_file(char *t, char *g, char *d, char *a, char *s);

//Below functions are used in (2)read menu. + list menu

char* mv_get_title(T_Movie* p);
char* mv_get_genre(T_Movie* p);
char* mv_get_distri(T_Movie* p);
char* mv_get_age(T_Movie* p);
char* mv_get_state(T_Movie* p);

// Below function are used in menus related to update.
void mv_update(T_Movie* p, char* g, char* d, int a, int s);
void mv_update_by_genre(T_Movie* p, char* g);
void mv_update_by_distri(T_Movie* p, char* d);
void mv_update_by_age(T_Movie* p, int a);
void mv_update_by_state(T_Movie* p, int s);
char* get_state(int s);

// Bello functions are used in menus related to delete.
void mv_delete(T_Movie* p);

// for save report 
int mv_get_titles_save(char* mt[]);
int mv_get_distris_save(char* md[]);
// end

void mv_get_all(T_Movie* a[]);
int mv_get_some_by_genre(T_Movie* a[], char* g);
int mv_get_some_by_distri(T_Movie* a[], char* d);
int mv_get_some_by_age(T_Movie* a[], int age);
int mv_get_some_by_state(T_Movie* a[], int s);

char* mv_to_string(T_Movie* p);
 
//Below functions are used in menus related to statistics or file

void print_statistics(int g[], int a[], int s[]);
void save_statistics(char* filename, int g[], int a[], int s[]);
void mv_count_genre(int g[]);
void mv_count_age(int a[]);
void mv_count_state(int s[]);

const int get_genre_size();
const int get_age_size();
const int get_state_size();

//Below functions are use in file menu

char* mv_to_string_save(T_Movie* p);
void report_about_titles(FILE* f);
void report_about_states(FILE* f);
void report_about_genres(FILE* f);
void report_about_ages(FILE* f);
void report_about_distris(FILE* f);
