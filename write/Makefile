include ../build.rule

SRC := $(wildcard *.c)
TMP_OBJ := $(addsuffix .o,$(basename $(SRC)))
OBJ := $(basename $(SRC))

all:$(OBJ)

clean:
	$(RM) -f $(TMP_OBJ) $(OBJ)
