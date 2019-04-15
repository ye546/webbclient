#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <fstream>
using namespace std; //im lazy okay

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)

#define PORT 80

int main() {
	WSADATA wsadata;
	int sock;
	int connection_status;
	struct sockaddr_in server_addr;
	std::string server_address;

	getline(cin, server_address);

	WSAStartup(0x2020, &wsadata);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(server_address.c_str());

	if (sock == -1) {
		printf("socket creation failed");
		WSACleanup();
		closesocket(sock);
		getchar();
		return 1;
	}
	
	if (connection_status = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		printf("failed to connect\n");
		WSACleanup();
		closesocket(sock);
		getchar();
		return 1;
	}

	char sendbuf[4096];
	char recvbuf[4096];
	memset(sendbuf, 0, sizeof(sendbuf));
	memset(recvbuf, 0, sizeof(recvbuf));

	sprintf(sendbuf, "GET / HTTP/1.1\r\n\r\n");
	int bytesSent = strlen(sendbuf);
	int n;

	if (send(sock, sendbuf, bytesSent, 0) != bytesSent) {
		printf("send error\n");
		WSACleanup();
		closesocket(sock);
		getchar();
		return 1;
	}
	ofstream f;
	std::string new_file = server_address + ".txt";
	f.open(new_file, fstream::app);

	while ((n = recv(sock, recvbuf, 4096-1, 0)) > 0) {
		printf("server said: %s\n", recvbuf);
		f << recvbuf;
	}
	
	if (n < 0) {
		printf("receive error\n");
		WSACleanup();
		closesocket(sock);
		getchar();
		return 1;
	}
	
	WSACleanup();
	closesocket(sock);
	
	getchar();

	return 0;
}
