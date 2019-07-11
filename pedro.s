.name "pedro"
.comment "monfort el gabacho"

ld %0, r10
ld %57672449, r3	# CORROMPEMOS:	st r3, 350
ld %589833, r4		# PROTEGEMOS:	zjmp %9
and %0, %0, r10
fork %:inicializamos
and %1, %1, r16
zjmp %:atacamos

dormimos:
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500
	st r10, -500

atacamos:
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	st r3, 500
	sti r1, %:bebemos, %1

bebemos:
	live %-14
	and %0, %0, r10
	zjmp %:saltamos

inicializamos:
	sti r1, %:vivimos, %1
	sti r4, %-7, %0
	and %0, %0, r10

vivimos:
	live %-14
	zjmp %:vivimos

saltamos:
	zjmp %146
