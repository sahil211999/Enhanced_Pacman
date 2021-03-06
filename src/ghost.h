#pragma once
#include <random>

#include "direction.h"
#include "ofMain.h"
#include "maze.h"

class Ghost {
private:
    // FOR GENERATING RANDOM DIRECTIONS
    // Next 2 lines adapted from OF-SNAKE MP (Food class): https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
    ofVec2f window_dims_;
    std::mt19937 generator_; // pseudorandom number generation
    
    // DIRECTIONS
    static const int kNumDirections_ = 4; // number of real directions, to exclude dummy direction
    Direction current_direction_ = EAST; // starts off going right
    int num_rotations_; // keeps track of the number of rotations needed

    // LOCATION
    int num_steps_taken_ = 0; // keeps track of the number of steps taken in the current direction
    ofVec2f maze_position_; // x, y position of the maze
        // important: this corresponds to the MAZE ELEMENT and NOT to the actual coordinates in the
        // coordinatep lane.
    
    // GHOST IMAGE
    ofImage ghost_image_; // image that correpsonds with a ghost object
    static const std::string kImagePath_;
        
public:
    static const int kNumStepsBeforeDirectionChange_ = 30; // number of steps to take in the new
        // direction before changing direction. Note that this is used in ofApp so each step can be
        // drawn out (else the ghost would jump around)
    static const int kPointsWorth_ = 10; // worth 10 points
    
    Ghost(); // Default constructor
    
    // GETTERS AND SETTERS
    void SetDirection(Direction newDirection);
    ofVec2f& GetMazePosition();
    ofImage& GetGhostImage(); // gets image
    int GetNumStepsTaken(); // gets the number of steps taken
    void IncrNumStepsTaken(); // increments the number of steps taken
    Direction GetDirection(); // gets the current direction - needed to check whether the ghost
        // is eating the pacman or if the pacman is eating the ghost
    int GetNumRotations(); // returns the number of rotations
    
    // KEEPS TRACK OF ROTATIONS - note that rotating the ghosts means that the new direction must
    // be returned first (to calculate the rotations needed) and thus cannot just be set
    void CalculateNumRotations(Direction new_direction); // calculates the number of clockwise 90 degree rotations needed
    void ClearNumRotations(); // sets num rotations back to 0, must be called each time an object

    // CALCULATING RANDOM DIRECTION AND MOVING IN IT
    void Update();
    Direction FindRandomDirection(); // finds new direction - note that this returns a direction
        // because the new direction and the old direction are both needed to calculate the number
        // of rotations
    void SetPosition(int x_pos, int y_pos); // Sets the maze position to the corresponding x and
        // y coords. Note that this method doesn't check if the new position is valid.

    void resize(int w, int h); // Called by application resize, resizes to new window dimensions
};

