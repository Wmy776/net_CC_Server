net_CC_Server: main.o servernet.o
	$(CC) $(LDFLAGS) main.o servernet.o -o net_CC_Server
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
servernet.o: servernet.c
	$(CC) $(CFLAGS) -c servernet.c

clean:
	rm *.o net_CC_Server
