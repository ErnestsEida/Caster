#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

double const PI = 3.14159265358979323846;

class Player {
private:
  Vector2i mousePos = Mouse::getPosition();
  float movespeed = 0.05;
  float rotation_speed = 0.5;
  int border_x;
  int border_y;

  void move_fwd_bck() {
    short movement_sign = Keyboard::isKeyPressed(Keyboard::Key::W) -
                          Keyboard::isKeyPressed(Keyboard::Key::S);

    double rot = this->rotation();
    this->x += movement_sign * (cos(rot)) * movespeed;
    this->y += movement_sign * (sin(rot)) * movespeed;
  }

  void move_sides() {
    short movement_sign = Keyboard::isKeyPressed(Keyboard::Key::D) -
                          Keyboard::isKeyPressed(Keyboard::Key::A);

    double rot = this->rotation(90);
    this->x += movement_sign * (cos(rot)) * movespeed;
    this->y += movement_sign * (sin(rot)) * movespeed;
  }

  void move_rotation() {
    Vector2i temp = Mouse::getPosition();
    
    float rot_value = temp.x - this->mousePos.x;
    this->mousePos = temp;

    this->raw_rotation += rot_value * rotation_speed;
    // if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
    //   this->raw_rotation += rotation_speed;
    // } else if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
    //   this->raw_rotation -= rotation_speed;
    // }
  }

public:
  float x = 0;
  float y = 0;
  float raw_rotation = 0;

  Player(int x, int y) {
    this->border_x = x;
    this->border_y = y;
  }

  void perform() {
    move_fwd_bck();
    move_sides();
    move_rotation();
  }

  double rotation(double append_rot = 0) const {
    return (this->raw_rotation + append_rot) * (PI / 180);
  }
};