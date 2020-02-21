#include "Online/PacketStructs.h"

namespace PS
{
	ChatMessage::ChatMessage(const std::string & msg)
		:m_message(msg)
	{
	}

	std::shared_ptr<Packet> ChatMessage::toPacket()
	{
		std::shared_ptr<Packet> p = std::make_shared<Packet>();
		p->Append(PacketType::ChatMessage);
		p->Append(m_message.size());
		p->Append(m_message);
		return p;
	}

	DataMessage::DataMessage(const std::string& msg) :
		m_message(msg)
	{
	}

	std::shared_ptr<Packet> DataMessage::toPacket(PacketType type) {
		std::shared_ptr<Packet> p = std::make_shared<Packet>();
		p->Append(type);
		p->Append(m_message.size());
		p->Append(m_message);
		return p;
	}
}