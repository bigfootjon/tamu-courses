# Setup matrix addresses
regset V0, R1
regset V4, R2
regset V8, R5

# Copy first matrix into memory
regset V0, R3
memset R3, R1, V0
regset V0, R3
memset R3, R1, V1
regset V0, R3
memset R3, R1, V2
regset V0, R3
memset R3, R1, V3

# Copy second matrix into memory
regset V0, R3
memset R3, R2, V0
regset V1, R3
memset R3, R2, V1
regset V2, R3
memset R3, R2, V2
regset V3, R3
memset R3, R2, V3

# Add
memld R3, R1, V0
memld R4, R2, V0
add R3, R4
memset R4, R5, V0

memld R3, R1, V1
memld R4, R2, V1
add R3, R4
memset R4, R5, V1

memld R3, R1, V2
memld R4, R2, V2
add R3, R4
memset R4, R5, V2

memld R3, R1, V3
memld R4, R2, V3
add R3, R4
memset R4, R5, V3

halt
