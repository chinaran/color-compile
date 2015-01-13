CFLAGS	:= -Wall
OBJ	:= color_compile out_color_info
ALIAS_FILE	:= ~/.bashrc

all: $(OBJ)

color_compile: color_compile.o
	gcc -o $@ $^

out_color_info: out_color_info.o
	gcc -o $@ $^

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o $(OBJ)


install:
	cp color_compile /usr/local/bin/
	cp out_color_info /usr/local/bin/

	echo 'alias gcc="color_compile gcc"' >> $(ALIAS_FILE)
	echo 'alias g++="color_compile g++"' >> $(ALIAS_FILE)
	echo 'alias make="color_compile make"' >> $(ALIAS_FILE)

TEST:
	gcc test.c -Wall