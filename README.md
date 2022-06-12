# PA2-DNS-Client
This reposatory is part of a small project I did in my B.sc in Elecrical engineering at [Tel-Aviv University](https://www.tau.ac.il). The project about computer comunication and networks. The project simulates *nslookup* functionality. For a given *Domain name* the program will execute a *DNS Query* and will return to the user all the IP Addresses of the given domain name. The query will be executed according to [RFC 1035](https://www.ietf.org/rfc/rfc1035.txt).

---------------------------------------------------------------------------------------

### *Description & Functuinallity*:

The purpose of this exercise is to implement a DNS client, and impement the functionality of [*gethostbyname()*](https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-gethostbyname) [using DnsQuery()](https://docs.microsoft.com/en-us/windows/win32/api/windns/nf-windns-dnsquery_a).
When executing the program, the program gets an IP address as an argument, in dotted-decimal notation. the IP address must be a valid IP address of a DNS server.
The nsclient program prompt on the stdout the user to input a domain name. 
The domain names are case insensitive, meaning: 'abcde.net' = 'AbCdE.nEt'.
After inputting a domain name the program will perform a DNS Query ([More Information - ClouDNS](https://www.cloudns.net/wiki/article/254/)) and will return the IP addresses that corespond with the domain name, if it is in fact a valid domain name, else it will return an informative error message.
#### Error messages:
1. `ERROR : INVALID NAME`  
This message correspond with error code '123', and printed out when domain name is structurally not valid

2. `ERROR : DOMAIN NAME DOES NOT EXIST`  
This message correspond with error code '9003', and printed out when the domain name is valid, but do not exist.

3. `ERROR : DOMAIN NAME CONTAINS AN INVALID CHARACTER`  
This message correspond with error code '9560', and printed out when there is an invalid character such as ' ' or '@'.

4. `ERROR : TIMEOUT`  
This message correspond witherror code '1460', and printed out when the dns query timeout period expired ([TTL](https://en.wikipedia.org/wiki/Time_to_live)).

5. `Failed to query the host record for '%domain_name_input' and the error code is '%Error_code_number'`  
This message is a general case message. when error occured and it is not of the above, this message will print out with the corresponding domain name and error code.

For each time the user inputs a domain name a stuct HOSTENT is created with the wanted host information.
For exiting the program the user inputs 'quit', case insensitive.

For more information on *Windows Error Code*: [Debug system error codes](https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes).  
For more information on *DNS*: [Domain Name System - Wikipedia](https://en.wikipedia.org/wiki/Domain_Name_System).  


### *Nsclient's Examplery Run*:
![nsclient_run](https://user-images.githubusercontent.com/34989887/170880017-11172fe8-1a07-4b46-af54-91189d3a4ce2.png)


### **Comiplation**:
1. Compile via Visual Studio -
- Open project in Visual Studio.
- Build Solution & Run (F5/ctrl + F5).
2. Compile via Developer Command Prompt for VS -
- Open Developer 'Command Prompt for VS' (application file inside 'Visual Studio Tools' directory).
- Go to directory of the wanted C file.
- Type on the Command Prompt :`cl /EHsc name.c` (name of the file instead of 'name.c').
- Type command for the executable file: 'name argument1 argument2'
* For more information : [https://docs.microsoft.com](https://docs.microsoft.com/en-us/cpp/build/walkthrough-compiling-a-native-cpp-program-on-the-command-line?view=msvc-170).


### **Operation & Conditions**:
1. Maximum input length is 256 character, so it could store even the longest subdomain name.
2. The IP address when executing `nsclient 'ip_address'` must be of a valid DNS server, else will be outputed TIMEOUT error message.
3. The program gives all the IP addresses that corresponds to the domain name given.
4. If the input is `localhot` the program will return `127.0.0.1`, even for an invalid DNS IP address.
5. The program deals with CNAME, if given a [CNAME Record](https://en.wikipedia.org/wiki/CNAME_record) the program will return the canonical name IP address.
6. The program will return only IPv4 addresses And will ignore IPv6 addresses.
7. Part of the exercise demands was to maintain a [struct HOSTENT](https://docs.microsoft.com/en-us/windows/win32/api/winsock2/ns-winsock2-hostent), so every call of the fuction also create a struct HOSTENT with the wanted host information.
