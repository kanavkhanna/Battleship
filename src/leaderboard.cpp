//
// Created by Kanav Khanna on 4/26/20.
//

#include "battleship/leaderboard.h"

namespace battleship {
using std::string;
using std::vector;


LeaderBoard::LeaderBoard(const string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists leaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";
}

void LeaderBoard::AddScoreToLeaderBoard(const Player& player) {
  db_ << "INSERT INTO leaderboard(name, score) VALUES (?,?);"
      <<player.name
      <<player.score;
}

vector<Player> GetPlayers(sqlite::database_binder* rows) {
  vector<Player> players;

  for (auto&& row : *rows) {
    string name;
    size_t score;
    row >> name >> score;
    Player player = {name, score};
    players.push_back(player);
  }

  return players;
}

vector<Player> LeaderBoard::RetrieveHighScores(const size_t limit) {
  auto rows = db_ << "SELECT name,score from leaderboard order by score desc limit ?;"
                  <<limit;
  return GetPlayers(&rows);
}

vector<Player> LeaderBoard::RetrieveHighScores(const Player& player,
                                               const size_t limit) {
  auto rows = db_ << "select name,score from leaderboard where name = ? order by score desc limit ?;"
                  <<player.name<<limit;
  return GetPlayers(&rows);
}

}