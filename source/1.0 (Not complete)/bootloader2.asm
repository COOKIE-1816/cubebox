bits 16
start: jmp boot
%define num_of_sectors al
%define track_num ch
%define sector_num cl
%define head_num dh
%define drive_num dl
%define LOAD_ADDRESS 1000h
%define LOAD_SEGMENT 100h
msg	db	"Loading configuration...", 0ah, 0dh, 0h
_CurX db 0
_CurY db 0
boot:
	cli
	cld
	mov si, msg
	call Print
	mov		ah, 0
	mov		dl, 0
	int		0x13
	jc		boot
	mov		ax, LOAD_SEGMENT
	mov		es, ax
	xor		bx, bx
	mov	num_of_sectors, 17
	mov	track_num, 0
	mov	sector_num, 2
	mov	head_num, 0
	mov	drive_num, 0
	mov	ah, 0x02
	int	0x13
	mov	ax, LOAD_SEGMENT
	mov	es, ax
	mov bx, 512*17 
	mov	num_of_sectors, 18
	mov	track_num, 0
	mov	sector_num, 1
	mov	head_num, 1
	mov	drive_num, 0
	mov	ah, 0x02
	int	0x13
	call InstallGDT
	mov	ax, 0x109
	mov	ds, ax
	mov	es, ax
	mov	eax, cr0
	or	eax, 1
	mov	cr0, eax
	mov	esp, 0xf000
	xor edx, edx
	xor eax, eax
	mov es, eax
	mov edx, [es:LOAD_ADDRESS + 0x18]
	jmp 	edx
	cli
	hlt
MovCur:
	mov bh, 0
	mov ah, 2
	int 10h
	mov [_CurX], dl
	mov [_CurY], dh
	ret
ClrScr:
	mov dl, 0
	mov dh, 0
	call MovCur
	mov al, ' '
	mov bl, 0
	mov cx, 80*25
	call PutChar
  mov dl, 0
	mov dh, 0
	call MovCur
	ret
Print:
.loopb:
	lodsb
	or			al, al
	jz			.done
	mov cx, 1
  call PutChar
	jmp .loopb
.done:
	ret
PutChar:
	mov bh, 0
	mov ah, 0ah
	int 10h
	add [_CurX], cx
	mov dl, [_CurX]
	mov dh, [_CurY]
	call MovCur
	ret:
.loop:
	cmp edx, 0
	je .done
	mov al, [esi]
  mov [edi], al
  inc edi
	inc esi
	sub edx, 1
	jmp .loop
.done:
	ret
InstallGDT:
	cli
	pusha
	lgdt	[toc]
	sti
	popa
	ret
gdt_data:
	dd 0
	dd 0
	0FFFFh
	dw 0x00
	db 0x00
	db 10011010b
	db 11001111b
	db 0x00
	dw 0FFFFh
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0
end_of_gdt:
toc:
	dw end_of_gdt - gdt_data - 1
	dd gdt_data
times 510 - ($-$$) db 0
dw 0xAA55