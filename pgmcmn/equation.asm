;Jules Assembler test

;Эта программа решает квадратное уравнение с параметрами a b c и выводит корни (если они есть)
@4000

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
	;A теперь в rdx
	pusha

	call get_mode

	cmp rax 0
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
	mov 0 rdx
	ret

get_mode:
	;По соглашению параметр для этой функции - rdx
	;При этом с регистрами она может делать что хочет
	fcmp rdx 0.0001
	jg GM_TWO
	fcmp rdx 0
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
	fmul 2.0 rax ;2a на стеке
	fsub 0 rbx   ;-b на стеке
	pop rbx      ;-b в rbx
	fdiv rbx rsp ;-b/2a на стеке
	out lf       ;вывод
	pop rsp      ;
	pop rsp      ;стек пуст
	jmp end

prc_two:
	;x = -b/2a
	fmul 2.0 rax ;2a на стеке
	fsub 0 rbx   ;-b на стеке
	pop rbx      ;-b в rbx
	fdiv rbx rsp ;-b/2a на стеке
	pop rbx      ;-b/2a в rbx
	sqrt rdx     ;корень из дискриминанта на стеке
	pop rdx      ;теперь он в rdx
	;на стеке теперь 2a
	fdiv rdx rsp
	pop rdx
	fadd rbx rdx ;x1
	out lf
	fsub rbx rdx ;x2
	out lf	
	pop rsp
	pop rsp
	pop rsp ;стек пуст	
	jmp end

end:
	hlt

