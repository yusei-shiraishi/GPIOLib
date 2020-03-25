#include "gpio.hpp"
#include <cstdio>
#include <fcntl.h>
#include <sys/mman.h>

const int Gpio::PeripheralAddr = bcm_host_get_peripheral_address();

Gpio::Gpio() {
  m_memory_fd = open("/dev/mem", O_RDWR|O_SYNC);
  if(m_memory_fd < 0) {
    perror("Failed to open /dev/mem");
		return;
  }

  m_map = mmap(
    NULL,
    PeripheralSize,
    PROT_READ|PROT_WRITE,
    MAP_SHARED,
    m_memory_fd,
    PeripheralAddr
  );
}

Gpio::~Gpio() {
}

int Gpio::set_pin(int pin, Gpio::FunctionSelect fsel) {
  if (!validate_pin(pin)){
    perror("gg");
  }
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
