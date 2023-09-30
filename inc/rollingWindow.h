/**
 * Author:    Haerteleric
 * Created:   11.07.23
 * 
 * (c) Copyright by Eric Haertel
 * 
 * Portable Rolling Window template implementation
 * 
 **/
#define _ROLLING_WINDOW_TEMPLATE_BUFFER_
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef ROLLING_WINDOW_CONFIG_HEADER_INCLUDE
    #include ROLLING_WINDOW_CONFIG_HEADER_INCLUDE
#endif

#ifndef ROLLING_WINDOW_DATA_TYPE
    #define ROLLING_WINDOW_DATA_TYPE float
#endif

typedef ROLLING_WINDOW_DATA_TYPE rollingWindowDatatype_t;

typedef struct rollingWindow_s
{
    rollingWindowDatatype_t *buffer;
    const unsigned int bufferSize;
    unsigned int k0Pos;

#ifdef ROLLING_WINDOW_CHECK_VALUE_EXISTENCE
    unsigned int availableValues;
#endif

}rollingWindow_t;

static void rollingWindow_reset(rollingWindow_t * handle)
{
    handle->k0Pos=0;

    for (unsigned int i = 0; i < handle->bufferSize; i++)
    {
        handle->buffer[i] = 0;
    }

#ifdef ROLLING_WINDOW_CHECK_VALUE_EXISTENCE
    handle->availableValues = 0;
#endif
}

static void rollingWindow_put(rollingWindow_t * handle, rollingWindowDatatype_t value)
{
    handle->k0Pos = ( handle->k0Pos + 1 ) % handle->bufferSize;
    handle->buffer[handle->k0Pos] = value;

#ifdef ROLLING_WINDOW_CHECK_VALUE_EXISTENCE
    if(handle->availableValues < handle->bufferSize )
    {
        handle->availableValues++;
    }
#endif
}

static const rollingWindowDatatype_t * rollingWindow_getSampleKMinusN(rollingWindow_t * handle, unsigned int n)
{
#ifdef ROLLING_WINDOW_CHECK_VALUE_EXISTENCE
    if((handle->availableValues < handle->bufferSize) && (n >= handle->availableValues))
#else
    if (n > (handle->bufferSize - 1))
#endif
    {
        return NULL;
    }

    if( n <= handle->k0Pos )
    {
        return &(handle->buffer[handle->k0Pos - n]);
    }

    return &(handle->buffer[(handle->k0Pos + handle->bufferSize) - n]);
}