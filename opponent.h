#ifndef OPPONENT_H
#define OPPONENT_H

#include <memory>
#include <vector>

#include "cpputils/graphics/image.h"
#include "game_element.h"

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& screen) override;
  std::unique_ptr<class OpponentProjectile> LaunchProjectile();

 private:
  const graphics::Color kOrange{255, 165, 0};
};

class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& screen) override;
  std::unique_ptr<class OpponentProjectile> LaunchProjectile(
      GameElement* object);

 private:
  const graphics::Color kRed{255, 0, 0};
  const graphics::Color kOrange{255, 165, 0};
  const graphics::Color kYellow{255, 255, 0};
  bool going_right_ = true;
};

#endif
