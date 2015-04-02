color-compile
=============

show compile message with color when show up error/warning/note using gcc/g++/make

(1) compile ("\make" means using system make, not alias)

$ \make

(2) install (need root permission)

$ \make install

// copy exec program to /usr/local/bin/

// alias gcc/g++/make in ~/.bashrc

(3) test

// open a new terminal

$ make TEST (== gcc test.c -Wall)

note:
-----
(1) if your gcc version >= 4.9.0, you can use -fdiagnostics-color=auto argument(it should be better than color-compile, but I am not convenient to try).

(2) if you want to uninstall or reinstall, please remove alias added in ~/.bashrc at the end of line manually.

(3) if you want to add new compile tool, you can add it at Makefile, like echo 'alias arm-linux-gcc="color_compile arm-linux-gcc"' >> $(ALIAS_FILE) or change ~/.bahsre directly.

(4) if you want to change the color of color-compile showed, you can change out_color_info.c, there are some macro define color.

result:
-------
before using color-compile
![before using color-compile](https://github.com/chinaran/my-pictures/blob/master/color-compile/before.png)

after using color-compile
![after using color-compile](https://github.com/chinaran/my-pictures/blob/master/color-compile/after.png)

Author: Alan Wang <gchinaran@gmail.com>

Started: Dec. 20, 2014

Licence: Apache Licene 2.0

中文说明：
---------
(1) 编译 （进到项目根目录，"\make" 是使用系统make，而不是alias别名）

$ \make

(2) 安装 (需要超级权限)

$ \make install

（这一步做了两件事，一是把主程序拷贝到 /usr/local/bin/ 下，二是添加了 gcc/g++/make 的别名到 ~/.bashrc 的末尾）

(3) 测试 （新打开一个终端）

$ make TEST  (== gcc test.c -Wall)

注意事项:

(1) 如果你的 gcc 版本 >= 4.9.0，可以直接使用 -fdiagnostics-color=auto 参数，显示效果应该比 color-compile 好（没试过）

(2) 如果你需要卸载或者重装，请删除 ~/.bashrc 末尾处的gcc/g++/make 别名，以免影响之后的使用。

(3) 如果你需要添加新的编译工具，可以修改Makefile 的 install: 处，以 arm-linux-gcc 为例，echo 'alias arm-linux-gcc="color_compile arm-linux-gcc"' >> $(ALIAS_FILE)，或者直接修改 ~/.bashrc 都行。

(4) 如果你需要更改显示的颜色，直接修改 out_color_info.c 源码就行，其中有一些颜色定义的宏。
