/*
 * Programmer: Matas Noreika Tue Jan 21 12:04:39 AM GMT 2025
 * Purpose: This is an example on how to use custom socket library to create a client on windows or POSIX 
*/

#include "sockets.h" //include the declerations and macros in sockets.h

#define SERVERIP "127.0.0.1" //set the server IP (change to desired address)
#define PORT 2000 //set the server port to connect (change to desired port)

int main(){//start of main method
	
	#ifdef _WIN32//currently on windows platform

		SOCKET clientSocket;//Windows uses its own unsigned int with last value assigned the value as INVALID_SOCKET
		WSADDATA wsaData;//decleration of WSADATA type variable that holds the status of the WSA
		int startWSAExitCode;//decleration of variable to hold the exit code of the startWSA() function
		
		startWSAExitCode = startWSA(&wsaData);//call function to try start the WSA

	#else//currently on POSIX platform

		int clientSocket;//POSIX uses a file descriptor to address the socket

	#endif
	
	//decleration of server address used for connecting
	struct sockaddr_in serverAddr;
	
	serverAddr.sin_family = AF_INET;//set the address family type as an IPV4 address
	serverAddr.sin_port = htons(PORT);//converts the port to big-endian network format
	serverAddr.sin_addr.s_addr = inet_addr(SERVERIP);//call function to convert the client IP adress into expanded network byte order
	
	printf("Creating socket...\n");

	//create a new socket using IPV4 address family and configured to be a UDP fire and forget socket
	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	//call function to determine if error occured
	if(socketError(clientSocket)){
		
		#ifdef _WIN32

			WSACleanup();//cleanup the WSA

		#endif


		return 1;
	
	}
	
	printf("Socket created\nPreparing to send message to server...\n");

	//definition of message to send to server
	char* msg = "Message from client to server: hi!";
	
	//call function sendto() to send a message to destination address using socket
	int sendToExitCode = sendto(clientSocket, msg, strlen(msg), 0, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
	
	//check if sendto() failed
	if(socketError(sendToExitCode)){
		
		close(clientSocket);//close the socket
		
		#ifdef _WIN32

			WSACleanup();//cleanup the WSA

		#endif

		return 1;
	
	}

	printf("Message was sent to server\nClosing socket\n");

	//call function to close the socket
	close(clientSocket);
	
	#ifdef _WIN32

		WSACleanup();//cleanup the WSA

	#endif

	return 0;

}//end of main method
