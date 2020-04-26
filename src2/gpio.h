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

	 int set_fsel(int pin, FunctionSelect fsel);
	 int set_pin(int pin);
	 int clear_pin(int pin);

private:
	static const int PERIPHERAL_ADDRESS;
        static const int PAGE_SIZE = 4096;
	int m_fd;
	unsigned int m_addr;
};
#endif
