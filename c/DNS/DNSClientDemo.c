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

void DieWithError(char *errorMessage)
{
#ifdef _WIN32
	fprintf(stderr, "%s: %d\n",
		errorMessage, WSAGetLastError());
#else
	perror(errorMessage);
#endif
	getchar();
	exit(1);
}

int main(int argc, char *argv)
{
	DNSClientRequest *request = NULL;
	DNSClientResponse *response = NULL;
	request = calloc(1, sizeof(DNSClientRequest));
	response = calloc(1, sizeof(DNSClientResponse));
	if ((!request) 
		|| (!response)
		)
		DieWithError("calloc() error");
	request->AdditionalRRs = 0;
	request->AnswerRRs = 0;
	request->AuthorityRRs = 0;
	request->Questions = 1;
	request->TransactionID = 256;
	request->RecordType = 1; // A
	request->ClassType = 1; // IN
	request->Flags = 256;
	request->Hostname = "google.com";
	GetHostByName(request, response);

	printf("%s\n", response->Answers->HostAddressString);
	getchar();

	return 0;
}