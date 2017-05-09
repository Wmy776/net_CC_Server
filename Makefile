net_CC_Server: ./build/main.o ./build/servernet.o
	cc ./build/main.o ./build/servernet.o -o net_CC_Server
./build/main.o: ./src/main.c
	cc -c ./src/main.c -o ./build/main.o
./build/servernet.o: ./src/servernet.c
	cc -c ./src/servernet.c -o ./build/servernet.o

clean:
	rm ./build/*.o net_CC_Server
