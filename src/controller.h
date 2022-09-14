#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "paddles.h"

class Controller {
 public:
  void HandleInput(bool &running, Paddle &paddle_one, Paddle &paddle_two) const;
};

#endif