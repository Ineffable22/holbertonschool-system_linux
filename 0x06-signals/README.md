# 0x06. C - Signals

## Description:

# Files

### 0. Handle signal
### [0-handle_signal.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/0-handle_signal.c)

```C
alex@~/0x06-signals$ cat 0-main.c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "signals.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    int i;

    if (handle_signal() == -1)
    {
        printf("Failure\n");
        return (EXIT_FAILURE);
    }
    for (i = 0; ; i++)
    {
        printf("[%d] Wait for it ...\n", i);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 0-main.c 0-handle_signal.c -o 0-handle_signal
alex@~/0x06-signals$ ./0-handle_signal 
[0] Wait for it ...
[1] Wait for it ...
[2] Wait for it ...
^CGotcha! [2]
[3] Wait for it ...
^CGotcha! [2]
[4] Wait for it ...
[5] Wait for it ...
^CGotcha! [2]
[6] Wait for it ...
[7] Wait for it ...
^CGotcha! [2]
[8] Wait for it ...
[9] Wait for it ...
^\Quit (core dumped)
alex@~/0x06-signals$

```

### 1. Current handler - signal
### [1-current_handler_signal.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/1-current_handler_signal.c)

```C
alex@~/0x06-signals$ cat 1-main.c 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "signals.h"

/* Our functions */
void print_hello(int);
void set_print_hello(void);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    void (*handler)(int);
    int i;

    handler = current_handler_signal();
    printf("Address of the current handler: %#lx\n", (unsigned long int)handler);

    /* Set 'print_hello()` as the handler for SIGINT */
    set_print_hello();

    handler = current_handler_signal();
    printf("Address of the 'print_hello' function: %#lx\n", (unsigned long int)&print_hello);
    printf("Address of the current handler: %#lx\n", (unsigned long int)handler);

    for (i = 0; ; i++)
    {
        printf("[%d] Wait for it ...\n", i);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 1-main.c 1-set_print_hello.c 1-current_handler_signal.c -o 1-current_handler_signal
alex@~/0x06-signals$ ./1-current_handler_signal
Address of the current handler: 0
Address of the 'print_hello' function: 0x4006da
Address of the current handler: 0x4006da
[0] Wait for it ...
[1] Wait for it ...
^CHello :)
[2] Wait for it ...
^CHello :)
[3] Wait for it ...
[4] Wait for it ...
^CHello :)
[5] Wait for it ...
^\Quit (core dumped)
alex@~/0x06-signals$

```

### 2. Gotta catch them all
### [2-handle_sigaction.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/2-handle_sigaction.c)

```C
alex@~/0x06-signals$ cat 2-main.c 
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "signals.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    int i;

    if (handle_sigaction() == -1)
    {
        printf("Failure\n");
        return (EXIT_FAILURE);
    }
    for (i = 0; ; i++)
    {
        printf("[%d] Wait for it ...\n", i);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 2-main.c 2-handle_sigaction.c -o 2-handle_sigaction
alex@~/0x06-signals$ ./2-handle_sigaction 
[0] Wait for it ...
[1] Wait for it ...
^CGotcha! [2]
[2] Wait for it ...
[3] Wait for it ...
^CGotcha! [2]
[4] Wait for it ...
^CGotcha! [2]
[5] Wait for it ...
^CGotcha! [2]
[6] Wait for it ...
[7] Wait for it ...
^CGotcha! [2]
[8] Wait for it ...
^\Quit (core dumped)
alex@~/0x06-signals$

```

### 3. Current handler - sigaction
### [3-current_handler_sigaction.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/3-current_handler_sigaction.c)

```C
alex@~/0x06-signals$ cat 3-main.c 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "signals.h"

/* Our functions */
void print_hello(int);
void set_print_hello(void);

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    void (*handler)(int);
    int i;

    handler = current_handler_sigaction();
    printf("Address of the current handler: %#lx\n", (unsigned long int)handler);

    /* Set 'print_hello()` as the handler for SIGINT */
    set_print_hello();

    handler = current_handler_sigaction();
    printf("Address of the 'print_hello' function: %#lx\n", (unsigned long int)&print_hello);
    printf("Address of the current handler: %#lx\n", (unsigned long int)handler);

    for (i = 0; ; i++)
    {
        printf("[%d] Wait for it ...\n", i);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 3-main.c 3-set_print_hello.c 3-current_handler_sigaction.c -o 3-current_handler_sigaction
alex@~/0x06-signals$ ./3-current_handler_sigaction 
Address of the current handler: 0
Address of the 'print_hello' function: 0x4006ea
Address of the current handler: 0x4006ea
[0] Wait for it ...
[1] Wait for it ...
^CHello :)
[2] Wait for it ...
^CHello :)
[3] Wait for it ...
[4] Wait for it ...
^CHello :)
[5] Wait for it ...
^CHello :)
[6] Wait for it ...
^\Quit (core dumped)
alex@~/0x06-signals$

```

### 4. Who said that?!
### [4-trace_signal_sender.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/4-trace_signal_sender.c)

```C
alex@~/0x06-signals$ cat 4-main.c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "signals.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    int i;

    if (trace_signal_sender() == -1)
    {
        printf("Failure\n");
        return (EXIT_FAILURE);
    }
    for (i = 0; ; i++)
    {
        printf("[%d] Wait for it ...\n", i);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 4-main.c 4-trace_signal_sender.c -o 4-trace_signal_sender
alex@~/0x06-signals$ ./4-trace_signal_sender
[0] Wait for it ...
[1] Wait for it ...
^\SIGQUIT sent by 0
[2] Wait for it ...
^\SIGQUIT sent by 0
[3] Wait for it ...
^\SIGQUIT sent by 0
[4] Wait for it ...
[5] Wait for it ...
^\SIGQUIT sent by 0
[6] Wait for it ...
[7] Wait for it ...
[8] Wait for it ...
SIGQUIT sent by 95337
[9] Wait for it ...
^C
alex@~/0x06-signals$

```

### 5. Description
### [5-signal_describe.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/5-signal_describe.c)

```C
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 5-signal_describe.c -o 5-signal_describe
alex@~/0x06-signals$ ./5-signal_describe
Usage: ./5-signal_describe <signum>
alex@~/0x06-signals$ ./5-signal_describe 1
1: Hangup
alex@~/0x06-signals$ ./5-signal_describe 9
9: Killed
alex@~/0x06-signals$ ./5-signal_describe 3
3: Quit
alex@~/0x06-signals$ ./5-signal_describe 2
2: Interrupt
alex@~/0x06-signals$ ./5-signal_describe 0
0: Unknown signal 0
alex@~/0x06-signals$ ./5-signal_describe 100
100: Unknown signal 100
alex@~/0x06-signals$ ./5-signal_describe 20
20: Stopped
alex@~/0x06-signals$

```

### 6. Catch a single time
### [6-suspend.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/6-suspend.c)

```C
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 6-suspend.c -o 6-suspend
alex@~/0x06-signals$ ./6-suspend 
^CCaught 2
Signal received
alex@~/0x06-signals$ echo $?
0
alex@~/0x06-signals$

```

### 7. Sending a signal
### [7-signal_send.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/7-signal_send.c)

```C
alex@~/0x06-signals$ cat 7-main.c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - Simple program, printing its PID and running infinitely
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    pid_t pid;

    pid = getpid();
    printf("PID: %d\n", (int)pid);
    while (98)
    {
        printf("Waiting ...\n");
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 7-main.c -o 7-wait_for_it
alex@~/0x06-signals$ ./7-wait_for_it 
PID: 98631
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...

alex@~/0x06-signals$

```

### 8. Sending a signal in a shell
### [8-signal_send.sh](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/8-signal_send.sh)

```C
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 7-signal_send.c -o 7-signal_send
alex@~/0x06-signals$ ./7-signal_send
Usage: ./7-signal_send <pid>
alex@~/0x06-signals$ ./7-signal_send 98631
alex@~/0x06-signals$

```

### 9. Catch with sh
### [9-handle_signal.sh](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/9-handle_signal.sh)

```C
alex@~/0x06-signals$ cat 8-main.c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - Simple program, printing its PID and running infinitely
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    pid_t pid;

    pid = getpid();
    printf("PID: %d\n", (int)pid);
    while (98)
    {
        printf("Waiting ...\n");
        sleep(1);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 8-main.c -o 8-wait_for_it
alex@~/0x06-signals$ ./8-wait_for_it 
PID: 98988
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...
Waiting ...

alex@~/0x06-signals$

```

### 10. Does it exist?
### [10-pid_exist.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/10-pid_exist.c)

```C
alex@~/0x06-signals$ sh ./8-signal_send.sh
Usage: ./8-signal_send <pid>
alex@~/0x06-signals$ sh ./8-signal_send.sh 98988
alex@~/0x06-signals$

```

### 11. Blog post
### [100-all_in_one.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/100-all_in_one.c)

```C
alex@~/0x06-signals$ cat 9-main.sh
#!/bin/sh
. ./9-handle_signal.sh

echo "PID: $$"

while :
do
    echo "Waiting ..."
    sleep 2
done
alex@~/0x06-signals$ sh 9-main.sh
PID: 99440
Waiting ...
Waiting ...
Nope
Waiting ...
Nope
Waiting ...
Nope
Waiting ...
Nope
Waiting ...
Waiting ...
Nope
Waiting ...
Nope
Waiting ...
Waiting ...
Waiting ...
Nope
Waiting ...
Nope
Waiting ...
Waiting ...
Killed
alex@~/0x06-signals$

```

### 12. I'm saying it's unkillable.
### [101-sigset_init.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/101-sigset_init.c)

```C
alex@~/0x06-signals$ cat 10-main.c 
#include <stdlib.h>
#include <stdio.h>

#include "signals.h"

/**
 * main - Entry point
 * @argc: Arguments counter
 * @argv: Arguments vector
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, const char *argv[])
{
    pid_t pid;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return (EXIT_FAILURE);
    }
    pid = atoi(argv[1]);

    if (pid_exist(pid))
    {
        printf("PID %d exists\n", pid);
    }
    else
    {
        printf("PID %d does not exist\n", pid);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 10-main.c 10-pid_exist.c -o 10-pid_exist
alex@~/0x06-signals$ ./10-pid_exist 1
PID 1 exists
alex@~/0x06-signals$ ./10-pid_exist 2
PID 2 exists
alex@~/0x06-signals$ ./10-pid_exist 1234
PID 1234 does not exist
alex@~/0x06-signals$ ./10-pid_exist 98
PID 98 does not exist
alex@~/0x06-signals$ ./10-pid_exist 890
PID 890 exists
alex@~/0x06-signals$

```

### 13. Sigset
### [102-signals_block.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/102-signals_block.c)

```C
alex@~/0x06-signals$ cat 100-main.c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "signals.h"

/**
 * main - Simple program, printing its PID and running infinitely
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    pid_t pid;

    all_in_one();

    pid = getpid();
    printf("PID: %d\n", (int)pid);
    while (98)
    {
        sleep(2);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 100-main.c 100-all_in_one.c -o 100-all_in_one
alex@~/0x06-signals$ ./100-all_in_one
PID: 101656
^CCaught: Interrupt (Signal sent by the kernel 0 0)
^\Caught: Quit (Signal sent by the kernel 0 0)
^ZCaught: Stopped (Signal sent by the kernel 0 0)
Caught: Hangup (Signal sent by kill() 98081 1000)
Caught: Interrupt (Signal sent by kill() 98081 1000)
Caught: Quit (Signal sent by kill() 98081 1000)
Caught: Illegal instruction (Signal sent by kill() [0x3e800017f21])
Caught: Trace/breakpoint trap (Signal sent by kill() 98081 1000)
Caught: Aborted (Signal sent by kill() 98081 1000)
Caught: Bus error (Signal sent by kill() [0x3e800017f21])
Caught: Floating point exception (Signal sent by kill() [0x3e800017f21])
Caught: User defined signal 1 (Signal sent by kill() 98081 1000)
Caught: Segmentation fault (Signal sent by kill() [0x3e800017f21])
Caught: User defined signal 2 (Signal sent by kill() 98081 1000)
Caught: Broken pipe (Signal sent by kill() 98081 1000)
Caught: Alarm clock (Signal sent by kill() 98081 1000)
Caught: Terminated (Signal sent by kill() 98081 1000)
Caught: Stack fault (Signal sent by kill() 98081 1000)
Caught: Child exited (Signal sent by kill() 98081 -1693514734 1000)
Caught: Continued (Signal sent by kill() 98081 1000)
Caught: Stopped (Signal sent by kill() 98081 1000)
Caught: Stopped (tty input) (Signal sent by kill() 98081 1000)
Caught: Stopped (tty output) (Signal sent by kill() 98081 1000)
Caught: Urgent I/O condition (Signal sent by kill() 98081 1000)
Caught: CPU time limit exceeded (Signal sent by kill() 98081 1000)
Caught: File size limit exceeded (Signal sent by kill() 98081 1000)
Caught: Virtual timer expired (Signal sent by kill() 98081 1000)
Caught: Profiling timer expired (Signal sent by kill() 98081 1000)
Caught: Window changed (Signal sent by kill() 98081 1000)
Caught: I/O possible (Signal sent by kill() 4294967394081)
Caught: Power failure (Signal sent by kill() 98081 1000)
Caught: Bad system call (Signal sent by kill() 98081 1000)
Killed
alex@~/0x06-signals$

```

### 14. Block signals
### [103-signals_unblock.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/103-signals_unblock.c)

```C
alex@~/0x06-signals$ cat 101-main.c
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "signals.h"

/**
 * sigset_print - Prints a signal set
 * @set: Set to be printed
 */
void sigset_print(const sigset_t *set)
{
    int sig;
    int cnt;

    cnt = 0;
    for (sig = 1; sig < NSIG; sig++)
    {
        if (sigismember(set, sig))
        {
            cnt++;
            printf("%d (%s)\n", sig, strsignal(sig));
        }
    }
    if (cnt == 0)
        printf("Empty signal set\n");
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    sigset_t set;
    int signals[] = {
        SIGINT,
        SIGQUIT,
        SIGSEGV,
        SIGTRAP,
        0
    };

    if (sigset_init(&set, signals) == -1)
    {
        fprintf(stderr, "Failed to init sigset\n");
        return (EXIT_FAILURE);
    }
    sigset_print(&set);
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 101-main.c 101-sigset_init.c -o 101-sigset_init
alex@~/0x06-signals$ ./101-sigset_init
2 (Interrupt)
3 (Quit)
5 (Trace/breakpoint trap)
11 (Segmentation fault)
alex@~/0x06-signals$

```

### 15. Unblock signals
### [104-handle_pending.c](https://github.com/Ineffable22/holbertonschool-system_linux/blob/main/0x06-c-signals/104-handle_pending.c)

```C
alex@~/0x06-signals$ cat 102-main.c
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "signals.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    int signals[] = {
        SIGINT,
        SIGQUIT,
        SIGSEGV,
        SIGTRAP,
        0
    };

    if (signals_block(signals) == -1)
    {
        fprintf(stderr, "Failed to block signals\n");
        return (EXIT_FAILURE);
    }
    while (98)
    {
        sleep(5);
    }
    return (EXIT_SUCCESS);
}
alex@~/0x06-signals$ gcc -Wall -Wextra -Werror -pedantic 102-main.c 102-signals_block.c -o 102-signals_block
alex@~/0x06-signals$ ./102-signals_block
^C^C^C^C^C^C^\^\^C^\^\^\^C^C^\^\^\Terminated
alex@~/0x06-signals$

```

