OPTS = -pthread -lrt

hw:
	gcc producer.c $(OPTS) -o producer
	gcc consumer.c $(OPTS) -o consumer

clean:
	gcc delTable.c $(OPTS) -o del
	./del
	rm consumer
	rm producer
	rm del
