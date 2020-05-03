// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <random>
#include <string>
#include <time.h>
#include <gflags/gflags.h>

namespace myapp {
const size_t kMaxShips = 5;
const size_t kMaxAttackChances = 5;

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;

const size_t kLimit = 3;
const char kDbPath[] = "project.db";

const char kNormalFont[] = "Papyrus";

DECLARE_uint32(size);
DECLARE_uint32(tilesize);
DECLARE_uint32(speed);
DECLARE_string(name1);
DECLARE_string(name2);


MyApp::MyApp()
    : player1_{FLAGS_name1,FLAGS_size,FLAGS_size,FLAGS_tilesize},
      player2_{FLAGS_name2,FLAGS_size,FLAGS_size,FLAGS_tilesize},
      leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
      paused_{false},
      printed_game_over_{false},
      size_{FLAGS_size},
      state_{GameState::kWelcome},
      tile_size_{FLAGS_tilesize},
      gameBoard_(FLAGS_tilesize, 27) {}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() {
  if (state_ == GameState::kGameOver) {
    leaderboard_.AddScoreToLeaderBoard({winner_name_, leaderboard_.RetrievePlayerScore(winner_name_)});
    top_players_ = leaderboard_.RetrieveHighScores(kLimit);
    current_player_info_ = leaderboard_.RetrieveHighScores({winner_name_, leaderboard_.RetrievePlayerScore(winner_name_)},kLimit);
    // It is crucial the this vector be populated, given that `kLimit` > 0.
    assert(!top_players_.empty());
    return;
  }

  if (paused_) return;

  const auto time = system_clock::now();


  if (isPlayer1Turn) {
    if ((shipLocations_.size() == kMaxShips && shipDirections_.size() == kMaxShips)
        || attackLocations_.size() == kMaxAttackChances)
      PlayerTask(player1_,player2_);

  } else if (isPlayer2Turn) {
    if ((shipLocations_.size() == kMaxShips && shipDirections_.size() == kMaxShips)
        || attackLocations_.size() == kMaxAttackChances)
      PlayerTask(player2_,player1_);
  }
}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  if (state_ == GameState::kGameOver) {
    if (!printed_game_over_) cinder::gl::clear(Color(0, 0, 0));
    DrawGameOver();
    return;
  }
  if (state_ == GameState::kWelcome) {
    DrawWelcomeScreen();
  }

  if (state_ == GameState::kPlaying) {
    if (paused_) return;


    if (isPlayer1Turn)
      PlayerDraw(player1_,player2_);

    if (isPlayer2Turn)
      PlayerDraw(player2_,player1_);
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_k:
    case KeyEvent::KEY_w: {
      shipDirections_.emplace_back(battleship::Direction::kUp);
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_j:
    case KeyEvent::KEY_s: {
      shipDirections_.emplace_back(battleship::Direction::kDown);
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_h:
    case KeyEvent::KEY_a: {
      shipDirections_.emplace_back(battleship::Direction::kLeft);
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_l:
    case KeyEvent::KEY_d: {
      shipDirections_.emplace_back(battleship::Direction::kRight);
      break;
    }
    case KeyEvent::KEY_p: {
      paused_ = !paused_;

      if (paused_) {
        last_pause_time_ = system_clock::now();
      } else {
        last_intact_time_ += system_clock::now() - last_pause_time_;
      }
      break;
    }
    case KeyEvent::KEY_m: {
      if (state_ == GameState::kWelcome)
        state_ = GameState::kPlaying;
      else {
        paused_ = !paused_;

        if (paused_) {
          last_pause_time_ = system_clock::now();
        } else {
          last_intact_time_ += system_clock::now() - last_pause_time_;
        }
        DrawWelcomeScreen();
      }
      break;
    }
    case KeyEvent::KEY_0: {
      paused_ = !paused_;

      if (paused_) {
        last_pause_time_ = system_clock::now();
      } else {
        last_intact_time_ += system_clock::now() - last_pause_time_;
      }
      DrawScoreBoard();
      break;
    }
    case KeyEvent::KEY_r: {
      ResetGame();
      break;
    }
    case KeyEvent::KEY_2: {
      isPlayer1Turn = !isPlayer1Turn;
      isPlayer2Turn = !isPlayer2Turn;
      break;
    }
    case KeyEvent::KEY_4: {
      if (isPlayer1Turn) {
        player1_.showAttackLocs_ = !player1_.showAttackLocs_;
        player1_.SetShipMapCreated(!player1_.IsShipMapCreated());
      } else if (isPlayer2Turn) {
        player2_.showAttackLocs_ = !player2_.showAttackLocs_;
        player2_.SetShipMapCreated(!player2_.IsShipMapCreated());
      }
    }
  }
}



void MyApp::ResetGame() {
  player1_.Reset();
  player2_.Reset();
  paused_ = false;
  printed_game_over_ = false;
  state_ = GameState::kPlaying;
  top_players_.clear();
  current_player_info_.clear();
  shipDirections_.clear();
  shipLocations_.clear();
  attackLocations_.clear();
}

void MyApp::DrawBackground() {
  cinder::gl::TextureRef texture = cinder::gl::Texture2d::create
      (cinder::loadImage("/Users/kanavkhanna/Downloads"
      "/cinder_0.9.2_mac/my-projects/final-project-kanavk26/assets/background.jpg"));

  cinder::gl::clear();
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthRead();
  cinder::gl::enableAlphaBlending();
  cinder::gl::color(Color::white());

  cinder::gl::setMatricesWindow( getWindowSize() );
  Rectf drawRect( 0, 0, texture->getWidth()/7,
                  texture->getHeight()/5);

  cinder::gl::draw( texture, drawRect );
}

template <typename C>
void MyApp::PrintText(const string& text, const C& color,
                      const glm::ivec2& size, const glm::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawGameOver() {
  // Lazily print.
  if (printed_game_over_) return;
  if (top_players_.empty()) return;
  if (current_player_info_.empty()) return;

  DrawBackground();
  const cinder::vec2 topScoresLoc = {getWindowCenter().x, getWindowCenter().y-350};
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();

  PrintText("Game Over :(", color, size, topScoresLoc);
  DrawScoreBoard();

  printed_game_over_ = true;
}

void MyApp::DrawScoreBoard() {
  const cinder::vec2 topScoresLoc = {getWindowCenter().x, getWindowCenter().y-300};
  const cinder::vec2 playerScoresLoc = {getWindowCenter().x, getWindowCenter().y};
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();

  size_t rowTopScore = 0;
  PrintText("Top scores", color, size, topScoresLoc);
  for (const battleship::Player& player : top_players_) {
    std::stringstream ss;
    ss << player.name << " - " << player.score;
    PrintText(ss.str(), color, size, {topScoresLoc.x, topScoresLoc.y + (++rowTopScore) * 50});
  }

  size_t rowCurrPlayer = 0;
  PrintText("Current Player Scores", color, size, playerScoresLoc);
  for (const battleship::Player& player : current_player_info_) {
    std::stringstream ss;
    ss << player.name << " - " << player.score;
    PrintText(ss.str(), color, size, {playerScoresLoc.x, playerScoresLoc.y + (++rowCurrPlayer) * 50});
  }
}

void MyApp::mouseDown(cinder::app::MouseEvent event) {
  if (isPlayer1Turn) {
    if (!player1_.IsShipMapCreated() && shipLocations_.size() < kMaxShips) {
      shipLocations_.emplace_back(event.getX(),event.getY());
    }
    if (attackLocations_.size() < kMaxAttackChances && player1_.showAttackLocs_) {
      attackLocations_.emplace_back(event.getX(),event.getY());
    }
  } else if (isPlayer2Turn) {
    if (!player2_.IsShipMapCreated() && shipLocations_.size() < kMaxShips) {
      shipLocations_.emplace_back(event.getX(), event.getY());
    }
    if (attackLocations_.size() < kMaxAttackChances && player2_.showAttackLocs_) {
      attackLocations_.emplace_back(event.getX(), event.getY());
    }
  }
}

void MyApp::PlayerTask(battleship::Engine& player, battleship::Engine& opponent) {
  if (shipLocations_.size() == kMaxShips && shipDirections_.size() == kMaxShips) {
    player.SetShips(shipLocations_, shipDirections_);
    player.SetShipMapCreated(true);
    shipLocations_.clear();
    shipDirections_.clear();

  } else if (attackLocations_.size() == kMaxAttackChances) {
    player.Attack(attackLocations_, opponent.battleships_);
    attackLocations_.clear();
  }
  if (opponent.IsGameOver()) {
    state_ = GameState::kGameOver;
    winner_name_ = player.player_name_;
  }
}
void MyApp::PlayerDraw(battleship::Engine& player, battleship::Engine& opponent) {
  cinder::gl::clear();
  DrawBackground();
  PrintText(player.player_name_,Color::white(),{700, 50},getWindowCenter());
  player.DrawMap();

  if (player.IsShipMapCreated() || !player.showAttackLocs_) {
    player.DrawShips();
    player.SetShipMapCreated(false);
  } else if (player.showAttackLocs_) {
    player.DrawMissile();

    for (battleship::Ship& ship : opponent.battleships_) {
      if (ship.IsDestroyed()) {
        vector<battleship::Location> locations = ship.ShipLocation();
        for (battleship::Location& location : locations) {
          cinder::gl::color(cinder::Color(0,1,1));
          battleship::Location loc = gameBoard_.LocationOnBoard(location);
          loc = loc.GetCenter();
          cinder::gl::drawSolidCircle({loc.Row(), loc.Col()}, 15);
        }
      }
    }
  }
}

void MyApp::DrawWelcomeScreen() {
  cinder::gl::clear();
  DrawBackground();
  PrintText("Welcome to Battleship Royale!", Color::white(),{600, 50},{getWindowCenter().x, getWindowCenter().y-300});

  string text = "The game is simple: You have to destory your opponent's ships "
      "before they destroy yours. Each player has 5 ships and 5 attack chances per chance. "
      "To setup your ships, simply click on the starting location you desire, "
      "and specify the direction of the ship using the arrow keys. To choose the attacking position, "
      "just click on the box you want. \n To swtich between players, use key 2, for attack mode and ship mode, use key 4. "
      "Press p to pause, r to reset game, or 0 for scores"
      "\nBest of luck! \n Press m when ready.";
  PrintText(text, Color::white(),{800, 500},getWindowCenter());
}

}  // namespace myapp
