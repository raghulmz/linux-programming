CC=gcc
VERBOSE="V=1"

# pthread for sempahore
# lrt for shm
CC_OPT=-pthread -lrt 

producer: producer.c common.h
	$(CC) -o producer producer.c common.h  $(CC_OPT) 

test-producer: producer
	./producer

consumer: consumer.c common.h
	$(CC) -o consumer consumer.c common.h  $(CC_OPT) 

test-consumer: consumer
	./consumer

clean:
	rm -f producer consumer