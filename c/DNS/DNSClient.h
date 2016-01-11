#ifndef DNSCLIENT_H_ONCE
#define DNSCLIENT_H_ONCE

#include <stdint.h>

#define RCVBUFFSIZE 32 

typedef struct DNSClientRequest
{
	uint16_t TransactionID;
	uint16_t Flags;
	uint16_t Questions;
	uint16_t AnswerRRs;
	uint16_t AuthorityRRs;
	uint16_t AdditionalRRs;
	char *Hostname;
	uint16_t RecordType;
	uint16_t ClassType;
} DNSClientRequest;

typedef struct DNSClientResponseFlags
{
	uint32_t Response : 1;
	uint32_t Opcode : 4;
	uint32_t Authoritative : 1;
	uint32_t Truncated : 1;
	uint32_t RecursionDesired : 1;
	uint32_t RecursionAvailable : 1;
	uint32_t Reserved_Z : 1;
	uint32_t AnswerAuthenticated : 1;
	uint32_t NonAuthenticatedData : 1;
	uint32_t ReplyCode : 4;
} DNSClientResponseFlags;

typedef struct DNSClientResponseHost
{
	char *HostName;
	uint16_t HostType;
	uint16_t HostClass;
} DNSClientResponseHost;

typedef struct DNSClientResponseAnswers
{
	uint16_t Name;
	uint16_t HostType;
	uint16_t HostClass;
	uint32_t HostTTL;
	uint16_t DataLength;
	uint32_t HostAddress;
} DNSClientResponseAnswers;

typedef struct DNSClientResponse
{
	uint16_t TransactionID;
	DNSClientResponseFlags Flags;
	uint16_t Questions;
	uint16_t AnswerRRs;
	uint16_t AuthorityRRs;
	uint16_t AdditionalRRs;
	DNSClientResponseHost *Queries;
	DNSClientResponseAnswers *Answers;
} DNSClientResponse;



uint32_t GetHostByName(const DNSClientRequest *Request, DNSClientResponse *Response);

#endif DNSCLIENT_H_ONCE