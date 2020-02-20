#pragma once
#include "ClientPacketType.h"
#include "ClientPacket.h"
#include <string> //for std::string
#include <memory> //for std::shared_ptr

namespace PS //Packet Structures Namespace
{
	class ChatMessage
	{
	public:
		ChatMessage(const std::string & str);
		std::shared_ptr<Packet> toPacket(); //Converts ChatMessage to packet
	private:
		std::string m_message;
	};
	class FileDataBuffer //Used when sending a file
	{
	public:
		std::shared_ptr<Packet> toPacket(); //Converts FileDataBuffer to Packet so that it can be appended to packet manager
		int m_size; //size of data buffer
	};
	class DataMessage {
	public:
		DataMessage(const std::string& str);
		std::shared_ptr<Packet> toPacket(PacketType type);
	private:
		std::string m_message;
	};

}