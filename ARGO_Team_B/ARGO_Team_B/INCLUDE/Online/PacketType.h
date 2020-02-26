#pragma once
enum class PacketType
{
	StartCountdown, // for waiting player 
	StartGameTimer, // the waiting before start game
	InGameTimer, // the timer for game
	PlayerData, // the player data, include position and get cheese checj;
	ChatMessage,
	FileTransferRequestFile, //Sent to request a file
	FileTransfer_EndOfFile, //Sent for when file transfer is complete
	FileTransferByteBuffer, //Sent before sending a byte buffer for file transfer
	FileTransferRequestNextBuffer //Sent to request the next buffer for file
};