#include "game.h"

#include <iostream>

#include "cpputils/graphics/image_event.h"

void Game::Init() {
  my_player_.SetX(375);
  my_player_.SetY(500);
  game_screen_.AddMouseEventListener(*this);
  game_screen_.AddAnimationEventListener(*this);
}
void Game::CreateOpponents() {
  std::unique_ptr<Opponent> my_opponent = std::make_unique<Opponent>(100, 20);
  opponents_.push_back(std::move(my_opponent));
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive()) {
      opponents_[i]->Move(game_screen_);
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->GetIsActive()) {
      opponent_projectiles_[i]->Move(game_screen_);
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    if (player_projectiles_[i]->GetIsActive()) {
      player_projectiles_[i]->Move(game_screen_);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive() && my_player_->GetIsActive() &&
        my_player_->IntersectsWith(opponents_[i])) {
      // opponents_.erase(opponents_.begin() + i);
      opponents_[i]->SetIsActive(false);
      my_player_->SetIsActive(false);
      HasLost();
    } else {
      for (int j = 0; j < player_projectiles_.size(); j++) {
        if (opponents_[i]->GetIsActive() &&
            player_projectiles_[j]->GetIsActive() &&
            player_projectiles_[j]->IntersectsWith(opponents_[i])) {
          opponents_[i]->SetIsActive(false);
          player_projectiles_[j]->SetIsActive(false);
          score_++;
        }
      }
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->GetIsActive() && my_player_->GetIsActive() &&
        my_player_->IntersectsWith(opponent_projectiles_[i])) {
      opponent_projectiles_[i]->SetIsActive(false);
      my_player_->SetIsActive(false);
      HasLost();
    }
  }
}

void Game::UpdateScreen() {
  game_screen_.DrawRectangle(0, 0, game_screen_.GetWidth(),
                             game_screen_.GetHeight(),
                             graphics::Color(255, 255, 255));
  game_screen_.DrawText(0, 0, "Score: ", 40, graphics::Color(0, 0, 0));
  game_screen_.DrawText(100, 0, GetScore(), 40, graphics::Color(0, 0, 0));
  if (has_lost_ = true) {
    game_screen_.DrawText(50, 50, "GAME OVER", 40, graphics::Color(0, 0, 0))
  }
  if (my_player_->GetIsActive()) {
    my_player_->Draw(game_screen_);
  }
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive()) {
      opponents_[i]->Draw(game_screen_);
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->GetIsActive()) {
      opponent_projectiles_[i]->Draw(game_screen_);
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    if (player_projectiles_[i]->GetIsActive()) {
      player_projectiles_[i]->Draw(game_screen_);
    }
  }
}

void Game::Start() { game_screen_.ShowUntilClosed(); }

void Game::OnMouseEvent(const graphics::MouseEvent& event) {
  if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    int new_x = event.GetX() - my_player_.GetWidth() / 2;
    int new_y = event.GetY() - my_player_.GetHeight() / 2;
    int old_x = my_player_.GetX();
    int old_y = my_player_.GetY();

    my_player_.SetX(new_x);
    my_player_.SetY(new_y);

    if (my_player_.IsOutOfBounds(game_screen_)) {
      my_player_.SetX(old_x);
      my_player_.SetY(old_y);
    }
  }
  if (event.GetMouseAction() == graphics::MouseAction::kPressed ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
  }
}

void Game::OnAnimationStep() {
  MoveGameElements();
  FilterIntersections();
  UpdateScreen();
  game_screen_.Flush();
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponents_.size(); i++) {
    opponent_[i]->LaunchProjectile();
    if (/* condition */) {
      /* code */
    }
  }
}

void Game::RemoveInactive() {}
