# Regular-Expression-Parser

The Regular Expression Parser is a testing tool. In particular,

* it checks whether a given string is accepted by a regular expression; and

* it checks whether two given regular expressions describe the same language, and gives a distinguishable string if they do not.

## Formating

The input of the regular expression must follow the following convension.

* Concatenation: represented by writing two elements next to each other. *Example: $01$ stands for $\{0\}\dot\{1\}$.*

* Union: represented by the symbol '$+$'. *Example: $0+1$ stands for $\{0\}\cup\{\1\}$.*

* Kleene closure: represented by the single symbol '$*$' right after the language. *Example: $0*$ stands for $\{0\}^*$.*

* Higher precedence of operation: represented by the parentheses, '$($' and '$)$'. *Example: $10(0+1)$ stands for the $\{100,101\}$.*

