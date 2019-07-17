// client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define BUF_SIZE 100
int main()
{
	//��ʼ��DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	
	//���������������
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	//sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", &sockAddr.sin_addr.s_addr);

	sockAddr.sin_port = htons(1234);

	//
	char bufSend[BUF_SIZE] = { 0 };
	char bufRecv[BUF_SIZE] = { 0 };
	while (1)
	{					   
		SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//�����׽���
		connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		
		//��ȡ�û�������ַ��������͸�������
		printf("Input a string: ");
		scanf_s("%s", bufSend, BUF_SIZE);
		send(sock, bufSend, strlen(bufSend), 0);
		//���շ��������ص�����

		recv(sock, bufRecv, BUF_SIZE, 0);

		//������յ�������
		printf("Message from server: %s\n", bufRecv);
		memset(bufSend, 0, BUF_SIZE);  //���û�����
		memset(bufRecv, 0, BUF_SIZE);  //���û�����	
		
		//�ر��׽���
		closesocket(sock);
	}

	//��ֹʹ�� DLL
	WSACleanup();

	system("pause");
	return 0;
}

