// udpclient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#define BUF_SIZE 100

int main() {
	//��ʼ��DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);

	//��������ַ��Ϣ
	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));  //ÿ���ֽڶ���0���
	servAddr.sin_family = PF_INET;
	//servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr.s_addr);
	servAddr.sin_port = htons(1234);

	//���ϻ�ȡ�û����벢���͸���������Ȼ����ܷ���������
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
