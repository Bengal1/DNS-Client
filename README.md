# PA2-DNS-Client
This reposatory is part of a small project I did in my B.sc in Elecrical engineering at [Tel-Aviv University](https://www.tau.ac.il). The project about computer comunication and networks. The project simulates .... 

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

For more information on *Hamming Code* :
- [3Blue1Brown](https://www.youtube.com/watch?v=X8jsijhllIA&t=906s) - 2 Videos which explains it well in simple language.
- [Wikipedia](https://en.wikipedia.org/wiki/Hamming_code) - there are a lot of websites and books that explain hamming code well.

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
1. The first file must be channel.c such that we will have the ports numbers and ip number. the order doesn't matter between sender.c and receiver.c.
2. To continue to another channel interval answer 'yes' (case-unsensitive), every other answer will stop channel's run.
3. To continue to another sender/receiver interval put in an existing file name with suffix to be read, non-valid name will end the run.
4. To end sender/receiver run put in 'quit' (case-unsensitive) when asked for file name.
5. Channel's noise: the noise parameter is in hamming border of success.
