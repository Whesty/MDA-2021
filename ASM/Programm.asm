.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "../Debug/Lib.lib
ExitProcess PROTO:DWORD 
.stack 4096

ExitProcess PROTO :DWORD
outn PROTO : SDWORD
outw PROTO : DWORD
len PROTO : DWORD
stcmp PROTO : DWORD, : DWORD

.const
		newline byte 13, 10, 0
L1 byte 'ÔÛÂÛûàûâà123423.ýþýæþáüþþ._=394832SFhsdfDSHh', 0
L2 sdword -12
L3 sdword 15
L4 sdword 42
L5 sdword 3
L6 sdword 2
.data
		temp sdword ?
		buffer byte 256 dup(0)
t dword ?
a sdword 0
w sdword 0
b sdword 0
i sdword 0
q sdword 0
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


;----------- fr ------------
fr PROC,
	frt : sdword, fre : dword  
; --- save registers ---
push ebx
push edx
; ----------------------
mov eax, frt
mov result, eax	
INVOKE int_to_char, offset result_str, result
INVOKE outw, offset result_str

; --- restore registers ---
pop edx
pop ebx
; -------------------------
ret
fr ENDP
;------------------------------

right0:

;----------- MAIN ------------
main PROC
mov t, offset L1
push L2

pop ebx
mov a, ebx

push L3

pop ebx
mov w, ebx

push L4

pop ebx
mov b, ebx

push a
push b
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov a, ebx

push a

pop ebx
mov left, ebx

push w

pop ebx
mov rig, ebx

mov edx, left
cmp edx, rig

jl right1
jg wrong1
 right1:
push w
push a
pop ebx
pop eax
sub eax, ebx
push eax

pop ebx
mov a, ebx

wrong1:
push w
push a
pop ebx
pop eax
sub eax, ebx
push eax

pop ebx
mov a, ebx


push t
call len
push eax

pop ebx
mov i, ebx

mov eax, i
mov result, eax	
INVOKE int_to_char, offset result_str, result
INVOKE outw, offset result_str


push t
push a
call fr

cycle1:
push w
push a
pop ebx
pop eax
sub eax, ebx
push eax

pop ebx
mov left, ebx

push L5

pop ebx
mov rig, ebx

mov edx, left
cmp edx, rig

jg cycle2
jmp cyclenext2
cycle2:
push a
push q
push w
pop ebx
pop eax
cdq
idiv ebx
push eax
pop ebx
pop eax
add eax, ebx
push eax
push L6
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov a, ebx

push a

pop ebx
mov left, ebx
push w

pop ebx
mov rig, ebx
push w
push a
pop ebx
pop eax
sub eax, ebx
push eax

pop ebx
mov left, ebx
push L5

pop ebx
mov rig, ebx
mov edx, left
cmp edx, rig

jg cycle2
cyclenext2:
mov eax, a
mov result, eax	
INVOKE int_to_char, offset result_str, result
INVOKE outw, offset result_str

INVOKE ExitProcess,0
main ENDP
end main
