#include "runner.h"

int main(void)
{
    char *result = NULL;

    runner("n*m+k+m", &result);

    if (result) {
        g_free(result);
    }
}
