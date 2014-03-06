#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <remote.h>
#include <fb2png.h>
#include <QGuiApplication>
#include <QWidget>
#include <QApplication>

#include <fb.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

#define DEFAULT_SAVE_PATH "fbdump.png"
/* defined in $T/system/core/adb/framebuffer_service.c */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    char fn[128];

    if (argc == 2) {
        //if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        if (argv[1][0] == '-') {
            printf("Usage: fb2png [path/to/output.png]\n"
                   "The default output path is ./fbdump.png\n");
            exit(0);
        } else {
            sprintf(fn, "%s", argv[1]);
        }
    } else {
        sprintf(fn, "%s", DEFAULT_SAVE_PATH);
    }
    fb2png fbtopng(&a, fn);
    return a.exec();
}
