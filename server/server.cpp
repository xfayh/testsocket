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
	
	char szIP[16] = {0};
	printf("���������IP��ַ��");
	char *pRet = gets_s(szIP);
	if (NULL == pRet)
	{
		return 0;
	}
	printf(szIP);

	int nLen = strlen(szIP);
	if (nLen > 0)
	{
		//sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
		inet_pton(AF_INET, szIP, &sockAddr.sin_addr.s_addr);
	}
	else
	{
		sockAddr.sin_addr.s_addr = htons(INADDR_ANY);
	}

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
	struct ip_mreq
	//��ֹ DLL ��ʹ��
	WSACleanup();
	INADDR_BROADCAST
	return 0;
}

