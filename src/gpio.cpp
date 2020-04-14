#include "gpio.hpp"
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

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
    PeripheralAddr + OffsetGPIO
  );

  if (m_map == MAP_FAILED) {
    perror("failed with mmap()\n");
  }

  m_addr = (volatile unsigned long*)m_map;
}

Gpio::~Gpio() {
  munmap(m_map, PeripheralSize);
  m_addr = nullptr;
  close(m_memoryFd);
}

int Gpio::set_fsel(int pin, Gpio::FunctionSelect fsel) {
  if (!validate_pin(pin)){
    perror("gg");
  }

  *(m_addr + (pin/10)) = ((int)fsel << 3*(pin%10));

  return 0;
}

int Gpio::set_pin(int pin){
  *(m_addr + OffsetGPSET0 + (pin / 32)) = (1 << (pin % 32));
  return 0;
}

int Gpio::clear_pin(int pin){
  *(m_addr + OffsetGPCLR0 + (pin / 32)) = (1 << pin);
  return 0;
}

Gpio::Status* Gpio::get_status(int pin, Status* pStatus){
  return pStatus;
}

bool Gpio::validate_pin(int pin){
  return false;
}

bool Gpio::is_high(int pin){
  long val = *(m_addr + OffsetGPLEV0 + (pin / 32));
  return (val & (1 << (pin % 32))) > 0;
}

Gpio::FunctionSelect Gpio::get_fsel(int pin){
  FunctionSelect::OUT;
}
