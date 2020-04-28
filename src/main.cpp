#include <cstring>
#include <cstdio>
#include "gpio.hpp"

int main() {
  Gpio* g = new Gpio();
  g->set_fsel(2, Gpio::FunctionSelect::IN);
  printf("2-fsel:%d", (int)g->get_fsel(2));
  g->set_fsel(2, Gpio::FunctionSelect::OUT);
  g->set_fsel(4, Gpio::FunctionSelect::OUT);
  printf("2-fsel:%d", (int)g->get_fsel(2));
  while(true){
    printf("pls typing on or off\n");

    char buff[256];
    scanf("%s", buff);

    if(strcmp(buff, "on") == 0){
      g->set_pin(2);
      g->set_pin(4);
    }
    else{
      g->clear_pin(2);
      g->clear_pin(4);
    }
  }
  delete g;

  return 0;
}
