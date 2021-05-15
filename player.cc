#include "player.h"

#include <vector>

#include "cpputils/graphics/image.h"

void PlayerProjectile::Draw(graphics::Image &screen) {
  screen.DrawRectangle(GetX() + 1, GetY(), 2, 2, kBlue);
  screen.DrawRectangle(GetX(), GetY() + 3, 2, 2, kBlue);
  screen.DrawRectangle(GetX() + 3, GetY() + 3, 2, 2, kBlue);
}

void Player::Draw(graphics::Image &screen) {
  screen.DrawLine(GetX() + 19, GetY(), GetX() + 30, GetY(), kBlack);
  screen.DrawRectangle(GetX() + 24, GetY() + 1, 2, 2, kBlack);
  std::vector<int> engine = {20, 3, 29, 3, 31, 8, 18, 8};
  PadPoints(engine, GetX(), GetY());
  screen.DrawPolygon(engine, kGreen);
  std::vector<int> wing = {44, 14, 49, 20, 49, 27, 43, 27, 43, 29,
                           37, 29, 37, 27, 12, 27, 12, 29, 6,  29,
                           6,  27, 0,  27, 0,  20, 5,  14};
  PadPoints(wing, GetX(), GetY());
  screen.DrawPolygon(wing, kRed);
  std::vector<int> body = {17, 9, 32, 9, 27, 40, 22, 40};
  PadPoints(body, GetX(), GetY());
  screen.DrawPolygon(body, kBlue);
  std::vector<int> tail = {22, 41, 17, 46, 17, 48, 32, 48, 32, 46, 27, 41};
  PadPoints(tail, GetX(), GetY());
  screen.DrawPolygon(tail, kRed);
  screen.DrawRectangle(GetX() + 21, GetY() + 12, 7, 5, kGreen);
  screen.DrawRectangle(GetX() + 21, GetY() + 17, 7, 5, kRed);
}

void PlayerProjectile::Move(const graphics::Image &screen) {
  SetY(GetY() - 3);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}
