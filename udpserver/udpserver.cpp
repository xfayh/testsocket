// udpserver.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#define BUF_SIZE 100

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	//���׽���
	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));  //ÿ���ֽڶ���0���
	servAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //�Զ���ȡIP��ַ
	servAddr.sin_port = htons(1234);  //�˿�
	bind(sock, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

	//���տͻ�������
	SOCKADDR clntAddr;  //�ͻ��˵�ַ��Ϣ
	int nSize = sizeof(SOCKADDR);
	char buffer[BUF_SIZE];  //������
	while (1) 
	{
		int strLen = recvfrom(sock, buffer, BUF_SIZE, 0, &clntAddr, &nSize);
		sendto(sock, buffer, strLen, 0, &clntAddr, nSize);
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}

