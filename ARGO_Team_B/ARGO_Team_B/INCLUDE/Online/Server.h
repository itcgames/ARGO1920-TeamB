#pragma once
#include <WinSock2.h> //For win sockets
#include <ws2tcpip.h>
#include <string> //For std::string
#include "PacketManager.h" //for PacketManager class
#include <vector> //for std::vector
#include <shared_mutex> //for shared_mutex


class Connection
{
public:
	Connection(SOCKET socket) 
		:m_socket(socket)
	{
	}
	SOCKET m_socket;
	//file transfer data
	PacketManager m_pm; //Packet Manager for outgoing data for this connection
	int m_ID = 0;
};

class Server
{
public: //Public functions
	Server(int port, bool loopBacktoLocalHost = true);
	~Server();
	bool ListenForNewConnection();
	int getTotalConnections() { return m_connections.size(); }
	void SendStringToAll(const std::string& data, PacketType type);
	std::string getPlayerData() { return m_playerData; }
private: //Private functions
	bool sendall(std::shared_ptr<Connection> connection, const char * data, const int totalBytes);
	bool recvall(std::shared_ptr<Connection> connection, char * data, int totalBytes);
	void SendString(std::shared_ptr<Connection> connection, const std::string & str, PacketType type);
	void SendString(std::shared_ptr<Connection> connection, const std::string& str);
	bool Getint32_t(std::shared_ptr<Connection> connection, std::int32_t & int32_t);
	bool GetPacketType(std::shared_ptr<Connection> connection, PacketType & packetType);
	bool GetString(std::shared_ptr<Connection> connection, std::string & str);
	bool ProcessPacket(std::shared_ptr<Connection> connection, PacketType packetType);
	static void ClientHandlerThread(Server & server, std::shared_ptr<Connection> connection);
	static void PacketSenderThread(Server & server); 
	void DisconnectClient(std::shared_ptr<Connection> connection); //Called to properly disconnect and clean up a client (if possible)
private: //Private Variables
	std::vector<std::shared_ptr<Connection>> m_connections;
	std::shared_mutex m_mutex_connectionMgr; //mutex for managing connections (used when a client disconnects)
	int m_IDCounter = 0;
	SOCKADDR_IN m_addr; //Address that we will bind our listening socket to
	SOCKET m_sListen;
	bool m_terminateThreads = false;
	std::vector<std::thread*> m_threads; //so destructor can wait on created threads to end...
	
	// data message for player 
	std::string m_playerData;
};
