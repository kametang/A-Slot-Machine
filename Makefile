Prefix=tools/bin/arm-linux-
CC=gcc
INC=-I./lib/minigui_lib/2.0.3/include -I./
LIB=-L./lib/minigui_lib/2.0.3/lib
FLAGS=-lminigui -ljpeg -lpng -lpthread -lz -lm

SUBDIR=common driver
OBJS=

OUTPUT=asm
INPUT=asm.c

export PROJECT_ROOT=$(PWD)

.PHONY:all clean $(SUBDIR)

all: $(INPUT) $(SUBDIR)
	$(eval OBJS += $(wildcard obj/*))
	$(Prefix)$(CC) -o $(OUTPUT) $(INPUT) $(OBJS) $(INC) $(LIB) $(FLAGS)

$(SUBDIR):
	$(MAKE) -C $@ all

clean:
	-rm -f obj/*.o
	-rm -f asm