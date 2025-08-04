# Minishell Project Roadmap

## Project Structure File

```
Minishell
|-docs/
|-include/
|	|-minishell.h
|	|-structures.h
|	|-utils.h
|-lib/
|	|-ft_printf/
|	|-get_next_line/
|	|-libft/
|-src/
|	|-initializer/		# all the initializer functions
|	|-lexer/			# all the function for tokenization and syntax analysis
|	|-parser/			# all the parsing functions (command construction, etc.)
|	|-exec/				# all the pipe, fork, redirection, AST tree, and exec functions
|	|-builtins/			# all the builtins functions
|	|-signals/			# all the functions to manage signals
|	|-shell/			# all the functions to manage shell
|	|-env/				# all the environment variable functions
|	|-utils/			# all the utils functions
|	|-main.c
|-Makefile
|-readme.md
```

---

## Phase 1: Input Handling

- [x] Use `readline()` to display prompt and collect input.
- [x] Add input to history with `add_history()`.
- [X] Close the program when writing `exit`
- [ ] Handle `CTRL-D` (exit), `CTRL-C` (new prompt), `CTRL-\` (ignored).

---

## Phase 2: Lexing (Tokenization)

- [x] Define Token Type
- [x] Recognize redirection operators: `<`, `>`, `<<`, `>>`
- [x] Recognize parenthesis: `(`, `)`
- [x] Recognize `pipe` operator : `|`
- [x] Recognize logical `AND` operator : `&&`
- [x] Recognize logical `OR` operator : `||`
- [x] Identify words by implementing the <unquoted_char> grammar rule
- [x] Handle quoting:
	- [x] Single quote `'`
	- [x] Double quote `"`
- [x] Handle `TOKEN_END_OF_FILE` Token
- [x] Handle `TOKEN_UNKNOWN` Token
- [x] Fix issue with `TOKEN_END_OF_FILE` and `TOKEN_UNKNOWN` conflicts
- [x] Fix issue with `&&` not returning the right token type
- [x] Fix issue with `&` which currently close the program but rather create a `TOKEN_UNKNOWN` in order not to close the program
- [x] Refactored the single quote handling?
- [] Handle `*` Wildcard Token
- [] Handle unknow character such as `;` which currently close the program...
- [x] Add check on number of quotes and parenthesis -> should be an even number

#### Example:

Input:

```bash
echo "Hello $USER" > out.txt
```

Tokens:
`[echo] [Hello $USER] [>] [out.txt]` => like this?
`[echo] ["Hello $USER"] [>] [out.txt]` => or this?

---

## Phase 3: Syntax Analysis

- [x] Define grammar rules
- [x] Fix grammar rules to better incorporate parenthesis in <command_line> rule
- [x] Validate token order and grammar => Recursive Descent Parsing algo?
	- [x] Implement the grammar rules in function
	- [x] Implement the match function
	- [x] Handle syntax errors ? (unclosed quotes, invalid chars)
	- [x] Handle syntax errors (e.g., empty pipes, unmatched tokens) (e.g., `| > file`, `cat infile |`)
- [x] Fix error when line finished with pipe (e.g: `(echo hi && ls) | (grep main || ((echo fallback && exit))) | `)
- [] Fix tokenizer which seems to close the program when it encountere an unknown character (e.g. `;`, `echo hi &&;` and create leaks)
- [x] Modifu tokenizer to classify all  TOKEN_WORD correctly,
- [x] Implement var_expansion
- [x] Implement retokenize
- [x] Implement quoteremoval
---

## Phase 4: Parsing / Building Command Structures + Environment Management ?

### Environment Management ?
- [x] Load environment variables into internal structure
- [x] Load environment from `envp` into internal list/structure
	- [] what if the user write `env -i ./minishell` while starting the program,is env well saved in the structures?
- [ ] Implement `getenv`, `setenv`, `unsetenv` functions
- [x] Replace environment variables: `$VAR`, `$?`
	- [x] If an environment variable is used as a limiter with heredoc, the variale should not be extended
- [x] Build the command / Store command in a structure (e.g., `t_command`)
	- [x] No need to implement linked list since we are using AST tree
- [x] Build the redirection structure (e.g., `t_command`) and link it with command if needed
	- [x] Used linked list to link multiple redirection
- [x] Implement AST tree to find token priority => see Piscine C13 for Binary Tree
- [x] Handle input/output files, heredoc
	- [X] in Linked-List style?
- [x] Implement error messages
	- [] Fix error message that pop in double
	(ex: `cat < | ls`
		=> minishell: syntax error near unexpected token '|', expected file/limiter after redirection
		=> minishell: syntax error near unexpected token '|')
- [x] Check memory leak with valgrind
---

## Phase 5: Execution

- [x] Implement `fork`/`execve` with pipes
- [x] Handle input/output redirection with `dup2`
- [] Manage file descriptors (prevent leaks): close / open the right fds
	- [] still unclosed fds with pipe and multiple heredocs (ex: `cat file.txt | grep "hello" && echo "Match found" || echo "No match"`)
	- [] still unclosed fds with simple command (ex: `<< eof << end > readme.md cat`)
	- [] still unclosed fds with simple command (ex: `<< eof cat < readme.md`)
- [] Manage child process exit codes
	- [] 0
	- [] 1
	- [] 126 - No such file / redirectory, permission denied
	- [x] 127 - Command not found
	- [] 130 - 128 + SIGINT (CTRL-C)
	- [] 131 - 128 + SIGQUIT ("CTR-\")

- [x] implement parse_error (e.g `<< eof >` => should open the heredoc but return an error message since the final redirection is wrongly build)
- [] Traverse the AST tree to execute the command according to the node priority
	- [x] Pipe
	- [x] Redirect In, Out, Append out
	- [x] Heredoc
	- [x] Simple Command
	- [x] Logical Operator
	- [] Wildcard
- [] handle absolute_path and relative_path (S_ISDIR, )
- [] implement builtin execution
	- [x] echo
	- [x] cd
	- [x] export
		- [] see for order of the expansion in cases like the following: `export TEST="test" && echo $TEST`
	- [x] unset
	- [x] end
	- [x] pwd
	- [] exit
- [] check all builtin with logical operator
- [] fix all leaks
	- [x] in simple command
	- [x] in pipe
	- [x] in redirections
	- [x] in heredoc
	- [x] with logical operator
	- [] with wildcard
	- [] with builtins

<!-- Create the Pipe with all the forking and redirection
Create the AST to execute the command (and get command priority) => C13 from Piscine for Binary Tree -->

## Phase 6: Builtins

- [] Should we implement them by using execve?
- [] `echo [-n]`
- [x] CD + PWD
	- [x] `cd [relative_path]`
	- [x] `cd [absolute_path]`
	- [x] `pwd`
	- [] check if all the edge cases are handled
- [] EXPORT + UNSET + ENV
	- [] `export KEY=VAL`
		- [] export should handle the expand
		- [] variable name can't start with a number. 9eg "123VAR_A" is invalid
		- [] can we echo an unset variable (e.g. `export TEST; echo test`)?
	- [] `unset KEY`
	- [] `env`
	- [] `env [arguments]` => how to use it exactly?
- [] `exit`
	- [] exit can take argument but only numeric argument

---

## Phase 7: Signals

- [ ] Handle `SIGINT` signal for `CTRL-C`
- [ ] Handle `EOF` signal for `CTRL-D`
- [ ] Handle ??? signal for `CTRL-\`
	- [] if blocking command like `sleep 5`, `wc` -> should return exit code 131
- [] Reset signal handlers for child processes
- [] Interactive mode?
- [] Handle signal with heredoc

---

## Phase 8: Bonus

- [x] Implement `&&` and `||`
	- [] Handle Parenthesis for grouping / priority
- [] Implement `*` wildcard expansion: should match only files in current working directory
	- [] Be careful of the behavior with expansion
	```
		echo $PAT*
		build docs include lib libminishell.a Makefile minishell readline.supp readme.md src

		echo $PATH*
		/home/jgossard/.local/funcheck/host:/home/jgossard/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin*

	```
	- [] Be careful with the type of wildcard because `*` is a valid character in a file name and should not be expanded


## Phase 9: Clear the code before correction
- [] Tester avec funcheck / valgrind
- [] Check all the TODO in the project and remove them
	- [] Todo in Makefile: don't forget to update the list of files
- [] Block the execution of minishell inside minishell, if not, we should update the env SHLVL by 1 and decrease teh SHLVL by 1 if we exit the minishell
---
