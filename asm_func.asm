section .data
    var1 dq 255.0                ; constant to be used later

section .text
    bits 64
    default rel
    global imgCvtGrayIntToDouble

imgCvtGrayIntToDouble:
    ; Windows x64 calling convention:
    ; rcx  - int param
    ; xmm0 - return dpuble float

    ; convert long long int to double float
    cvtsi2sd xmm1, rcx           ; xmm1 = (double)rcx

    ; Load 255.0 into xmm0
    movsd xmm0, [var1]              ; move 255.0 in a float register

    ; Divide: xmm1 / xmm0
    divsd xmm1, xmm0             ; xmm1 = rcx / 255.0

    ; Move result to return register
    movaps xmm0, xmm1

    ret
