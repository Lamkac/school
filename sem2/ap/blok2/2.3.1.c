#include <stdio.h>

int main(){

	char iso[] = {165,169,171,174,181,185,187,190};
	char windows[] = {188,138,141,142,190,154,157,158};

	FILE *fread;
	FILE *fwrite;
	
	fread = fopen("poviedka.htm","r");
	fwrite = fopen("poviedka_r.htm","w");
	
	char c = 0;
	while(c != EOF){
		c = getc(fread);
		
		for(int i = 0; i < 8; i++){
			if(c == iso[i]){
				c = windows[i];
				break;
			}
		}
		
		putc(c,fwrite);
	}
	
	fclose(fread);
	fclose(fwrite);
	
	return 0;
}