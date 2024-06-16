#include "headers/App.hpp"

App::App() {
}

App::~App() {
}

void App::update() {

}
void App::render() {

}
void App::end() {
    this->console->~Console();

}
void App::start() {
    this->console = new Console();
}