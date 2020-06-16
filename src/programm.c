#include <glib.h>

#include "runner.h"

int main(int argc, char *argv[])
{
    g_print("Parser is running.\n\n");

    if (argv[1]) {
        runner(argv[1]);
    }
    else {
        g_print("Empty input.\n");
    }

    return 0;
}
