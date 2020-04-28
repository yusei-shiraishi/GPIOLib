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
  int set_fsel(int pin, FunctionSelect fsel);
  int set_pin(int pin);
  int clear_pin(int pin);

  FunctionSelect get_fsel(int pin);
private:
	static const int PERIPHERAL_ADDRESS;
  static const int PAGE_SIZE = 256;

	int m_fd;
	unsigned int m_addr;

  bool validate_pin(int pin);
  bool is_high(int pin);
};

#endif
