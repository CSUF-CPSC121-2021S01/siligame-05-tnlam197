#include "opponent.h"

#include <vector>

#include "cpputils/graphics/image.h"

void OpponentProjectile::Draw(graphics::Image& screen) {
  screen.DrawRectangle(GetX(), GetY(), 2, 2, kOrange);
  screen.DrawRectangle(GetX() + 3, GetY(), 2, 2, kOrange);
  screen.DrawRectangle(GetX() + 3, GetX() + 3, 2, 2, kOrange);
  screen.DrawRectangle(GetX(), GetY() + 3, 2, 2, kOrange);
}

void Opponent::Draw(graphics::Image& screen) {
  std::vector<int> layer1 = {12, 1,  33, 6,  40, 21, 47, 8, 45, 35, 37, 48,
                             9,  48, 2,  39, 3,  19, 10, 5, 10, 12, 23, 19};
  PadPoints(layer1, GetX(), GetY());
  screen.DrawPolygon(layer1, kRed);

  std::vector<int> layer2 = {20, 7,  31, 11, 39, 24, 43, 22, 42, 33, 36,
                             46, 12, 46, 6,  38, 8,  14, 15, 21, 28, 22};
  PadPoints(layer2, GetX(), GetY());
  screen.DrawPolygon(layer2, kOrange);

  std::vector<int> layer3 = {32, 21, 38, 27, 38, 33, 33, 42, 15,
                             42, 10, 37, 10, 21, 15, 24, 32, 25};
  PadPoints(layer3, GetX(), GetY());
  screen.DrawPolygon(layer3, kYellow);
}

void Opponent::Move(const graphics::Image& screen) {
  if (going_right_ && GetX() + GetWidth() >= screen.GetWidth()) {
    going_right_ = false;
  } else if (!going_right_ && GetX() <= 0) {
    going_right_ = true;
  }
  int offset = going_right_ ? 1 : -1;

  SetX(GetX() + offset * 5);
  SetY(GetY() + 2);

  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}

void OpponentProjectile::Move(const graphics::Image& screen) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}

std::unique_ptr<class OpponentProjectile> Opponent::LaunchProjectile(
    GameElement* object) {
  std::unique_ptr<OpponentProjectile> projectile;
  int counter = 0;
  if ((counter % 120) != 0) {
    counter++;
    projectile = nullptr;
    return std::move(projectile);
  } else {
    projectile =
        std::make_unique<OpponentProjectile>(object->GetX(), object->GetY());
    counter = 0;
    return std::move(projectile);
  }
}
