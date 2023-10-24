C = gcc
OPTS = -pthread -lrt

hw: producer consumer
	

producer:
	$(C) producer.c $(OPTS) -o producer

consumer:
	$(C) consumer.c $(OPTS) -o consumer

clean:
	rm consumer
	rm producer
