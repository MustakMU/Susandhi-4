
main.o:     file format elf32-littlearm


Disassembly of section .text.main:

00000000 <main>:
   0:	b580      	push	{r7, lr}
   2:	af00      	add	r7, sp, #0
   4:	f44f 5016 	mov.w	r0, #9600	; 0x2580
   8:	f7ff fffe 	bl	0 <UartInit>
   c:	480e      	ldr	r0, [pc, #56]	; (3c <createList+0x3c>)
   e:	f7ff fffe 	bl	0 <createList>
  12:	480e      	ldr	r0, [pc, #56]	; (3c <createList+0x3c>)
  14:	f7ff fffe 	bl	0 <createList>
  18:	f7ff fffe 	bl	0 <gpioInit>
  1c:	f7ff fffe 	bl	0 <realTimeClockInit>
  20:	f7ff fffe 	bl	0 <UartLoopBack>
  24:	4603      	mov	r3, r0
  26:	2b00      	cmp	r3, #0
  28:	d009      	beq.n	3e <main+0x3e>
  2a:	4809      	ldr	r0, [pc, #36]	; (50 <main+0x50>)
  2c:	4906      	ldr	r1, [pc, #24]	; (48 <main+0x48>)
  2e:	4a07      	ldr	r2, [pc, #28]	; (4c <main+0x4c>)
  30:	f7ff fffe 	bl	0 <parsing>
  34:	4603      	mov	r3, r0
  36:	2b00      	cmp	r3, #0
  38:	d001      	beq.n	3e <main+0x3e>
  3a:	2301      	movs	r3, #1
  3c:	e000      	b.n	40 <main+0x40>
  3e:	2300      	movs	r3, #0
  40:	4a04      	ldr	r2, [pc, #16]	; (54 <main+0x54>)
  42:	6013      	str	r3, [r2, #0]
  44:	e7ec      	b.n	20 <main+0x20>
  46:	bf00      	nop
	...
