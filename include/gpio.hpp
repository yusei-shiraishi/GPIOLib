#ifndef GPIO_HPP
#define GPIO_HPP

class Gpio{
public:
	Gpio();
	~Gpio();

  enum struct FunctionSelect {
   IN  = 0b000,
   OUT = 0b001
  };

  // Enter the GPIO pin number for the first argument 'pin'.
  // It has nothing to do with the number on the board.
  void set_fsel(unsigned int pin, FunctionSelect fsel);
  void set_pin(unsigned int pin);
  void clear_pin(unsigned int pin);
  FunctionSelect get_fsel(unsigned int pin);
  bool is_high(unsigned int pin);

private:
  static const int PERIPHERAL_ADDRESS;
  static const int PAGE_SIZE = 256;

  int m_fd;
  unsigned int m_addr;

  bool validate_pin(int pin);
};

#endif
