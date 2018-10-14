#pragma once
#include "NetworkBase.h"
#include "..\VektoriaMath\HMat.h"
#include "..\VektoriaMath\Color.h"

namespace Vektoria
{

	class CNetworkUDPServer : public CNetworkBase
	{
	private:
		int m_iErrorCode;
		SOCKET m_socketMain;
		SOCKADDR_IN m_sockaddrinMain;
		char m_ac[4012];
		char m_acIPAddress[100];
		char m_acCollect[MAX_UDP_BUFFER_SIZE];
		struct sockaddr_in m_sockaddrinOther;
		// void HandleRecvError(char * ac);
	public:
		CNetworkUDPServer();
		~CNetworkUDPServer();

		void Init(); // Initialisiert einen Broadcast-UDP-Server áuf dem Vektoria-Default-Port (50023)
		void Init(char * acIPAddress, int iPort = DEFAULT_PORT); // Initialisiert einen UDP Server mit IP-Adresse und optionalem Port

		void SendBroadcastMethod(char * ac); 
		void SendBroadcast(char * ac); // Sendet per Broadcast den String ac an alle Clients
		void SendBroadcast(bool & b); // Sendet per Broadcast den boolschen Wert b an alle Clients
		void SendBroadcast(int & i); // Sendet per Broadcast den Integer i an alle Clients 
		void SendBroadcast(unsigned int & i); // Sendet per Broadcast den unsigned Integer i an alle Clients 
		void SendBroadcast(float & f); // Sendet per Broadcast die Gleitkommazahl f an alle Clients
		void SendBroadcast(CHMat & m); // Sendet per Broadcast die Matrix m an alle Clients
		void SendBroadcast(CHVector & v); // Sendet per Broadcast den Vektor v an alle Clients
		void SendBroadcast(CColor & color); // Sendet per Broadcast die Farbe color an alle Clients

		void CollectMethod(char * ac);
		void Collect(char * ac); // Sammelt den string für einen späteren Broadcast 
		void Collect(bool & b); // Sammelt den boolschen Wert b für einen späteren Broadcast 
		void Collect(int & i); // Sammelt die ganze Zahl i für einen späteren Broadcast  
		void Collect(unsigned int & u); // Sammelt den unsigned int u für einen späteren Broadcast  
		void Collect(float & f); // Sammelt dei Gleitkommazahl f für einen späteren Broadcast 
		void Collect(CHMat & m); // Sammelt die Matrix m für einen späteren Broadcast 
		void Collect(CHVector & v); // Sammelt den Vektor v für einen späteren Broadcast 
		void Collect(CColor & color); // Sammelt die Farbe color für einen späteren Broadcast 
		void SendBroadcastCollection(); // Sendet per Broadcast alle gesammelten Werte mit einem einzigen UDP-Paket, löscht danach die Sammlung


		int RecvI(); // Holt eine Message vom Client und interpretiert sie als Integer, bleibt danach im Broadcast-Mode
		void RecvHandshake(); // Wartet auf ein Handshake von irgeneinem Client, bleibt danach im Broadcast-Mode
		void RecvHandshakes(int iTimes); // Wartet auf n Handshakes von irgenswelchen Clients, bleibt danach im Broadcast-Mode

		void Cleanup();
		void StartWinsock();

	};


}