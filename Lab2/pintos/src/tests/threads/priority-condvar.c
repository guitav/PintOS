/* Tests that cond_signal() wakes up the highest-priority thread
   waiting in cond_wait(). */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/condvar.h"
#include "threads/lock.h"
#include "threads/thread.h"
#include "devices/timer.h"

static thread_func priority_condvar_thread;
static struct lock lock;
static struct condvar condvar;

void
test_priority_condvar(void)
{
    int i;

    /* This test does not work with the MLFQS. */
    ASSERT(!thread_mlfqs);

    lock_init(&lock);
    condvar_init(&condvar);

    thread_set_priority(PRI_MIN);
    for (i = 0; i < 10; i++) {
        int priority = PRI_DEFAULT - (i + 7) % 10 - 1;
//        int priority = PRI_DEFAULT + i; 
        char name[16];

        snprintf(name, sizeof name, "priority %d", priority);
        thread_create(name, priority, priority_condvar_thread, NULL);
    }

    for (i = 0; i < 10; i++) {
//        msg("A STEP %s .", thread_name());
        lock_acquire(&lock);
        msg("Signaling...");
        condvar_signal(&condvar, &lock);
//        msg("B STEP %s .", thread_name());
        lock_release(&lock);
    }
}

static void
priority_condvar_thread(void *aux UNUSED)
{
    msg("Thread %s starting.", thread_name());
    lock_acquire(&lock);
//    msg("C STEP %s .", thread_name());
    condvar_wait(&condvar, &lock);
    msg("Thread %s woke up.", thread_name());
    lock_release(&lock);
//    msg("D STEP %s .", thread_name());
}
