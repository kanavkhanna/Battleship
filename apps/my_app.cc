// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>


namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
    window.initialize();
}

void MyApp::update() { }

void MyApp::draw() {
    window.draw();

}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
