@2000
;Это комментарий чисто поржать

in
pop rax ;Сюда запихали число, факториал которого ищем
mov 1 rbx ;А здесь будет индекс
mov 1 rcx ;А здесь сам факториал


!factorial

mul rcx rbx
pop rcx
inc rbx
cmp rbx rax
jg  final
call factorial

!final
push rcx
out
hlt
