// Jan Kucan 85917

#include "stdafx.h"

#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#define DEFAULT_BUFFER_LEN 4096

int connectToServer(SOCKET *ConnectSocket, char* ip, char* port) {

	// init
	WSADATA wsaData; //struktura WSADATA pre pracu s Winsock
	int status_result;

	// Initialize Winsock
	status_result = WSAStartup(MAKEWORD(2, 2), &wsaData); //zakladna inicializacia
	if (status_result != 0) {
		printf("WSAStartup failed : %d\n", status_result);
		return 0;
	}

	struct addrinfo *result = NULL, *ptr = NULL; //struktura pre pracu s adresami
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP; //pracujeme s protokolom TCP/IP

									 // Resolve the server address and port
	status_result = getaddrinfo(ip,port, &hints, &result);
	if (status_result != 0) {
		printf("getaddrinfo failed : %d\n", status_result);
		WSACleanup();
		return 0;
	}
	else {
		printf("getaddrinfo didn't fail\n");
	}

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = result;

	// Create a SOCKET for connecting to server => pokus o vytvorenie socketu
	*ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (*ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket() : %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 0;
	}
	else {
		printf("Error at socket DIDN'T occur\n");
	}
	// Connect to server. => pokus o pripojenie sa na server

	status_result = connect(*ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (status_result == SOCKET_ERROR)
		printf("Not connected to server\n");
	else
		printf("Connected to server!\n");

	if (status_result == SOCKET_ERROR) {
		closesocket(*ConnectSocket);
		*ConnectSocket = INVALID_SOCKET;
		WSACleanup();
		return 0;
	}

	Sleep(2000);

	return 1;
}

void disconnectFromServer(SOCKET *ConnectSocket) {
	printf("Disconnecting from server!\n");
	closesocket(*ConnectSocket);
	WSACleanup();
}

int sendMessage(FILE *file, SOCKET *ConnectSocket, char* message) {

	int status_result = send(*ConnectSocket, message, (int)strlen(message), 0);
	if (status_result == SOCKET_ERROR)
	{
		printf("send failed : %d\n", WSAGetLastError());
		closesocket(*ConnectSocket);
		WSACleanup();
		return 0;
	}

	fprintf(file, "Poslane:\n");
	fprintf(file, message);
	fprintf(file, "\n");

	return 1;
}

int recieveMessage(FILE *file, SOCKET *ConnectSocket, char* recieve_buffer, int len) {
	int status_result = recv(*ConnectSocket, recieve_buffer, len, 0);

	if (status_result > 0) {

		fprintf(file, "prijate:\n");
		fprintf(file, recieve_buffer);
		fprintf(file, "\n");

		return 1;
	} else if (status_result == 0) {
		printf("Connection closed\n"); //v tomto pripade server ukoncil komunikaciu
		return 0;
	} else {
		printf("recv failed with error : %d\n", WSAGetLastError()); //ina chyba
		return 0;
	}

}

void printMessage(HANDLE *hConsole, char *message, char *title, int offset, int len) {

	int line = 4;
	int tempLen = 0;

	COORD point = { offset, line - 1 };
	SetConsoleCursorPosition(*hConsole, point);
	printf("%s", title);

	point.X = offset + tempLen;
	point.Y = line;

	char *word;
	word = strtok(message, " ");

	while (word != NULL) {

		if (tempLen + strlen(word) > len) {
			line++;
			tempLen = 0;
			continue;
		}

		point.X = offset + tempLen;
		point.Y = line;
		SetConsoleCursorPosition(*hConsole, point);
		printf("%s",word);

		tempLen += strlen(word) + 1;

		word = strtok(NULL, " ");

	}

}

void printMessages(HANDLE *hConsole, char *messageLeft, char *messageRight) {

	printMessage(hConsole, messageLeft, "Poslane:", 2, 58);
	printMessage(hConsole, messageRight, "Prijate:", 63, 56);

	COORD point = {1, 1};
	SetConsoleCursorPosition(*hConsole, point);
	
	printf(" Poslat: ");

}

int parseCommnad(char *command) {

	char *temp;
	temp = strtok(command, " ");

	if (!strcmp(temp, "exit")) {
		return -1;
	} else if (!strcmp(temp, "decode")) {
		return 1;
	}else if (!strcmp(temp, "prime")) {
		return 2;
	}

	return 0;
}

void decode(char *message, int key, int n) {

	for (int i = 0; i < n; i++)
		message[i] ^= key;

	message[n] = 0;
}

char* decodePrime(char *message) {

	int m = 0;
	char newMessage[DEFAULT_BUFFER_LEN];

	for (int i = 1; i < strlen(message); i++) {

		int del = 0;
		for (int j = 2; j <= (i + 1); j++) {

			if (!((i + 1) % j))
				del++;

		}
		if (del < 2) {
			newMessage[m] = message[i];
			m++;
		}
	}
	newMessage[m] = 0;
	return newMessage;

}

int main() {

	FILE *file;
	int recieve_buffer_len = DEFAULT_BUFFER_LEN;
	char recieve_buffer[DEFAULT_BUFFER_LEN] = "";
	char send_buffer[DEFAULT_BUFFER_LEN] = "";
	char command_buffer[DEFAULT_BUFFER_LEN] = "";
	int status_result;
	char *pToNewLine;
	char *temp;
	int result;

	file = fopen("\\\\home31.cpu2.fei.stuba.sk\\users\\roc2018\\xkucan\\Documents\\zaznam.txt", "w");
	if (file == NULL) {
		printf("Error opening file");
		return 0;
	}

	SOCKET ConnectSocket = INVALID_SOCKET;

	SetConsoleOutputCP(CP_UTF8);

	// farba
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int defaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	int textColor = FOREGROUND_GREEN;
	SetConsoleTextAttribute(hConsole, textColor);

	if (!connectToServer(&ConnectSocket, "147.175.115.34", "777"))
		return 1;

	while (1) {

		system("cls");
		printMessages(&hConsole, send_buffer, recieve_buffer);

		// posielanie dat
		scanf("%[^\n]s", command_buffer);
		getchar();

		result = parseCommnad(command_buffer);

		if (result < 0) {
			break;
		}else if (result) {

			if (result == 1) {

				temp = strtok(NULL, " ");
				char *send = temp;

				temp = strtok(NULL, " ");
				int key = atoi(temp);

				temp = strtok(NULL, " ");
				int len = atoi(temp);

				if (!sendMessage(file, &ConnectSocket, send))
					break;
				if (!recieveMessage(file, &ConnectSocket, recieve_buffer, recieve_buffer_len))
					break;

				decode(recieve_buffer, key, len);

			}
			else if (result == 2) {

				if (!sendMessage(file, &ConnectSocket, decodePrime(recieve_buffer)))
					break;
				if (!recieveMessage(file, &ConnectSocket, recieve_buffer, recieve_buffer_len))
					break;

			}

		}else{

			strcpy(send_buffer,command_buffer);

			if (!sendMessage(file, &ConnectSocket, send_buffer))
				break;

			// primanie dat
			if (!recieveMessage(file, &ConnectSocket, recieve_buffer, recieve_buffer_len))
				break;

			pToNewLine = strchr(recieve_buffer, '\n');
			*pToNewLine = 0;

		}
	}

	// zavretie socketu
	disconnectFromServer(&ConnectSocket);
	// reset farby
	SetConsoleTextAttribute(hConsole, defaultColor);
	// zavriet subor
	fclose(file);
	
	system("cls");

    return 0;
}

