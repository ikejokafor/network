#pragma once


// Definitions
#define MAX_BLK_SZ      16384
#define BACKLOG_QUE_SZ  128


// System Inludes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#endif


// --------------------------------------------------------------------------------------------------------------------------------------------------
/**
 *      \brief              hosts a server
 *  
 *      \param[in]          ip_address IP Address server hosts from
 *      \param[in]          port port server hosts from
 *  
 *      \return             0 if successful, -1 if failure
 */
// --------------------------------------------------------------------------------------------------------------------------------------------------
int server_connect(char* ip_address = nullptr, uint16_t port = 8888);


// --------------------------------------------------------------------------------------------------------------------------------------------------
/**
 *      \brief              connects to a server
 *      
 *      \param[in]          ip_address IP Address client connects to
 *      \param[in]          port port client connects to
 *      
 *      \return 
 */
// --------------------------------------------------------------------------------------------------------------------------------------------------
int client_connect(const char* ip_address = "127.0.0.1", uint16_t port = 8888);


// --------------------------------------------------------------------------------------------------------------------------------------------------
/**
 *      \brief              send data over socket
 *
 *      \param[in]          sock server socket
 *      \param[in, out]     blk block to put data in
 *      \param[in]          len of data to send
 *      
 *      \return             0 if successful, -1 if failure
 */
// --------------------------------------------------------------------------------------------------------------------------------------------------
int send_data(int sock, uint8_t* blk, int len);


// --------------------------------------------------------------------------------------------------------------------------------------------------
/**
 *      \brief              receive data from the socket
 *      
 *      \param[in]          sock server socket
 *      \param[in, out]     blk block to put data in
 *      \param[in]          sz maxmimum size of buffer
 *      \param[in]          minsz minimum bytes to read
 *      
 *      \return             bytes read if successful, -1 if failure
 */
// --------------------------------------------------------------------------------------------------------------------------------------------------
int recv_data(int sock, uint8_t* blk, int sz, int minsz);
