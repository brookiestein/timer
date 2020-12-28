#include "main.h"

static error_t parse_opt(int key, char *arg, struct argp_state *state);

const char *argp_program_version        = "Timer v0.1";

static const struct argp argp = { options, parse_opt, 0, doc, 0, 0, 0 };

static void
die(const char *msg)
{
        fprintf(stderr, "%s\n", msg);
        exit(EXIT_FAILURE);
}

static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{
        struct arguments *args = state->input;

        switch (key)
        {
        case 'c':
                args->cmd = arg;
                break;
        case 'h':
                if (arg && isdigit(arg[0])) {
                        args->hours = atoi(arg);
                } else {
                        die("The entered hours are not valid.");
                }
                break;
        case 'm':
                if (arg && isdigit(arg[0])) {
                        args->minutes = atoi(arg);
                } else {
                        die("The entered minutes are not valid.");
                }
                break;
        case 'M':
                args->body = arg;
                break;
        case 's':
                if (arg && isdigit(arg[0])) {
                        args->seconds = atoi(arg);
                } else {
                        die("The entered seconds are not valid.");
                }
                break;
        case ARGP_ERR_UNKNOWN:
                return ARGP_ERR_UNKNOWN;
        }

        return EXIT_SUCCESS;
}

int
main(int argc, char *argv[])
{
        struct arguments args;
        args.cmd        = NULL;
        args.body       = NULL;
        args.hours      = 0;
        args.minutes    = 0;
        args.seconds    = 0;

        argp_parse(&argp, argc, argv, 0, 0, &args);

        if (args.hours == 0 && args.minutes == 0 && args.seconds == 0)
                die("You've not specified neither hours, minutes nor seconds.");

        timer(args.hours, args.minutes, args.seconds, args.body);

        if (args.cmd) {
                char RED[]      = "\e[1;32m";
                char ORANGE[]   = "\e[1;33m";
                char BLUE[]     = "\e[1;34m";
                char RESET[]    = "\e[0m";
                printf("%sExecuting %s'%s'%s...\n", BLUE, ORANGE, args.cmd, RESET);
                printf("%sTo stop it, press CTRL + C%s\n", BLUE, RESET);
                FILE *fp = popen(args.cmd, "r");
                if (!fp)
                        fprintf(stderr, "%sAn error occurred while executing the command: %s%s\n",
                                RED, args.cmd, RESET);
                else
                        pclose(fp);
        }

        return EXIT_SUCCESS;
}
