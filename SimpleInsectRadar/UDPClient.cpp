// UDPClient.cpp : 实现文件
//

#include "stdafx.h"
#include "SimpleInsectRadar.h"
#include "UDPClient.h"


// CUDPClient

CUDPClient::CUDPClient()
{
	sockServ = INVALID_SOCKET;
	af = AF_INET;
	type = SOCK_DGRAM;
	protocol = IPPROTO_UDP;
}

CUDPClient::~CUDPClient()
{
}

CUDPClient::CUDPClient(u_short port, const char *ip)
{
	sockServ = INVALID_SOCKET;
	af = AF_INET;
	type = SOCK_DGRAM;
	protocol = IPPROTO_UDP;

	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(port);
	addrServ.sin_addr.S_un.S_addr = inet_addr(ip);
	
}


// CUDPClient 成员函数
int CUDPClient::Open(bool isBind)
{
	sockServ = socket(af, type, protocol);
	if(sockServ == INVALID_SOCKET)
		return WSAGetLastError();

	if(isBind)
		bind(sockServ, (sockaddr*)&addrServ, sizeof(addrServ));

	return 0;
}

int CUDPClient::Send(const unsigned char *buf, int len)
{
	return Send(buf, len, 0);
}

int CUDPClient::Send(const unsigned char *buf, int len, int flags)
{
	int index = 0;
	int bytes;

	if (sockServ == INVALID_SOCKET)
	{
		return SOCKET_ERROR;
	}

	while (index < len)
	{
		bytes = sendto(sockServ,(const char*)buf+index,len-index,flags, (sockaddr*)&addrServ, sizeof(addrServ));

		if (bytes == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAENOBUFS)
				continue;
			break;
		}

		if (bytes == 0)
		{
			break;
		}

		index += bytes;
	}

	return index;
}

int CUDPClient::Recv(unsigned char *buf, int len)
{
	return Recv(buf, len, 0);
}

int CUDPClient::Recv(unsigned char *buf, int len, int flags)
{
	int index = 0;
	int bytes;
	int iAddrLen = sizeof(addrServ);
	if (sockServ == INVALID_SOCKET)
	{
		return SOCKET_ERROR;
	}

	while (index < len)
	{
		bytes = recvfrom(sockServ,(char*)buf+index,len-index,flags, (sockaddr*)&addrServ, &iAddrLen);

		if (bytes == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAENOBUFS)
				continue;
			break;
		}

		if (bytes == 0)
		{
			break;
		}

		index += bytes;
	}

	return index;
}

int CUDPClient::Close()
{
	return closesocket(sockServ);
}