# diff

Usage: diff [OPTION]... FILES

Compare FILES line by line.

Mandatory arguments to long options are mandatory for short options too.
________________________
/\ WARNING : OPTION IMPORTANTE EN PRIORITE /\
________________________
--normal output a normal diff (the default)

-q, --brief report only when files differ

-s, --report-identical-files report when two files are the same

________________________
/\ OPTION SECONDAIRE /\
_______________________

-c, -C NUM, --context[=NUM] output NUM (default 3) lines of copied context

-u, -U NUM, --unified[=NUM] output NUM (default 3) lines of unified context

-y, --side-by-side output in two columns

-i, --ignore-case ignore case differences in file contents

-w, --ignore-all-space ignore all white space

-a, --text treat all files as text

-W, --width=NUM output at most NUM (default 130) print columns

-N, --new-file treat absent files as empty

-B, --ignore-blank-lines ignore changes whose lines are all blank

_____________________
