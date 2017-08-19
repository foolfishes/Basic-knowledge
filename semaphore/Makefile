all:window_service producer_consumer
window_service: window_service.o
		g++ -lpthread window_service.o -o window_service
producer_consumer: producer_consumer.o
		g++ -lpthread producer_consumer.o -o producer_consumer
window_service.o: window_service.cpp
		g++ -g -Wall -lpthread -c window_service.cpp
producer_consumer.o: producer_consumer.cpp
		g++ -g -Wall -lpthread -c producer_consumer.cpp

.PHONY:clean

clean:
		rm window_service.o producer_consumer.o

