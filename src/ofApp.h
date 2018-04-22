#pragma once
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <utility>

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

#include "maze.h"
#include "pacman.h"
#include "ghost.h"
#include "food.h"

// LOOSELY adapted from OF-SNAKE MP: https://github.com/uiuc-sp18-cs126/of-snake-ElizWang (mostly just structural stuff)

class PacmanGame : public ofBaseApp {
private:
    // Enum to represent the current state of the game
    enum GameState {
        NOT_STARTED = 0,
        TAKING_PHOTO,
        DISPLAYING_PHOTO,
        IN_PROGRESS,
        PAUSED,
        FINISHED
    };
    
    // SOUND PATHS
    std::string kIntroMusicPath_ = "/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/sound_files/intro_music.mp3";
    std::string kPacmanEating_ = "/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/sound_files/eating_sound.mp3";
    std::string kDeathSoundPath_ = "/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/sound_files/wilhelmscream.mp3";
    std::string kDemoMoviePath_ = "/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/demos/raw_screencast_demo.mov";
    
    // MISC PATHS
    std::string kTextPath_ = "/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/font_files/square_block.ttf";
    std::string kFoodImagePath_ = "/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/image_files/apple.png";
    std::string kFacialCascadePath_ = "/Users/elizabeth/CS126-FINAL-PROJECT/final-project-ElizWang/bin/data/haar_cascades/haarcascade_frontalface_alt.xml";
    
    // ALL SOUNDS
    ofSoundPlayer intro_music_; // plays music
    ofSoundPlayer pacman_death_sound_; // wilhem scream
    ofSoundPlayer pacman_eating_sound_; // cartoonish crunch
    
    // FOR INTRODUCTION PANEL
    ofTrueTypeFont string_font_; // sets font, used to print strings with colors/sizes/fonts other than the default
    GameState current_state_ = NOT_STARTED; // The current state of the game, used to determine possible actions
    ofVideoPlayer demo_movie_; // demo of what the game looks like
    
    // EVERYTHING TO DO WITH THE WEBCAM (,taking photos, and the general UI)
    ofxButton photo_taking_button_; // button to press to take the photo
    ofxButton face_approval_button_; // button to press to set face as sprite and move on to the game
    ofVideoGrabber webcam_; // turns on webcam and gets webcam video feed
    ofImage photo_taken_; // stores the photo taken
    bool show_webcam_ = true; // to show the webcam
    
    // FACIAL DETECTION
    ofxCvHaarFinder facial_detector_; // finds faces
    ofxCvColorImage temp_color_img; // temp color img
    ofxCvGrayscaleImage grayscale_img_; // need to convert from regular iamge to ofxCvColorImage to ofxCvGrayscaleImage in order to use the haar cascader
    
    // OBJECTS
    Maze maze_; // object that stores the maze, created a class for this to protect the maze from being modified and to allow the other objects to access the maze (to check for valid positions)
    Pacman game_pacman_; // The object that represents the user controlled snake
    std::vector<Ghost> all_ghosts_;
    const int kNumGhosts_ = 10;

    // OBJECT PROPERTIES - CONSTANTS
    const int kNumFoodItems_ = 10; // 10 food items to put in map - can change
    const int kOneDObjectSize_ = 20; // standardized size for all the objects (to prevent the bigger ones from "leaving" the maze)
    
    // MULTIPLIERS - convert coordinates on the maze matrix to coordinates on a coordinate plane
    float coord_multiplier_x_;
    float coord_multiplier_y_;
    const int kFoodPointsWorth_ = 1; // how many points a food object is worth
    
    bool should_update_ = true;     // A flag boolean used in the update() function.
    
    // METHODS
    // FOR INTRODUCTIONARY PARTS
    void PhotoButtonPressed(); // listener - takes photo when button is pressed
    void ApprovalButtonPressed(); // listener - sets face as sprite and moves on to the game when button is pressed
    void DetectFacesInPhoto(); // use haar cascade to detect faces
    
    // FACIAL PROCESSING
    void SetFaceAsPacman(); // cuts the face out and uses it as pacman

    // COLLISIONS
    void ManageObjectCollisons(); // contains logic for objects eating each other rename later
    void ManagePacmanGhostCollisions(Ghost& current_ghost); // interactions between the pacman and the ghost
    
    // METHODS FOR RENDERING
    void DrawIntroduction();
    void DrawWebcamUI();
    void DrawFacialDetectionPhoto();
    void DrawFood(int x_index, int y_index);
    void DrawMaze();
    void DrawGhosts();
    void DrawPacman();
    void DrawScoreboard();
    void DrawGameOver();
    void DrawGamePaused();
    
    // Resets the game objects to their original state.
    void Reset();
    
public:
    // Function used for one time setup
    void setup();
    
    // Main event loop functions called on every frame
    void update();
    void draw();
    
    // Event driven functions, called on appropriate user action
    void keyPressed(int key);
    void windowResized(int w, int h);
    void mousePressed(int x, int y, int button);
};


