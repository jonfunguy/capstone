#pragma once

#include <raylib-cpp.hpp>
#include <gameobject.h>

namespace game {

namespace rl = raylib;

/**
 * @class Platform
 * @brief A class extending GameObject that handles platforms in the game
 *
 */
    class Platform:public GameObject {
        public:
        Platform(rl::Vector2 position, rl::Vector2 dimensions, rl::Color color);
        void Draw() override;
        void Draw(float scale);
        void Update() override;
        private:
            rl::Color color_;
            rl::Vector2 dimensions_;
    };
}