@4000

in
pop rax
call fib
push rbx
out
pop rsp
hlt


;call convention - ������ ����� � rax, ������������ �������� � rbx
fib:
	cmp rax 1
	jl jl_0
	je jl_1
	dec rax
	call fib
	push rbx ;�� ����� ����� �����
	dec rax
	call fib
	add rsp rbx ; ��� ��������
	pop rbx
	pop rsp
	inc rax
	inc rax
	ret


	jl_0:
	mov 0 rbx
	ret

	jl_1:
	mov 1 rbx
	ret
;	sdfsdf
		