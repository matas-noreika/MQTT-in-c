/*
 * Programmer: Matas Noreika Fri Jan 17 05:41:36 PM GMT 2025
 * Purpose: Holds general mqtt message structures
*/

//control packet type values
#define CONNECT 1
#define PUBLISH 3
#define SUBSCRIBE 8
#define UNSUBSCRIBE 10
#define DISCONNECT 14

//definition of control packet fixed header
struct packetFixedHeader{

	char packetType;//byte size field to specify the control packet type
	char packetFlag;//byte size field to specify the control packet flag
	
	//two byte offset to pad the fixed header to match size requirement of 4 bytes
	char offsetByte;
	char offsetByte2;

}

//definition of control packet structure used for transmitting mqtt messages
struct controlPacket{
	
	
	struct packetFixedHeader fixedHeader;

}
