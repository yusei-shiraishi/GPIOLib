#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include "gpio.hpp"

int main() {
  Gpio* g = new Gpio();
  //while(true){
  //  if(g->is_high(2)) printf("2-high\n");
  //  printf("pls typing on or off\n");

  //  char buff[256];
  //  scanf("%s", buff);

  //  if(strcmp(buff, "on") == 0){
  //    g->set_pin(2);
  //    g->set_pin(21);
  //  }
  //  else{
  //    g->clear_pin(2);jjj
  //    g->clear_pin(21);
  //  }
  //}

  //std::vector<bool> states(128, false);
  g->set_fsel(20, Gpio::FunctionSelect::IN);
  //while(true){
  //  states[255] = g->is_high(20);

  //  //print
  //  for(auto ite = states.begin(); ite != states.end(); ++ite){
  //    if(*ite) printf("-");
  //    else     printf("_");
  //  }
  //  printf("\n");
  //  usleep(1000);
  //}

  bool state = g->is_high(20);
  if   (state) printf("current:high/n");
  else         printf("current:low/n");
 
  while(true){
    if(state != g->is_high(20)){
      if   (state) printf("current:high/n");
      else         printf("current:low/n");
    }
    state = g->is_high(20);
  }
  delete g;

  return 0;
}
