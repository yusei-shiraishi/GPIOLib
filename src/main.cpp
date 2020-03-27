#include <stdio.h>
#include <bcm_host.h>
#include "gpio.hpp"

int main(){
  Gpio* gpio = new Gpio();

  printf("create gpio");
  return 0;
}
