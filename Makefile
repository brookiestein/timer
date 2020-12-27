CC	:= cc
CFLAGS	:= -O2 -march=native -Iinclude -Wall -Wextra -std=c99 -lnotify
CFLAGS	+= $(shell pkg-config --cflags --libs gtk+-3.0)
CP	:= cp -fv
MV	:= mv -fv
RM	:= rm -fv
TARGET	:= timer
SRC_DIR	:= src
SRC	:= ${SRC_DIR}/main.c ${SRC_DIR}/timer.c ${SRC_DIR}/notify.c
OBJ	:= ${SRC:.c=.o}

all : ${OBJ}
	${CC} ${CFLAGS} ${SRC} -o ${TARGET}

.PHONY : clean
clean :
	${RM} ${OBJ}
