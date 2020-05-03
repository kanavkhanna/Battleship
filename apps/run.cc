// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <gflags/gflags.h>
#include "my_app.h"


using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {
DEFINE_uint32(size, 10, "the number of tiles in each row and column");
DEFINE_uint32(tilesize, 30, "the size of each tile");
DEFINE_uint32(speed, 50, "the speed (delay) of the game");
DEFINE_string(name1, "Player 1", "the name of the player");
DEFINE_string(name2, "Player 2", "the name of the player");

const int kSamples = 8;
const int kWidth = 805;
const int kHeight = 900;

void ParseArgs(vector<string>* args) {
  gflags::SetUsageMessage(
      "Play a game of Snake. Pass --helpshort for options.");
  int argc = static_cast<int>(args->size());

  vector<char*> argvs;
  for (string& str : *args) {
    argvs.push_back(&str[0]);
  }

  char** argv = argvs.data();
  gflags::ParseCommandLineFlags(&argc, &argv, true);
}


void SetUp(App::Settings* settings) {
  vector<string> args = settings->getCommandLineArgs();
  ParseArgs(&args);
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("My CS 126 Application");
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
