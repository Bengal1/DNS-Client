# PA2-DNS-Client
This reposatory is part of a small project I did in my B.sc in Elecrical engineering at [Tel-Aviv University](https://www.tau.ac.il). The project about computer comunication and networks. The project simulates .... specify RFC reference and stuff ...

---------------------------------------------------------------------------------------

### *Description & Functuinallity*:

The purpose of this exercise is to implement a DNS client.
When executing the program, the program gets an IP address as an argument. the IP address must be a valid IP address of a DNS server.
The nsclient program prompt on the stdout the user to input a domain name. 
The domain names are case insensitive, meaning: 'abcde.net' = 'AbCdE.nEt'.
After inputting a domain name the program will perform a [DNS Query]() and will return the IP addresses that corespond with the domain name, if it is in fact a valid domain name, else it will return an informative error message.
#### Error messages:
1. `ERROR : INVALID NAME`  
This message correspond with error code '123', and printed out when domain name is structurally not valid

2. `ERROR : DOMAIN NAME DOES NOT EXIST`  
This message correspond with error code '9003', and printed out when the domain name is valid, but do not exist.

3. `ERROR : DOMAIN NAME CONTAINS AN INVALID CHARACTER`  
This message correspond with error code '9560', and printed out when there is an invalid character such as ' ' or '@'.

4. `ERROR : TIMEOUT`  
This message correspond witherror code '1460', and printed out when the dns query timeout period expired (---info link---).

5. `Failed to query the host record for '%domain_name_input' and the error code is '%Error_code_number'`  
This message is a general case message. when error occured and it is not of the above, this message will print out with the corresponding domain name and error code.

For more information on *Windows Error Code*: [Debug system error codes](https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes).

For exiting the program the user inputs 'quit', case insensitive.


### **Comiplation**:
1. Compile via Visual Studio -
- Open project in Visual Studio.
- Build Solution & Run (F5/ctrl + F5).
2. Compile via Developer Command Prompt for VS -
- Open Developer 'Command Prompt for VS' (application file inside 'Visual Studio Tools' directory).
- Go to directory of the wanted C file.
- Type on the Command Prompt :`cl /EHsc name.c` (name of the file instead of 'name.c').
- Type command for the executable file: 'name argument1 argument2'
* for more information : [https://docs.microsoft.com](https://docs.microsoft.com/en-us/cpp/build/walkthrough-compiling-a-native-cpp-program-on-the-command-line?view=msvc-170).


### **Operation & Conditions**:
1. The IP address when executing `nsclient 'ip_address'` must be of a valid DNS server, else will be outputed TIMEOUT error message.
2. The program gives all the IP addresses that corresponds to the domain name given.
3. If the input is `localhot` the program will return `127.0.0.1` even for an invalid DNS IP address.
4. To end sender/receiver run put in 'quit' (case-unsensitive) when asked for file name.
5. Channel's noise: the noise parameter is in hamming border of success.
