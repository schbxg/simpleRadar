#pragma once



class CTCPClient : public CObject
{
	friend class CTCPServer;

private:

	//SOCKET
	SOCKET sockSrv;

	//SOCKET����
	int af;
	int type;
	int protocol;

	//SOCKADDR
	sockaddr_in addrSrv;

	CTCPClient(void);

	int Send(const unsigned char *buffer, int len, int flags);
	int Recv(unsigned char *buffer, int len, int flags);

public:

	//����������
	CTCPClient(u_short port, const char *ip);
	virtual ~CTCPClient(void);

	//����ر�
	virtual int Open();
	virtual int Close();

	//���������
	virtual int Send(const unsigned char *buffer, int len);
	virtual int Recv(unsigned char *buffer, int len);

	//OOB
	virtual int SendOOB(const unsigned char *buffer, int len);
	virtual int RecvOOB(unsigned char *buffer, int len);
};
