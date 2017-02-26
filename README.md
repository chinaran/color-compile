color-compile
=============

Show compile message with color when show up error/warning/note using gcc/g++/make

**(1) compile** ("\make" means using system make, not alias)

    $ \make

**(2) install** (need root permission)

    $ \make install

// copy exec program to /usr/local/bin/

// alias gcc/g++/make in corresponding shell config file (like ~/.bashrc)

**(3) test**

// open a new terminal

    $ make TEST (== gcc test.c -Wall)

Note:
-----
**(1)** If your gcc version >= 4.9.0, you can use -fdiagnostics-color=auto argument to show compiling color(It's similar to color-compile).

**(2)** If you want to uninstall or reinstall, please remove alias added in ~/.bashrc at the end of line manually.

**(3)** If you want to add new compile tool, you can add it at Makefile, like echo 'alias arm-linux-gcc="color_compile arm-linux-gcc"' >> $(ALIAS_FILE) or change ~/.bashrc directly.

**(4)** If you want to change the color of color-compile showed, you can change out_color_info.c, there are some macro define color.

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
**(1) 编译** （进到项目根目录，"\make" 是使用系统make，而不是alias别名）

    $ \make

**(2) 安装** (需要超级权限)

    $ \make install

（这一步做了两件事，一是把主程序拷贝到 /usr/local/bin/ 下，二是添加了 gcc/g++/make 的别名到对应的 shell 配置文件的末尾，例如 ~/.bashrc）

**(3) 测试** （新打开一个终端）

    $ make TEST  (== gcc test.c -Wall)

注意事项:
-----
**(1)** 如果你的 gcc 版本 >= 4.9.0，可以直接使用 -fdiagnostics-color=auto 参数，显示效果和 color-compile 类似

**(2)** 如果你需要卸载或者重装，请删除 ~/.bashrc 末尾处的gcc/g++/make 别名，以免影响之后的使用。

**(3)** 如果你需要添加新的编译工具，可以修改Makefile 的 install: 处，以 arm-linux-gcc 为例，echo 'alias arm-linux-gcc="color_compile arm-linux-gcc"' >> $(ALIAS_FILE)，或者直接修改 ~/.bashrc 都行。

**(4)** 如果你需要更改显示的颜色，直接修改 out_color_info.c 源码就行，其中有一些颜色定义的宏。



# 2017-02-26更新
-------

**修复了mingw下的显示异常的问题**


由于 `linux` 和 `windows` 下snprintf返回值不同

根据输出结果总结如下：

1.	在 `windows` 下, 如果字符串长度大于 `count`, 函数返回 `-1` 以标志可能导致的错误, 如果字符串长度小于或者等于 `count`, 函数返回实际的字符串的长度. 在 `linux` 下, 返回实际的字符串的长度.

2.	输出不同, 在 `windows` 下, 如果字符串长度大于 `count`, 会输出 `count` 个字符, 但是没有结束符, 后面的值会混乱; 如果字符串的长度等于 `count`, 输出全部字符串, 但是没有结束符, 后面的值同样很混乱; 在 `linux` 下, 永远输出 `count - 1` 个字符, 加一个结束符 '\0', 所以在本例子中, `count = 13` 时, 无论 `windows` 下还是 `linux` 下都正确.


因此修改代码中, `snprintf` 后, 增加 buf[XXX] = '\0';


```cpp
snprintf(buf, mark_p - p, "%s", p + 1);
buf[mark_p - p - 1] = '\0';
```


