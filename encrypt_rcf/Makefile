SRC := main.c
objs := $(patsubst %.c,%.o, ${SRC})
prcf: ${objs}
	gcc -o prcf ${objs}

%.o:%.c
	gcc -c -o $(@) $<

clean:
	rm -rf ${objs}
