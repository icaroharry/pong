PATH_ALLEGRO="C:\Documents and Settings\m916\Desktopallegro-5.0.10-mingw-4.6.2"
LIB_ALLEGRO=\lib\liballegro-5.0.10-monolith-mt.a
INCLUDE_ALLEGRO=\include

all: passaro_andante.exe teclado.exe bouncer.exe louco.exe

passaro_andante.exe: passaro_andante.o
	gcc -o passaro_andante.exe passaro_andante.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

passaro_andante.o: passaro_andante.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c passaro_andante.c

bouncer.exe: bouncer.o
	gcc -o bouncer.exe bouncer.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

bouncer.o: bouncer.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c bouncer.c

teclado.exe: teclado.o
	gcc -o teclado.exe teclado.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

teclado.o: teclado.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c teclado.c

louco.exe: louco.o
	gcc -o louco.exe louco.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

louco.o: louco.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c louco.c

clean:
	del passaro_andante.o
	del passaro_andante.exe
	del louco.o
	del louco.exe
	del teclado.o
	del teclado.exe
	del bouncer.o
	del bouncer.exe
