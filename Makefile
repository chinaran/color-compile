CFLAGS	:= -Wall
OBJ	:= color_compile out_color_info
BASH_FILE	:= ~/.bashrc
ZSH_FILE	:= ~/.zshrc

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

	echo 'alias gcc="color_compile gcc"' >> $(BASH_FILE)
	echo 'alias g++="color_compile g++"' >> $(BASH_FILE)
	echo 'alias make="color_compile make"' >> $(BASH_FILE)
	echo 'alias gcc="color_compile gcc"' >> $(ZSH_FILE)
	echo 'alias g++="color_compile g++"' >> $(ZSH_FILE)
	echo 'alias make="color_compile make"' >> $(ZSH_FILE)
	. $(BASH_FILE)

test:
	gcc test.c -Wall
