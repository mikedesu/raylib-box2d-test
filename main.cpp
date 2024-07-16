

#include <box2d/box2d.h>
#include <iostream>
#include <raylib.h>
#include <string>
#include <unistd.h>

using namespace std;

int main() {

  //--------------------
  InitWindow(800, 450, "Raylib Box2D");
  SetExitKey(KEY_Q);
  SetTargetFPS(60);
  RenderTexture2D target = LoadRenderTexture(800, 450);

  Camera2D camera = {0};

  string path = "../raylib-cpp-template/img/redbrick.png";
  Texture texture = LoadTexture(path.c_str());

  b2Vec2 gravity(0.0f, -10.0f);
  b2World world(gravity);
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
  b2Body *groundBody = world.CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(GetScreenWidth(), 10.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);

  // Define the dynamic body. We set its position and call the body factory.
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, GetScreenHeight());
  b2Body *body = world.CreateBody(&bodyDef);
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  body->CreateFixture(&fixtureDef);

  float timeStep = 1.0f / 60.0f;
  int velocityIterations = 8;
  int positionIterations = 3;

  while (!WindowShouldClose()) {
    const int horizontal_speed = 40;
    const int jump_speed = 20;

    if (IsKeyDown(KEY_LEFT)) {
      body->SetTransform(
          b2Vec2(body->GetPosition().x - 0.1, body->GetPosition().y), 0);
    }
    if (IsKeyDown(KEY_RIGHT)) {
      body->SetTransform(
          b2Vec2(body->GetPosition().x + 0.1, body->GetPosition().y), 0);
    }
    if (IsKeyDown(KEY_SPACE)) {
      body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, jump_speed));
    }

    world.Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();

    BeginDrawing();
    BeginMode2D(camera);
    BeginTextureMode(target);

    ClearBackground(RAYWHITE);

    // draw a red rectangle line around the ground box
    // iterate over each vertex
    b2Vec2 v1 = groundBody->GetPosition();
    DrawRectangleLines(v1.x - GetScreenWidth() / 2.0f, v1.y, GetScreenWidth(),
                       10, RED);

    DrawTexturePro(
        texture, {0, 0, (float)texture.width, (float)texture.height},
        {position.x, position.y, (float)texture.width, (float)texture.height},
        {0, 0}, angle, WHITE);

    EndMode2D();
    EndTextureMode();

    ClearBackground(RAYWHITE);
    DrawTextureRec(
        target.texture,
        {0, 0, (float)target.texture.width, (float)target.texture.height},
        {0, 0}, WHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
