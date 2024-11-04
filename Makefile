# Makefile 由一下3部分组成
# <目标名称>:<前置依赖>
# \t<需要执行的命令> 这里是区分 \t 和 \s 的, 所以必须是 \t 

# 定义变量 objects
objects := hello.o \
			main.o

#这2个main要一致，第一个是要告诉makefile 你要追踪的目标是 main，第2个是 gcc 生成的 main 文件
main: $(objects)
	gcc $(objects) -o main

# -o main. 这是默认的
# main.o: main.c hello.h
# 	gcc -c main.c
# 能自动推导的都不要了,只保留makefile 推不出来的
main.o: hello.h

# hello.o: hello.c hello.h
# 	gcc -c hello.c
hello.o: hello.h

#声明伪目标,如果你有一个叫clean 的文件，并且不加这个声明的话，make clean 这个功能会失效
#它会把 clean 当成你要 make 的文件
.PHONY: clean

#加一个 ‘-’ 可以忽略错误
clean:
	-rm main $(objects)