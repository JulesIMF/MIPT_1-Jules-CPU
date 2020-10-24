@4000

in
pop rax

mov 0 rbx

label:
inc rbx
push rbx
out
pop rbx
cmp rax rbx
jne label

hlt