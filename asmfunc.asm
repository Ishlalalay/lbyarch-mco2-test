; convert.asm
; Compile with: nasm -f elf64 convert.asm -o convert.o

section .text
    global convert_image

; void convert_image(uint8_t *input, double *output, int height, int width)
convert_image:
    ; Arguments:
    ; rdi = input pointer (uint8_t*)
    ; rsi = output pointer (double*)
    ; rdx = height
    ; rcx = width

    push rbp
    mov rbp, rsp
    push rbx

    ; Calculate total pixels: height * width → r8
    imul r8, rdx, rcx      ; r8 = total pixels
    xor r9, r9             ; r9 = index = 0

    movsd xmm1, qword [rel divisor] ; xmm1 = 255.0

.loop:
    cmp r9, r8
    jge .done

    ; Load uint8_t input[r9] → zero-extend to eax
    movzx eax, byte [rdi + r9]
    cvtsi2sd xmm0, eax       ; xmm0 = (double)input[r9]
    divsd xmm0, xmm1         ; xmm0 /= 255.0
    movsd [rsi + r9*8], xmm0 ; output[r9] = result

    inc r9
    jmp .loop

.done:
    pop rbx
    pop rbp
    ret

section .data
    divisor: dq 255.0
    