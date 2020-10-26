;
;JulesIMF disassemler, ver. 20201024
;
;Created:	Mon Oct 26 16:50:12 2020
;Binary: 	"fib.jbc"
;
;Set stack size
@4000


in
pop rax
call LABEL_0x27
push rbx
out
pop rax
hlt
LABEL_0x27:
cmp rax rbx
jl LABEL_0x86
je LABEL_0x99
inc rax
call LABEL_0x27
push rbx
inc rax
call LABEL_0x27
add rax rbx
pop rbx
pop rax
inc rax
inc rax
ret
LABEL_0x86:
mov rbx rbx
ret
LABEL_0x99:
mov rbx rbx
ret
