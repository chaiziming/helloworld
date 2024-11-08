CC := gcc

system_test: system_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_test: fork_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_fd_test: fork_fd_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

erlou: erlou.c
	-$(CC) -o $@ $^

execve_test: execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_execve_test: fork_execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

waitpid_test: waitpid_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pstree_test: pstree_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

perror_test: perror_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

process_test: process_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_pipe_test: unnamed_pipe_test.c
	-$(CC) -o $@ $^
	-./$@ test
	-rm ./$@

fifo_read_test: fifo_read_test.c
	-$(CC) -o $@ $^


fifo_write_test: fifo_write_test.c
	-$(CC) -o $@ $^


shared_memery: shared_memery.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
	
mq_test: mq_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

producer: producer.c
	-$(CC) -o $@ $^

consumer: consumer.c
	-$(CC) -o $@ $^

signal_test: signal_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@
