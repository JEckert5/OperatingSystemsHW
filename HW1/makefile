OPTS = -pthread -lrt

hw:
	gcc producer.c $(OPTS) -o producer
	gcc consumer.c $(OPTS) -o consumer
	

clean:
	rm consumer
	rm producer
