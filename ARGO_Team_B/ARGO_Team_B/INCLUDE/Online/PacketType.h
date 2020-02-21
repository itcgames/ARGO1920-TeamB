#pragma once
enum class PacketType
{
	StartCountdown,
	InGameStartCountdown,
	PlayerData,
	BombData,
	TrapData,
	ButtonData,
	ChatMessage,
	FileTransferRequestFile, //Sent to request a file
	FileTransfer_EndOfFile, //Sent for when file transfer is complete
	FileTransferByteBuffer, //Sent before sending a byte buffer for file transfer
	FileTransferRequestNextBuffer //Sent to request the next buffer for file
};