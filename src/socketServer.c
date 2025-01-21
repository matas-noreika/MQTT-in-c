/*
 * Programmer: Matas Noreika Tue Jan 21 02:38:42 AM GMT 2025
 * Purpose: to create a simple server that recieves UDP packets from clients
*/

//include my custom sockets library
#include "sockets.h"

#define SERVERIP "127.0.0.1" //change to desired IP address 
#define PORT 2000 //change to desired port

int main(){//start of main method

	#ifdef _WIN32//if we are on windows platform
		
		WSADATA wsaData;//WSA data variable that hold the current properties of WSA instance
		SOCKET server;//decleration of server socket despcriptor on windows
		startWSA(&wsaData);//call function to start WSA

	#else//if we are on POSIX

		int server;//decleration of server socket descriptor

	#endif

	struct sockaddr_in serverAddr, clientAddr;//decleration of server and client address variables
	
	serverAddr.sin_family = AF_INET;//set the IP address to an IPV4 address type	
	serverAddr.sin_addr.s_addr = inet_addr(SERVERIP);//sets the IP address to the converted big-endian format of string address 
	serverAddr.sin_port = htons(PORT);//sets the port to the converted big-endian format of provided port number
	
	socklen_t clientAddrSize = sizeof(clientAddr);//definition of clientAddrSize variable to pass into recvfrom() 
	
	printf("creating server socket...\n");

	//create a socket for a UDP connection
	server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	//check if socket() failed
	if(socketError(server)){
	
		#ifdef _WIN32

			WSACleanup();//release WSA resources

		#endif

		return 1;
	
	}
	
	printf("Created server socket\n");

	printf("binding socket to address and port...\n");

	//call bind() function to bind the server address ip and port to socket
	int bindExitCode = bind(server, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
	
	//check if bind failed
	if(socketError(bindExitCode)){

		close(server);//call function to close the socket
		
		#ifdef _WIN32

			WSACleanup();//release WSA resources

		#endif
		
		return 1;
	
	}
	
	printf("socket binded\n");


	printf("waiting on message from client...\n");

	//decleration of read buffer to read client UDP packet
	char readBuffer[255];

	//call recvfrom() function to read data sent to server
	int readSize = recvfrom(server, readBuffer, 255, 0, (struct sockaddr*) &clientAddr, &clientAddrSize);
	
	//check if recvfrom() failed 
	if(socketError(readSize)){
	
		readSize = 0;//manually rest the readSize to zero
	
	}
	
	if(readSize > 0){
		char* clientAddrStr = inet_ntoa(clientAddr.sin_addr);

		//print the details onto the terminal
		printf("Client: %s sent %d bytes\nMessage: %s\n", clientAddrStr, readSize,readBuffer);
	
		readSize = 1;//cancel the while loop
	}

	//while there is no data sent (repeatedly read from socket)
	while(!readSize){
		
		//read from socket
		readSize = recvfrom(server, readBuffer, 255, 0, (struct sockaddr*) &clientAddr, &clientAddrSize);
	
		//there is something read
		if(readSize > 0){
			
			char* clientAddrStr = inet_ntoa(clientAddr.sin_addr);

			//print the details onto the terminal
			printf("Client: %s sent %d bytes\nMessage: %s\n", clientAddrStr, readSize,readBuffer);
			
		}else if(readSize < 0){//an error occurred
			
			//get the socketError() function to print the error reason string to terminal
			socketError(readSize);
			readSize = 0;//manually rest the readSize to zero

		}
	
	}//end of read loop
	
	printf("Closing socket\n");

	close(server);//close the socket

	#ifdef _WIN32

		WSACleanup();//release WSA resources

	#endif

	return 0;

}//end of main method
