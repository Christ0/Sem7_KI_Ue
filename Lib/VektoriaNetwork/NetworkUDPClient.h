#pragma once
#include "NetworkBase.h"
#include "..\VektoriaMath\HMat.h"
#include "..\VektoriaMath\Color.h"
#include "../Vektoria/Timer.h"

namespace Vektoria
{

	class CNetworkUDPClient : public CNetworkBase
	{
	private:
		int m_iErrorCode;
		SOCKET m_socketMain;
		SOCKADDR_IN m_sockaddrin;
		char m_acSelect[MAX_UDP_BUFFER_SIZE];
		int m_iLastSelect;
		int m_iSizeSelect;
		int NextSelect();
		CTimer m_timer;
	public:
		CNetworkUDPClient();
		~CNetworkUDPClient();

		void Init(char * acServerIp, int iPort = DEFAULT_PORT); // Initialisiert einen UDP Client per IP-Adresse und Port, wird kein Port angegeben, so wird der Stadard-Vektoria-Port (50023) genommen

		void RecvBroadcastS(char * ac); // Wandelt erhalteten Broadcast in eine Zeichenkette um
		bool RecvBroadcastB(); // Wandelt erhalteten Broadcast in einen Bool um
		int RecvBroadcastI(); // Wandelt erhalteten Broadcast in einen Integer um
		float RecvBroadcastF(); // Wandelt erhalteten Broadcast in einen Float um
		CHMat RecvBroadcastM(); // Wandelt erhalteten Broadcast in einen CHMat um
		CHVector RecvBroadcastV(); // Wandelt erhalteten Broadcast in einen CHVector um
		CColor RecvBroadcastC(); // Wandelt erhalteten Broadcast in einen CColor um

		void RecvSelection(); // Wandelt erhaltetes UDP-Paket in eine Selection um
		void SelectS(char * ac); // Extrahiert eine Zeichenkette aus der Selection 
		bool SelectB(); // Extrahiert einen Bool aus der Selection 
		int SelectI(); // Extrahiert einen Integer aus der Selection 
		float SelectF(); // Extrahiert einen Float aus der Selection 
		CHMat SelectM(); // Extrahiert einen CHMat aus der Selection 
		CHVector SelectV(); // Extrahiert einen CHVector aus der Selection 
		CColor SelectC(); // Extrahiert eine CColor aus der Selection 

		void SendToMaster(int i); // Sendet eine Integer-Zahl zum Master zurück
		void SendHandshake(); // Sendet ein Handshake zum Master zurück

		void Cleanup();
		bool IsSelectionEmpty();

		struct sockaddr_storage m_src_addr;
		socklen_t m_src_addr_len = sizeof(m_src_addr);
		char m_acBuffer[UDP_BUFFER_SIZE];
	};

}