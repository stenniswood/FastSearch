CC=g++
OPTIONS	= -std=C11 -lm -fno-rtti 
INC	= /usr/include/mysql/
SELF_INC= ./
CFLAGS 	= -lm -g
DEPS   	= 
OBJ     =   main.o sql_file_indexer.o

CPPOBJ    = 

LDFLAGS = -L /usr/lib/mysql -lmysqlclient -lpthread -lrt

%.o: %.cpp $(DEPS)
	$(CC) $(addprefix -I,$(INC)) -c -o $@ $< $(CFLAGS)
%.o: %.c $(DEPS)
	$(CC) $(addprefix -I,$(INC)) $(addprefix -I,$(SELF_INC)) -c -o $@ $< $(OPTIONS) $(CFLAGS)
	
ffs: $(OBJ)
	$(CC) -o  $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o $(PRG).elf *.bak 
	rm -rf ../core/can/*.o
	rm -rf ../core/msg/*.o
	rm -rf ../core/misc/*.o
	rm -rf *.lst *.map

