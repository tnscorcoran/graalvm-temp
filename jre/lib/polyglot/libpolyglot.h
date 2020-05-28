#ifndef __LIBPOLYGLOT_H
#define __LIBPOLYGLOT_H

#include <stdbool.h>
#include <stdint.h>
#include <graal_isolate.h>


#if defined(__cplusplus)
extern "C" {
#endif

void vmLocatorSymbol(graal_isolatethread_t* thread);

#if defined(__cplusplus)
}
#endif
#endif
