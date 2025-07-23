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
| << $USER'$HOME'               | $USER$HOME                    | ❌ Error |
fix: include TOKEN_EXPANSION in ft_expand_heredoc_delimiter
| << '$USER'$HOME'              | $USER$HOME                    | ✅ OK    |

## Tests for builtins

| Command                       | Expected behaviour                         | Result   |
|-------------------------------|--------------------------------------------|----------|
| cd                            | change directory to home, return 0         | ✅ OK    |
| cd ..                         | return to nearest outer folder             | ✅ OK    |
| cd src                        | change to src folder in current directory  | ✅ OK    |
| cd /home/mcamaren/Desktop     | change to given root                       | ✅ OK    |
| c /home/mcamaren/Desktop      | return EXIT_FAILURE                        | ✅ OK    |
| export VAR1 VAR!              | Add VAR1 to export, error message for VAR! | ✅ OK    |
| export                        | print export vars                          | ✅ OK    |
| export VAR1=                  | Add VAR1 to export and env                 | ✅ OK    |
| env                           | print env variables                        | ✅ OK    |
| env extra                     | return EXIT_FAILURE                        | ✅ OK    |
| echo                          | print newline                              | ✅ OK    |
| echo -nnnnnonnnn hi           | print -nnnnnonnnn hi and newline           | ✅ OK    |
| echo -n                       | print nothing                              | ✅ OK    |
| unset                         | return EXIT_SUCCESS                        | ✅ OK    |
| unset var!                    | return EXIT_SUCCESS                        | ✅ OK    |
| unset LS_COLORS               | remove LS_COLORS of env and export         | ✅ OK    |
| pwd                           | print  PWD variable                        | ✅ OK    |
| pwd  bla bla                  | print  PWD variable                        | ✅ OK    |
