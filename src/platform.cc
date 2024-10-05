#include "platform.h";

namespace game {

    Platform::Platform(rl::Vector2 position, rl::Vector2 dimensions, rl::Color color)
    :GameObject(position), dimensions_(dimensions), color_(color){ SetDimensions(dimensions_); }

    void Platform::Draw() { Draw(1.0F); }

    void Platform::Draw(float scale){
        float width = dimensions_.x * scale;
        float height = dimensions_.y * scale;
        rl::Rectangle rect = {position_.x, position_.y, width, height};
        rect.Draw(color_);
    }
    
    void Platform::Update(){};
}