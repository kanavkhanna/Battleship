// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <battleship/Location.h>
#include <battleship/board.h>
#include <battleship/direction.h>
#include <battleship/engine.h>
#include <battleship/leaderboard.h>
#include <battleship/player.h>
#include <choreograph/Choreograph.h>
#include <cinder/app/App.h>
#include <magicwindow.h>

namespace myapp {

enum class GameState {
  kPlaying,
  kGameOver,
};

class MyApp : public cinder::app::App {
 private:
  vector<battleship::Location> locations1_;
  vector<battleship::Location> locations2_;
  battleship::Engine player1_;
  battleship::Engine player2_;
  battleship::Board gameBoard_;
  vector<battleship::Direction> shipDirections1_;
  vector<battleship::Direction> shipDirections2_;
  std::chrono::time_point<std::chrono::system_clock> last_intact_time_;
  std::chrono::time_point<std::chrono::system_clock> last_pause_time_;
  std::chrono::time_point<std::chrono::system_clock> last_time_;
  battleship::LeaderBoard leaderboard_;
  bool paused_;
  bool isPlayer1Turn = true;
  bool isPlayer2Turn = false;
  const std::string player_name_;
  bool printed_game_over_;
  const size_t size_;
  const size_t speed_;
  GameState state_;
  const size_t tile_size_;
  size_t time_left_;
  std::vector<battleship::Player> top_players_;
  std::vector<battleship::Player> current_player_info_;

 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  //void mouseMove(cinder::app::MouseEvent) override;
  //void mouseDrag(cinder::app::MouseEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;


  void ResetGame();

  void DrawBackground();

  template <typename C>
  void PrintText(const string& text, const C& color, const glm::ivec2& size,
                 const glm::vec2& loc);

  void DrawGameOver();
  void DrawScoreBoard();

  void DrawShips();

  void DrawMap();

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
