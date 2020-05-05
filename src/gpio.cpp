#include "../include/gpio.hpp"

#include <bcm_host.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <cstdio>
#include <sys/mman.h>
#include <unistd.h>

#define GPIO_OFFSET 0x00200000
#define GPFSEL0_OFFSET 0x0000
#define GPSET0_OFFSET 0x001C
#define GPCLR0_OFFSET 0x0028
#define GPLEV0_OFFSET 0x0034

#define DEVICE_FILE "/dev/mem"

using std;

const int Gpio::PERIPHERAL_ADDRESS = bcm_host_get_peripheral_address();

Gpio::Gpio(){
  if ((m_fd = open(DEVICE_FILE, O_RDWR | O_SYNC)) < 0) {
    perror("failed to open DEVICE_FILE");
    throw system_error("failed to open DEVICE_FILE");
  }

  m_addr = (unsigned int)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, PERIPHERAL_ADDRESS + GPIO_OFFSET);
  if ((void*)m_addr == MAP_FAILED) {
    perror("failed with mmap");
    close(m_fd);
    throw system_error("failed with mmap");
  }
}

Gpio::~Gpio(){
  munmap((void*)m_addr, PAGE_SIZE);
  close(m_fd);
}

void Gpio::set_fsel(unsigned int pin, Gpio::FunctionSelect fsel) {
  if (!validate_pin(pin)) throw invalid_argument("argument error");

  volatile unsigned int* addr = ((volatile unsigned int*)(m_addr + GPFSEL0_OFFSET) + (pin / 10));
  int offset = 3*(pin % 10);
  unsigned int high_part = ((*addr >> (offset+3)) << (offset+3));
  unsigned int target_part = (int)fsel << offset;
  unsigned int low_part = (((1 << offset) - 1) & *addr);
  *addr = high_part | target_part | low_part;
}

void Gpio::set_pin(unsigned int pin){
  if (!validate_pin(pin)) throw invalid_argument("argument error");

  volatile unsigned int* addr = ((volatile unsigned int*)(m_addr + GPSET0_OFFSET) + (pin / 32));
  *addr = (*addr | (1 << (pin % 32)));
}

void Gpio::clear_pin(unsigned int pin){
  if (!validate_pin(pin)) throw invalid_argument("argument error");

  volatile unsigned int* addr = ((volatile unsigned int*)(m_addr + GPCLR0_OFFSET) + (pin / 32));
  *addr = (*addr | (1 << (pin%32)));
  return;
}

bool Gpio::validate_pin(unsigned int pin){
  if(pin > 53) return false;
  return true;
}

bool Gpio::is_high(unsigned int pin){
  if (!validate_pin(pin)) throw invalid_argument("argument error");

  volatile unsigned int* addr = ((volatile unsigned int*)(m_addr + GPLEV0_OFFSET) + (pin / 32));
  int offset = pin % 32;
  return (bool)(*addr & (1 << offset));
}

Gpio::FunctionSelect Gpio::get_fsel(unsigned int pin){
  if (!validate_pin(pin)) throw invalid_argument("argument error");

  volatile unsigned int* addr = ((volatile unsigned int*)(m_addr + GPFSEL0_OFFSET) + (pin / 10));
  int offset = 3*(pin % 10);
  return (FunctionSelect)((*addr & (0b111 << offset)) >> offset);
}
