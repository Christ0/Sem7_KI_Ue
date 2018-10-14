#pragma once

// TODO: Checken für VS2015:
#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")


namespace Vektoria
{

#define DEFAULT_PORT 50023 // there is always an overloaded funtion to specify a port for yourself
#define MAX_CLIENTS 2 //tcp how many clients can be threaded
#define UDP_BUFFER_SIZE 1024 // udp buffer size für normale single brodcasts
#define MAX_UDP_BUFFER_SIZE 262142 // maximale zulässige Größe von winsock für ein UDP-Paket in Bytes


	class CNetworkBase
	{
	public:
		virtual ~CNetworkBase(){};
		virtual void Cleanup() = 0;


		void GetOwnIP(char * acIPAddress);
		void GetOwnName(char * acHost);

		void HandleError(char * acMethod);


		WSADATA m_wsadata;
	};
}