
objs := public.o

all: $(objs)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	
clean:
	rm -f *.o