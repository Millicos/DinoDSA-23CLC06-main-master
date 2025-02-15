#include "moving_object.h"

// Triển khai các phương thức của MovingObject
MovingObject::MovingObject(Vector2 pos, Texture2D tex, int spd)
    : position(pos), frame(tex), speed(spd) {}

MovingObject::~MovingObject() {
    // Giải phóng tài nguyên của frame nếu cần
    UnloadTexture(frame);
}

void MovingObject::Update() {
    position.x -= speed; // Di chuyển sang trái
}

Rectangle MovingObject::GetRect() const {
    return {position.x, position.y, static_cast<float>(frame.width), static_cast<float>(frame.height)};
}

bool MovingObject::IsCollision(Dino* dino) const {
    Rectangle objectRect = GetRect();
    Rectangle dinoRect = dino->GetRect();
    return CheckCollisionRecs(objectRect, dinoRect);
}

// Triển khai các phương thức của Item
Item::Item(Vector2 pos, Texture2D tex, int spd)
    : MovingObject(pos, tex, spd) {}

// Triển khai các phương thức của Shield
Shield::Shield(Vector2 pos, Texture2D tex, int spd)
    : Item(pos, tex, spd) {}

bool Shield::Collected() {
    // Kích hoạt trạng thái bất tử
    ActivateInvincibility(5.0f);
    return true;
}

// Triển khai các phương thức của Apple
Apple::Apple(Vector2 pos, Texture2D tex, int spd)
    : Item(pos, tex, spd) {}

bool Apple::Collected() {
    // Tăng HP
    HP::Increase(50);
    return true;
}

// Triển khai các phương thức của Trap
Trap::Trap(Vector2 pos, Texture2D tex, int spd)
    : MovingObject(pos, tex, spd) {}

bool Trap::Collected() {
    // Giảm HP
    DecreaseHP();
    return true;
}
