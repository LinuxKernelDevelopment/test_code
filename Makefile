CFLAGS=-Wall
SRC := $(wildcard *.c)
TMP_OBJ := $(addsuffix .o,$(basename $(SRC)))
OBJ := $(basename $(SRC))
CFLAGS := -static

$(OBJ):


.PHONY: clean install mount

install: $(OBJ)
	mount -o loop -t xfs /home/hmsjwzb/code.img ./ftest
	cp $(OBJ) ./ftest/
	umount ./ftest

	
clean:
	rm -f *.o $(OBJ)

