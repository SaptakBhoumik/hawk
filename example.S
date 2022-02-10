;LOAD <data> <address>
;Assign <data> to register <address>
LOAD 20 0
;MOV <address1> <address2>
;Assign the value of register <address1> to register <address2>
MOV 0 1
;POP <address>
;delete the value <address>
POP 0
;PRINT <address>
;print the value of register <address>
PRINT 0
;ADD <address1> <address2> <address3>
;Assign the value of <address1>+<address2> to <address3>
ADD 0 1 2
;SUB <address1> <address2> <address3>
;Assign the value of <address1>-<address2> to <address3>
SUB 0 1 2
;NEG <address1> <address2>
;Assign the value of -<address1> to <address2>
NEG 0 1
;MOD <address1> <address2> <address3>
;Assign the value of <address1>%<address2> to <address3>
MOD 0 1 2
;DIV <address1> <address2> <address3>
;Assign the value of <address1>/<address2> to <address3>
DIV 0 1 2
;BIT_XOR <address1> <address2> <address3>
;Assign the value of <address1>^<address2> to <address3>
BIT_XOR 0 1 2
;EQ <address1> <address2> <address3>
;Assign the value of <address1>==<address2> to <address3>
EQ 0 1 2
;NEQ <address1> <address2> <address3>
;Assign the value of <address1>!=<address2> to <address3>
NEQ 0 1 2
;GT <address1> <address2> <address3>
;Assign the value of <address1>><address2> to <address3>
GT 0 1 2
;LT <address1> <address2> <address3>
;Assign the value of <address1><<address2> to <address3>
LT 0 1 2
;GE <address1> <address2> <address3>
;Assign the value of <address1>>=<address2> to <address3>
GE 0 1 2
;LE <address1> <address2> <address3>
;Assign the value of <address1><=<address2> to <address3>
LE 0 1 2
;AND <address1> <address2> <address3>
;Assign the value of <address1>&&<address2> to <address3>
AND 0 1 2
;OR <address1> <address2> <address3>
;Assign the value of <address1>||<address2> to <address3>
OR 0 1 2
;NOT <address1> <address2>
;Assign the value of !<address1> to <address2>
NOT 0 1
;BIT_AND <address1> <address2> <address3>
;Assign the value of <address1>&<address2> to <address3>
BIT_AND 0 1 2
;BIT_OR <address1> <address2> <address3>
;Assign the value of <address1>|<address2> to <address3>
BIT_OR 0 1 2
;BIT_NOT <address1> <address2>
;Assign the value of ~<address1> to <address2>
BIT_NOT 0 1
;BIT_SHL <address1> <address2> <address3>
;Assign the value of <address1> << <<address2> to <address3>
BIT_SHL 0 1 2
;BIT_SHR <address1> <address2> <address3>
;Assign the value of <address1> >> <address2> to <address3>
BIT_SHR 0 1 2
;JMP <address>
;Jump label <address> and execute it
JMP 0
;RET
;Stop execution of a label or exit if at a global scope
RET
;EXIT <address>
;EXIT with error code at label <address>
EXIT 0
;IF <address1> <address2>
;If <address1> is true then jump to <address2>
IF 0 1
;ELSE <address>
;If false then jump to <address>
ELSE 0