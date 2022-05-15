#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
	// khoi tao winsock
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// tao socket cho ket noi
	SOCKET serverListener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Tao dia chi server
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int port = strtol(argv[1],NULL,10);
	addr.sin_port = htons(port);

	// gan socket voi cau truc dia chi
	bind(serverListener, (SOCKADDR*)&addr, sizeof(addr));

	// Chuyen socket sang trang thai cho ket noi
	// tham so backLog chi dinh so client cung luc
	// co the ket noi den, nhieu hon thi se bi loai khoi 
	// ket noi
	listen(serverListener, 5);

	// Chap nhan ket noi 
	printf("\nDang cho ket noi...");

	SOCKADDR_IN clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	SOCKET client = accept(serverListener, (SOCKADDR*)&clientAddr, &clientAddrLen);
	printf("\nKet noi moi: %d, dia chi IP: %s\n", client, inet_ntoa(clientAddr.sin_addr));


	// Vi tri chua cau chao "C:\\Users\\Lenovo\\source\\repos\\bvn254ltm\\loichaotuserver.txt"
	FILE* fp = fopen(argv[2], "r");

	char arr[128];
	while (fgets(arr, 128, fp) != NULL)
	{
		//Xuat tung dong ra man hinh
		printf("%s", arr);
	}
	fclose(fp);

	// nhan du lieu tu phia client
	char buf[100];
	int ret = recv(client, buf, sizeof(buf), 0);
	//  luu vao file 
	// vi tri chua noi can luu du lieu "C:\\Users\\Lenovo\\source\\repos\\bvn254ltm\\dulieutuclient.txt" 
	FILE* fptr = fopen(argv[3], "w");
	int countChar = ret;



	fwrite(buf, 1, countChar, fptr);
	// Dong ket noi
	closesocket(client);


}
