@2000
;��� ����������� ����� �������

in
pop rax ;���� �������� �����, ��������� �������� ����
mov 1 rbx ;� ����� ����� ������
mov 1 rcx ;� ����� ��� ���������


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
