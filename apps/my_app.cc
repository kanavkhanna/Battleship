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

namespace myapp {
const size_t kMaxShips = 5;
const size_t kShipSize = 7;

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;

const double kRate = 25;
const size_t kLimit = 3;
const char kDbPath[] = "project.db";

const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";


MyApp::MyApp()
    : player_{10,10,30},
      leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
      paused_{false},
      player_name_{"FLAGS_name"},
      printed_game_over_{false},
      size_{10},
      speed_{50},
      state_{GameState::kPlaying},
      tile_size_{30},
      time_left_{0},
      gameBoard_(30, 27) {}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() {
  if (state_ == GameState::kGameOver) {
    leaderboard_.AddScoreToLeaderBoard({player_name_, 0});
    top_players_ = leaderboard_.RetrieveHighScores(kLimit);
    current_player_info_ = leaderboard_.RetrieveHighScores({player_name_, 0},kLimit);
    // It is crucial the this vector be populated, given that `kLimit` > 0.
    assert(!top_players_.empty());
    return;
  }

  if (paused_) return;

  const auto time = system_clock::now();

  //setting up random distribution for ship size
  std::random_device rd;
  std::mt19937 e2(rd());
  std::uniform_real_distribution<> dist(3, 10);
  int ship_size = dist(e2);

  vector<battleship::Ship> battleships;
  if (locations_.size() == kMaxShips && shipDirections_.size() == kMaxShips) {
    for (int i = 0 ; i< locations_.size(); i++) {
      battleships.emplace_back(battleship::Ship(kShipSize,locations_.at(i), shipDirections_.at(i)));
    }
    player_.battleships_ = battleships;
    player_.SetShipMapCreated(true);
  }
}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  if (state_ == GameState::kGameOver) {
    if (!printed_game_over_) cinder::gl::clear(Color(1, 0, 0));
    DrawGameOver();
    return;
  }

  if (paused_) return;


  cinder::gl::clear();
  DrawBackground();
  player_.DrawMap();

  if (player_.IsShipMapCreated())
    player_.DrawShips();


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
      paused_ = !paused_;

      if (paused_) {
        last_pause_time_ = system_clock::now();
      } else {
        last_intact_time_ += system_clock::now() - last_pause_time_;
      }
      const cinder::ivec2 size = {700, 50};
      const Color color = Color::white();
      PrintText("Press p to pause, r to reset game, or 0 for scores",color,size,getWindowCenter());
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
  }
}



void MyApp::ResetGame() {
  player_.Reset();
  paused_ = false;
  printed_game_over_ = false;
  state_ = GameState::kPlaying;
  time_left_ = 0;
  top_players_.clear();
}

void MyApp::DrawBackground() {
  cinder::gl::clear(Color(0, 0, 0));
  /*cinder::gl::TextureRef texture = cinder::gl::Texture2d::create
      (cinder::loadImage("/Users/kanavkhanna/Downloads"
      "/cinder_0.9.2_mac/my-projects/final-project-kanavk26/assets/board.jpg"));
  cinder::Area destRect = texture->getBounds();
  destRect.x2 *= 300;
  destRect.y2 *= 300;

  float decentMod = 10;

  cinder::gl::color( Color::white() );

  cinder::gl::ScopedModelMatrix modelScope;
  cinder::gl::translate( 0, decentMod * 0.5f );

  cinder::gl::draw( texture, destRect, destRect );
  //cinder::gl::draw(texture);*/
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

  const cinder::vec2 topScoresLoc = {getWindowCenter().x, getWindowCenter().y-300};
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::white();

  size_t rowTopScore = 0;
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

void MyApp::DrawShips() {
  cinder::gl::color(Color(1,0,0));
  /*for (battleship::Location& location : locations_) {
    battleship::Location loc = gameBoard_.LocationOnBoard(location);
    loc = loc.GetCenter();
    cinder::gl::drawSolidCircle({loc.Row(),loc.Col()}, 10);
  }*/

  for (battleship::Ship& ship : player_.battleships_) {
    for (battleship::Location& location : ship.ShipLocation()) {
      battleship::Location loc = gameBoard_.LocationOnBoard(location);
      loc = loc.GetCenter();
      cinder::gl::drawSolidCircle({loc.Row(), loc.Col()}, 10);
    }
  }
}

void MyApp::DrawMap() {
  for (int i = 0; i < gameBoard_.BoardSize(); i++) {
    for (int j = 0; j < gameBoard_.BoardSize(); j++) {
      cinder::gl::color(Color::white());
      battleship::Location loc = battleship::Location(i,j);
      loc = loc.GetCenter();
      cinder::gl::drawLine({tile_size_*i,tile_size_*j}, {(i)*tile_size_,(j+1)*tile_size_});
      cinder::gl::drawLine({tile_size_*i,tile_size_*j}, {(i+1)*tile_size_,(j)*tile_size_});
      cinder::gl::drawSolidRect(Rectf((loc.Row()-5),
                                      (loc.Col()-5),
                                      (loc.Row()-5) +10,
                                      (loc.Col()-5) + 10));
    }
  }
}
void MyApp::mouseDown(cinder::app::MouseEvent event) {

  if (!player_.IsShipMapCreated()) {
    locations_.emplace_back(event.getX(),event.getY());
  }

}

}  // namespace myapp
