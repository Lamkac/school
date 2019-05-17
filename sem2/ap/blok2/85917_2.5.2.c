// Jan Kucan 85917

#include <stdio.h>
#include <windows.h>

const unsigned char RightDown = 217;
const unsigned char LeftDown = 192;
const unsigned char RightUp = 191;
const unsigned char LeftUp = 218;
const unsigned char Hline = 196;
const unsigned char Vline = 179;
const unsigned char LeftTree = 180;
const unsigned char RightTree = 195;
const unsigned char DownTree = 194;
const unsigned char UpTree = 193;
const unsigned char Cross = 197;

typedef struct{
	char name[100];
	char size[100];
	char weight[100];
	char tl[100];
	
} Info;

void printXChars(char c, int count){
	for(int i = 0; i < count; i++)
		printf("%c",c);
}

void printValue(HANDLE *hConsole,COORD *point, int defaultColor, int textColor,char key[], char value[],int keySize,int valueSize, char line){

	point->Y++;
	SetConsoleCursorPosition(*hConsole, *point);
	
	SetConsoleTextAttribute(*hConsole, defaultColor);
	putchar(line);
	
	SetConsoleTextAttribute(*hConsole, textColor);
	printf("%s%*c",key,keySize-strlen(key),' ');
	
	SetConsoleTextAttribute(*hConsole, defaultColor);
	putchar(line);
	
	SetConsoleTextAttribute(*hConsole, textColor);
	printf("%*c%s",valueSize-strlen(value),' ',value);
	
	SetConsoleTextAttribute(*hConsole, defaultColor);
	putchar(line);
	
}

void printLine(HANDLE *hConsole,COORD *point, int color,char start, char end, char middle, char fill, int keySize, int valueSize){

	point->Y++;
	SetConsoleCursorPosition(*hConsole, *point);
	
	SetConsoleTextAttribute(*hConsole, color);
	
	putchar(start);
	printXChars(fill, keySize);
	putchar(middle);
	printXChars(fill, valueSize);
	putchar(end);
	
}

void printTable(int x, int y,char title[], Info *info){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	int defaultColor = FOREGROUND_GREEN | FOREGROUND_RED;
	int textColor = FOREGROUND_GREEN;
	
	int maxLenKey = 10;
	int maxLenValue = 0;
	
	maxLenValue = strlen(info->name);
	if(strlen(info->size)>maxLenValue) maxLenValue = strlen(info->size);
	if(strlen(info->weight)>maxLenValue) maxLenValue = strlen(info->weight);
	if(strlen(info->tl)>maxLenValue) maxLenValue = strlen(info->tl);
	maxLenValue++;
	
	int width = maxLenKey + maxLenValue + 3;
	
	COORD point = {x,y};
	SetConsoleCursorPosition(hConsole, point); 
	
	// top
	SetConsoleTextAttribute(hConsole, defaultColor);
	putchar(LeftUp);
	int offestStart = width/2 - (strlen(title)/2) - 3;
	printXChars(Hline, offestStart);
	SetConsoleTextAttribute(hConsole, textColor);
	printf(" %s ",title);
	SetConsoleTextAttribute(hConsole, defaultColor);
	printXChars(Hline, width - offestStart-strlen(title) - 4);
	putchar(RightUp);
	
	printLine(&hConsole,&point,defaultColor, RightTree,LeftTree,DownTree,Hline,maxLenKey,maxLenValue);
	// meno
	printValue(&hConsole,&point,defaultColor,textColor,"Meno",info->name,maxLenKey,maxLenValue,Vline);
	
	printLine(&hConsole,&point,defaultColor, RightTree,LeftTree,Cross,Hline,maxLenKey,maxLenValue);
	// vyska
	printValue(&hConsole,&point,defaultColor,textColor,"Vyska",info->size,maxLenKey,maxLenValue,Vline);
	
	printLine(&hConsole,&point,defaultColor,RightTree,LeftTree,Cross,Hline,maxLenKey,maxLenValue);
	// hmotnost
	printValue(&hConsole,&point,defaultColor,textColor,"Hmotnost",info->weight,maxLenKey,maxLenValue,Vline);
	
	printLine(&hConsole,&point,defaultColor,RightTree,LeftTree,Cross,Hline,maxLenKey,maxLenValue);
	// hmotnost
	printValue(&hConsole,&point,defaultColor,textColor,"Tel.",info->tl,maxLenKey,maxLenValue,Vline);
	
	printLine(&hConsole,&point,defaultColor,LeftDown,RightDown,UpTree,Hline,maxLenKey,maxLenValue);
	
	point.Y++;
	SetConsoleCursorPosition(hConsole, point);
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main(int argc, char* argv[]){
  system("cls");
  
  Info info = {"Nejake menoooooooooooo","180 cm","70 kg", "0915 123 456"};
  printTable(5,5,"Zaznam xx",&info);
  
  printf("Stlac ENTER a skoncime...\n");
  scanf("?");
  return(0);
}