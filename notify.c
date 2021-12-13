#include "notify.h"

char *
notify(char *body)
{
        char summary[]  = "Timer";
        char *err = NULL;

        if (!body)
                body = "The time has finished.";

        if (!notify_init(summary)) {
                err = "An error occurred while initialising libnotify.";
                return err;
        }

        NotifyNotification *n = notify_notification_new(summary, body, NULL);
        notify_notification_set_timeout(n, NOTIFY_EXPIRES_DEFAULT);

        if (!notify_notification_show(n, NULL)) {
                err = "An error occurred while showing notification.";
        } else {
                err = "ok";
        }

        notify_uninit();
        return err;
}
