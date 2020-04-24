#include "gpio.hpp"
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

#define GPIO_OFFSET 0x00200000
#define PAGE_SIZE 4096
#define GPFSEL0_OFFSET 0x0000
#define GPSET0_OFFSET 0x001C
#define GPCLR0_OFFSET 0x0028
#define GPLEV0_OFFSET 0x0034

const int Gpio::PeripheralAddr = bcm_host_get_peripheral_address();

Gpio::Gpio() {
  m_memoryFd = open("/dev/mem", O_RDWR|O_SYNC);
  if(m_memoryFd < 0) {
    perror("Failed to open /dev/mem\n");
		return;
  }

  m_map = mmap(
    NULL,
    PeripheralSize,
    PROT_READ|PROT_WRITE,
    MAP_SHARED,
    m_memoryFd,
    //PeripheralAddr + OffsetGPIO
    PeripheralAddr + GPIO_OFFSET
  );

  if (m_map == MAP_FAILED) {
    perror("failed with mmap()\n");
    close(m_memoryFd);
    return;
  }
}

Gpio::~Gpio() {
  munmap(m_map, PeripheralSize);
  close(m_memoryFd);
}

int Gpio::set_fsel(int pin, Gpio::FunctionSelect fsel) {
  //１つしかできないからなんとかしろ
  if (!validate_pin(pin)){
    perror("gg");
  }

  *((volatile unsigned int*)(m_map + GPFSEL0_OFFSET)) = (1 << pin);
  //volatile unsigned long* addr = (volatile unsigned long*)(m_map);
  //*(addr + (pin / 10)) = ((int)fsel << 3*(pin % 10));
  //*(m_addr + (pin / 10)) = ((int)fsel << 3*(pin % 10));

  return 0;
}

int Gpio::set_pin(int pin){
  *((volatile unsigned int*)(m_map + GPSET0_OFFSET)) = (1 << pin);
  return 0;
}

int Gpio::clear_pin(int pin){
  *((volatile unsigned long*)(m_map + GPCLR0_OFFSET)) = (1 << pin);
  return 0;
}

Gpio::Status* Gpio::get_status(int pin, Status* pStatus){
  return pStatus;
}

bool Gpio::validate_pin(int pin){
  return false;
}

bool Gpio::is_high(int pin){
  //long val = *(m_addr + (OffsetGPLEV0 / 4) + (pin / 32));
  return true;
  //return (val & (1 << (pin % 32))) > 0;
}

Gpio::FunctionSelect Gpio::get_fsel(int pin){
  FunctionSelect::OUT;
}
