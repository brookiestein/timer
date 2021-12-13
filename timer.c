#include "timer.h"

bool limit = false;
static int
print_message(int hours, int minutes, int seconds)
{
        if (limit)
                return EXIT_SUCCESS;

        printf("Running until ");
        if (hours)
                printf("%i %s ", hours, (hours > 1 ? "hours" : "hour"));

        if (minutes)
                printf("%i %s ", minutes, (minutes > 1 ? "minutes" : "minute"));

        if (seconds && (hours || minutes ))
                printf("and %i %s ", seconds, (seconds > 1 ? "seconds" : "second"));
        else if (seconds)
                printf("%i %s ", seconds, (seconds > 1 ? "seconds" : "second"));

        printf("had finished.\n");
        limit = true;
        return EXIT_SUCCESS;

}

int
timer(int hours, int minutes, int seconds, char *body)
{
        while (1) {
                while (seconds > 59) {
                        minutes++;
                        seconds -= 60;
                }

                while (minutes > 59) {
                        hours++;
                        minutes -= 60;
                }

                if (hours > 0 && minutes == 0) {
                        minutes = 60;
                        hours--;
                }

                if (minutes > 0 && seconds == 0) {
                        seconds = 60;
                        minutes--;
                }

                print_message(hours, minutes, seconds);
                setbuf(stdout, NULL);
                printf("\r%i:%i:%i ", hours, minutes, seconds);
                seconds--;
                sleep(1);

                if (hours == 0 && minutes == 0 && seconds == 0) {
                        printf("\rTime finished.\n");
                        break;
                }
        }

        char *err = notify(body);

        if (strncmp(err, "ok", 2)) {
                fprintf(stderr, "%s", err);
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
