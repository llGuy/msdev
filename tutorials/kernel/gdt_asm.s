global gdt_flush

gdt_flush:
    mov eax, [esp+4]
    lgdt [eax]

    mov ax, 0x10  ; 0x10 is offset data segment -> into all segemnet
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush ; 0x08 offset of code segment

.flush:
    ret
.end
