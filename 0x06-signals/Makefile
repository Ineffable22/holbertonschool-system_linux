0:
	cp files/0-main.c .
	gcc -Wall -Wextra -Werror -pedantic 0-main.c 0-handle_signal.c -o 0-handle_signal
	rm 0-main.c
	./0-handle_signal

1:
	cp files/1-main.c .
	gcc -Wall -Wextra -Werror -pedantic 1-main.c 1-set_print_hello.c 1-current_handler_signal.c -o 1-current_handler_signal
	rm 1-main.c
	./1-current_handler_signal
2:
	cp files/2-main.c .
	gcc -Wall -Wextra -Werror -pedantic 2-main.c 2-handle_sigaction.c -o 2-handle_sigaction
	rm 2-main.c
	./2-handle_sigaction

3:
	cp files/3-main.c .
	gcc -Wall -Wextra -Werror -pedantic 3-main.c 3-set_print_hello.c 3-current_handler_sigaction.c -o 3-current_handler_sigaction
	rm 3-main.c
	./3-current_handler_sigaction

4:
	cp files/4-main.c .
	gcc -Wall -Wextra -Werror -pedantic 4-main.c 4-trace_signal_sender.c -o 4-trace_signal_sender
	rm 4-main.c
	./4-trace_signal_sender

5:
	gcc -Wall -Wextra -Werror -pedantic 5-signal_describe.c -o 5-signal_describe
	./5-signal_describe 1
	./5-signal_describe 9
	./5-signal_describe 3
	./5-signal_describe 2
	./5-signal_describe 0
	./5-signal_describe 100
	./5-signal_describe 20

6:
	gcc -Wall -Wextra -Werror -pedantic 6-suspend.c -o 6-suspend
	./6-suspend
	rm 6-suspend

7:
	cp files/7-main.c .
	gcc -Wall -Wextra -Werror -pedantic 7-main.c -o 7-wait_for_it
	rm 7-main.c
	./7-wait_for_it

7.1:
	gcc -Wall -Wextra -Werror -pedantic 7-signal_send.c -o 7-signal_send
	./7-signal_send

8:
	cp files/8-main.c .
	gcc -Wall -Wextra -Werror -pedantic 8-main.c -o 8-wait_for_it
	rm 8-main.c
	./8-wait_for_it

8.1:
	sh ./8-signal_send.sh

9:
	cp files/9-main.sh .
	sh 9-main.sh

9.1:
	sh 9-handle_signal.sh

10:
	cp files/10-main.c .
	gcc -Wall -Wextra -Werror -pedantic 10-main.c 10-pid_exist.c -o 10-pid_exist
	rm 10-main.c
	./10-pid_exist 1
	./10-pid_exist 2
	./10-pid_exist 1234
	./10-pid_exist 98
	./10-pid_exist 890

100:
	cp files/100-main.c .
	gcc -Wall -Wextra -Werror -pedantic 100-main.c 100-all_in_one.c -o 100-all_in_one
	rm 100-main.c
	./100-all_in_one

101:
	cp files/101-main.c .
	gcc -Wall -Wextra -Werror -pedantic 101-main.c 101-sigset_init.c -o 101-sigset_init
	rm 101-main.c
	./101-sigset_init

102:
	cp files/102-main.c .
	gcc -Wall -Wextra -Werror -pedantic 102-main.c 102-signals_block.c -o 102-signals_block
	rm 102-main.c
	./102-signals_block

103:
	cp files/103-main.c .
	gcc -Wall -Wextra -Werror -pedantic 103-main.c 103-signals_unblock.c 102-signals_block.c -o 103-signals_unblock
	rm 103-main.c
	./103-signals_unblock

104:
	cp files/104-main.c .
	gcc -Wall -Wextra -Werror -pedantic 104-main.c 104-handle_pending.c 102-signals_block.c 103-signals_unblock.c -o 104-handle_pending
	rm 104-main.c
	./104-handle_pending

kill: clean
	./kprocess $(ARGS)

betty:
	betty *.c files/*.c

clean:
	rm *~ -f 0-handle_signal
	rm -f 1-current_handler_signal
	rm -f 2-handle_sigaction
	rm -f  3-current_handler_sigaction
	rm -f  4-trace_signal_sender
	rm -f  5-signal_describe
	rm -f  6-suspend
	rm -f 7-wait_for_it 7-signal_send
	rm -f 8-wait_for_it
	rm -f 9-main.sh
	rm -f 10-pid_exist
	rm -f 100-all_in_one
	rm -f 101-sigset_init
	rm -f 102-signals_block
	rm -f 103-signals_unblock
	rm -f 104-handle_pending
