#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#include <windows.h>
#include <winsock2.h> //winsock
#include <ws2tcpip.h>
#include <windns.h>   //DNS API's
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Dnsapi.lib")

#define IP_LENGTH 16
#define MAX_INPUT_LENGTH 256
#define QUIT "quit"


void free_host(HOSTENT* host, int num_of_ip) 
{
	HOSTENT* r_host = host;
	
	//free ip addresses
	for (int i = 0; i < num_of_ip; i++) {
		free(host->h_addr_list[i]);
	}

	free(host->h_addr_list);
	free(host);

	return;
}

char* lowercase(const char* str)
{
	int str_size = strlen(str);
	char* str_before = str, * str_after = NULL;

	if ((str_after = (char*)calloc(1, (str_size + 1) * sizeof(char))) == NULL) {
		perror("calloc");
		exit(EXIT_FAILURE);
	}

	if (str != NULL) {
		for (int i = 0; i < str_size; i++) {
			(*(str_after + i)) = tolower((*(str_before + i)));
		}
	}
	else {
		printf("Attempt to operate on NULL pointer\n");
		return NULL;
	}
	return str_after;
}

void print_dns_error(const DNS_STATUS stat, PDNS_RECORD pDnsRecord, char* domain_name)
{

	switch (stat) {
	case 123: {
		printf("ERROR : INVALID NAME\n");
		break;
	}
	case 9003: {
		printf("ERROR : DOMAIN NAME DOES NOT EXIST\n");
		break;
	}
	case 9560: {
		printf("ERROR : DOMAIN NAME CONTAINS AN INVALID CHARACTER\n");
		break;
	}
	case 1460: {
		printf("ERROR : TIMEOUT\n");
		break;
	}
	default: {
		printf("Failed to query the host record for %s and the error code is %d\n", domain_name, stat);
		break;
	}
	}
	// free resources
	DnsRecordListFree(pDnsRecord, DnsFreeRecordListDeep);
	free(domain_name);

	return;
}

HOSTENT* init_hostent_struct(const PDNS_RECORD pQRecord, const char* host_domain,int* max_ip)
{
	int ip_num = 0;
	HOSTENT* r_host = NULL;
	PDNS_RECORD q_record = NULL;

	q_record = pQRecord;

	if ((r_host = (HOSTENT*)malloc(sizeof(HOSTENT))) == NULL) {
		perror("malloc");
		return NULL;
	}
	r_host->h_name = host_domain;
	r_host->h_addrtype = AF_INET;
	r_host->h_length = pQRecord->wDataLength;
	r_host->h_aliases = NULL;

	while (q_record != NULL) {
		if (q_record->wType == 1)
			(ip_num)++;
		q_record = q_record->pNext;
	}

	*max_ip = ip_num;

	if ((r_host->h_addr_list = (char**)calloc(ip_num, sizeof(char*))) == NULL) {
		perror("calloc");
		return NULL;
	}

	return r_host;
}

HOSTENT* create_host_and_print(const PDNS_RECORD pDnsRecord, char* domain_name, int* num_of_ip)
{
	int ip_num = 0, i = 0;
	char* domain = domain_name, *ip_address = NULL;
	PDNS_RECORD current_record, previous_record;
	IN_ADDR ip_addr = { 0 };
	HOSTENT* remote_host = NULL;
	
	current_record = pDnsRecord;

	remote_host = init_hostent_struct(pDnsRecord, domain, &ip_num);
	
	while ((current_record != NULL)) {
		ip_addr.s_addr = (current_record->Data.A.IpAddress);
		switch (current_record->wType) {
		case 1: { //IPv4
			if (!(strcmp(domain, (char *)(current_record->pName)))) {
				if ((remote_host->h_addr_list[i] = (char*)calloc(1, (IP_LENGTH + 1) * sizeof(char))) == NULL) {
					perror("calloc");
					return NULL;
				}
				memcpy((remote_host->h_addr_list[i]), inet_ntoa(ip_addr), IP_LENGTH);
				printf(" > %s\n", (remote_host->h_addr_list[i]));
				i = i < ip_num ? i + 1 : i;
				break;
			}
			else {
				break;
			}
		}
		case 5: { //CNAME
			domain = current_record->Data.pDataPtr;
			remote_host->h_name = domain;
			break;
		}
		case 28: { //IPv6
			break;
		}
		default:
			break;
		}
		previous_record = current_record;
		current_record = previous_record->pNext;
	}
	*num_of_ip = i;

	// free resources
	DnsRecordListFree(pDnsRecord, DnsFreeRecordListDeep);
	if(domain_name != NULL)
		free(domain_name);

	return remote_host;
}

int main(int argc, char* argv[]) 
{
	int num_of_ip = 0;
	HOSTENT* remote_host = NULL;
	DNS_STATUS status;
	PIP4_ARRAY pSrvList = NULL;
	PDNS_RECORD pDnsRecord = NULL;
	char dns_ip[IP_LENGTH] = { '\0' }, domain_name[MAX_INPUT_LENGTH] = { '\0' }, *domain_lowercase = NULL;
	
	if (argc == 2) {
		strcpy(dns_ip, argv[1]); // get DNS server IP address

		if ((pSrvList = (PIP4_ARRAY)LocalAlloc(LPTR, sizeof(IP4_ARRAY))) == NULL) { // Allocate memory for DNS IP Address
			printf("Error: Memory allocation failed with error code: %d\n", GetLastError());
			return EXIT_FAILURE;
		}
		pSrvList->AddrCount = 1;
		pSrvList->AddrArray[0] = inet_addr(dns_ip);
	}
	else {
		printf("Error: Too many arguments\n Closing...\n");
		return EXIT_FAILURE;
	}

	while (1) {
		printf("nsclient> ");
		gets_s(domain_name, MAX_INPUT_LENGTH);

		domain_lowercase = lowercase(domain_name);
		if (0 == strcmp(domain_lowercase, QUIT)) {
			printf("Quiting...\n");
			LocalFree(pSrvList);
			return EXIT_SUCCESS;
		}

		status = DnsQuery_A(domain_lowercase, DNS_TYPE_A, DNS_QUERY_STANDARD, pSrvList, (PDNS_RECORD*)&pDnsRecord, NULL);
		if (status) {
			print_dns_error(status, pDnsRecord, domain_lowercase);
		}
		else {
			if ((remote_host = create_host_and_print(pDnsRecord, domain_lowercase, &num_of_ip)) == NULL) {
				printf("Failed to create struct HOSTENT\n");
				return EXIT_FAILURE;
			}
			free_host(remote_host, num_of_ip);
		}
		strcpy(domain_name, "");
	}

	LocalFree(pSrvList);
	
	return EXIT_FAILURE;
}