<shell>					::= <command_line>*

<command_line>			::= <pipeline> | <grouped_pipeline>

<grouped_pipeline>		::= <left_parenthesis> <pipeline> (<special_operator> <pipeline>)* <right_parenthesis>
<pipeline>				::= <simple_command> (<pipe> <simple_command>)*
<!-- <command_line>			::= <left_parenthesis>? <pipeline> (('&&' | '||') <pipeline>)* <right_parenthesis>? -->
<simple_command>		::= (<redirection>)* <word> (<arguments>)* (<word> | <redirection>)*
<arguments>				::= <word> | <quoted_string> | <env_variable>
<word>					::= <unquoted_char>+
<unquoted_char> ::= any printable character
    except: '|', '&', ';', '<', '>', '(', ')', ' ', '"', "'", '$', '\'

<!-- > Bash treats the following as token separators, even without spaces:
| & ; < > ( ) { } newline
So those should not be included in your ft_is_special_char() — unless they are escaped or quoted. -->

<!-- <unquoted_char>			::= "!" | "."
 | "," | ";" | ":" | "?" | "!" | "~" | "_" | "@" | "+" | "/" | "=" | "[" | "]" | "*" | " " | "-" | "\" | <letter> | <digit> | "|" | "<" | ">" | ">>" | "<<" | "$" | "^" | "&"| "#" | "%" | "(" | ")" -->
<quoted_string>			::= <single_quoted> | <double_quoted_string>
<!-- A `single_quoted` string starts and ends with single quotes and contains any characters except single quote. -->
<single_quoted>			::= "'" [^']* "'"
<double_quoted_string>	::= '"' <double_quoted_char>* '"'
<double_quoted_char>	::= [^"]* | <env_variable>
<env_variable>			::= "$" <env_name> | "$?"
<redirection>			::= ('<' | '>' | '>>' | '<<') <word>
<env_name>				::= <letter> (<letter> | <digit> | "_")*
<special_operator>		::= "|" | "&" | ";" | "<" | ">" | "(" | ")"
<letter>				::= "a"-"z" | "A"-"Z"
<digit>					::= "0"-"9"
<left_parenthesis>		::= "("
<right_parenthesis>		::= ")"
<pipe>					::= "|"

<!-- <export_args> ::= <env_name> "=" <word> -->
