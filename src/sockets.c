/*
 * Programmer: Matas Noreika Mon Jan 20 10:59:38 PM GMT 2025
 * Purpose: Holds definitions for sockets static library
*/

#include "sockets.h"//include the socket declerations in header

//windows specific functions to use Windows Socket API (WSA)
#ifdef _WIN32
	
	//function to call at the start of the program to request ws2_32.lib resources
	int startWSA(WSADATA* wsaData){
		
		//decleration of variable to store the desired version of WSA 
		WORD version;

		//call function to create a word variable of the desired version 
		version = makeWord(versionHighByte,versionLowByte);

		//call fuction to try and start up the WSA at version with pointer to data variable
		//return the exit code associated to be handled by calling process
		return WSAStartup(version, wsaData);

	}

#endif

//definition of function to handle socket errors
int socketError(int exitCode){
	
	#ifdef _WIN32//Windows platform
	
		//check if its an error exit code
		if(exitCode ~= 0){
		
			char* errorMsg;//decleration of variable to hold the error reason from strerror()
	 		fprintf(stderr, "Error: %s\n", strerror(errno));//prints the reason for the error to standard error stream
			return 1;//return non-zero value indicating an error was found
		
		}else{
		
			return 0;//return a zero indicating no error occured
		
		}

	#else//POSIX platform
		
		//check if its a error exit code
		if(exitCode < 0){

			char* errorMsg;//decleration of variable to hold the error reason from strerror()
	 		fprintf(stderr, "Error: %s\n", strerror(errno));//prints the reason for the error to standard error stream
			return 1;//return non-zero value indicating an error was found

		}else{
		
			return 0;//return a zero indicating no error occured
		
		}
	#endif
	
}

