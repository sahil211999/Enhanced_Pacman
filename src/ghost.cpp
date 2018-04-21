#include <stdlib.h>
#include "ghost.h"

// Adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
Ghost::Ghost() {    
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    
    generator_ = std::mt19937(rand());
    dist_x_ = std::uniform_int_distribution<>(0, maze_.kMazeWidth_ - 1); // inclusive on both ends - needs index
    dist_y_ = std::uniform_int_distribution<>(0, maze_.kMazeHeight_ - 1);
    dist_directions_ = std::uniform_int_distribution<>(0, kNumDirections_ - 1);

    ghost_image_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/image_files/ghost.png"); // loading image
}

void Ghost::SetInitialRandomPosition() { // intial random pos
    auto x = dist_x_(generator_);
    auto y = dist_y_(generator_);
    
    maze_position_.set(x, y);
}

// Method adapted and modified from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
void Ghost::resize(int w, int h) {
    //one_d_size_ = kFoodModifier * w;
    //image_frame_.setSize(size_d, size_d);
    
    //float new_x = ((image_frame_.getWidth() / window_dims_.x) * w);
    //float new_y = ((image_frame_.getHeight() / window_dims_.y) * h);
    //float new_x = ((k1DSize_ / window_dims_.x) * w); // x and y shouldn't change if they represent the position of the element on the map rather than the actual coordinates
    //float new_y = ((k1DSize_ / window_dims_.y) * h);

    //image_frame_.setPosition(new_x, new_y);
    
    //dist_x_ = std::uniform_int_distribution<>(0, w - k1DSize_); // shouldn't change
    //dist_y_ = std::uniform_int_distribution<>(0, h - k1DSize_);
    window_dims_.set(w, h);
}

ofVec2f Ghost::GetMazePosition() {
    return maze_position_;
}

ofImage& Ghost::get_ghost_image() {
    return ghost_image_;
}

int Ghost::get_num_steps_taken() { // gets the number of steps taken
    return num_steps_taken_;
}

void Ghost::incr_num_steps_taken() { // increments the number of steps taken
    num_steps_taken_++;
}

Direction& Ghost::get_direction() { // gets the current direction - needed to check whether the ghost is eating the pacman or if the pacman is eating the ghost
    return current_direction_;
}

bool Ghost::is_valid_position(ofVec2f& position) {// checks if new position is valid
    return (position.x >= 0 && position.y >= 0 && position.x < maze_.kMazeWidth_ && position.y < maze_.kMazeHeight_);
}

ofVec2f& Ghost::calculate_new_position(Direction direction) { // calculates the new position and returns a pair represententing the position
    ofVec2f new_position;
    
    int x = maze_position_.x;
    int y = maze_position_.y;
    
    switch (current_direction_) {
    case UP:
        if (y - 1 >= 0) {
            new_position.set(x, y - 1);
        }
        break;
    case DOWN:
        if (y + 1 < maze_.kMazeHeight_) {
            new_position.set(x, y + 1);
        }
        break;
    case LEFT:
        if (x - 1 >= 0) {
            new_position.set(x - 1, y);
        }
        break;
    case RIGHT:
        if (x + 1 < maze_.kMazeWidth_) {
            new_position.set(x + 1, y);
        }
        break;
    }
    return new_position;
}

void Ghost::choose_random_direction() { // valid position - can take at least 1 step in that direction
    Direction random_direction;
    ofVec2f new_location;
    new_location.set(-1, -1);
    
    while (!is_valid_position(new_location)) { // while position isn't valid
        //random_direction = static_cast<Direction>(rand() % kNumDirections_); // 1 of the 4 real direction
        random_direction = static_cast<Direction>(dist_directions_(generator_)); // 1 of the 4 real direction
        new_location = calculate_new_position(random_direction);
    }
    current_direction_ = random_direction;
}

void Ghost::move_in_new_direction() { // need to figure out what to do if the ghost becomes stuck
    ofVec2f new_position = calculate_new_position(current_direction_);
    
    if (is_valid_position(new_position)) {
        maze_position_.set(new_position.x, new_position.y);
    }
}
