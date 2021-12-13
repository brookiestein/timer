CC	:= cc
CFLAGS	:= -O2 -march=native -Iinclude -Wall -Wextra -std=c99 -lnotify
CFLAGS	+= $(shell pkg-config --cflags --libs libnotify)
RM	:= rm -f
PREFIX	:= /usr/local/bin
TARGET	:= timer
SRC	:= main.c timer.c notify.c
OBJ	:= ${SRC:.c=.o}

all : ${OBJ}
	${CC} ${CFLAGS} ${SRC} -o ${TARGET}

.PHONY : clean
clean :
	${RM} ${OBJ} ${TARGET}

.PHONY : install
install :
	install -m755 ${TARGET} ${PREFIX}

.PHONY : uninstall
uninstall :
	${RM} ${PREFIX}/${TARGET}
