#include "stdafx.h"
#include "TCPClient.h"

CTCPClient::CTCPClient(void)
{
	sockSrv = INVALID_SOCKET;

	af = AF_INET;
	type = SOCK_STREAM;
	protocol = IPPROTO_TCP;
}

CTCPClient::CTCPClient(u_short port, const char *ip)
{
	sockSrv = INVALID_SOCKET;

	af = AF_INET;
	type = SOCK_STREAM;
	protocol = IPPROTO_TCP;

	memset(&addrSrv, 0, sizeof(sockaddr_in));
	addrSrv.sin_addr.S_un.S_addr = inet_addr(ip);
	addrSrv.sin_family = PF_INET;
	addrSrv.sin_port = htons(port);
}

CTCPClient::~CTCPClient(void)
{
}

int CTCPClient::Open()
{
	sockSrv = socket(af, type, protocol);

	if (sockSrv == INVALID_SOCKET)
		return WSAGetLastError();

	if (connect(sockSrv, (const sockaddr *)(&addrSrv), sizeof(sockaddr)) == SOCKET_ERROR)
		return WSAGetLastError();

	return 0;
}

int CTCPClient::Send(const unsigned char *buffer, int len, int flags)
{
	int index = 0;
	int bytes;

	if (sockSrv == INVALID_SOCKET)
	{
		return SOCKET_ERROR;
	}

	while (index < len)
	{
		bytes = send(sockSrv,(const char*)buffer+index,len-index,flags);

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

int CTCPClient::Recv(unsigned char *buffer, int len, int flags)
{
	int index = 0;
	int bytes;

	if (sockSrv == INVALID_SOCKET)
	{
		return SOCKET_ERROR;
	}

	while (index < len)
	{
		bytes = recv(sockSrv,(char*)buffer+index,len-index,flags);

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

int CTCPClient::Send(const unsigned char *buffer, int len)
{
	return Send(buffer, len, 0);
}

int CTCPClient::Recv(unsigned char *buffer, int len)
{
	return Recv(buffer, len, 0);
}

int CTCPClient::SendOOB(const unsigned char *buffer, int len)
{
	return Send(buffer, len, MSG_OOB);
}

int CTCPClient::RecvOOB(unsigned char *buffer, int len)
{
	return Recv(buffer, len, MSG_OOB);
}

int CTCPClient::Close()
{
	return closesocket(sockSrv);
}
