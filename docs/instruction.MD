# Hawk instruction set

## General syntax

```assembly
<op> <register1> <register2> <destination>
```
### Instructions

#### BACK
Hawk ir
```assembly
back <register1> <destination> ;$destination = $register1.back()
```
Same as

```cpp
destination = register1.back()//get the last element of the array
```


#### AT

```assembly
at <register1> <register2> <destination>;$destination = $register2.at($register1)
```
Same as

```cpp
destination = register2[register1]//get the element at the index register1 of register2
```
#### ASPTR_VAL
    
```assembly
asptr_val <register1> <destination>;*$destination = $register1
```
Same as
```cpp
*destination = register1//assign the value of the register to the pointer destination
```

#### LDPTR_VAL
```assembly
ldptr_val <register1> <destination>;$destination = *$register1
```
Same as
```cpp
destination = *register1//Dereference pointer and assign to destination
```

#### GETPTR
```assembly
getptr <register1> <destination>;$destination =&$register1
```
Same as
```cpp
destination = &register1//get the address of the register
```

#### LEN
```assembly
len <register1> <destination>;$destination = $register1.length()
```
Same as
```cpp
destination = register1.length()//get the length of array
```
####  FREE
```assembly
free <register1>;free($register1)
```
Same as
```cpp
free(register1)//free up memory used by register1
```
#### MALLOC
```assembly
malloc <register1> <destination>;$destination = malloc($register1)
```
Same as
```cpp
destination = malloc(register1)//allocate register1 bytes of memory to destination
```

#### REALLOC
```assembly
realloc <register1> <destination>;$destination = realloc($register1)
```
Same as
```cpp
destination = realloc(register1)//reallocate register1 bytes of memory to destination
```

#### INSERT
```assembly
insert <register1> <register2> <destination>;$destination[$register2]=$register1
```
Same as
```cpp
destination[register2]=register1
```

#### APPEND
```assembly
append <register1> <destination>;$destination.push_back($register1)
```
Same as
```cpp
destination.push_back(register1)//append register1 to the end of the array
```

#### EQ_ARRAY
```assembly
eq_array <register1> <register2> <destination>;$destination = $register1 == $register2
```
Same as
```cpp
destination = register1 == register2//check if the arrays are equal
```

#### IF_NEQ
```assembly
if_neq <register1> <register2> <destination>;if($register1 != $register2): jmp $destination
```
Same as
```cpp
if(register1 != register2){
    destination()
}
```

#### IF_EQ
```assembly
if_eq <register1> <register2> <destination>;if($register1 == $register2): jmp $destination
```
Same as
```cpp
if(register1 == register2){
    destination()
}
```
#### IF_GT
```assembly
if_gt <register1> <register2> <destination>;if($register1 > $register2): jmp $destination
```
Same as
```cpp
if(register1 > register2){
    destination()
}
```
#### IF_LT
```assembly
if_lt <register1> <register2> <destination>;if($register1 < $register2): jmp $destination
```
Same as
```cpp
if(register1 < register2){
    destination()
}
```
#### IF_GE
```assembly
if_ge <register1> <register2> <destination>;if($register1 >= $register2): jmp $destination
```
Same as
```cpp
if(register1 >= register2){
    destination()
}
```
#### IF_LE
```assembly
if_le <register1> <register2> <destination>;if($register1 <= $register2): jmp $destination
```
Same as
```cpp
if(register1 <= register2){
    destination()
}
```
#### IF_AND
```assembly
if_and <register1> <register2> <destination>;if($register1 && $register2): jmp $destination
```
Same as
```cpp
if(register1 && register2){
    destination()
}
```
#### IF_OR
```assembly
if_or <register1> <register2> <destination>;if($register1 || $register2): jmp $destination
```
Same as
```cpp
if(register1 || register2){
    destination()
}
```
#### OP_IF
```assembly
op_if <register1> <destination>;if($register1==True): jmp $destination
```
Same as
```cpp
if(register1){
    destination()
}
```
#### OP_ELSE
```assembly
op_else <destination>;else: jmp $destination
```
Same as
```cpp
else{
    destination()
}
```

#### LOAD
```assembly
op_load <value> <destination>;$destination = value
```
Same as
```cpp
destination = value//value is a const expression
```
#### MOV
```assembly
mov <register1> <destination>;$destination = $register1
```
Same as
```cpp
destination = register1//assign the value of register1 to destination
```

#### ADD
```assembly
add <register1> <register2> <destination>;$destination = $register1 + $register2
```
Same as
```cpp
destination = register1 + register2//add register1 and register2 and assign to destination
```
#### SUB
```assembly
sub <register1> <register2> <destination>;$destination = $register1 - $register2
```
Same as
```cpp
destination = register1 - register2//subtract register2 from register1 and assign to destination
```