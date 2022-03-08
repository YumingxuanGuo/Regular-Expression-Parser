# Regular-Expression-Parser

The Regular Expression Parser is a testing tool. In particular,

* it checks whether a given string is accepted by a regular expression; and

* it checks whether two given regular expressions describe the same language, and gives a distinguishable string if they do not (still under development).

## Formating

The input of the regular expression must follow the following convension.

* Concatenation: represented by writing two elements next to each other. 

* Union: represented by the symbol '+'. 

* Kleene closure: represented by the single symbol '*' right after the language. 

* Higher precedence of operation: represented by the parentheses, '(' and ')'.

* The empty string (epsilon): represented by '$'.

* No spaces are needed.