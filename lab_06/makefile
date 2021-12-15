CC = gcc
INC = ./inc/
OUT = ./out/
SRC = ./src/
CFLAGS = -I../inc/ -Wall -Werror -Wextra -pedantic -Wvla -Wfloat-equal -Wfloat-conversion -std=c99
MKOUT = mkdir -p out
RM = rm -rf

release : app.exe

SRCS = $(wildcard $(SRC)*.c)
UNITS = $(wildcard $(UNIT)*.c)
OBJS = $(patsubst $(SRC)%.c,$(OUT)%.o,$(SRCS))


app.exe: $(OBJS)
	$(CC) $^ -o $@


$(OUT)%.o : $(SRC)%.c
	$(MKOUT) && cd out && $(CC) $(CFLAGS) -c ../$<


.PHONY : clean release 

clean :
	$(RM) out 
	$(RM) *.exe
