#include "runner.h"

int main(void)
{
    char *result = NULL;

    runner("n*mm", &result);

    if (result) {
        g_free(result);
    }
}
