#include <stdio.h>
#include <assert.h>
#include <time.h>
/*****************************TEMPLATE INCLUDE**************************************/
#define ROLLING_WINDOW_DATA_TYPE char
#include "rollingWindow.h"
/***********************************************************************************/


static char s_buffer[32] ;
static rollingWindow_t s_rollingWindow = 
{
    .buffer = s_buffer,
    .bufferSize = sizeof(s_buffer)/sizeof(s_buffer[0]),
};

int main(void)
{
    clock_t start = clock();
    rollingWindow_reset(&s_rollingWindow);

    char input = getchar();
    while (input != 'Q')
    {
        if((input >= '0') && (input <= '9'))
        {
            rollingWindow_put(&s_rollingWindow, input);
            printf("writePos %i\n", s_rollingWindow.k0Pos);
            for (size_t i = 0; i < s_rollingWindow.bufferSize; i++)
            {
                printf("[%c]",*rollingWindow_getSampleKMinusN(&s_rollingWindow, i));
            }
            printf("\n");
        }
        input = getchar();
    }
    
}