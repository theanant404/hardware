#include <stdint.h>
#define  IOPORT_BASE (0x50000000UL)
#define GPIOA_BASE (IOPORT_BASE + 0x00000000UL)

void initGPIO(){
  uint32_t mask=0x00000c00;
  volatile uint32_t* ledport=(uint32_t*)(GPIOA_BASE);
  uint32_t x=*(ledport+0x00);
  x=(x & ~mask)|(0x001<<10);
  *(ledport+0x00)=x;
}

void toggle_pin(uint32_t gpiobase, uint16_t pin){
  uint32_t x=*(volatile uint32_t*)(gpiobase + 0x14);
  *(volatile uint32_t*)(gpiobase+0x18)=((x & (1<<pin))<<16)|(~x&(1<<pin));
}

int main(void)
{
  initGPIO();
  toggle_pin(GPIOA_BASE,5);
  while(1){
    for(int i=0;i<1000000;i++);
    toggle_pin(GPIOA_BASE,5);
  }
  return 0;
}