#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _GL_STDBOOL_H
#include <stdbool.h>
#endif

#ifndef _UNISTD_H
#include <unistd.h>
#endif

#ifndef NOTIFY_H
#include "notify.h"
#endif

#define TIMER_H 1

int timer(int hours, int minutes, int seconds, char *body);
