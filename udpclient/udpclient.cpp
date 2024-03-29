// udpclient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#define BUF_SIZE 100

int main() {
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

	//服务器地址信息
	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
	servAddr.sin_family = PF_INET;
	//servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr.s_addr);
	servAddr.sin_port = htons(1234);

	//不断获取用户输入并发送给服务器，然后接受服务器数据
	sockaddr fromAddr;
	int addrLen = sizeof(fromAddr);
	while (1) {
		char buffer[BUF_SIZE] = { 0 };
		printf("Input a string: ");
		gets_s(buffer);
		sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
		int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, (sockaddr*)&servAddr, &addrLen);
		if (strLen<=0)
		{
			printf("Message from server: %dbytes\n", strLen);
		}
		else
		{
			buffer[strLen] = 0;
			printf("Message from server: %s\n", buffer);
		}
		
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}
