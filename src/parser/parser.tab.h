
extern char* image;

typedef enum LexTokens
{
    EOL = 0,
    ERROR = -1,
    WS = 258,
    K_CHAR = 259,
    M_CHAR = 260,
    N_CHAR = 261,
    MUL = 262,
    ADD = 263
} LexToken;
