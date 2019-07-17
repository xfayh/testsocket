// server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define BUF_SIZE 100
int main()
{
	//��ʼ�� DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	//sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
	inet_pton(AF_INET, "127.0.0.1", &sockAddr.sin_addr.s_addr);
	sockAddr.sin_port = htons(1234);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//�������״̬
	listen(servSock, 20);

	//���տͻ�������
	char buffer[BUF_SIZE] = {0};  //������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		int strLen = recv(clntSock, buffer, BUF_SIZE, 0);  //���տͻ��˷���������
		printf("Message from server: %s\n", buffer);//������յ�������
		send(clntSock, buffer, strLen, 0);  //������ԭ������
		closesocket(clntSock);//�ر��׽���
		memset(buffer, 0, BUF_SIZE);//���û�����
	}

	//�ر��׽���
	closesocket(servSock);

	//��ֹ DLL ��ʹ��
	WSACleanup();

	return 0;
}

