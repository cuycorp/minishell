<shell>						::= <command_line>*
<command_line>				::= <and_or_list>
<and_or_list>				::= <subshell_group> ( <logical_operator> <subshell_group> )*
<subshell_group>			::= <subshell> | <pipeline>
<subshell>					::= <left_parenthesis> <and_or_list> <right_parenthesis>
<pipeline>					::= <pipeline_command> (<pipe> <pipeline_command>)*
<pipeline_command>			::= <subshell> | <simple_command>
<simple_command>			::= <redirection>* <command_word>? <argument>* <redirection>* <command_terminator>
<command_word>				::= <word> | <env_variable>
<argument>					::= <word> | <env_variable>
<word>						::= <unquoted_char>+ | <quoted_string>
<unquoted_char>				::= any printable character, except: '|', '&', ';', '<', '>', '(', ')', ' ', '"', "'", '$', '\\'
<quoted_string>				::= <single_quoted> | <double_quoted_string>
<!-- A `single_quoted` string starts and ends with single quotes and contains any characters except single quote. -->
<single_quoted>				::= "'" [^']* "'"
<double_quoted_string>		::= '"' <double_quoted_char>* '"'
<double_quoted_char>		::= [^"]* | <env_variable>
<env_variable>				::= "$" <env_name> | "$?"
<redirection>				::= ('<' | '>' | '>>' | '<<') <word>
<env_name>					::= <letter> (<letter> | <digit> | "_")*
<command_terminator>		::= <pipe> | <logical_operator> | <right_parenthesis>
<!-- <special_operator>		::= "|" | "&" | ";" | "<" | ">" | "(" | ")" -->
<logical_operator>			::= <logical_and> | <logical_or>
<logical_and>				::= "&&"
<logical_or>				::= "||"
<!-- <end_of_line>				::= "\n" | ";" -->
<letter>					::= "a"-"z" | "A"-"Z"
<digit>						::= "0"-"9"
<left_parenthesis>			::= "("
<right_parenthesis>			::= ")"
<pipe>						::= "|"

<!-- <export_args> ::= <env_name> "=" <word> -->

<!-- > Bash treats the following as token separators, even without spaces:
| & ; < > ( ) { } newline
So those should not be included in your ft_is_special_char() — unless they are escaped or quoted. -->

<!-- <unquoted_char>			::= "!" | "."
 | "," | ";" | ":" | "?" | "!" | "~" | "_" | "@" | "+" | "/" | "=" | "[" | "]" | "*" | " " | "-" | "\" | <letter> | <digit> | "|" | "<" | ">" | ">>" | "<<" | "$" | "^" | "&"| "#" | "%" | "(" | ")" -->
