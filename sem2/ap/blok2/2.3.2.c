#include <stdio.h>

int main(){

	FILE *fread;
	FILE *fwrite;
	
	fread = fopen("koniec.htm","rb");
	fwrite = fopen("koniec_r.htm","wb");
	
	char c = getc(fread);
	while(c != EOF){
		putc(c^27,fwrite);
		c = getc(fread);
	}
	
	fclose(fread);
	fclose(fwrite);
	
	return 0;
}