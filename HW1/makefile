C = gcc
OPTS = -pthread -lrt

hw:
	$(C) producer.c $(OPTS) -o producer
	$(C) consumer.c $(OPTS) -o consumer
	

clean:
	rm consumer
	rm producer
