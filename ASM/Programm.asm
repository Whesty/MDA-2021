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
L1 byte 'Hello World', 0
L2 byte 'hi:', 0
L3 sdword 0
L4 byte 'len(hi)', 0
L5 byte 'comp(hi, bay)', 0
L6 byte 'bay', 0
L7 sdword 1
L8 byte 'max: ', 0
L9 sdword 5
L10 byte 'i:', 0
L11 byte 'i/2>5+1*8:', 0
L12 sdword 2
L13 sdword 8
L14 byte 'true', 0
L15 byte 'false', 0
L16 sdword 3
L17 sdword 4
L18 sdword 7
L19 sdword 9
L20 byte 'Sum(2, 4): ', 0
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

INVOKE outw, offset L2


INVOKE outw, hi

push L3

pop ebx
mov i, ebx


INVOKE outw, offset L4


push hi
call len
push eax

mov result, eax	
INVOKE int_to_char, offset result_str, result

mov result, eax
INVOKE outn, result


INVOKE outw, offset L5


push offset L6
push hi
call comp
push eax

mov result, eax	
INVOKE int_to_char, offset result_str, result

mov result, eax
INVOKE outn, result

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
push L7
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov i, ebx

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

INVOKE outw, offset L8


push L9
push i
call max
push eax

mov result, eax	
INVOKE int_to_char, offset result_str, result

mov result, eax
INVOKE outn, result


INVOKE outw, offset L10

mov eax, i
mov result, eax	
INVOKE int_to_char, offset result_str, result
INVOKE outw, offset result_str


INVOKE outw, offset L11

push i
push L12
pop ebx
pop eax
cdq
idiv ebx
push eax

pop ebx
mov left, ebx

push L9
push L7
push L13
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

INVOKE outw, offset L14

push L3

pop ebx
mov i, ebx


jmp next3
wrong3:

INVOKE outw, offset L15

next3:
push L12
push L16
pop ebx
pop eax
add eax, ebx
push eax
push L17
pop ebx
pop eax
add eax, ebx
push eax
push L9
push L12
pop ebx
pop eax
cdq
idiv ebx
push eax
push L18
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
pop eax
add eax, ebx
push eax
push L19
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


INVOKE outw, offset L20


push L17
push L12
call sum

INVOKE ExitProcess,0
main ENDP
end main
