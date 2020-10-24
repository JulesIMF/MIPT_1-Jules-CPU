;Jules Assembler test

;Эта программа решает квадратное уравнение с параметрами a b c и выводит корни (если они есть)

start:

	in ;a
	in ;b
	in ;c
	pop rcx
	pop rbx
	pop rax
	call get_discriminant
	;Теперь дискриминант лежит в 0xEDA
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