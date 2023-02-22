# 0x0C-sockets

# Files

### 0. Listen
### [0-server.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/0-server.c)

```C
alex@~/0x0C-sockets$ gcc -Wall -Wextra -Werror -pedantic -o 0-server 0-server.c 
alex@~/0x0C-sockets$ ./0-server 
Server listening on port 12345

```

### 1. Accept
### [1-server.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/1-server.c)

```C
alex@~/0x0C-sockets$ lsof -i :12345
COMMAND    PID    USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
0-server 24895 vagrant    3u  IPv4 251230      0t0  TCP *:12345 (LISTEN)
alex@~/0x0C-sockets$ killall 0-server
alex@~/0x0C-sockets$

```

### 2. Client
### [2-client.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/2-client.c)

```C
alex@~/0x0C-sockets$ gcc -Wall -Wextra -Werror -pedantic -o 1-server 1-server.c 
alex@~/0x0C-sockets$ ./1-server 
Server listening on port 12345
Client connected: 127.0.0.1
alex@~/0x0C-sockets$

```

### 3. Roger
### [3-server.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/3-server.c)

```C
alex@~/0x0C-sockets$ ./1-client localhost 12345
Connected to localhost:12345
alex@~/0x0C-sockets$

```

### 4. REST API - The Request
### [Makefile](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/Makefile)

```C
alex@~/0x0C-sockets$ ./2-server 
Server listening on port 12345
Client connected: 127.0.0.1

```

### 5. REST API - Queries
### [Makefile](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/Makefile)

```C
alex@~/0x0C-sockets$ gcc -Wall -Wextra -Werror -pedantic -o 2-client 2-client.c 
alex@~/0x0C-sockets$ ./2-client localhost 12345
Connected to localhost:12345
alex@~/0x0C-sockets$

```

### 6. REST API - Headers
### [Makefile](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/Makefile)

```C
alex@~/0x0C-sockets$ gcc -Wall -Wextra -Werror -pedantic -o 3-server 3-server.c 
alex@~/0x0C-sockets$ ./3-server 
Server listening on port 12345
Client connected: 127.0.0.1
Message received: "Holberton School !!!"
alex@~/0x0C-sockets$

```

### 7. REST API - Body parameters
### [Makefile](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/Makefile)

```C
alex@~/0x0C-sockets$ ./3-client localhost 12345 'Holberton School !!!'
Connected to localhost:12345
Sending the message: "Holberton School !!!"
Sent
alex@~/0x0C-sockets$

```

### 8. REST API - Create TODO
### [Makefile](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/Makefile)

```C
alex@~/0x0C-sockets$ make todo_api_0
[...]
alex@~/0x0C-sockets$ ./todo_api_0 
Server listening on port 8080
Client connected: 127.0.0.1
Raw request: "GET /test HTTP/1.1
User-Agent: curl/7.35.0
Host: localhost:8080
Accept: */*

"
Method: GET
Path: /test
Version: HTTP/1.1
Client connected: 127.0.0.1
Raw request: "POST /holberton HTTP/1.1
User-Agent: curl/7.35.0
Host: localhost:8080
Accept: */*

"
Method: POST
Path: /holberton
Version: HTTP/1.1
^C
alex@~/0x0C-sockets$

```

### 9. REST API - Retrieve all TODOs
### [Makefile](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/Makefile)

```C
alex@~/0x0C-sockets$ curl -D - 'http://localhost:8080/test' 2> /dev/null | cat -e
HTTP/1.1 200 OK^M$
^M$
alex@~/0x0C-sockets$ curl -D - -X POST 'http://localhost:8080/holberton' 2> /dev/null | cat -e
HTTP/1.1 200 OK^M$
^M$
alex@~/0x0C-sockets$

```

### 10. REST API - Retrieve a single TODO
### [Makefile](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/Makefile)

```C
alex@~/0x0C-sockets$ make todo_api_1
[...]
alex@~/0x0C-sockets$ ./todo_api_1 
Server listening on port 8080
Client connected: 127.0.0.1
Raw request: "GET /test?value1=holberton&value2=school HTTP/1.1
User-Agent: curl/7.35.0
Host: localhost:8080
Accept: */*

"
Path: /test
Query: "value1" -> "holberton"
Query: "value2" -> "school"
^C
alex@~/0x0C-sockets$

```

### 11. REST API - Delete a TODO
### [Makefile](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x0C-sockets/Makefile)

```C
alex@~/0x0C-sockets$ curl -D - 'http://localhost:8080/test?value1=holberton&value2=school' 2> /dev/null | cat -e
HTTP/1.1 200 OK^M$
^M$
alex@~/0x0C-sockets$

```

