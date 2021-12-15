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
stcmp PROTO : DWORD, : DWORD

.const
		newline byte 13, 10, 0
L1 byte 'Hello World!', 0
L2 sdword 0
L3 sdword 1
L4 sdword 5
L5 byte 'i:', 0
L6 sdword 2
L7 sdword 8
L8 byte 'true', 0
L9 byte 'false', 0
L10 sdword 3
L11 sdword 4
L12 sdword 7
L13 sdword 9
L14 byte 'Sum: ', 0
.data
		temp sdword ?
		buffer byte 256 dup(0)
maxres sdword 0
hi dword ?
i sdword 0
sum1 sdword 0
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
push maxx

pop ebx
mov left, ebx

push maxy

pop ebx
mov rig, ebx

mov edx, left
cmp edx, rig

jg right1
jl wrong1
 right1:
push maxx

pop ebx
mov maxres, ebx


jmp next1
wrong1:
push maxy

pop ebx
mov maxres, ebx

next1:
; --- restore registers ---
pop edx
pop ebx
; -------------------------
mov eax, maxres
ret
max ENDP
;------------------------------


;----------- sum ------------
sum PROC,
	sumx : sdword, sumy : sdword  
; --- save registers ---
push ebx
push edx
; ----------------------
push sumx
push sumy
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov sumx, ebx

mov eax, sumx
mov result, eax	
INVOKE int_to_char, offset result_str, result
INVOKE outw, offset result_str

; --- restore registers ---
pop edx
pop ebx
; -------------------------
ret
sum ENDP
;------------------------------


;----------- MAIN ------------
main PROC
mov hi, offset L1

INVOKE outw, hi

push L2

pop ebx
mov i, ebx

cycle1:
push i

pop ebx
mov left, ebx


push hi
call len
push eax

pop ebx
mov rig, ebx

mov edx, left
cmp edx, rig

jl cycle2
jmp cyclenext2
cycle2:
push i
push L3
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov i, ebx


push L4
push i
call max
push eax

mov result, eax	
INVOKE int_to_char, offset result_str, result
INVOKE outw, offset result_str


push L4
push i
call max

push i

pop ebx
mov left, ebx

push hi
call len
push eax

pop ebx
mov rig, ebx
mov edx, left
cmp edx, rig

jl cycle2
cyclenext2:

INVOKE outw, offset L5

mov eax, i
mov result, eax	
INVOKE int_to_char, offset result_str, result
INVOKE outw, offset result_str

push i
push L6
pop ebx
pop eax
cdq
idiv ebx
push eax

pop ebx
mov left, ebx

push L4
push L3
push L7
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov rig, ebx

mov edx, left
cmp edx, rig

jg right3
jl wrong3
 right3:

INVOKE outw, offset L8

push L2

pop ebx
mov i, ebx


jmp next3
wrong3:

INVOKE outw, offset L9

next3:
push L6
push L10
pop ebx
pop eax
add eax, ebx
push eax
push L11
pop ebx
pop eax
add eax, ebx
push eax
push L4
push L6
pop ebx
pop eax
cdq
idiv ebx
push eax
push L12
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
pop eax
add eax, ebx
push eax
push L13
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov sum1, ebx

mov eax, sum1
mov result, eax	
INVOKE int_to_char, offset result_str, result
INVOKE outw, offset result_str


INVOKE outw, offset L14


push L11
push L6
call sum

INVOKE ExitProcess,0
main ENDP
end main
