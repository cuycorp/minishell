## Grammar Rules

```shell
# A `command_line` consists of a single `logical_expr`.
command_line    ::= logical_expr
# A `logical_expr` is a `pipeline` optionally followed by any number of `&&` or `||`, each followed by another `pipeline`.
logical_expr    ::= pipeline (('&&' | '||') pipeline)*
```
```shell
# A `pipeline` consists of a `simple_command`, and optionally any number of other `simple_command` joined by `|`.
pipeline        ::= simple_command ('|' simple_command)*
# A `simple_command` consists of zero or more `redirection` operators, followed by a `word`, and optionally followed by more `words` or `redirection`.
simple_command  ::= (redirection)* word (word | redirection)*
# A `redirection` operator is one of `<`, `>`, `>>`, or `<<`, followed by a `word`.
redirection     ::= ('<' | '>' | '>>' | '<<') word
# A `word` is one or more of the following: a `quoted_string`, an `unquoted_string`, or a `variable`.
word            ::= (quoted_string | unquoted_string | variable)+
# A `quoted_string` is either a `single_quoted` string or a `double_quoted` string.
quoted_string   ::= single_quoted | double_quoted
# A `single_quoted` string starts and ends with single quotes and contains any characters except single quote.
single_quoted   ::= "'" [^']* "'"
```
```shell
# A `double_quoted` string starts and ends with double quotes (`"`), and can contain `regular_char` or `variable`.
double_quoted   ::= '"' (regular_char | variable)* '"'
# A `variable` starts with a `$` symbol, followed by either an `identifier` or the special `?` character.
variable        ::= '$' (identifier | '?')
# An `unquoted_string` consists of one or more `regular_char` or `escaped_char`.
unquoted_string ::= (regular_char | escaped_char)+
# An `identifier` starts with a letter or underscore (`_`), followed by zero or more letters, digits, or underscores.
identifier		::= [a-zA-Z_][a-zA-Z0-9_]*
# A `regular_char` is any character except for: pipe (`|`), ampersand (`&`), angle brackets (`<`, `>`), parentheses (`()`), curly braces (`{}`, `}`), double quotes (`"`), dollar sign (`$`), space (` `), tab (`\t`), or newline (`\n`).
regular_char	::= [^|&<>(){}"'$\ \t\n]
```


### Key Precedence Points:
* **Logical operators (`&&`, `||`)** have the **lowest precedence**, as they connect entire pipelines.
* **Pipes (`|`)** have **medium precedence**. They connect commands within a pipeline.
* **Redirections (`<`, `>`, `>>`, `<<`)** have the **highest precedence**. They apply within a `simple_command` and are processed before the `word` part of the command.

