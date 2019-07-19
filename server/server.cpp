// server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define BUF_SIZE 100
int main()
{
	//初始化 DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//绑定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	
	char szIP[16] = {0};
	printf("请输入监听IP地址：");
	char *pRet = gets_s(szIP);
	if (NULL == pRet)
	{
		return 0;
	}
	printf(szIP);

	int nLen = strlen(szIP);
	if (nLen > 0)
	{
		//sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
		inet_pton(AF_INET, szIP, &sockAddr.sin_addr.s_addr);
	}
	else
	{
		sockAddr.sin_addr.s_addr = htons(INADDR_ANY);
	}

	sockAddr.sin_port = htons(1234);  //端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//进入监听状态
	listen(servSock, 20);

	//接收客户端请求
	char buffer[BUF_SIZE] = {0};  //缓冲区
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		int strLen = recv(clntSock, buffer, BUF_SIZE, 0);  //接收客户端发来的数据
		printf("Message from server: %s\n", buffer);//输出接收到的数据
		send(clntSock, buffer, strLen, 0);  //将数据原样返回
		closesocket(clntSock);//关闭套接字
		memset(buffer, 0, BUF_SIZE);//重置缓冲区
	}

	//关闭套接字
	closesocket(servSock);
	struct ip_mreq
	//终止 DLL 的使用
	WSACleanup();
	INADDR_BROADCAST
	return 0;
}

