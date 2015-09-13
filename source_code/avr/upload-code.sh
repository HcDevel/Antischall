echo Es sind root Rechte erforderlich!
sudo echo OK: Root Rechte erhalten!
rm program.o main.elf main.hex
avr-gcc -mmcu=attiny85 -Os -o main.elf *.c
avr-objcopy -O ihex -j .text -j .data main.elf main.hex
avr-size --mcu=attiny85 -C main.elf
sudo avrdude -B 10 -c avrisp2 -p t85 -U flash:w:main.hex:a
