#pragma once



class CTCPClient : public CObject
{
	friend class CTCPServer;

private:

	//SOCKET
	SOCKET sockSrv;

	//SOCKET参数
	int af;
	int type;
	int protocol;

	//SOCKADDR
	sockaddr_in addrSrv;

	CTCPClient(void);

	int Send(const unsigned char *buffer, int len, int flags);
	int Recv(unsigned char *buffer, int len, int flags);

public:

	//构造与析构
	CTCPClient(u_short port, const char *ip);
	virtual ~CTCPClient(void);

	//打开与关闭
	virtual int Open();
	virtual int Close();

	//发送与接收
	virtual int Send(const unsigned char *buffer, int len);
	virtual int Recv(unsigned char *buffer, int len);

	//OOB
	virtual int SendOOB(const unsigned char *buffer, int len);
	virtual int RecvOOB(unsigned char *buffer, int len);
};
