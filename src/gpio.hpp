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

    struct Status {
      int pin;
      bool is_active;
      bool is_high;
      FunctionSelect fsel;
    };

    // Enter the GPIO pin number for the first argument 'pin'.
    // It has nothing to do with the number on the board.
    int set_fsel(int pin, FunctionSelect fsel);

    // As described above
    int set_pin(int pin);

    // As described above
    int clear_pin(int pin);

    // As described above
    Status* get_status(int pin, Status* pStatus);

  private:
    static const int PeripheralAddr;
    static const int PeripheralSize = 4096;

    int m_memoryFd;
    unsigned int m_map;

    bool validate_pin(int pin);
    bool is_high(int pin);
    FunctionSelect get_fsel(int pin);
};

#endif
