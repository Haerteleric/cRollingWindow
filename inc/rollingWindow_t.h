/**
 * Portable Rolling Window template implementation
 * 
 * Author:    Haerteleric
 * 
 * MIT License
 * 
 * Copyright (c) 2023 Eric Härtel
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#include <stddef.h>
#ifdef ROLLING_WINDOW_CONFIG_HEADER_INCLUDE
    #include ROLLING_WINDOW_CONFIG_HEADER_INCLUDE
#endif

#ifndef _ROLLING_WINDOW_INCLUDED
#define _ROLLING_WINDOW_INCLUDED
#endif


#ifndef ROLLING_WINDOW_DATA_TYPE
    #define ROLLING_WINDOW_DATA_TYPE float
#endif

typedef ROLLING_WINDOW_DATA_TYPE rollingWindowDatatype_t;

#ifndef _ROLLING_WINDOW_INSTANCE_STRUCT_DEFINED
#define _ROLLING_WINDOW_INSTANCE_STRUCT_DEFINED

typedef struct rollingWindowInstance_s
{
    rollingWindowDatatype_t *buffer;
    const unsigned int bufferSize;
    unsigned int k0Pos;

#ifdef ROLLING_WINDOW_CHECK_VALUE_EXISTENCE
    unsigned int availableValues;
#endif
}rollingWindow_t;

#endif //_ROLLING_WINDOW_INSTANCE_STRUCT_DEFINED

#ifdef ROLLING_WINDOW_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ROLLING_WINDOW_STATIC_IMPLEMENTATION
static
#endif 
void rollingWindow_reset(rollingWindow_t * handle)
#ifdef ROLLING_WINDOW_ONLY_PROTOTYPE_DECLARATION
;
#else
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
#endif // NOT(ROLLING_WINDOW_ONLY_PROTOTYPE_DECLARATION)



#ifdef ROLLING_WINDOW_INLINE_IMPLEMENTATION
inline
#endif 
#ifdef ROLLING_WINDOW_STATIC_IMPLEMENTATION
static
#endif 
void rollingWindow_put(rollingWindow_t * handle, rollingWindowDatatype_t value)
#ifdef ROLLING_WINDOW_ONLY_PROTOTYPE_DECLARATION
;
#else
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
#endif // NOT(ROLLING_WINDOW_ONLY_PROTOTYPE_DECLARATION)



#ifdef ROLLING_WINDOW_INLINE_IMPLEMENTATION
inline 
#endif 
#ifdef ROLLING_WINDOW_STATIC_IMPLEMENTATION
static
#endif 
const rollingWindowDatatype_t * rollingWindow_getSampleKMinusN(rollingWindow_t * handle, unsigned int n)
#ifdef ROLLING_WINDOW_ONLY_PROTOTYPE_DECLARATION 
;
#else
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
#endif // NOT(ROLLING_WINDOW_ONLY_PROTOTYPE_DECLARATION)


