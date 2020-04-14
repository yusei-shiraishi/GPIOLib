#include "gpio.hpp"
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

const int Gpio::PeripheralAddr = bcm_host_get_peripheral_address();

Gpio::Gpio() {
  m_memoryFd = open("/dev/mem", O_RDWR|O_SYNC);
  if(m_memoryFd < 0) {
    perror("Failed to open /dev/mem");
		return;
  }

  m_map = mmap(
    NULL,
    PeripheralSize,
    PROT_READ|PROT_WRITE,
    MAP_SHARED,
    m_memoryFd,
    PeripheralAddr + 0x00200000
  );

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

  std::cout << "fsel:" << (int)fsel << std::endl;
  std::cout << "shift:" << 3*(pin%10) << std::endl;
  std::cout << "pin_num:" << pin << std::endl;
  std::cout << "addr:" << std::hex << m_addr + (pin/10) << std::endl;
  std::cout << "m_addr:" << std::hex << m_addr << std::endl;
  std::cout << "peri:" << std::hex << Gpio::PeripheralAddr << std::endl;
  std::cout << "val:" << std::hex << ((int)fsel << 3*(pin%10)) << std::endl;
  std::cout << "current_val:" << std::hex << *(m_addr + (pin/10)) << std::endl;
  std::cout << "valsize:" << sizeof(*(m_addr + (pin/10))) << std::endl;

  *(m_addr + (pin/10)) = ((int)fsel << 3*(pin%10));

  std::cout << "after_val:" << std::hex << *(m_addr + (pin/10)) << std::endl;
  return 0;
}

int Gpio::set_pin(int pin){
  *(m_addr + OffsetGPSET0) = (1 << pin);
  return 0;
}

int Gpio::clear_pin(int pin){
  return 0;
}

Gpio::Status* Gpio::get_status(int pin, Status* pStatus){
  return nullptr;
}

bool Gpio::validate_pin(int pin){
  return false;
}

bool Gpio::is_high(int pin){
  return false;
}

Gpio::FunctionSelect Gpio::get_fsel(int pin){
  FunctionSelect::OUT;
}
