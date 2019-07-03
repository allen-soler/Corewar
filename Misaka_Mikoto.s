.name		"Misaka Mikoto"
.comment	"jpp de ca aussi"

entry:
	sti		r1, %:run, %1
	sti		r1, %:f1_a, %1
	sti     r1, %:f1_b, %1
	sti     r1, %:f2_a, %1
	sti     r1, %:f2_d, %1

	st      r2, :entry

nothing:
	fork	%:clear
	add		r3, r3, r3
	zjmp	%:loader

filler:
	zjmp	%:run
	zjmp    %:run
	zjmp    %:run
	zjmp    %:run
	zjmp    %:run
	zjmp    %:run

clear:
	live	%404
	
	add		r3, r3, r3
	fork	%:f0_z
	zjmp	%:f1_a

f0_z:
	zjmp	%:f1_b

f1_a:
	live	%404
	fork	%:f1_z
	zjmp	%:f2_a

f1_b:
	live	%404
	fork	%:f1_y
	zjmp	%:f2_b

f1_z:
	zjmp	%:f2_c

f1_y:
	zjmp	%:f2_d



f2_a:
	live    %404
	fork	%:f2_z
	zjmp	%:f3_a
f2_b:
	live    %404
	fork    %:f2_y
	zjmp    %:f3_b
f2_c:
	live    %404
	fork    %:f2_w
	zjmp    %:f3_c
f2_d:
	live    %404
	fork    %:f2_x
	zjmp    %:f3_d
f2_z:
	zjmp	%:f3_e
f2_y:
	zjmp    %:f3_f
f2_x:
	zjmp    %:f3_g
f2_w:
	zjmp    %:f3_h



f3_b:
	ld		%-498, r9
	ldi     %0, %:bomb_b, r8
	add     r3, r3, r3
	zjmp	%:run

f3_f:
	ld		%-504, r9
	ldi     %0, %:bomb_b, r8
	add     r3, r3, r3
	zjmp	%:run

f3_d:
	ld		%508, r9
	ldi     %0, %:bomb_a, r8
	add     r3, r3, r3
	zjmp	%:run

f3_c:
	ld		%516, r9
	ldi     %0, %:bomb_a, r8
	add     r3, r3, r3
	zjmp	%:run

f3_g:
	ld		%512, r9
	ldi     %0, %:bomb_a, r8
	add     r3, r3, r3
	zjmp	%:run

f3_a:
	ld		%19, r9
	ldi     %8, %:run, r8
	add     r3, r3, r3
	zjmp	%:run

f3_e:
	ld		%11, r9
	ldi     %0, %:run, r8
	add     r3, r3, r3
	zjmp	%:run

f3_h:
	ld		%15, r9
	ldi     %4, %:run, r8
	add     r3, r3, r3
	zjmp	%:run

run:
	live	%777
	sti		r8, %:run, r9
	sti     r8, %:run, r9
	sti     r8, %:run, r9
	sti     r8, %:run, r9
	sti     r8, %:run, r9
	sti     r8, %:run, r9
	sti     r8, %:run, r9
	sti     r8, %:run, r9

bomb_b:
	lfork	%-50

bomb_a:
	zjmp	%0

data_miner:
	live	%404
	
loader:
	ldi		%0,	%:data_miner, r3
	
shotgun:
	ldi		%7, %:shotgun, r2
	st		r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	st      r2, 256
	live	%404
	st		r3, 256
