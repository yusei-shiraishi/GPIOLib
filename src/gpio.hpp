#ifndef GPIO_HPP
#define GPIO_HPP

#include <bcm_host.h>

class Gpio {
  public:
    Gpio();
    ~Gpio();

    enum struct FunctionSelect {
      IN  = 0b000,
      OUT = 0b001
    };

    // Enter the GPIO pin number for the first argument 'pin'.
    // It has nothing to do with the number on the board.
    int set_pin(int pin, FunctionSelect fsel);

    // As described above
    FunctionSelect get_pin(int pin);

  private:
    static const int PeripheralAddr;
    static const size_t PeripheralSize = 5;

    int memory_fd;
    void* map;
    volatile unsigned int* addr;

    bool validate_pin(int pin);
};

#endif
