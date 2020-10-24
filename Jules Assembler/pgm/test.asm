@2000
push 10
push 0
pop rbx
pop rax

label:
inc rbx
push rbx
out
cmp rax rbx
jne label