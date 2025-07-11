## Test done during parsing to test grammar rules
| Command     | Expect | Description             |
| ----------- | ------ | ----------------------- |
| `> out.txt` | ✅ OK   | Only output redirection |
| `< input`   | ✅ OK   | Only input redirection  |


| Command           | Expect | Description                |
| ----------------- | ------ | -------------------------- |
| `echo hello`      | ✅ OK   | Basic command with one arg |
| `echo "hi there"` | ✅ OK   | Quoted word                |
| `echo $USER`      | ✅ OK   | Expansion                  |
| `ls -la /tmp`     | ✅ OK   | Multiple arguments         |


| Command                  | Expect | Description                  |
| ------------------------ | ------ | ---------------------------- |
| `cat < input.txt`        | ✅ OK   | Redirection before command   |
| `echo hello > out.txt`   | ✅ OK   | Output redirection after     |
| `> out.txt echo hello`   | ✅ OK   | Redirection before and after |
| `echo hello > out > log` | ✅ OK   | Multiple redirections        |
| `< in cat > out`         | ✅ OK   | In/out redirection           |



| Command          | Expect   | Why?                            |
| --------         | -------  | ------------------------------- |
| `\|`             | ❌ Error | Starts with pipe                |
| `echo hello \|`  | ❌ Error | Pipe without right-hand command |
| `> >`            | ❌ Error | Redirection with no word        |
| `echo <`         | ❌ Error | Missing file after `<`          |


| Command                        | Expect   | Notes                         |
| ------------------------------ | -------- | ----------------------------- |
| `echo hello         \| grep h` | ✅ OK    | Pipeline                      |
| `(echo hello && ls)`           | ✅ OK    | Grouped expression            |
| `((echo hello))`               | ✅ OK    | Nested group (optional logic) |


grep foo < infile > outfile
grep < infile foo > outfile
< infile grep foo > outfile
grep foo > outfile < infile


Grouped pipeline

echo hi && ls | grep main || (echo fallback && exit)
(echo hi && ls) | grep main || ((echo fallback && exit))
(echo hi && ls) | (grep main || ((echo fallback && exit)))
echo hi | grep h && (ls -l || echo fail) ; echo done
((ls && pwd) || echo fail)
(echo hello && echo world) | cat

## 🧪 Test Cases You Can Try

```bash
echo hi                         ✅
echo hi && ls                   ✅
ls -l | grep main               ✅
(echo A && echo B)              ✅
echo hi || (ls && echo fail)   ✅
((echo x))                      ✅
(echo 1 && echo 2) | cat        ✅
(echo a && echo b) || ls -l     ✅
(echo start && (ls || echo x))  ✅
```


`cat < input.txt`        ✅ OK
`echo hello > out.txt`   ✅ OK
`> out.txt echo hello`   ✅ OK
`echo hello > out > log` ✅ OK
`< in cat > out`         ✅ OK
`ehco hello` ✅ OK
`|` ✅ OK
`(echo hi && ls) | (grep main || ((echo fallback && exit)))` ✅ OK
`(echo hi && ls) | (grep main || ((echo fallback && exit))) | ` ✅ OK
`(echo hi && ls) | (grep main || ((echo fallback && exit))) && ` ✅ OK
`(echo hi && ls) | (grep main || ((echo fallback && exit))) && ` ✅ OK
`(echo hi && ls) | (grep main || ((echo fallback && exit))) | ()` ✅ OK
`(echo hi | cat | grep h) || && (cat | echo hi)` ❌ Error
`|| &&` ✅ OK


`(echo hi | cat | grep h) || ((cat && echo hi | (cat | echo hi))` ❌ Error
`(echo hi | cat | grep h) || ((cat && echo hi | (cat | echo hi)))` ✅ OK
`(hello hi` ❌ Error
`(hello hi))` ❌ Error


Redirection with expansion variable
<< $USER-e cat >> $USER >> $USER-e



(< infile cat -e) | (ls > out > out 1) -> not working...because of the final 1


## Tests for expansion_quote_removal

| Command                       | Expected behaviour            | Result   |
| ------------------------------| ------------------------------|----------|
| echo "$USER"123"$USER"'$USER' | mcamaren123mcamaren$USER      | ✅ OK    |
| $USER'$USER'                  | mcamaren$USER                 | ✅ OK    |
| '$USER'$USER                  | $USERmcamaren                 | ✅ OK    |
| $?$?                          | 00                            | ✅ OK    |
| $$                            | end program                   | ✅ OK    |
| << $USER'$HOME'               | $USER$HOME                    | ✅ OK    |
fix: include TOKEN_EXPANSION in ft_expand_heredoc_delimiter
| << '$USER'$HOME'              | $USER$HOME                    | ✅ OK    |

## Tests for builtins

| Command                  | Expected behaviour                                        | Result   |
|--------------------------|-----------------------------------------------------------|----------|
| cd                       | change directory to home, return 0                        | ✅ OK    |
| cd ..                    | return to nearest outer folder                            | ✅ OK    |
| cd src                   | change to src folder in current directory                 | ✅ OK    |
| cd /home/mcamaren/Desktop| change to given root                                      | ✅ OK    |
| c /home/mcamaren/Desktop | return EXIT_FAILURE                                       | ✅ OK    |
| export VAR1 VAR!         | Add VAR1 to export, error message for VAR!                | ✅ OK    |
| export                   | print export vars                                         | ✅ OK    |
| export VAR1=             | Add VAR1 to export and env                                | ✅ OK    |
| env                      | print env variables                                       | ✅ OK    |
| env extra                | return EXIT_FAILURE                                       | ✅ OK    |
| echo                     | print newline                                             | ✅ OK    |
| echo -nnnnnonnnn hi      | print -nnnnnonnnn hi and newline                          | ✅ OK    |
| echo -n                  | print nothing                                             | ✅ OK    |
| unset                    | return EXIT_SUCCESS                                       | ✅ OK    |
| unset var!               | return EXIT_SUCCESS                                       | ✅ OK    |
| unset LS_COLORS          | remove LS_COLORS of env and export                        | ✅ OK    |
| pwd                      | print  PWD variable                                       | ✅ OK    |
| pwd  bla bla             | print  PWD variable                                       | ✅ OK    |
| exit 3                   | echo $? -> 3 , quit                                       | ✅ OK    |
| exit aaa                 | echo $? -> 2 ,quit,  error message: numeric argument req  | ✅ OK    |
| exit aaa 2 3             | echo $? -> 2 ,quit , error message: numeric argument req  | ✅ OK    |
| exit 11 22               | echo $? -> 1, not quit, too many arguments                | ret value|
| exit 258                 | echo $? -> 2, quit                                        | ✅ OK    |
| exit                     | echo $? -> exitcode store in t_shell  variable            | ✅ OK    |
| exit -1                  | echo $? -> 255 , quit                                     | ✅ OK    |
## Tests for balancec quote check

| Command                       | Expected behaviour                         | Result   |
|-------------------------------|--------------------------------------------|----------|
| echo "he said 'hi"            | Balanced                                   | ✅ OK    |
| echo 'hello"""'               | Balanced                                   | ✅ OK    |
| echo "hello | " aa            | Balanced                                   | ✅ OK    |

## Tests done during execution part

**Legends**
* ✅ OK => should succeed and return EXIT_SUCCESS (exit code == 0)
* ❌ Error => should failed and return an error code (1, 127, 126, etc.)

### Test Only Redirections
```Shell
# Existing file
< Makefile #✅ OK
< Makefile < readme.md #✅ OK

# Non-Existing file
< Infile # ❌ Error

# Existing file with no right
touch infile
chmod 000 infile
< infile # ❌ Error

# Multiple infile (non-existing + no right files)
< infile cat < Makefile # ❌ Error
< infile < non_existing_file < non_existing_file2 # ❌ Error
# TODO: check exit program, maybe the redirection need to be reset in ft_handle_shell because needed to write exit 4 times

```
### Test Simple command
```Shell
cat readme.md  # ✅ OK
ls -l  # ✅ OK
ls -la  # ✅ OK
wc # will block the shell  # ✅ OK
```
### Test Only Builtins
```Shell
# ECHO
echo hi # ✅ OK

# CD
cd ..  # ✅ OK
cd ./src # ✅ OK
cd ./srcs #  ⚠️ not working, error message to fix and exit code

# PWD
pwd

# EXPORT
export
export test
export test="dfghj"

# ENV
env # ✅ OK
env hello # ⚠️ not working perfectly, should return the following error message "env: ‘hello’: No such file or directory" with error code = 127 but currently does not return error message and wrong error message
env hello hi # same as above
```

### Command with pipe and Builtins
```Shell
cd .. | ls # ✅ OK
cat readme.md | cd .. # ⚠️ not working

```

### Test Simple command with pipe
```Shell
cat readme.md | ls  # ✅ OK
cat readme.md | wc -l  # ✅ OK
```

### Test Logical operator with simple command + pipe
```Shell
true && ls # ✅ OK
false || ls # ✅ OK
```
### Test Multiple Logical operator with simple command + pipe
// TODO Not working yet
```Shell
true && false && ls # ⚠️ not working
(true || ls) | cat # ✅ OK
```

### Test Multiple Redirections with Command
```Shell
# Multiple Infile
< Makefile cat < ./include/exec.h

# Multiple Infile with Pipe + multiple Redirect Out
< Makefile cat < ./include/exec.h | cat > testo1 > testo3 # ✅ OK
cat readme.md | < ./include/exec.h < ./include/minishell.h cat > out123 > out456 | wc -l  # ✅ OK

# Multiple Infile with Pipe + multiple Append Out
< Makefile cat < ./include/exec.h | cat >> testo1 >> testo3 # ✅ OK

# Multiple Infile with Pipe + mix Redirect Out +  Append Out
< Makefile cat < ./include/exec.h | cat >> testo1 > testo3 # ✅ OK
< Makefile cat < ./include/exec.h | cat > testo1 >> testo3 # ✅ OK
< Makefile cat < ./include/exec.h | cat > out1 >> out2 > out3 # ✅ OK

# Heredoc
<< eof  # ⚠️ not working
<< eof cat # ✅ OK
<< eof << hello cat # ✅ OK
< readme.md << eof cat # ✅ OK
<< eof < readme.md cat # ✅ OK
<< hello cat | wc - l # ✅ OK
<< eof cat | cat | grep 'TODO' # ⚠️ wait for the expansion code
<< eof cat | cat | grep TODO # ⚠️ wait for the expansion code
<< eof << end cat | cat | grep test # ✅ OK
<< eof << end cat | cat | wc -l # ✅ OK
<< eof << end cat < readme.md | cat | grep test # ✅ OK return with exit code 1 if readme does not have any words "test" else return exit code 0
<< eof << end cat < readme.md | << eof cat | grep hello # ✅ OK
<< eof << end cat < readme.md | << eof cat | << eof grep hello # ✅ OK

<< eof << end cat | << cat eof | cat > out11 # ⚠️ not working because teh exit_code is not correct yet=> return exit_code = 0 instead of exit_code = 127

<< '$HOME-e$test' # ⚠️ not working
<< '$HOME-e$test' cat # ✅ OK

# Multiple Heredoc with multiple type of redirections
<< eof << end cat < readme.md | << eof cat < Makefile| << eof grep # < Makefile # ✅ OK
<< eof << end cat < readme.md > out1 | << eof cat < Makefile| << eof grep # < Makefile # ✅ OK
<< eof << end cat < readme.md > out1 | << eof cat < Makefile| << eof grep '#' < Makefile # ⚠️ Not working, need to remove the quote around the `#` to make it works
```

### Subshell

```Shell
// TODO: fix the parsing of this line which is currently not working
cat (< readme << eof cat) # ⚠️⚠️⚠️⚠️⚠️ not working
```

### Logical operator
```Shell
cat < readme.md | grep excel && ls
<< EOF cat | ls && echo hi > file

false || true | echo hi
false || false | echo hi

```
### Complex Command

```Shell
# Multiple pipes with Multiple Redirections
<< EOF cat | ls && echo hi > file
cat Makefile > test001 | ls | wc -l | cat readme.md | wc -l > testo1 > testo2 #✅ OK


# Multiple pipes with Multiple Redirections and one file with no right
chmod 000 testo2 #✅ OK
ls -l # ✅ OK (to check right)
cat Makefile > test001 | ls | wc -l | cat readme.md | wc -l > testo1 > testo2 ❌ Error

# Multiple pipes + mix command and builtins
# Multiple pipes + mix command and builtins + logical operator
```



tricky tests

./srcs | echo a => affiche 'a' + message erreurs +


### Refactoring test

echo hello > file.txt
cat < file.txt
cat << EOF
cat << EOF | cat
echo hello >> out.txt
ls | grep minishell > result.txt
