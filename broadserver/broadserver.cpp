// broadserver.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int main()
{
	WSADATA WSAData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &WSAData) != 0)
		return 0;

	SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == clientSocket)
	{
		cout << "socket error!";
		return 0;
	}

	sockaddr_in dstAddr;
	dstAddr.sin_family = AF_INET;
	dstAddr.sin_port = htons(8888);
	//dstAddr.sin_addr.S_un.S_addr = inet_addr("234.2.2.2");
	//inet_pton(AF_INET, "238.0.0.1", &dstAddr.sin_addr.S_un.S_addr);
	inet_pton(AF_INET, "238.0.0.1", &dstAddr.sin_addr);
	const char* sendData = "Hello word!";
	while (1)
	{
		sendto(clientSocket, sendData, strlen(sendData), 0, (sockaddr*)&dstAddr, sizeof(dstAddr));
		Sleep(1000);
	}
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}

