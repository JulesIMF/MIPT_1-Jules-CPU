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
	out
	hlt
get_discriminant:
	mul rbx rbx
	mul rax rcx
	mul rsp 4
	pop rdx
	pop rsp
	sub rsp rdx
	pop rdx
	pop rsp
	mov rdx p 0xEDA
	mov 0 rdx
	ret
end:
	hlt