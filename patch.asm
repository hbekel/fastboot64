.pc = $fd6c 
fakeMemoryCheck: {
	jsr $fd02 // check for cartridge
	beq cart
nocart:
	ldx #$00
	ldy #$a0  // assume memory top at $a000
	jmp done
	
cart:
	ldx #$00
	ldy #$80 // assume memory top at $8000
	
done:	jmp $fd8c 
}
