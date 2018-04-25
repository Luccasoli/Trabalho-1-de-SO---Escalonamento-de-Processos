#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>

int main ( int argc, int argv[] )
{
	std::cout << "running....\n";

	try
	{
		// Create the socket
		ServerSocket server ( 30000 );

		while ( true )
		{

			ServerSocket new_sock;
			server.accept ( new_sock );

			try
			{
				while ( true )
				{
					std::string data;
					new_sock >> data; // Recebe do Cliente
					new_sock << data; // Responde o Cliente
				}
			}
			catch ( SocketException& ) {}

		}
	}
	catch ( SocketException& e )
	{
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}

	return 0;
}
