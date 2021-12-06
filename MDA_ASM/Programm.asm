.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "../Debug/GenLib.lib
ExitProcess PROTO:DWORD 
.stack 4096


 outlich PROTO : DWORD

 outrad PROTO : DWORD

 concat PROTO : DWORD, : DWORD, : DWORD

 lenght PROTO : DWORD, : DWORD

 atoii  PROTO : DWORD,  : DWORD

.const
		newline byte 13, 10, 0
L1 byte 'ÔÛÂÛûàûâà123423.ýþýæþáüþþ._=394832SFhsdfDSHh', 0
L2 sdword 12
L3 sdword 15
L4 sdword 42
L5 sdword 2
.data
		temp sdword ?
		buffer byte 256 dup(0)
maint dword ?
maina sdword 0
mainw sdword 0
mainb sdword 0
mainq sdword 0
left dword ?
rig dword ?

.code

;----------- fr ------------
fr PROC,
	frt : sdword, fre : dword  
; --- save registers ---
push ebx
push edx
; ----------------------

push frt
call outlich

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
mov maint, offset L1
push L2

pop ebx
mov maina, ebx

push L3

pop ebx
mov mainw, ebx

push L4

pop ebx
mov mainb, ebx

push maina
push mainb

pop ebx
mov maina, ebx

push maina

pop ebx
mov left, ebx

push mainw

pop ebx
mov rig, ebx

mov edx, left
cmp edx, rig

jl right1
jg wrong1
jmp next1
right1:
push mainw
push maina

pop ebx
mov maina, ebx

wrong1:
push mainw
push maina

pop ebx
mov maina, ebx


push maint
push maina
push offset buffer
call P

cycle1:
push mainw
push maina
pop ebx
pop eax
sub eax, ebx
push eax

pop ebx
mov left, ebx

push mainw
push maina
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov rig, ebx

mov edx, left
cmp edx, rig

jl cycle2
jmp cyclenext2
push maina
push mainq
push mainw
push L5

pop ebx
mov maina, ebx

mov edx, left
cmp edx, rig

jl cycle2
cyclenext2:

push maina
call outlich

push 0
call ExitProcess
main ENDP
end main
