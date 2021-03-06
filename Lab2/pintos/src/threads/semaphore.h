#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <list.h>
#include <stdbool.h>

/* Semaphore */
struct semaphore {
    unsigned value; /* Current value */
    struct list waiters; /* List of waiting threads */
    struct list_elem elem; /* condvar waiters list elem  */
    int priority;
};

void semaphore_init(struct semaphore *, unsigned value);
void init_semaphore(struct semaphore *, unsigned value, unsigned priority);
void semaphore_down(struct semaphore *);
bool semaphore_try_down(struct semaphore *);
void semaphore_up(struct semaphore *);
void sema_self_test (void);
#endif /* UCSC CMPS111 */
