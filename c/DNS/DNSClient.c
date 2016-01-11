#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#endif

#include "DNSClient.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#pragma comment(lib, "wsock32.lib")
#include <winsock.h>
// either define MAKEWORD here, or include Windows.h
#ifndef MAKEWORD
#define MAKEWORD(a,b)   ((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))
#endif
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif


void DNSClient_DieWithError(char *errorMessage)
{
#ifdef _WIN32
	fprintf(stderr, "DNSClient: %s: %d\n",
		errorMessage, WSAGetLastError());
#else
	perror(errorMessage);
#endif
	getchar();
	exit(1);
}

char *ConvertStringToDNS(const char *Hostname, uint16_t *length)
{
	int start = 0;
	int end = 0;
	size_t slen = strlen(Hostname);
	char *output = calloc(1, slen + 2);
	if (!output)
		return NULL;
	char dot = '.';
	//TODO: Algorithm fails if first character is a dot
	for (size_t i = 0; i < slen; i++)
	{
		if (Hostname[i] == '.')
		{
			// compute length and part of string
			output[start] = end - start;
			memcpy(output + start + 1, Hostname + start, end - start);
			start = i + 1;
			end = i + 1;
		}
		else
		{
			end = i + 1;
		}

		if (i == (slen - 1))
		{
			// last character, so compute stuffs
			output[start] = end - start;
			memcpy(output + start + 1, Hostname + start, end + 1 - start);
		}
	}
	*length = end + 2;
	return output;
}

uint32_t GetHostByName(const DNSClientRequest *Request, DNSClientResponse *Response)
{
	int sock = 0;
	struct sockaddr_in DNSServerAddr;
	unsigned short DNSServerPort = 53;
	char *DNSServerIP = "8.8.8.8";
	char *DNSQuery;
	int DNSQueryLen = 0;
	WSADATA wsaData;

	uint16_t TempBuff = 0;

	// TODO: Calculate the buffer required more accurately
	DNSQuery = calloc(1, 512);
	if (!DNSQuery)
		DNSClient_DieWithError("calloc() error 1");

#ifdef _WIN32
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
		DNSClient_DieWithError("WSAStartup() failed\n");
	}
#endif

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DNSClient_DieWithError("socket() failed");
	
	memset(&DNSServerAddr, 0, sizeof(DNSServerAddr));
	DNSServerAddr.sin_family = AF_INET;
	DNSServerAddr.sin_addr.s_addr = inet_addr(DNSServerIP);
	DNSServerAddr.sin_port = htons(DNSServerPort);

	if (connect(sock, (struct sockaddr *) &DNSServerAddr, sizeof(DNSServerAddr)) < 0)
		DNSClient_DieWithError("connect() failed");
	
	TempBuff = htons(Request->TransactionID);
	memcpy(DNSQuery + DNSQueryLen, &TempBuff, sizeof(Request->TransactionID));
	DNSQueryLen += 2;
	TempBuff = htons(Request->Flags);
	memcpy(DNSQuery + DNSQueryLen, &TempBuff, sizeof(Request->Flags));
	DNSQueryLen += 2;
	TempBuff = htons(Request->Questions);
	memcpy(DNSQuery + DNSQueryLen, &TempBuff, sizeof(Request->Questions));
	DNSQueryLen += 2;
	TempBuff = htons(Request->AnswerRRs);
	memcpy(DNSQuery + DNSQueryLen, &TempBuff, sizeof(Request->AnswerRRs));
	DNSQueryLen += 2;
	TempBuff = htons(Request->AuthorityRRs);
	memcpy(DNSQuery + DNSQueryLen, &TempBuff, sizeof(Request->AuthorityRRs));
	DNSQueryLen += 2;
	TempBuff = htons(Request->AdditionalRRs);
	memcpy(DNSQuery + DNSQueryLen, &TempBuff, sizeof(Request->AdditionalRRs));
	DNSQueryLen += 2;

	char *t;
	uint16_t HostnameLength;
	t = ConvertStringToDNS(Request->Hostname, &HostnameLength);
	if (!t)
	{
		free(DNSQuery);
		return -1;
	}
	memcpy(DNSQuery + DNSQueryLen, t, HostnameLength);
	DNSQueryLen += HostnameLength;
	free(t);

	TempBuff = htons(Request->RecordType);
	memcpy(DNSQuery + DNSQueryLen, &TempBuff, sizeof(Request->RecordType));
	DNSQueryLen += 2;
	TempBuff = htons(Request->ClassType);
	memcpy(DNSQuery + DNSQueryLen, &TempBuff, sizeof(Request->ClassType));
	DNSQueryLen += 2;
	
	if (send(sock, DNSQuery, DNSQueryLen, 0) != DNSQueryLen)
		DNSClient_DieWithError("send() sent a different number of bytes than expected");

#ifdef _WIN32
	closesocket(sock);
	WSACleanup();
#else
	close(sock);
#endif

	free(DNSQuery);

	return 0;
}
