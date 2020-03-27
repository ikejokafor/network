#include "Network.hpp"
using namespace std;


int server_connect(char* ip_address, int port) 
{
#ifdef WIN32

#else
    int sock;
    struct sockaddr_in inet;
	memset(&inet, 0x0, sizeof(inet));
    inet.sin_family = AF_INET;
	inet.sin_port = htons(port);
	inet.sin_addr.s_addr = (ip_address != nullptr) ? inet_addr(ip_address) : htonl(INADDR_ANY);
	// Connect to the server */
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		// Complain, explain, and return 
		cout << "Failed server socket create" << endl;
		return -1;
	}
	// Setup the socket option to reuse
	int on = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	// Call the connect
	if(bind(sock, (struct sockaddr *)&inet, sizeof(inet)) != 0) 
    {
		// Complain, explain, and return
		cout << "Failed server socket bind" << endl;
	    return -1;
	}
	// Do the listen
	if(listen(sock, BACKLOG_QUE_SZ) != 0) 
    {
		/* Complain, explain, and return */
		cout << "Failed server socket listen" << endl;
	    return -1;
	}
#endif
    return sock;
}


int client_connect(char *ip_address, int port)
{
#ifdef WIN32

#else
	/* Local variables */
	int sock;
	struct sockaddr_in inet;
	// Zero/Set the ip_address
	memset(&inet, 0x0, sizeof(inet));
	inet.sin_family = AF_INET;
	inet.sin_port = htons(port);
	inet.sin_addr.s_addr = (ip_address != nullptr) ? inet_addr(ip_address) : htonl(INADDR_ANY);

	/* Connect to the server */
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		/* Complain, explain, and exit */
		cout << "Failed to create socket" << endl;
		return -1;
	}

	// Call the connect
	if(connect(sock, (struct sockaddr *)&inet, sizeof(inet)) != 0)
	{
		/* Complain, explain, and return */
		cout << "Failed client socket connection" << endl;
		return -1;
	}

	/* Print a log message */
	printf("Client connected to ip_address [%s / %d], successful ...\n", ip_address, port);
#endif
	/* Return the file handle */
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
