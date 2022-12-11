;@ STM32F103 - Assembly template
;@ Turns on GPIOD Pin 1

;@ Start with enabling thumb 32 mode since Cortex-M3 do not work with arm mode
;@ Unified syntax is used to enable good of the both words...
;@ Make sure to run arm-none-eabi-objdump.exe -d prj1.elf to check if
;@ the assembler used proper insturctions. (Like ADDS)

;The semicolon is used to lead an inline documentation.
;This is the first ARM Assembly language program you see in the lab.
;This program skeleton was from Dave Duguid and Trevor Douglas in summer 2013.
;When you write your program, you could have your info at the top document block.
;For Example:  Your Name, Student Number, what the program is for, and what it does etc.

;;; Directives
          PRESERVE8
          THUMB       

; Vector Table Mapped to Address 0 at Reset
; Linker requires __Vectors to be exported
 
          AREA    RESET, DATA, READONLY
          EXPORT  __Vectors
 
__Vectors 
	  DCD  0x20001000     ; stack pointer value when stack is empty
			;The processor uses a full descending stack. 
			;This means the stack pointer holds the address of the last 
			;stacked item in memory. When the processor pushes a new item 
			;onto the stack, it decrements the stack pointer and then 
			;writes the item to the new memory location.

          DCD  Reset_Handler  ; reset vector
  
          ALIGN
 
; The program
; Linker requires Reset_Handler
 
          AREA    MYCODE, CODE, READONLY
 
   	  ENTRY
   	  EXPORT Reset_Handler
 
 
Reset_Handler
;;;;;;;;;;User Code Starts from the next line;;;;;;;;;;;;
	

  	  MOV R0, #12
	  ;@ Enable GPIOD Peripheral Clock (Page 145 from RM0008)
	LDR R6, = 0x40021018  ;APB2_ENR @ Load peripheral clock enable regiser
	LDR R5, [R6]           ;@ Read its content
	ORR R5, 0x00000010     ;@ Set Bit 5 to enable GPIOD clock 10 0000
	STR R5, [R6]           ;@ Store back the result in Perihperal clock enable register

	;@ Make GIOOD Pin1 as output pin (Page 170 from RM0008)
					;+0x1000
	LDR R6, = 0x40011400    ;@ Load GPIOD control register low  (Pin1 is in CRL register)
	LDR R5, = 0x00000020   ;@ Set MODE bits to 10 and CNF bits to 00, thus 0x00000020
	STR R5, [R6]           ;@ Store back the result in GPIOD control register low

	;@ Set GIOOD Pin1 to 1 (Page 172 from RM0008)
	LDR R6, = 0x4001140C    ;@ Load GPIOD output data register
	LDR R5, = 0x00000002   ;@ Set Pin 1 to 1
	STR R5, [R6]           ;@ Store back the result in GPIOD output data register
	
	NOP
	NOP
	LDR R5, = 0x00000000   ;@ Set MODE bits to 10 and CNF bits to 00, thus 0x00000020
	STR R5, [R6]           ;@ Store back the result in GPIOD output data register

 
LOOP  
;@ Set GIOOD Pin1 to 1 (Page 172 from RM0008)
	LDR R6, = 0x4001140C    ;@ Load GPIOD output data register
	LDR R5, = 0x00000002   ;@ Set Pin 1 to 1
	STR R5, [R6]           ;@ Store back the result in GPIOD output data register
	
	NOP
	NOP
	
	LDR R5, = 0x00000000   ;@ Set MODE bits to 10 and CNF bits to 00, thus 0x00000020
	STR R5, [R6]           ;@ Store back the result in GPIOD output data register

    ADD R0, R0, #4
	
   	B  LOOP
 
          END	;End of the program
