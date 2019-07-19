// broadserver.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	WSADATA WSAData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &WSAData) != 0)
		return 0;

	SOCKET sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == sendSocket)
	{
		cout << "socket error!";
		return 0;
	}

	bool bOpt = true;
	//设置该套接字为广播类型
	setsockopt(sendSocket, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));

	//传入的网卡IP地址
	unsigned long address;
	inet_pton(AF_INET, "127.0.0.1", &address);
	setsockopt(sendSocket, IPPROTO_IP, IP_MULTICAST_IF, (char FAR *)&address, sizeof(address));
	
	//
	sockaddr_in dstAddr;
	dstAddr.sin_family = AF_INET;
	//dstAddr.sin_addr.S_un.S_addr = inet_addr("234.2.2.2");
	inet_pton(AF_INET, "238.0.0.1", &dstAddr.sin_addr.S_un.S_addr);
	dstAddr.sin_port = htons(8888);

	//
	const char* sendData = "Hello word!";
	while (1)
	{
		sendto(sendSocket, sendData, strlen(sendData), 0, (sockaddr*)&dstAddr, sizeof(dstAddr));
		Sleep(1000);
	}
	closesocket(sendSocket);
	WSACleanup();
	return 0;
}

