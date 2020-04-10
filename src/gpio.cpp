#include "gpio.hpp"
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>

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
    PeripheralAddr
  );

  m_addr = (volatile unsigned int*)m_map;
}

Gpio::~Gpio() {
  munmap(m_map, PeripheralSize);
  close(m_memoryFd);
}

int Gpio::set_pin(int pin, Gpio::FunctionSelect fsel) {
  if (!validate_pin(pin)){
    perror("gg");
  }

  perror("yea");

  *(m_addr + (pin/10)) = (short)fsel << 3*(pin%10);
  return 0;
}

Gpio::FunctionSelect Gpio::get_pin(int pin) {
  if (!validate_pin(pin)){
    perror("gg");
  }

  return FunctionSelect::IN;
}

bool Gpio::validate_pin(int pin) {
  return true;
}
