# Philosopher # 

## USED ##
`memset`,
`printf`,
`malloc`,
`free`,
`write`,

`usleep`
Pauses the thread for a time so other thread can work

## TRIED ##
`gettimeofday(t_timeval, NULL)` (second is unused)

2 long, tv_sec (since EPOCH) and tv_usec;

return != 0 if error

`pthread_create (thread, attr, routine, args_of_routine)`
Create a thread with attributes (not authorized here), the routine is the function to be executed by the thread.

`pthread_detach(thread)`,
Detach a thread from the parent so the memory is released automatically when thread dies.

Shouldn't be used in the routine itself, but it works.

---
### Mutex Creation and Destroy ###
`pthread_mutex_init(mutex_address)`,
Initialise a mutex so it can be locked or unlocked afterwise

`pthread_mutex_destroy(mutex_address)`
Valgrind doesn't show if a mutex is correctly destroyed so... ?

---
### Mutex Manipulation ###
`pthread_mutex_lock`
Makes the thread wait indefinitely until the mutex is available. It puts the thread in a suspended state.

`pthread_mutex_unlock`
Makes the mutex available for all the thread that could run (thread limit is defined by the hosting machine) so it break's the suspended state of the thread that 'won' the right to use the ressource

`pthread_join`
Waits for a thread to finish it's routine and frees its memory.
The advantage is that you don't need to detach the thread that is concerned. The function is BLOCKANT so the thread is suspended until the thread finishes. If it's already finished, the functions ends instantly and redeems memory of the thread.