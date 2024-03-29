#pragma once

#include <cstdint>
#include <list>
#include <string>

namespace MessageBuffer
{
	enum class MessageStatus : uint8_t
	{
		kUndefined		= 0,
		kSend			= 1,
		kReceived		= 2
	};

	struct MessageNode 
	{
		explicit MessageNode(MessageStatus messageType, const std::string& data) : data(data), messageType(messageType) {};
		
		std::string data;
		MessageStatus messageType = MessageStatus::kUndefined;
	};

	inline std::list<MessageNode> messageBuffer;

} // !namespace MessageBuffer

