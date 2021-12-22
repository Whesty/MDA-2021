.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "../Debug/Lib.lib"
ExitProcess PROTO:DWORD 
.stack 4096

ExitProcess PROTO :DWORD
outn PROTO : SDWORD
outw PROTO : DWORD
len PROTO : DWORD
comp PROTO : DWORD, : DWORD
stcmp PROTO : DWORD, : DWORD

.const
		newline byte 13, 10, 0
.data
		temp sdword ?
		buffer byte 256 dup(0)

maxa sdword 0
left dword ?
rig dword ?
result sdword ?
result_str byte 4 dup(0)
.code
int_to_char PROC uses eax ebx ecx edi esi,
pstr: dword,
intfield : sdword
mov edi, pstr
mov esi, 0
mov eax, intfield
cdq
mov ebx, 10
idiv ebx
test eax, 80000000h
jz plus
neg eax
neg edx
mov cl, '-'
mov[edi], cl
inc edi
plus :
push dx
inc esi
test eax, eax
jz fin
cdq
idiv ebx
jmp plus
fin :
mov ecx, esi
write :
pop bx
add bl, '0'
mov[edi], bl
inc edi
loop write
ret
int_to_char ENDP


;----------- max ------------
max PROC,
	maxx : sdword, maxy : sdword  
; --- save registers ---
push ebx
push edx
; ----------------------
; --- restore registers ---
pop edx
pop ebx
; -------------------------
mov eax, maxa
ret
max ENDP
;------------------------------


;----------- MAIN ------------
main PROC
INVOKE ExitProcess,0
main ENDP
end main
