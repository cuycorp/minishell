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
- [] Handle quoting:
	- [x] Single quote `'`
	- [x] Double quote `"`
- [x] Handle `TOKEN_END_OF_FILE` Token
- [x] Handle `TOKEN_UNKNOWN` Token
- [] Handle `*` Wildcard Token
- [x] Fix issue with `TOKEN_END_OF_FILE` and `TOKEN_UNKNOWN` conflicts
- [] Fix issue with `&&` not returning the right token type
- [] Fix issue with `&` which currently close the program but rather create a `TOKEN_UNKNOWN` in order not to close the program
- [] Refactored the single quote handling?

### Example:

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
- [] Fix grammar rules to better incorporate parenthesis in <command_line> rule
- [] Validate token order and grammar => Recursive Descent Parsing algo?
	- [] Implement the grammar rules in function
	- [] Implement the match function
	- [] Handle syntax errors ? (unclosed quotes, invalid chars)
	- [] Handle syntax errors (e.g., empty pipes, unmatched tokens) (e.g., `| > file`, `cat infile |`)

---

## Phase 4: Parsing / Building Command Structures + Environment Management ?

### Environment Management ?
- [ ] Load environment variables into internal structure
- [x] Load environment from `envp` into internal list/structure
- [ ] Implement `getenv`, `setenv`, `unsetenv` functions

- [ ] Replace environment variables: `$VAR`, `$?`
- [ ] Build the command / Store command in a structure (e.g., `t_command`)
	<!-- - [] --in Array style?-- -->
	- [X] in Linked-List style?
- [ ] Handle input/output files, heredoc
<!-- - [ ] Support command chaining via linked list or AST -->

---

## Phase 5: Execution

- [] Implement `fork`/`execve` with pipes
- [] Handle input/output redirection with `dup2`
- [] Manage file descriptors (prevent leaks): close / open the right fds
- [] Manage child process exit codes
- [] Implement AST tree to find token priority => see Piscine C13 for Binary Tree

<!-- Create the Pipe with all the forking and redirection
Create the AST to execute the command (and get command priority) => C13 from Piscine for Binary Tree -->

## Phase 6: Builtins

- [] Should we implement them by using execve?
- [] `echo [-n]`
- [] CD + PWD
	- [] `cd [relative_path]`
	- [] `cd [absolute_path]`
	- [] `pwd`
- [] EXPORT + UNSET + ENV
	- [] `export KEY=VAL`
	- [] `unset KEY`
	- [] `env`
	- [] `env [arguments]` => how to use it exactly?
- [] `exit`

---

## Phase 7: Signals

- [ ] Handle `SIGINT` signal for `CTRL-C`
- [ ] Handle `EOF` signal for `CTRL-D`
- [ ] Handle ??? signal for `CTRL-\`
- [ ] Reset signal handlers for child processes
- [] Interactive mode?

---

## Phase 8: Bonus

- [] Implement `&&` and `||`
	- [] Handle Parenthesis for grouping / priority
- [] Implement `*` wildcard expansion: should match only files in current working directory

---
