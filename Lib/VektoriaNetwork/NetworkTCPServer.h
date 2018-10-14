#pragma once
#include "NetworkBase.h"

namespace Vektoria
{

	class CNetworkTCPServer : public CNetworkBase
	{
	private:
		int iErrorCode;
		SOCKET m_socketMain;
		SOCKADDR_IN m_sockaddrin;
		SOCKET m_socketConnected[MAX_CLIENTS];
		SOCKET m_socketAccept;

	public:
		CNetworkTCPServer();
		~CNetworkTCPServer();
		void Init();
		void Init(int iPort);
		void AcceptThreaded(int i);

		void Send(char * acFardata, int iRecvSocket);
		void SendAll(char * acFardata);

		//send method first puts the length on the string at the end of the string so recv knows the length of the buffer size
		/* // TODO = String in char*
		void SendMethod(string acfardata,int iRecvSocket);
		void SendAllMethod(string acfardata);
		void RecvMethod(int iSendingSocket, int iLength);

		void Send(string acfardata, int iRecvSocket);
		void SendAll(string acfardata);
		*/
		void Recv(int iSendingSocket, int iLength);

		void Cleanup();
		void StartWinsock();

	};

}