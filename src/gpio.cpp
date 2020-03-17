#include "gpio.hpp"

Gpio::Gpio() {
  memory_fd = open("/dev/mem", O_RDWR|O_SYNC);
  if(gpio->memory_fd < 0) {
    perror("Failed to open /dev/mem");
		return;
  }

  map = mmap(
    NULL,
    PeripheralSize,
    PROT_READ|PROT_WRITE,
    MAP_SHARED,
    memory_fd,
    PeripheralAddr
  );
}

Gpio::~Gpio() {
}

int Gpio::set_pin(int pin, FunctionSelect fsel) {
  if (!validate_pin(pin)){
    perror("gg");
  }
}

FunctionSelect Gpio::get_pin(int pin) {
  if (!validate_pin(pin)){
    perror("gg");
  }
}
