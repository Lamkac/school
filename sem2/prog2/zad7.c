// Jan Kucan 85917

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 200 // maximalna dlzka pre output/input
#define MASK '*'
#define REPLACE "/"

int main(int argc, char* argv[])
{
	
	int filter = -1;
	
	char *filters[argc-1][2]; // filtre
	char *words; // odkaz na aktualne slovo vo vete
	
	char input[MAX_LENGTH];
	char output[MAX_LENGTH];
	// priprava filtrov
	for(int i = 1; i < argc; i++){
		filters[i-1][0] = strtok(argv[i],REPLACE);
		filters[i-1][1] = strtok(NULL,REPLACE);
	}
	// citat postupne kazdu vetu
	while (fgets(input, sizeof input, stdin) != NULL){
		// odstrani novy riadok ak je
		if(input[strlen(input)-1] == '\n')
			input[strlen(input)-1] = 0;
		// resetne output
		output[0] = 0;
		words = strtok(input," "); // rozdeli vetu na slova a pripravy prve slovo
		
		while(words != NULL){
			filter = -1; // reset - ziadna zhoda
			for(int i = 0; i < argc-1; i++){
				// ak je rovnake ako filter
				if(strcmp(words,filters[i][0])==0) {
					filter = i;
					break;
				}
			}
			// ak je filter
			if(filter >= 0){
				
				if(filters[filter][1] == NULL){
					// ak je len maskovanie
					for(int i = 0; i < strlen(words); i++)
						words[i] = MASK;
					strcat(output,words);
				}else{
					// zmeni slovo
					strcat(output,filters[filter][1]);
				}
				
			}else{
				// inak len skopiruje slovo
				strcat(output,words);
			}
			strcat(output," "); // prida medzeru
			// dalsie slovo
			words = strtok(NULL," ");
		}
		
		printf("%s\n",output);
		
	}
	
	return 0;
}
