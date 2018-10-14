#pragma once
#include "NetworkBase.h"

namespace Vektoria
{

	class CNetworkTCPClient : public CNetworkBase
	{
	private:
		int iErrorCode;
		SOCKET m_socketMain;
		SOCKADDR_IN sockaddrin;
		SOCKET m_socketConnected[MAX_CLIENTS];
		SOCKET m_socketAccept;

	public:
		CNetworkTCPClient();
		~CNetworkTCPClient();
		void Init();
		//you said port and server ip when initiating the client. or use defaults that are set in distributed base
		void Init(char * acServerIp, int iPort);
		//recv sets the buffer size correctly to the string it is waiting for
		void SendMethod(char * acFardata);
		void RecvMethod(char * ac, int iSocketNumber);

		void Send(char * acFardata);
		void Recv(char * ac, int iSocketNumber);

		void Cleanup();
		void StartWinsock();
	};

}