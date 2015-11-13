kola: small_libc1.o small_libc2.o main.o kolakoski.o
	ld -o kola small_libc1.o small_libc2.o main.o kolakoski.o
	strip -R .comment kola
	strip -R .eh_frame kola

small_libc1.o: small_libc.asm
	as small_libc.asm -o small_libc1.o 

small_libc2.o: small_libc.c
	gcc -fno-math-errno -Os -c small_libc.c -o small_libc2.o 

kolakoski.o: kolakoski.c
	gcc -fno-math-errno -O3 -c kolakoski.c -o kolakoski.o -std=c99 -fstrict-aliasing

main.o: main.c
	gcc -fno-math-errno -Os -c main.c -o main.o -std=c99 -fstrict-aliasing

clean: small_libc1.o small_libc2.o main.o kolakoski.o
	rm small_libc1.o small_libc2.o main.o kolakoski.o
