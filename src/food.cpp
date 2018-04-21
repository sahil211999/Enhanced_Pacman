//
//  food.cpp
//  final-project-ElizWang
//
//  Created by Elizabeth Wang on 4/19/18.
//

#include <stdlib.h>
#include "food.h"

const float Food::kfood_modifier_ = 0.1;

// Adapted from OF-SNAKE MP (SnakeFood class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
Food::Food() {
    int window_width = ofGetWindowWidth();
    int window_height = ofGetWindowHeight();
    window_dims_.set(window_width, window_height);
    //float size_d = kfood_modifier_ * window_width;
    one_d_size_ = kfood_modifier_ * window_width;
    //image_frame_.setSize(size_d, size_d);
    
    generator_ = std::mt19937(rand());
    dist_x_ = std::uniform_int_distribution<>(0, kMazeWidth_);
    dist_y_ = std::uniform_int_distribution<>(0, kMazeHeight_);

    food_image_.load("/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/image_files/apple.png");
    rebase();
}

void Food::resize(int w, int h) {
    //float size_d = kfood_modifier_ * w;
    one_d_size_ = kfood_modifier_ * w;
    //image_frame_.setSize(size_d, size_d);
    
    float new_x = ((kMazeWidth_ / window_dims_.x) * w);
    float new_y = ((kMazeHeight_ / window_dims_.y) * h);
    //image_frame_.setPosition(new_x, new_y);
    maze_position_.set(new_x, new_y);
    
    dist_x_ = std::uniform_int_distribution<>(0, w - one_d_size_);
    dist_y_ = std::uniform_int_distribution<>(0, h - one_d_size_);
    window_dims_.set(w, h);
    
    rebase();
}

void Food::rebase() {
    auto x = dist_x_(generator_);
    auto y = dist_y_(generator_);
    //image_frame_.setPosition(x, y);
    maze_position_.set(x, y);
}

ofVec2f& Food::GetMazePosition() {
    return maze_position_;
}

/*ofRectangle& Food::get_image_frame() {
    return image_frame_;
}*/

ofImage& Food::get_food_image() {
    return food_image_;
}

int Food::Get1DSize() {
    return one_d_size_;
}
