all:net_CC_Server

CC = gcc
INCLUDE = ./include/
SRC = ./src/
BUILD = ./build/
INSDIR = /usr/bin/


net_CC_Server: $(BUILD)main.o $(BUILD)servernet.o
	$(CC) -o net_CC_Server $(BUILD)main.o $(BUILD)servernet.o

$(BUILD)main.o: $(SRC)main.c
	$(CC) -I$(INCLUDE) -c $(SRC)main.c -o $(BUILD)main.o

$(BUILD)servernet.o: $(SRC)servernet.c
	$(CC) -I$(INCLUDE) -c $(SRC)servernet.c -o $(BUILD)servernet.o

clean:
	-rm $(BUILD)*.o net_CC_Server

install: net_CC_Server
	@echo "Now installing!"
	@if [ -d $(INSDIR) ] ; \
	then \
		echo "The $(INSDIR) is exist!" ;\
		else \
			mkdir $(INSDIR) ;\
			echo "The $(INSDIR) is not exist!now creating!" ;\
	fi
	@if [ -d $(INSDIR) ] && [ -f ./net_CC_Server ] ; \
	then \
		sudo cp net_CC_Server $(INSDIR) ; \
		echo "Install successful!" ; \
	else \
		echo "Install Failed!" ; \
	fi 

uninstall: 
	@echo "Now uninstalling!"
	@if [ -f $(INSDIR)net_CC_Server ] ; \
	then \
		echo "Delete net_CC_Server!" ; \
		sudo rm $(INSDIR)net_CC_Server ; \
	else \
		echo "It's not installed!" ; \
	fi
