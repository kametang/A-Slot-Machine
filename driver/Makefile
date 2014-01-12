Prefix=../tools/bin/arm-linux-
CC=gcc

OBJS=led.o dc_motor.o

all: $(OBJS)

$(OBJS):%.o: %.c %.h	
	$(Prefix)$(CC) -c -o $@ $<
	mv $@ $(PROJECT_ROOT)/obj/

clean:
	-rm -f *.o