#include "Online/Client.h"
#include <Ws2tcpip.h> //for inet_pton
#pragma comment(lib,"ws2_32.lib") //Required for WinSock
#include <iostream> //for std::cout

bool Client::ProcessPacketType(PacketType packetType)
{
	switch (packetType)
	{
	case PacketType::PlayerData: //Packet Type: Player Data
	{
		std::string Message; //string to store our message we received
		if (!GetString(Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false
		//std::cout << Message << std::endl; //Display the message to the user

		m_playerData = Message;

		break;
	}
	case PacketType::InGameTimer: //Packet Type: In Game Timer
	{
		std::string Message; //string to store our message we received
		if (!GetString(Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false
		//std::cout << Message << std::endl; //Display the message to the user

		m_inGameTimer = Message;

		break;
	}
	case PacketType::StartGameTimer: //Packet Type: Start Game Timer
	{
		std::string Message; //string to store our message we received
		if (!GetString(Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false
		//std::cout << Message << std::endl; //Display the message to the user

		m_startGameTimer = Message;

		break;
	}
	case PacketType::StartCountdown: //Packet Type: start countdown
	{
		std::string Message; //string to store our message we received
		if (!GetString(Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false
		//std::cout << Message << std::endl; //Display the message to the user

		m_startCountdown = Message;

		break;
	}
	case PacketType::ChatMessage: //If PacketType is a chat message PacketType
	{
		std::string Message; //string to store our message we received
		if (!GetString(Message)) //Get the chat message and store it in variable: Message
			return false; //If we do not properly get the chat message, return false
		//std::cout << Message << std::endl; //Display the message to the user

		m_playerId = Message;

		break;
	}

	default: //If PacketType type is not accounted for
		//std::cout << "Unrecognized PacketType: " << (std::int32_t)packetType << std::endl; //Display that PacketType was not found
		break;
	}
	return true;
}

void Client::ClientThread(Client & client)
{
	PacketType PacketType;
	while (true)
	{
		if (client.m_terminateThreads == true)
			break;
		if (!client.GetPacketType(PacketType)) //Get PacketType type
			break; //If there is an issue getting the PacketType type, exit this loop
		if (!client.ProcessPacketType(PacketType)) //Process PacketType (PacketType type)
			break; //If there is an issue processing the PacketType, exit this loop
	}
	//std::cout << "Lost connection to the server.\n";
	client.m_terminateThreads = true;
	if (client.CloseConnection()) //Try to close socket connection..., If connection socket was closed properly
	{
		//std::cout << "Socket to the server was closed successfully." << std::endl;
	}
	else //If connection socket was not closed properly for some reason from our function
	{
		//std::cout << "Socket was not able to be closed." << std::endl;
	}
}

void Client::PacketSenderThread(Client & client) //Thread for all outgoing packets
{
	while (true)
	{
		if (client.m_terminateThreads == true)
			break;
		while (client.m_pm.HasPendingPackets())
		{
			std::shared_ptr<Packet> p = client.m_pm.Retrieve();
			if (!client.sendall((const char*)(&p->m_buffer[0]), p->m_buffer.size()))
			{
				std::cout << "Failed to send packet to server..." << std::endl;
				break;
			}
		}
		Sleep(5);
	}
	std::cout << "Packet thread closing..." << std::endl;
}

void Client::Disconnect()
{
	m_pm.Clear();
	closesocket(m_connection);
	std::cout << "Disconnected from server." << std::endl;
}