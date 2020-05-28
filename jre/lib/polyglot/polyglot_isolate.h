#ifndef __POLYGLOT_ISOLATE_H
#define __POLYGLOT_ISOLATE_H

#include <stdbool.h>
#include <stdint.h>
#include <graal_isolate.h>
#include <polyglot_types.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * Create a new isolate, considering the passed parameters (which may be NULL).
 * Returns poly_ok on success, or a poly_generic_failure value on failure.
 * On success, the current thread is attached to the created isolate, and the
 * address of the isolate structure is written to the passed pointer.
 * Every thread starts with a default handle scope. This scope is released when
 * the thread is detached.
 */
poly_status poly_create_isolate(const poly_isolate_params* params, poly_isolate* isolate, poly_thread* thread);

/*
 * Attaches the current thread to the passed isolate.
 * On failure, returns poly_generic_failure. On success, writes the address of the
 * created isolate thread structure to the passed pointer and returns poly_ok.
 * If the thread has already been attached, the call succeeds and also provides
 * the thread's isolate thread structure.
 */
poly_status poly_attach_thread(poly_isolate isolate, poly_thread* thread);

/*
 * Given an isolate to which the current thread is attached, returns the address of
 * the thread's associated isolate thread structure.  If the current thread is not
 * attached to the passed isolate or if another error occurs, returns NULL.
 */
poly_thread poly_get_current_thread(poly_isolate isolate);

/*
 * Given an isolate thread structure, determines to which isolate it belongs and
 * returns the address of its isolate structure.  If an error occurs, returns NULL
 * instead.
 */
poly_isolate poly_get_isolate(poly_thread thread);

/*
 * Detaches the passed isolate thread from its isolate and discards any state or
 * context that is associated with it. At the time of the call, no code may still
 * be executing in the isolate thread's context.
 * Returns poly_ok on success, or poly_generic_failure on failure.
 */
poly_status poly_detach_thread(poly_thread thread);

/*
 * Using the context of the isolate thread from the first argument, detaches the
 * threads in an array pointed to by the second argument, with the length of the
 * array given in the third argument. All of the passed threads must be in the
 * same isolate, including the first argument. None of the threads to detach may
 * execute Java code at the time of the call or later without reattaching first,
 * or their behavior will be entirely undefined. The current thread may be part of
 * the array, however, using poly_detach_thread() should be preferred for detaching
 * only the current thread.
 * Returns poly_ok on success, or poly_generic_failure on failure.
 */
poly_status poly_detach_threads(poly_thread thread, poly_thread* threads, int32_t length);

/*
 * Tears down the passed isolate, waiting for any attached threads to detach from
 * it, then discards the isolate's objects, threads, and any other state or context
 * that is associated with it.
 * Returns poly_ok on success, or poly_generic_failure on failure.
 */
poly_status poly_tear_down_isolate(poly_thread thread);

#if defined(__cplusplus)
}
#endif
#endif
