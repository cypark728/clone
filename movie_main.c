#include <stdio.h>
#include "movie.h"

void create_mv_record();
void read_mv_record();
void update_mv_record();
void update_mv_record_by_distri();
void delete_mv_record();
void delete_mv_record_by_distri();
void list_mv_record();
void tidy_up_mv_record();
void sort_mv_record();
void print_statistics_mv_record();
void save_statistics_mv_record();
void load_mv_file();
void save_mv_file();
void make_mv_report();

int main(){
    mv_init();
    int menu;
    while(1){
        printf("\nMenu : 1.Create 2.Read 3.Update 4.Update by distributor 5.Delete 6.Delete by distributor 7.List\n"); 
		printf("       8.Tidy up 9.Sort 10.Print statistics 11.Save statistics 12.Load 13.Save 14.Report 0.Quit > ");
	menu = -1;
	scanf("%d", &menu);
	printf("\n");
	getchar();
	
	switch(menu){
	    case 1:
			create_mv_record();
			break;
	    case 2:
			read_mv_record();
	        break;
	    case 3:
			update_mv_record();
			break;
	    case 4:
			update_mv_record_by_distri();
			break;
	    case 5:
			delete_mv_record();
			break;
	    case 6:
			delete_mv_record_by_distri();
			break;
	    case 7:
			list_mv_record();
			break;
	    case 8:
			tidy_up_mv_record();
			break;
	    case 9:
			sort_mv_record();
			break;
	    case 10:
			print_statistics_mv_record();
			break;
	    case 11:
			save_statistics_mv_record();
	     	break;
	    case 12:
			load_mv_file();
			break;
	    case 13:
			save_mv_file();
			break;
	    case 14:
			make_mv_report();
			break;
	    case -1:
			printf("\nInvalid Menu. Enter a Right Menu.\n");
			break;
	    case 0:
			return 0;
	    }
	}
	return 0;
}

void create_mv_record(){

    if(!mv_is_available()){
	printf("There is no space!\n");
	return;
    }
   
    char title[30], genre[30], distri[30];
    int age, state;
    
    printf("Enter a new movie's info.\n");
    printf("Title > ");
    fgets(title, sizeof(title), stdin);
    title[strlen(title)-1] = '\0';
   
    if(mv_search_by_title(title)){
	printf("Duplicated title!\n");
	printf("Going back to menu...\n");
	return;
    }	
    
    printf("Genre -  Action / Melo / Thriller / Comedy / Mystery / Adventure / SF / Fantasy (Caution at the Capital letter) > ");
    do{
        fgets(genre, sizeof(genre), stdin);
        genre[strlen(genre)-1] = '\0';
	
        int valid = mv_valid_about_genre(genre);
        if(!valid){
	    printf("\nInvalid genre! Refer to the available genres.\n");
	    printf("Enter a right genre > ");
	    continue;
	}
        break;
    } while(1);

    printf("distributor > ");
    fgets(distri, sizeof(distri), stdin);
    distri[strlen(distri)-1] = '\0';
    
    printf("Minimum Viewing Age : 7 / 12 / 15 / 18 / 1(ALL) > ");
    do{
        scanf("%d", &age);
	int valid = mv_valid_about_age(age);
	if(!valid){
	    printf("\nInvalid mimimum viewing age! Refer to the available ages.\n");
	    printf("Enter a right miminum viewing age > ");
	    continue;
	}
	break;
    } while(1);
    
    printf("state : On screen - 1 / Due for release - 0 > ");
    do{
        scanf("%d", &state);
	int valid = mv_valid_about_state(state);
	if(!valid){
	    printf("\nInvalid state! Refer to the available states.\n");
	    printf("Enter a right state > ");
	    continue;
        }
	break;
    } while(1);
 
    mv_create(title, genre, distri, age, state);
}
    
void read_mv_record(){
    int option;
    printf( "Option (read by) : 1.Title 2.Genre 3. Distributor 4.Minimum Viewing Age 5.State> ");
    option = 0;
    scanf("%d", &option);
    getchar();

    switch(option){
	case 1:
	{
	    printf("This option will show a information of a movie.\n");
	    char title[30];
	    printf("\nEnter a title > ");
	    fgets(title, sizeof(title), stdin);
  	    title[strlen(title)-1] = '\0';
	   
	    T_Movie* p = mv_search_by_title(title);

	    if(p){
		printf("Movie info.\n");
	        printf("Title : %s\n", mv_get_title(p));
		printf("Genre : %s\n", mv_get_genre(p));
		printf("Distributor : %s\n", mv_get_distri(p));
		printf("Minimum viewing age : %s\n", mv_get_age(p));
		printf("State : %s\n", mv_get_state(p));
	    }
	    else{
		printf("No such movie!\n");
	    }

	    break;
	}

	case 2:
	{
	    char genre[30];
            printf("Enter a Genre -  Action / Melo / Thriller / Comedy / Mystery / Adventure / SF / Fantasy (Caution at the Capital letter) > ");
    	    fgets(genre, sizeof(genre), stdin);
            genre[strlen(genre)-1] = '\0';
	
	    if(!mv_valid_about_genre(genre)){
		printf("Invalid genre.\n");
		break;
	    }
	    
	    T_Movie* movies[MAX_MOVIES];

	    int size = mv_get_some_by_genre(movies, genre);
	    printf("%d movies are found!.\n", size);
	    for(int i = 0 ; i < size; i++){
		T_Movie* p = movies[i];
		printf("%d. %s\n", i+1, mv_to_string(p));
	    }

	    break;
	}

	case 3 : 
	{
	    char distri[30];
	    printf("Enter a distributor > ");	    
   	    fgets(distri, sizeof(distri), stdin);
    	    distri[strlen(distri)-1] = '\0';
	    
	  
	    T_Movie* movies[MAX_MOVIES];

	    int size = mv_get_some_by_distri(movies, distri);
	    printf("%d movies are found!.\n", size);
	    for(int i = 0 ; i < size; i++){
		T_Movie* p = movies[i];
		printf("%d. %s\n", i+1, mv_to_string(p));
	    }

	    break;
	}

	case 4:
	{
	    int age;
    	    printf("Enter a Minimum Viewing Age : 7 / 12 / 15 / 18 / 1(ALL) > ");
	    scanf("%d",&age);
	
	    if(!mv_valid_about_age(age)){
		printf("Invalid miminum viewing age.\n");
		break;
	    }
	    
	    T_Movie* movies[MAX_MOVIES];

	    int size = mv_get_some_by_age(movies, age);
	    printf("%d movies are found!.\n", size);
	    for(int i = 0 ; i < size; i++){
		T_Movie* p = movies[i];
		printf("%d. %s\n", i+1, mv_to_string(p));
	    }

	    break;
	}

	case 5:
	{
	    int state;
	    printf("Enter a state : On Screen - 1 / Due for Rrelease - 0 > ");
	    scanf("%d", &state);
	    
	    if(!mv_valid_about_state(state)){
		printf("Invalid state.\n");
		break;
	    }
	    
	    T_Movie* movies[MAX_MOVIES];

	    int size = mv_get_some_by_state(movies, state);
	    printf("%d movies are found!.\n", size);
	    for(int i = 0 ; i < size ; i++){
		T_Movie* p = movies[i];
		printf("%d. %s\n", i+1, mv_to_string(p));
	    }

            break;
	}

	default:
	    printf("Unvaild option.\n");
	    break;
    }
}	    

void update_mv_record(){
}

void update_mv_record_by_distri(){
}

void delete_mv_record(){
}

void delete_mv_record_by_distri(){
}

void list_mv_record(){
	
	printf("All movie records.\n");
	
	int size = mv_count();
	T_Movie* movies[MAX_MOVIES];

	mv_get_all(movies);

	for(int i = 0 ; i < size ; i++){
		T_Movie* p = movies[i];
		printf("%d. %s\n", i+1, mv_to_string(p));
	}
}


void tidy_up_mv_record(){

}

void sort_mv_record(){
}

void print_statistics_mv_record(){
	
	const int g_size = get_genre_size();
	const int a_size = get_age_size();
	const int s_size = get_state_size();

	int c_genre[g_size];
	int c_age[a_size];
	int c_state[s_size];
	
	mv_count_genre(c_genre);
	mv_count_age(c_age);
	mv_count_state(c_state);
#ifdef DEBUG
	printf("[DEBUG] Done of counting!\n");
	printf("[DEBUG] start printing...\n");
#endif
	print_statistics(c_genre, c_age, c_state);
}

void save_statistics_mv_record(){
	
	const int g_size = get_genre_size();
	const int a_size = get_age_size();
	const int s_size = get_state_size();
	
	int c_genre[g_size];
	int c_age[a_size];
	int c_state[s_size];
	
	mv_count_genre(c_genre);
	mv_count_age(c_age);
	mv_count_state(c_state);

#ifdef DEBUG
	printf("[DEBUG] Done of counting!\n");
#endif

	char filename[30];
	printf("Enter a filename to save > ");
	scanf("%s", filename);

	save_statistics(filename, c_genre, c_age, c_state);
}

void load_mv_file(){

	printf("All movie datas will be deleted and new movie records will be reloaded.\n");
	
	char filename[30];

	printf("\nEnter a filename to load > ");
	scanf("%s", filename); printf("\n");
	
	printf("Are you sure this process is going on?\n");
	printf("1.Yes 0.No > ");
	int answer; scanf("%d", &answer);
	if(answer!=1) return;
	else printf("\n");

	FILE* f = fopen(filename, "r");
	
	if(f==NULL){
		printf("Invalid file name! Back to the menu...\n");
		return;
	}
	
	mv_init();

	char title[30], genre[30], distri[30], age[30], state[30];
	int line = 0;

	while(!feof(f)){
		if(!mv_is_available()){
			printf("[Load] Line %d : there is no more space!\n", line+1);
			break;
		}

		char* isValid_t = fgets(title, sizeof(title), f);
		int result = fscanf(f, "%s %s %s ", genre, distri, age);
		char* isValid_s = fgets(state, sizeof(state), f);
		
		line+=2;
		
		if(isValid_t == NULL){
			break;
		}
		if(result<3) break;	
		if(isValid_s == NULL){
			break;
		}
	
		title[strlen(title)-1] = '\0';

		state[strlen(state)-1] = '\0';

		if(mv_search_by_title(title)){
			printf("[Load] Line %d : Duplicated title<%s>! keep loading...\n", line-1, title);
			continue;
		}
		if(!mv_valid_about_genre(genre)){
			printf("[Load] Line %d : Invalid genre<%s>! keep loading...\n", line, genre);
			continue;
		}
		if(!mv_valid_about_age_file(age)){
			printf("[Load] Line %d : Invalid minimum viewing age<%s>! keep loading...\n", line, age);
			continue;
		}
		if(!mv_valid_about_state_file(state)){
			printf("[Load] Line %d : Invalid state<%s>! keep loading...\n", line, state);
			continue;
		}
		mv_create_by_file(title, genre, distri, age, state);
#ifdef DEBUG
		printf("[DEBUG] load - %s\n", title);
#endif
	}
	printf("\n%d movies are read from file!\n", mv_count());
	fclose(f);
}

void save_mv_file(){
	
	char filename[30];
	printf("Enter a filename to save > ");
	scanf("%s", filename);

	FILE* f = fopen(filename, "w");
	int size = mv_count();
	T_Movie* movies[MAX_MOVIES];
	mv_get_all(movies);
	for(int i = 0 ; i<size; i++){
		T_Movie* p = movies[i];
		fprintf(f, "%s\n", mv_to_string_save(p));
	}
	printf("Movie data is now stored in %s!\n", filename);
	fclose(f);
}

void make_mv_report(){

	char filename[30];
	printf("Enter a filename to save report > ");
	scanf("%s", filename);

	FILE* f = fopen(filename, "w");
	
	fprintf(f, "Movie Report\n");
	fprintf(f, "--------------------\n\n");
	report_about_titles(f);
	fprintf(f, "--------------------\n\n");
	report_about_states(f);
	fprintf(f, "--------------------\n\n");
	report_about_genres(f);
	fprintf(f, "--------------------\n\n");
	report_about_ages(f);
	fprintf(f, "--------------------\n\n");
	report_about_distris(f);

	printf("Movie report is now saved in %s!\n", filename);
	fclose(f);
}
