#ifndef GAME_H
#define GAME_H
#include <memory>
#include <vector>

#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(int width, int height) : game_screen_(width, height) {}

  graphics::Image& GetGameScreen() { return game_screen_; }
  std::unique_ptr<Opponent>& GetOpponents() { return opponents_; }
  std::unique_ptr<OpponentProjectile>& GetOpponentProjectiles() {
    return opponent_projectiles_;
  }
  std::unique_ptr<PlayerProjectile>& GetPlayerProjectiles() {
    return player_projectiles_;
  }
  Player& GetPlayer() { return my_player_; }

  void HasLost() { has_lost_ = true; }

  int GetScore() { return score_; }

  void Init();

  void CreateOpponents();

  void CreateOpponentProjectiles();

  void CreatePlayerProjectiles();

  void MoveGameElements();

  void FilterIntersections();

  void UpdateScreen();

  void Start();

  void OnMouseEvent(const graphics::MouseEvent& event) override;

  void OnAnimationStep() override;

  void LaunchProjectiles();

  void RemoveInactive();

 private:
  graphics::Image game_screen_;
  std::unique_ptr<Opponent> opponents_;
  std::unique_ptr<OpponentProjectile> opponent_projectiles_;
  std::unique_ptr<PlayerProjectile> player_projectiles_;
  Player my_player_;
  int score_;
  bool has_lost_ = false;
};

#endif
