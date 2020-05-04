#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <vector>
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
  //    g->clear_pin(2);
  //    g->clear_pin(21);
  //  }
  //}
  std::vector<bool> states(256, false);
  g->set_fsel(20, GPIO::FunctionSelect::IN);
  while(true){
    states[255] = g->is_high(20);

    //print
    std::system("cls");
    for(auto ite = states.begin(); ite != states.end(); ++i){
      if(*ite) printf("-");
      else     printf("_");
    }
    printf("\n");
  }
  delete g;

  return 0;
}
