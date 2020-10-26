;
;JulesIMF disassemler, ver. 20201024
;
;Created:	Mon Oct 26 16:35:52 2020
;Binary: 	"sin.jbc"
;
;Set stack size
@10


in
pop rax
sin rax
out lf
cos rax
out lf
pop rcx
pop rdx
fmul rcx rcx
pop rcx
fmul rdx rdx
pop rdx
fadd rcx rdx
out lf
hlt
