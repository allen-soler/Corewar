.name "pedro"
.comment "monfort"

# TODO: PROTECT EACH (PC  + X) % MEM_SIZE BECAUSE IF PC + X < 0 WE WILL HAVE A PROBLEM

#sub r1, r1, r1
#and %1, %1, r2
live %-42
or r2, r2, r3
#xor r2, %1, r4
