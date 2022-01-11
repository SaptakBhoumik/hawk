;mov <value> <register>
mov 1 3 ;Regiester 3 has the value 
mov 2 4
;add <register1> <register2> <register>
add 3 4 5 ;Add the value of register 3 and 4 and assign it to register 5
;sub <register1> <register2> <register>
sub 3 4 5 ;Subtract the value of register 4 from the value of register 3 and assign it to register 5
;div <register1> <register2> <register>
div 3 4 5 ;Divide the value of register 3 with the value of register 4 and assign it to register 5
;mul <register1> <register2> <register>
mul 3 4 5 ;Multiply the value of register 3 and 4 and assign it to register 5
;pop <register>
pop 5 ;Assign register 5 to 0
;neg <register1> <register>
neg 3 5 ;Assign the negative value of register 3 to 5
;exit <register>
exit 5;exit with the exit code of value of 5
;Hault the execution
hlt