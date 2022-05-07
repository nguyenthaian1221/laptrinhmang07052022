#include <stdio.h>
#include <winsock2.h>
#include <string.h>

#pragma comment(lib,"ws2_32")
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{// khoi tao phien ban
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	// tao socket TCP
	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// khoi tao dia chi server
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	int port = strtol(argv[2], NULL, 10);
	serverAddr.sin_port = htons(port);
	// ket noi 
	system("pause");
	connect(client, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	// Nhap du lieu
	char sendBuf[100];
	fgets(sendBuf, 100, stdin);
	// gui du lieu qua server
	send(client,sendBuf,strlen(sendBuf), 0);

	// dong socket
	closesocket(client);
	WSACleanup();
}