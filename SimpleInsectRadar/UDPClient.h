#pragma once

// CUDPClient ����Ŀ��

class CUDPClient : public CObject
{
private:
	// socket
	SOCKET sockServ;

	// socket����
	int af;
	int type;
	int protocol;

	sockaddr_in addrServ;
	int Send(const unsigned char *buf, int len, int flags);
	int Recv(unsigned char *buf, int len, int flags);

public:
	CUDPClient();
	CUDPClient(u_short port, const char *ip);
	
	virtual ~CUDPClient();

	virtual int Open(bool isBind);
	virtual int Close();
	virtual int Send(const unsigned char *buf, int len);
	virtual int Recv(unsigned char *buf, int len);
};


