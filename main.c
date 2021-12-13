#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "timer.h"

struct Arguments
{
        char* cmd;
        char* body;
        char* message;
        int hours;
        int minutes;
        int seconds;
};

void usage(bool failure);

int
main(int argc, char* argv[])
{
        struct Arguments args;
        args.cmd        = NULL;
        args.body       = NULL;
        args.hours      = 0;
        args.minutes    = 0;
        args.seconds    = 0;

        const struct option long_options[] = {
                { "command",    required_argument,      0,      'c' },
                { "help",       no_argument,            0,      '?' },
                { "hours",      required_argument,      0,      'h' },
                { "minutes",    required_argument,      0,      'm' },
                { "message",    required_argument,      0,      'M' },
                { "seconds",    required_argument,      0,      's' },
                { NULL, 0, NULL, 0 }
        };

        int option = 0;
        while ((option = getopt_long(argc, argv, "c:h:m:M:s:", long_options, NULL)) >= 0)
        {
                switch (option)
                {
                case 'c': args.cmd = optarg; break;
                case 'h': args.hours = atoi(optarg); break;
                case 'm': args.minutes = atoi(optarg); break;
                case 'M': args.message = optarg; break;
                case 's': args.seconds = atoi(optarg); break;
                case '?': usage(false); break;
                default: fprintf(stderr, "Unknown option: %c\n", optopt);
                }
        }

        if (args.hours == 0 && args.minutes == 0 && args.seconds == 0)
                usage(true);

        timer(args.hours, args.minutes, args.seconds, args.body);

        if (args.cmd) {
                printf("Executing: %s...\n", args.cmd);
                printf("To stop it, press CTRL + C\n");
                char *const p[] = { args.cmd, NULL };
                execvp(args.cmd, p);
        }

        return EXIT_SUCCESS;
}

void usage(bool failure)
{
        printf("-c | --command=command\tCommand to be executed after timer had finished.\n\
                -h | --hours=hours\tHow many hours you want me to run.\n\
                -m | --minutes=minutes\tHow many minutes you want me to run.\n\
                -M | --message=message\tCustom message to be shown after timer.\n\
                -s | --seconds=seconds\tHow many seconds you want me to run.\n");
        exit(failure ? EXIT_FAILURE : EXIT_SUCCESS);
}
