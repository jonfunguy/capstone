#include "game.h"

namespace game {
/**
 * @brief Handle keyboard events, for example arrow keys, space bar, etc.
 */
void Game::HandleKeyboardEvents() {
    if (IsKeyDown(KEY_A)) {
        bg_source_rec_.x -= 10;
        bg_dest_rec_.x -= 10;

        if (camera_.Mode() == Camera::Mode::kFixed &&
            player_->GetPositionX() > bg_dest_rec_.x) {
            camera_.SubtractOffsetX(10.0f);
            player_->SetPositionX(player_->GetPositionX() - 10);
        }
    }
    if (IsKeyDown(KEY_D)) {
        bg_source_rec_.x += 10;
        bg_dest_rec_.x += 10;

        if (camera_.Mode() == Camera::Mode::kFixed &&
            player_->GetPositionX() <
                bg_dest_rec_.x + bg_dest_rec_.width - 128) {
            camera_.AddOffsetX(10.0f);
            player_->SetPositionX(player_->GetPositionX() + 10);
        }
    }
    //Basic jump has been added. We add negative y veloicty to make the player jump up.
    if (IsKeyDown(KEY_SPACE)) {
        player_->SetVelocityY(-20.0f);
    }
    if (IsKeyDown(KEY_UP)) {
        if (camera_.Zoom() > 2.0f) {
            return;
        }
        camera_.AddZoom(0.1F);
    } else if (IsKeyDown(KEY_DOWN)) {
        if (camera_.Zoom() < 0.4f) {
            return;
        }
        camera_.SubtractZoom(0.1F);
    }
    if (IsKeyPressed(KEY_F)) {
        camera_.ToggleMode();
    }
    CorrectPlayerPosition();
}

/**
 * @brief Handles collisions between game objects
 */
void Game::HandleCollisions() {
    for (int i = 0; i < game_objects_.size(); i++) {
        // If the object's left side is less than than the player's right side
        if (game_objects_[i]->GetPositionX() < player_->GetPositionX() + player_->GetDimensionsX() &&
        // and the object's right side is greater than the player's left side 
         game_objects_[i]->GetPositionX() + game_objects_[i]->GetDimensionsX() > player_->GetPositionX() &&
        // and the object's top side is less than the player's bottom side
         game_objects_[i]->GetPositionY() < player_->GetPositionY() + player_->GetDimensionsY() &&
         // and the object's bottom side is greater than the player's top side
         game_objects_[i]->GetPositionY() + game_objects_[i]->GetDimensionsY() > player_->GetPositionY()) {
            // Overlaps are from the perspective of the object, so the left_side_overlap is the player overlaping the left side of the object
            float right_side_overlap = game_objects_[i]->GetPositionX() + game_objects_[i]->GetDimensionsX() - player_->GetPositionX();
            float left_side_overlap = player_->GetPositionX() + player_->GetDimensionsX() - game_objects_[i]->GetPositionX();
            float top_side_overlap = player_->GetPositionY() + player_->GetDimensionsY() - game_objects_[i]->GetPositionY();
            float bottom_side_overlap = game_objects_[i]->GetPositionY() + game_objects_[i]->GetDimensionsY() - player_->GetPositionY();
            bool right_overlapping = right_side_overlap > 0;
            bool left_overlapping = left_side_overlap > 0;
            bool top_overlapping = top_side_overlap > 0;
            bool bottom_overlapping = bottom_side_overlap > 0;
            // Corner case, we are overlapping on the top right corner, resolve in the direction of the smallest overlap
            if (right_overlapping && top_overlapping){
                if (right_side_overlap < top_side_overlap) {
                    player_->SetPositionX(player_->GetPositionX() + right_side_overlap);
                }
                else {
                    player_->SetPositionY(player_->GetPositionY() - top_side_overlap);
                }
            }
            // Corner case, we are overlapping on the bottom right corner, resolve in the direction of the smallest overlap
            else if (right_overlapping && bottom_overlapping) {
                if (right_side_overlap < bottom_side_overlap) {
                    player_->SetPositionX(player_->GetPositionX() + right_side_overlap);
                }
                else {
                    player_->SetPositionY(player_->GetPositionY() + bottom_side_overlap);
                }
            }
            // Corner case, we are overlapping on the top left corner, resolve in the direction of the smallest overlap
            else if (left_overlapping && top_overlapping) {
                if (left_side_overlap < top_side_overlap) {
                    player_->SetPositionX(player_->GetPositionX() - left_side_overlap);
                }
                else {
                    player_->SetPositionY(player_->GetPositionY() - top_side_overlap);
                }
            }
            // Corner case, we are overlapping on the bottom left corner, resolve in the direction of the smallest overlap
            else if (left_overlapping && bottom_overlapping) {
                if (left_side_overlap < bottom_side_overlap) {
                    player_->SetPositionX(player_->GetPositionX() - left_side_overlap);
                }
                else {
                    player_->SetPositionY(player_->GetPositionY() + bottom_side_overlap);
                }
            }
        }
    }
}

}  // namespace game
