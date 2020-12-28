#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <argp.h>
#include <error.h>

#include "timer.h"

static const char doc[]                 = "\nThe option -c is not strictly necessary. \
You'll only use it if you want to play a music to notify you when the timer had finished.\n\
(For example, but of course, you can execute any command you want)\n\
That, apart from the notification it sends you.\n\
e.g.:\e[1;33m timer --minutes=30 --command='mpv any_music'\e[0m\n\n\
The command needs to be in your PATH variable, doh!";
static const char cmd_info[]            = "Command to be executed after timer had finished.";
static const char hours_info[]          = "How many hours you want me to run.";
static const char minutes_info[]        = "How many minutes you want me to run.";
static const char seconds_info[]        = "How many seconds you want me to run.";
static const char message_info[]        = "Custom message to be shown after timer\n\
had finished. (Default: 'The time has finished.')";

static struct
argp_option options[] = {
        { "command",    'c',    "command",      OPTION_ARG_OPTIONAL,    cmd_info,       0 },
        { "hours",      'h',    "hours",        OPTION_ARG_OPTIONAL,    hours_info,     0 },
        { "minutes",    'm',    "minutes",      OPTION_ARG_OPTIONAL,    minutes_info,   0 },
        { "message",    'M',    "message",      OPTION_ARG_OPTIONAL,    message_info,   0 },
        { "seconds",    's',    "seconds",      OPTION_ARG_OPTIONAL,    seconds_info,   0 },
        { 0 }
};

struct
arguments {
        char *cmd, *body;
        int hours, minutes, seconds;
};
