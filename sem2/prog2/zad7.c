#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int main(int argc, char* argv[])
{
	
	int filter = -1;
	char *filters[argc-1][2];
	char *words;
	
	char input[MAX_LENGTH];
	char output[MAX_LENGTH];
	
	for(int i = 1; i < argc; i++){
		filters[i-1][0] = strtok(argv[i],"/");
		filters[i-1][1] = strtok(NULL,"/");
	}
	
	while (fgets(input, sizeof input, stdin) != NULL){
		
		if(input[strlen(input)-1] == '\n')
			input[strlen(input)-1] = 0;

		output[0] = 0;
		words = strtok(input," ");
		
		while(words != NULL){
			filter = -1;
			for(int i = 0; i < argc-1; i++){
				
				if(strcmp(words,filters[i][0])==0) {
					filter = i;
					break;
				}
			}
			
			if(filter >= 0){
				
				if(filters[filter][1] == NULL){
					for(int i = 0; i < strlen(words); i++)
						words[i] = '*';
					strcat(output,words);
				}else{
					strcat(output,filters[filter][1]);
				}
				
			}else{
				strcat(output,words);
			}
			strcat(output," ");
			
			words = strtok(NULL," ");
		}
		
		printf("%s\n",output);
		
	}
	
	return 0;
}
