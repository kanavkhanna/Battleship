// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>


namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() { }

void MyApp::update() { }

void MyApp::draw() {
    auto box = b2Draw();
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
