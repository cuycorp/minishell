Common Exit Codes in C:

- `0` — Success:

	Meaning: The program executed successfully without errors.

	Example: exit(0); or return 0; from main().

	This is the standard exit status for a program that completed without issues.

- `1` — General Error (Failure):

	Meaning: This is a general error exit code. It usually signifies that something went wrong during the execution of the program, but the exact cause is not specified.

	Example: exit(1); or return 1; from main().

	Note: Often used to indicate a failure to initialize the program or a serious issue that caused abnormal termination.

- `2` — Misuse of Shell Builtins (in shell programs):

	Meaning: This is an exit status used by shells (like bash) for misuse of shell built-in commands or syntax errors. It’s not used widely outside shell programs.

	Example: For a shell script, a misuse of a built-in command can return 2.

	Note: It’s mostly relevant in the context of shell scripting, rather than C programs directly.

- `126` — Command Cannot Be Executed:

	Meaning: This indicates that the command was found but could not be executed. This is often due to permission issues (e.g., the file is not executable).

	Example: In a shell, if you try to run a command that’s not executable (e.g., without execution permission), it might return 126.

- `127` — Command Not Found:

	Meaning: This exit code indicates that the command could not be found. It typically means the program or command you tried to execute doesn’t exist in the system’s PATH or isn’t installed.

	Example: exit(127); if trying to execute a command that doesn’t exist or isn’t available.

- `128` — Invalid Argument to Exit:

	Meaning: This exit code can be returned if the exit status given to exit() or the return statement is out of range (i.e., it’s greater than 255).

	Example: exit(128); would indicate an invalid exit status if used improperly.

- `128 + n` — Signal Exit Code:

	Meaning: If a program is terminated by a signal, the exit code will be 128 + signal_number. For example, if the program receives SIGSEGV (segmentation fault, signal number 11), the exit code will be 139 (i.e., 128 + 11).

	Example: exit(139); indicates the program was terminated by a segmentation fault.

	Common signals and their exit codes:

		SIGSEGV (Segmentation Fault) → exit(139);

		SIGFPE (Floating-Point Exception) → exit(136);

		SIGINT (Interrupt from Keyboard) → exit(130);

		SIGTERM (Termination Signal) → exit(143);

- `255` — Exit Status Out of Range:

	Meaning: The exit status can range from 0 to 255. If a program explicitly tries to return a value outside this range (e.g., using a large positive number), it is truncated to fit into the valid range, usually resulting in 255 as the exit code.

	Example: A return value like exit(300); will be truncated to 255 (i.e., 300 % 256).
