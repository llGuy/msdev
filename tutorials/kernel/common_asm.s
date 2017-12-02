global outb

a_outb:
    mov al, [esp+8]
    mov dx, [esp+4]
    out dx, al
    ret

; input stack: i/o port
; return via eax
a_inb:
    mov dx, [esp+4]
    in al, dx
    ret
