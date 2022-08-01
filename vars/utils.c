#include "../newton.h"

void reset_image(char *buf, int len)
{
    while (len--)
        buf[len] = 0;
}