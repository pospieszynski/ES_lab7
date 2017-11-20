#lepiej tego nie modyfikowac
CCFLAGS=-g -mcpu=arm9 -Os -Wall
#LDFLAGS+=-nostartfiles -Wl,--cref -lc -lgcc -T /opt/arm_user/elf32-littlearm.lds -g -Ttext 0x20000000 -Tdata 0x300000 -n
# narzedzia w /opt/arm_user
LDFLAGS+=-nostartfiles -Wl -lc -lgcc -T /opt/arm_user/elf32-littlearm.lds -g -Ttext 0x20000000 -Tdata 0x300000 -n
OBJS=/opt/arm_user/include/cstartup.o /opt/arm_user/include/lowlevel.o DBGU.o FIFO.o
#koniec, dalej mozna dowolnie zmieniac

PROGRAM_NAME=fifo.elf

all: $(PROGRAM_NAME)

rebuild: clean $(PROGRAM_NAME)

$(PROGRAM_NAME): main.o DBGU.o FIFO.o
	arm-elf-gcc $(LDFLAGS) $(OBJS) $< -o $@

main.o: main.c 
	arm-elf-gcc -c $(CCFLAGS) $< -o $@

DBGU.o: DBGU.c DBGU.h
	arm-elf-gcc -c $(CCFLAGS) $< -o $@

FIFO.o: FIFO.c FIFO.h
	arm-elf-gcc -c $(CCFLAGS) $< -o $@

clean:
	rm -f *.o *.elf 