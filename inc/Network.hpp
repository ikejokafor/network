#pragma once


// Definitions
#define MAX_BLK_SZ      1024
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
#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#endif


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
int server_connect(char* ip_address = nullptr, int port = 8888);


// --------------------------------------------------------------------------------------------------------------------------------------------------
/**
 *      \brief
 *      
 *      \param[in] 
 *      \param[in, out] 
 *      \param[in] 
 *      
 *      \return 
 */
// --------------------------------------------------------------------------------------------------------------------------------------------------
int client_connect(char *address = nullptr, int port = 8888);


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
