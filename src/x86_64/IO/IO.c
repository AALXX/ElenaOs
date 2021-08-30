#include "../../kernel/interfaces/IO.h"

void outb(uint16_t port, uint8_t val){
  asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port){
    uint8_t retVal;
     asm volatile ("inb %1, %0": "=a"(retVal): "Nd"(port));

  return retVal;
}

void RemapPic(){
  uint8_t a1, a2;

  a1 = inb(PIC1_DATA);
  a2 = inb(PIC2_DATA);

  outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
  outb(PIC1_DATA, 0);
  outb(PIC2_DATA, 8);
  outb(PIC1_DATA, 4);
  outb(PIC2_DATA, 2);
  outb(PIC1_DATA, ICW4_8086);
  outb(PIC2_DATA, ICW4_8086);

  outb(PIC1_DATA, a1);
  outb(PIC2_DATA, a2);
}