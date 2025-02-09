# Philosopher # 

## USED ##
`memset`,
`printf`,
`malloc`,
`free`,
`write`,
`usleep`

## TRIED ##
`gettimeofday(t_timeval, NULL)` (second is unused)

2 long, tv_sec (since EPOCH) and tv_usec;

return != 0 if error

## Never used # #
`pthread_create`,
`pthread_detach`,
`pthread_join`

---
### Mutex Creation and Destroy ###
Need to check usability and error returns

`pthread_mutex_init`,
`pthread_mutex_destroy`

---
### Mutex Manipulation ###
Need to check if it's blockant

`pthread_mutex_lock`,
`pthread_mutex_unlock`
