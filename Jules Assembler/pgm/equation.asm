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
	push rdx
	out
	pop rsp
	jmp end

get_discriminant:
	mul rbx rbx
	mul rax rcx
	mul rsp 4
	pop rdx
	pop rsp
	sub rsp rdx
	pop rdx
	pop rsp
        out
	ret

end:
	hlt