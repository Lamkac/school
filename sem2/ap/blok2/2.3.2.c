#include <stdio.h>

int main(){

	FILE *fread;
	FILE *fwrite;
	
	fread = fopen("koniec.htm","rb");
	fwrite = fopen("koniec_r.htm","wb");
	
	char c = 0;
	while(c != EOF){
		c = getc(fread);
		
		c ^= 27;
		
		putc(c,fwrite);
	}
	
	fclose(fread);
	fclose(fwrite);
	
	return 0;
}