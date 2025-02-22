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
Need to check usability and error returns

`pthread_mutex_init(mutex_address)`,
Initialise a mutex properly

`pthread_mutex_destroy(mutex_address)`
Valgrind doesn't show if a mutex is correctly destroyed so... ?

---
### Mutex Manipulation ###
Need to check if it's blockant

`pthread_mutex_lock`,
`pthread_mutex_unlock`

## Never used # #
`pthread_join`
Waits for a thread to finish it's routine and frees its memory.