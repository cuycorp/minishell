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
`(echo hi | cat | grep h) || && (cat | echo hi)` ✅ OK
`|| &&` ✅ OK


`(echo hi | cat | grep h) || ((cat && echo hi | (cat | echo hi))` ❌ Error
`(echo hi | cat | grep h) || ((cat && echo hi | (cat | echo hi)))` ✅ OK
