lw $10, 0($5)
lw $11, 0($6) 
add $1, $10, $11
sub $2, $11, $10 
addi $2, $2, 6  
sw $2, 32($5)
slt $3, $2, $10  
slt $4, $10, $2  
