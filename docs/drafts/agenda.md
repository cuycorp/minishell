# Agenda

## Lexing
### Phase 1: Scanning / Tokenization
echo "hello world" > outfile

#### Still to be implemented

* redirection: <, >, << , >>
* unquoted_char
* single-quote
* double-quotes
* &&
* ||
* pipe: |

### Phase 2: Analize Syntax - Order of tokens => analysing the stream of token if it follows the grammar rules

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
