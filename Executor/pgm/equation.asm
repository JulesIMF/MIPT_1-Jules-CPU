;Jules Assembler test

;��� ��������� ������ ���������� ��������� � ����������� a b c � ������� ����� (���� ��� ����)

start:

	in ;a
	in ;b
	in ;c
	pop rcx
	pop rbx
	pop rax
	call get_discriminant
	;������ ������������ ����� � 0xEDA
	mov p 0xEDA rdx
	push rdx
	out lf
	hlt

get_discriminant:
	fmul rbx rbx
	fmul rax rcx
	fmul rsp 4.0
	pop rdx
	pop rsp
	fsub rsp rdx
	pop rdx
	pop rsp
	mov rdx p 0xEDA
	mov 0 rdx
	ret

end:
	hlt