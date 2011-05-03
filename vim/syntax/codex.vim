if exists("b:current_syntax")
    finish
endif

syn keyword codexStructure        module
syn keyword codexImport           import
syn keyword codexConditional      if elseif else
syn keyword codexStatement        for this while do for return end _internal

syn match   codexOperator         "[-!#$%&\*\+/∈<=≠>➔≤≥\[\]\(\)\?@\\^|~:.]*"
syn match   codexType             "\(\<[A-Z][a-zA-Z0-9_']*\)"
syn match   codexComment          "--.*"

syn match   codexSpecialChar      contained "\\\([0-9]\+\|o[0-7]\+\|x[0-9a-fA-F]\+\|[\"\\'&\\abfnrtv]\|^[A-Z^_\[\\\]]\)"
syn match   codexSpecialChar      contained "\\\(NUL\|SOH\|STX\|ETX\|EOT\|ENQ\|ACK\|BEL\|BS\|HT\|LF\|VT\|FF\|CR\|SO\|SI\|DLE\|DC1\|DC2\|DC3\|DC4\|NAK\|SYN\|ETB\|CAN\|EM\|SUB\|ESC\|FS\|GS\|RS\|US\|SP\|DEL\)"
syn match   codexSpecialCharError contained "\\&\|'''\+"
syn region  codexString           start=+"+  skip=+\\\\\|\\"+  end=+"+  contains=codexSpecialChar
syn match   codexCharacter        "[^a-zA-Z0-9_']'\([^\\]\|\\[^']\+\|\\'\)'"lc=1 contains=codexSpecialChar,codexSpecialCharError
syn match   codexCharacter        "^'\([^\\]\|\\[^']\+\|\\'\)'" contains=codexSpecialChar,codexSpecialCharError
syn match   codexNumber           "\<[0-9]\+\>\|\<0[xX][0-9a-fA-F]\+\>\|\<0[oO][0-7]\+\>"
syn match   codexReal             "\<[0-9]\+\.[0-9]\+\([eE][-+]\=[0-9]\+\)\=\>"
syn keyword codexSpecialConst     null true false

let b:current_syntax = "codex"

hi def link codexStructure        Structure
hi def link codexImport           Include
hi def link codexConditional      Conditional
hi def link codexStatement        Statement
hi def link codexComment          Comment
hi def link codexType             Type
hi def link codexOperator         Operator
hi def link codexString           Constant
hi def link codexCharacter        Constant
hi def link codexNumber           Constant
hi def link codexReal             Constant
hi def link codexSpecialConst     Constant

