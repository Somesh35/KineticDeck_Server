#include <iostream>
#include <string>

#ifdef _WIN32
    #include<winsock2.h>
    #pragma comment(lib,"ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define SOCKET int
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
#endif

int main() {
	#ifdef _WIN32
	    WSADATA wsaData;
	    WSAStartup(MAKEWORD(2,2),&wsaData);
	#endif
	
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		std::cerr <<"failed to create socket\n";
		return 1;
	}
	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(8080);
	
	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
		std::cerr <<"Bind failed\n";
		#ifdef _WIN32
		    closesocket(serverSocket);
		    WSACleanup();
		#else
		    close(serverSocket);
		#endif
		return 1;
	}
	listen(serverSocket, 3);
	std::cout <<"c++ Server is listening on port 8080...\n";
	
	sockaddr_in clientAddr{};
	int clientAddrSize = sizeof(clientAddr);
	SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&clientAddrSize);
	
	if(clientSocket != INVALID_SOCKET){
		std::cout<<"Client connected!\n";
		char buffer[1024]= {0};
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer)-1,0);
		if(bytesReceived > 0) {
			std::cout << "Received from phone: "<<buffer << "\n";
		}
		#ifdef _WIN32
		    closesocket(clientSocket);
		    closesocket(serverSocket);
		    WSACleanup();
		#else
		    close(clientSocket);
		    close(serverSocket);
		#endif
	}
	return 0;
}
