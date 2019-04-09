// Blok3.cpp : Defines the entry point for the console application.
//

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

	Sleep(250);

	return 1;
}

void disconnectFromServer(SOCKET *ConnectSocket) {
	printf("Disconnecting from server!\n");
	closesocket(*ConnectSocket);
	WSACleanup();
}

int sendMessage(SOCKET *ConnectSocket, char* message) {

	int status_result = send(*ConnectSocket, message, (int)strlen(message), 0);
	if (status_result == SOCKET_ERROR)
	{
		printf("send failed : %d\n", WSAGetLastError());
		closesocket(*ConnectSocket);
		WSACleanup();
		return 0;
	}

	printf("Bytes Sent : %ld\n", status_result); //vypisanie poctu odoslanych dat

	return 1;
}

int recieveMessage(SOCKET *ConnectSocket, char* recieve_buffer, int len) {
	int status_result = recv(*ConnectSocket, recieve_buffer, len, 0);

	if (status_result > 0) {
		printf("Bytes received : %d\n", status_result); //prisli validne data, vypis poctu
		return 1;
	} else if (status_result == 0) {
		printf("Connection closed\n"); //v tomto pripade server ukoncil komunikaciu
		return 0;
	} else {
		printf("recv failed with error : %d\n", WSAGetLastError()); //ina chyba
		return 0;
	}

}

void printMessages(HANDLE hConsole, char *message, int offset, int len) {

	int line = 1;
	int tempLen = 0;
	printf("Sprava %s", message);

	char *word = strtok(message, " ");

	printf("Sprava %s", word);

	/*while (word != NULL) {

		if (tempLen + strlen(word) > len) {
			line++;
			tempLen = 0;
			continue;
		}

		tempLen += strlen(word);

		COORD point = { offset+tempLen, line };
		SetConsoleCursorPosition(hConsole, point);
		printf("%s",word);

		word = strtok(NULL, " ");

	}*/

}

int main() {

	int recieve_buffer_len = DEFAULT_BUFFER_LEN;
	char recieve_buffer[DEFAULT_BUFFER_LEN];
	char send_buffer[DEFAULT_BUFFER_LEN];
	int status_result;
	char *pToNewLine;

	SOCKET ConnectSocket = INVALID_SOCKET;

	SetConsoleOutputCP(CP_UTF8);

	// farba
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int defaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	int textColor = FOREGROUND_GREEN;
	SetConsoleTextAttribute(hConsole, textColor);

	system("cls");
	char *end_buffer = "test test test";
	printMessages(hConsole, "test test test", 5, 5);

	/*if (!connectToServer(&ConnectSocket, "147.175.115.34", "777"))
		return 1;

	//85917

	while (1) {

		// posielanie dat
		scanf("%[^\n]s", send_buffer);
		getchar();

		if (strstr("exit", send_buffer) != NULL)
			break;

		printf("Posielam:\n%s\n",send_buffer);

		if (!sendMessage(&ConnectSocket, send_buffer))
			break;

		// primanie dat
		if (!recieveMessage(&ConnectSocket, recieve_buffer, recieve_buffer_len))
			break;

		pToNewLine = strchr(recieve_buffer, '\n');
		*pToNewLine = 0;

		printf("Prijata sprava:\n%s\n", recieve_buffer);
	}

	// zavretie socketu
	disconnectFromServer(&ConnectSocket);*/

	SetConsoleTextAttribute(hConsole, defaultColor);

    return 0;
}

