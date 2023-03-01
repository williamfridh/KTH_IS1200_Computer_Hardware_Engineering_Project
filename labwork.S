# Authors: Fridh, William & Åhlin, Pontus

.data
.text
.global enable_interrupt

enable_interrupt:
	ei
	jr 	$ra
	nop

