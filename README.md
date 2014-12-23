color-compile
=============

show compile message with color when show up error/warning/note using gcc/g++/make

(1) compile

$ make

(2) install (it need root permission)

$ make install

// copy exec program to /usr/local/bin/

// alias gcc/g++/make in ~/.bashrc

(3) test

// open a new terminal

$ make TEST (== gcc test.c -Wall)

note:
-----
(1) if your gcc version >= 4.9.0, you can use -fdiagnostics-color=auto argument(it should be better than color-compile, but I am not convenient to try).

(2) if you want to uninstall or reinstall, please remove alias added in ~/.bashrc at the end of line manually.

(3) if you want to add new compile tool, you can add it at Makefile, like echo 'alias arm-linux-gcc="color_compile arm-linux-gcc"' >> $(ALIAS_FILE)

(4) if you want to change the color of color-compile showed, you can change out_color_info.c, there are some macro define color.

result:
-------
before using color-compile
![before using color-compile](https://github.com/chinaran/my-pictures/blob/master/color-compile/before.png)

after using color-compile
![after using color-compile](https://github.com/chinaran/my-pictures/blob/master/color-compile/after.png)
