// broadclient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	WSADATA WSAData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &WSAData) != 0)
		return 0;

	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);	//创建服务器socket
	if (INVALID_SOCKET == serSocket)
	{
		cout << "socket error!";
		return 0;
	}

	//设置传输协议、端口以及目的地址 
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(serSocket, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)	 //将socket绑定地址 
	{
		cout << "bind error";
		closesocket(serSocket);
		return 0;
	}

	//加入组播组
	ip_mreq multiCast;
	multiCast.imr_interface.S_un.S_addr = INADDR_ANY;		//本地某一网络设备接口的IP地址。
															//multiCast.imr_multiaddr.S_un.S_addr = inet_addr("234.2.2.2");	//组播组的IP地址。
	inet_pton(AF_INET, "238.0.0.1", &multiCast.imr_multiaddr.S_un.S_addr);
	setsockopt(serSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast));

	sockaddr_in clientAddr;
	int iAddrlen = sizeof(clientAddr);
	char buff[1024];	//建立接收缓存字节数组 
	char ip[20];
	while (true)
	{
		memset(buff, 0, 1024);	//清空接收缓存数组
								//开始接收数据 
		int len = recvfrom(serSocket, buff, 1024, 0, (sockaddr*)&clientAddr, &iAddrlen);
		if (len > 0)
		{
			inet_ntop(AF_INET, &clientAddr.sin_addr, ip, 20);
			cout << "发流地址：" << ip << " content:" << buff << endl;
			//	sendto(serSocket,buff,1024,0,(sockaddr*)&clientAddr,iAddrlen);
		}
	}

	closesocket(serSocket);		//关闭socket 
	WSACleanup();
	return 0;
}

