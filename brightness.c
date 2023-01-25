#include <libnotify/notify.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// change the macro if not compatible
// picture must reside in the same dir with the executable
#define PICTURE_NAME "brightness_icon.png"
#define BACKLIGHT_FILE_PATH                                          \
    "/sys/class/backlight/intel_backlight/brightness"
#define MAX_BACKLIGHT_FILE_PATH                                      \
    "/sys/class/backlight/intel_backlight/max_brightness"

#ifdef DEBUG
void show_help() {
    puts(
    "usage: brightness_ctl_notify argument\n\nargument:\ninc : "
    "xbacklight -inc 1 -steps 1\ndec : xbacklight -dec 1 -steps 1");
    exit(EXIT_SUCCESS);
}
#endif
int main(int argc, char *argv[]) {
#ifdef DEBUG
    if (argc == 1) show_help();
#endif

    if (!strcmp(argv[1], "inc")) {
        if (system("xbacklight -inc 1 -steps 1")) return -1;
    }
    else if (!strcmp(argv[1], "dec")) {
        if (system("xbacklight -dec 1 -steps 1")) return -1;
    }
#ifdef DEBUG
    else show_help();
#endif

    notify_init("Brightness");
    FILE *f_max = fopen(MAX_BACKLIGHT_FILE_PATH, "r"),
         *f_cur = fopen(BACKLIGHT_FILE_PATH, "r");
    // edit the two paths if not compatible with your system

    if (!f_max || !f_cur) {
#ifdef DEBUG
        puts("cannot open file");
#endif
        return -1;
    }

    // Compute brightness
    int max_bri, cur_bri;
    if (fscanf(f_max, "%d", &max_bri) != 1 ||
        fscanf(f_cur, "%d", &cur_bri) != 1)
        return -1;
    int percent = cur_bri * 100 / max_bri;
    char content[5] = ""; // all '\0'
    if (percent == 100)
        content[0] = '1', content[1] = '0', content[2] = '0',
        content[3] = '%';
    else if (percent >= 10) {
        content[0] = percent / 10 + '0';
        content[1] = percent % 10 + '0';
        content[2] = '%';
    }
    else content[0] = percent + '0', content[1] = '%';

    // Picture path
    char pic_path[PATH_MAX];
    readlink("/proc/self/exe", pic_path, PATH_MAX);

    for (int i = strlen(pic_path); i > 0; --i) {
        if (pic_path[i - 1] == '/') {
            strcpy(pic_path + i, PICTURE_NAME);
            puts(pic_path);
            break;
        }
    }
    // Send notification

    NotifyNotification *n =
    notify_notification_new(content, NULL, pic_path);
    // cannot open with relative path
    g_object_set(&(n->parent_object), "id", INT_MAX,
                 NULL); // use up a fixed notification id
    notify_notification_set_timeout(n, 2500);
    if (!notify_notification_show(n, 0)) {
#ifdef DEBUG
        puts("cannot show");
#endif
        return -1;
    }
    return 0;
}
