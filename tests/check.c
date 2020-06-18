#include <glib.h>
#include "runner.h"

#include "check.h"

static char *result = NULL;

void check(char *actual, char *expected)
{
    runner(actual, &result);

    g_assert_cmpstr(result, ==, expected);

    if (result) {
        g_free(result);
    }
}
