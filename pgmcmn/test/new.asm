;Jules Assembler test

;��� ��������� ������ ���������� ��������� � ����������� a b c � ������� ����� (���� ��� ����)
@2







start:

	in ;a
	in ;b
	in ;c
	pop rcx
	pop rbx
	pop rax
	;
	;�������� �� ����������
	fmul rax rax
	cmp rsp 0.000001
	pop rsp
	jl linear
	;���� ���������
	call get_discriminant
	;������ ������������ ����� � 0xEDA
	mov p 0xEDA rdx
	;A ������ � rdx
	pusha

	call get_mode

	cmp rax 0.0
	popa

	;----DEBUG-----
	;push rcx
	;push rbx
	;push rdx
	;out lf
	;pop rsp
	;out lf
	;pop rsp
	;out lf
	;pop rsp
	;----DEBUG-----


	je prc_two
	jl prc_no
	jg prc_one
	

	hlt




get_discriminant:
	fmul rbx rbx
;	out lf
	fmul rax rcx
;	out lf
	fmul rsp 4.0
;	out lf
	pop rdx
	pop rsp
	fsub rsp rdx
;	out lf
	pop rdx
	pop rsp
	mov rdx p 0xEDA
	mov 0.0 rdx
	ret

get_mode:
	;�� ���������� �������� ��� ���� ������� - rdx
	;��� ���� � ���������� ��� ����� ������ ��� �����
	fcmp rdx 0.0001
	jg GM_TWO
	fcmp rdx 0.0
	jl GM_NO
	jmp GM_ONE
        
        GM_TWO:
	mov 0 rax
	ret
        GM_ONE:
	mov 1 rax
	ret
        
        GM_NO:
        mov -1 rax
        ret

prc_no:
	jmp end

prc_one:
	;x = -b/2a
	fmul 2.0 rax ;2a �� �����
	fsub 0.0 rbx   ;-b �� �����
	pop rbx      ;-b � rbx
	fdiv rbx rsp ;-b/2a �� �����
	out lf       ;�����
	pop rsp      ;
	pop rsp      ;���� ����
	jmp end

prc_two:
	;x = -b/2a
	fmul 2.0 rax ;2a �� �����
	fsub 0.0 rbx   ;-b �� �����
	pop rbx      ;-b � rbx
	fdiv rbx rsp ;-b/2a �� �����
	pop rbx      ;-b/2a � rbx
	sqrt rdx     ;������ �� ������������� �� �����
	pop rdx      ;������ �� � rdx
	;�� ����� ������ 2a
	fdiv rdx rsp
	pop rdx
	fadd rbx rdx ;x1
	out lf
	fsub rbx rdx ;x2
	out lf	
	pop rsp
	pop rsp
	pop rsp ;���� ����	
	jmp end

linear:
	fmul rbx rbx
	cmp rsp 0.0000001
	pop rsp
	jl linear_b0 ;�������� ������

	;���������� ������
	fsub 0.0 rcx
	fdiv rsp rbx
	out lf
	jmp end
	linear_b0:
	fmul rcx rcx
	cmp rsp 0.0000001
	jl linear_b0_a0
	push 0x7FF8000000000000
	out lf
	jmp end
	linear_b0_a0:
	push 0x7FF0000000000000
	out lf
	jmp end
end:
	hlt
