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
    static const size_t OffsetGPIO = 0x00200000;
    static const size_t PeripheralSize = 256;
    static const size_t OffsetGPSET0 = 0x0000001C;
    static const size_t OffsetGPCLR0 = 0x00000028;
    static const size_t OffsetGPLEV0 = 0x00000034;

    int m_memoryFd;
    void* m_map;
    volatile unsigned long* m_addr;

    bool validate_pin(int pin);
    bool is_high(int pin);
    FunctionSelect get_fsel(int pin);
};

#endif
