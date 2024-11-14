CC := gcc

detach: detach.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

terminate_test: terminate_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

create_pthread: create_pthread.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pthread_cancel_deferred: pthread_cancel_deferred.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

pthread_cancel_sync: pthread_cancel_sync.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@