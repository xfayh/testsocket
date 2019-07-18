// broadclient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int main()
{
	WSADATA WSAData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &WSAData) != 0)
		return 0;

	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);	//����������socket
	if (INVALID_SOCKET == serSocket)
	{
		cout << "socket error!";
		return 0;
	}

	//���ô���Э�顢�˿��Լ�Ŀ�ĵ�ַ 
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(serSocket, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)	 //��socket�󶨵�ַ 
	{
		cout << "bind error";
		closesocket(serSocket);
		return 0;
	}

	//�����鲥��
	ip_mreq multiCast;
	multiCast.imr_interface.S_un.S_addr = INADDR_ANY;		//����ĳһ�����豸�ӿڵ�IP��ַ��
															//multiCast.imr_multiaddr.S_un.S_addr = inet_addr("234.2.2.2");	//�鲥���IP��ַ��
	inet_pton(AF_INET, "238.0.0.1", &multiCast.imr_multiaddr.S_un.S_addr);
	setsockopt(serSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast));

	sockaddr_in clientAddr;
	int iAddrlen = sizeof(clientAddr);
	char buff[1024];	//�������ջ����ֽ����� 
	char ip[20];
	while (true)
	{
		memset(buff, 0, 1024);	//��ս��ջ�������
								//��ʼ�������� 
		int len = recvfrom(serSocket, buff, 1024, 0, (sockaddr*)&clientAddr, &iAddrlen);
		if (len > 0)
		{
			inet_ntop(AF_INET, &clientAddr.sin_addr, ip, 20);
			cout << "������ַ��" << ip << " content:" << buff << endl;
			//	sendto(serSocket,buff,1024,0,(sockaddr*)&clientAddr,iAddrlen);
		}
	}

	closesocket(serSocket);		//�ر�socket 
	WSACleanup();
	return 0;
}

