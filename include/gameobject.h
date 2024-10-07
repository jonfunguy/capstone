#pragma once

#include <raylib-cpp.hpp>

namespace game {

namespace rl = raylib;

/**
 * @class GameObject
 * @brief A drawable and updatable game object. Base class for everything in the
 * game.
 *
 */
class GameObject {
public:
    GameObject(const rl::Vector2& position);
    GameObject(float x, float y);
    
    virtual ~GameObject() = default;

    /* Draw function needs to be changed so that it takes a float value named scale. 
     Currently the list of game objects that are looped through to be drawn in game.cc are not drawn to proper scale. */
    virtual void Draw() = 0;
    virtual void Update() = 0;

    inline auto GetPosition() const -> const rl::Vector2& { return position_; }
    inline void SetPosition(const rl::Vector2& position) {
        position_ = position;
    }

    inline auto GetPositionX() const -> float { return position_.x; }
    inline auto GetPositionY() const -> float { return position_.y; }
    // added get x and y dimensions functions
    float GetDimensionsX() { return dimensions_.x; }
    float GetDimensionsY() { return dimensions_.y; }
    // added get x and y velocity functions
    float GetVelocityY() { return velocity_y;}
    float GetVelocityX() { return velocity_x;}

    inline void SetPosition(float x, float y) { position_ = rl::Vector2{x, y}; }
    inline void SetPositionX(float x) { position_.x = x; }
    inline void SetPositionY(float y) { position_.y = y; }
    // added set dimensions function
    void SetDimensions(rl::Vector2 newDimensions){ dimensions_ = newDimensions; }
    // Added set x and y velocity functions
    void SetVelocityX(float newVelocity){ velocity_x = newVelocity; }
    void SetVelocityY(float newVelocity){ velocity_y = newVelocity; }
    

protected:
    rl::Vector2 position_;
    rl::Vector2 dimensions_ = {0,0};
    // Added 2 variables for every game object, x and y velocity 
    float velocity_y = 0;
    float velocity_x = 0;
};

/**
 * @class Textured
 * @brief A textured game object.
 *
 */
class Textured : virtual public GameObject {
public:
    Textured(rl::Texture&& texture) : texture_{std::move(texture)} {}
    Textured(const rl::Vector2& position, rl::Texture&& texture)
        : GameObject(position), texture_{std::move(texture)} {}

protected:
    rl::Texture texture_;
};

/**
 * @class Moveable
 * @brief A moveable game object.
 *
 */
class Moveable : virtual public GameObject {
public:
    Moveable() = default;

    enum class Direction { kUp, kDown, kLeft, kRight };

    virtual void Move(Direction direction) = 0;
};

}  // namespace game
