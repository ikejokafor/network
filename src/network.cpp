#include "network.hpp"
using namespace std;


int server_connect(char* ip_address, uint16_t port) 
{
	int sock;
#ifdef MODEL_TECH
    return 0;
#endif

#ifdef WIN32

#else
    struct sockaddr_in address;
	memset(&address, 0x0, sizeof(address));
    address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = (ip_address != nullptr) ? inet_addr(ip_address) : INADDR_ANY;
	// Connect to the server 
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		cout << "Failed server socket create" << endl;
        cout << "Error: "; perror("socket");
		return -1;
	}
	// Setup the socket option to reuse
	int opt = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		cout << "Failed server set socket options" << endl;
        cout << "Error: "; perror("setsockopt");
		return -1;
	}
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
	{
		cout << "Failed server set socket options" << endl;
        cout << "Error: "; perror("setsockopt");
		return -1;
	}
	// Call the connect
	if(bind(sock, (struct sockaddr*)&address, sizeof(address))) 
    {
		cout << "Failed server socket bind" << endl;
        cout << "Error: "; perror("bind");
	    return -1;
	}
	// Do the listen
	if(listen(sock, BACKLOG_QUE_SZ)) 
    {     
		cout << "Failed server socket listen" << endl;
        cout << "Error: "; perror("listen");
	    return -1;
	}
#endif
    return sock;
}


int client_connect(const char* ip_address, uint16_t port)
{
	int sock;
#ifdef MODEL_TECH
    return 0;
#endif

#ifdef WIN32

#else
	struct sockaddr_in address;
	memset(&address, 0x0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);

	// Connect to the server
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		cout << "Failed to create socket" << endl;
        cout << "Error: "; perror("socket");
		return -1;
	}
	
	if(inet_pton(AF_INET, ip_address, &address.sin_addr) <= 0)  
    { 
        cout << "Invalid address/ Address not supported" << endl;
        cout << "Error: "; perror("inet_pton");
        return -1; 
    } 

	// Call the connect
	if(connect(sock, (struct sockaddr*)&address, sizeof(address)) == -1)
	{
		cout << "Failed client socket connection" << endl;
        cout << "Error: "; perror("connect");
		return -1;
	}

	// Print a log message
	cout << "Client connected to server" << endl;
#endif
	// Return the file handle
	return sock;
}


int send_data(int sock, uint8_t* blk, int len) 
{
#ifdef WIN32

#else	
    // Send data using the socket
	if(send(sock, blk, len, 0) != len)	
    {
		/* Complain, explain, and return */
		cout << "Failed socket send data from socket" << endl;
		return -1;
	}
	return len;
#endif
}


int recv_data(int sock, uint8_t *blk, int sz, int minsz) 
{
#ifdef WIN32

#else
	// Keep reading until you have enough bytes
	int rb = 0; 
    int ret;
	do 
    {
		// Receive data from the socket
		if((ret = recv(sock, &blk[rb], sz - rb, 0)) == -1) 
        {
			cout << "Failed read data from socket" << endl;
			return -1;
		}
		// Increment read bytes 
		rb += ret;
	} while(rb < minsz);
	return rb;    
#endif
}
