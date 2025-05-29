<shell>					::= <command_line>*
<command_line>			::= <pipeline> (('&&' | '||') <pipeline>)*
<pipeline>				::= <simple_command> ('|' <simple_command>)*
<pipe>					::= "|"
<simple_command>		::= (<redirection>)* <word> (<arguments>)* (<word> | <redirection>)*
<arguments>				::= <word> | <quoted_string> | <env_variable> | <special_variable>
<word>					::= <unquoted_char>+
<unquoted_char>			::= "!" | "." | "," | ";" | ":" | "?" | "!" | "~" | "_" | "@" | "+" | "/" | "=" | "[" | "]" | "*" | " " | "-" | "\" | <letter> | <digit> | "|" | "<" | ">" | ">>" | "<<" | "$" | "^" | "&"| "#" | "%"
<quoted_string>			::= <single_quoted> | <double_quoted_string>
<!-- A `single_quoted` string starts and ends with single quotes and contains any characters except single quote. -->
<single_quoted>			::= "'" [^']* "'"
<double_quoted_string>	::= '"' <double_quoted_char>* '"'
<double_quoted_char>	::= [^"]* | <env_variable>
<env_variable>			::= "$" <env_name> | "$?"
<env_name>				::= <letter> (<letter> | <digit> | "_")*
<letter>				::= "a"-"z" | "A"-"Z"
<digit>					::= "0"-"9"
<redirection>			::= ('<' | '>' | '>>' | '<<') <word>

<!-- <export_args> ::= <env_name> "=" <word> -->


## Still to be implemented

* redirection: <, >, << , >>

* unquoted_char
* single-quote
* double-quote

* &&
* ||
* pipe: |

## Lexing
### Phase 1: Scanning / Tokenization
echo "hello world" > outfile

echo

"hello world $HOME"

>

outfile

### Phase 2: Analize Syntax - Order of tokens => analysing th estream of token if it follows the grammar rules

## Parsing
### Phase 3: start replacing content of the token

"hello world $HOME" => "hello world /path/path/"

### Phase 4: Create the command

linked list of token [token1, token2, ...]

## Execution
Create the Pipe with all the forking and redirection
Create the AST to execute the command (and get command priority) => C13 from Piscine for Binary Tree

## Builtins
## Signals
