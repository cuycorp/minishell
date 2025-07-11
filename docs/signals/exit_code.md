## Man definition

- WIFSIGNALED(wstatus) returns true if the child process was terminated by a signal.

- WTERMSIG(wstatus) returns the number of the signal that caused the child process to terminate. This macro should be employed only if WIFSIGNALED returned true.



### CHATGPT - Exit Code
- WIFSIGNALED(status)
This checks if the process was terminated by a signal. In that case, WTERMSIG(status) gives the signal number.

To represent this in the exit code, the convention is:

exit_code = 128 + signal_number

Why 128 + signal_number?
This is not mandated by POSIX, but it is a widely followed convention used by many shells and utilities (e.g., Bash, system(), etc.) to encode the fact that a process terminated due to a signal.

Examples:

A program killed by SIGKILL (signal 9) → exit code = 128 + 9 = 137

A program terminated by SIGSEGV (signal 11) → exit code = 128 + 11 = 139

This helps tools and users distinguish between:

A normal exit: 0–127 (typically)

An abnormal signal-based exit: 128–255
