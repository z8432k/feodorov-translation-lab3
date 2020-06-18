#include "runner.h"

int main(void)
{
    char *result = NULL;

    runner("n+m", &result);

    if (result) {
        g_free(result);
    }
}
