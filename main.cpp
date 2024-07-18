

#include <box2d/box2d.h>
#include <iostream>
#include <raylib.h>
#include <string>
// #include <unistd.h>

using namespace std;

int main() {

  //--------------------
  const int width = 1280;
  const int height = 720;
  const char *window_title = "Raylib Box2D";
  bool debug_on = true;

  InitWindow(width, height, window_title);
  SetExitKey(KEY_Q);
  SetTargetFPS(60);
  RenderTexture2D target = LoadRenderTexture(width, height);

  Camera2D camera = {0};

  // string path = "../raylib-cpp-template/img/redbrick.png";
  // Texture texture = LoadTexture(path.c_str());

  b2Vec2 gravity(0.0f, -20.0f);
  b2World world(gravity);
  b2PolygonShape groundBox;
  b2EdgeShape groundEdge;
  b2BodyDef groundBodyDef;
  b2FixtureDef fixtureDef0;
  b2BodyDef bodyDef;
  b2Body *groundBody = nullptr;
  b2Body *body = nullptr;
  b2PolygonShape dynamicBox;
  b2FixtureDef fixtureDef;
  // const float gx = 0;
  // const float gy = GetScreenHeight() / 2.0f;
  //  groundEdge.SetOneSided((b2Vec2){0.0f, gy},
  //                         (b2Vec2){(float)GetScreenWidth() / 4.0f, gy},
  //                         (b2Vec2){(float)GetScreenWidth() * 3.0f / 4.0f,
  //                         gy}, (b2Vec2){(float)GetScreenWidth(), gy});

  groundBox.SetAsBox(GetScreenWidth() / 4.0f, 100.0f);
  // groundBox.SetAsBox(GetScreenWidth() / 2.0f, 10.0f);
  //  groundBox.SetAsBox(GetScreenWidth(), 20.0f);

  // groundEdge.SetTwoSided((b2Vec2){gx, gy},
  //                        (b2Vec2){(float)GetScreenWidth(), gy});

  // groundBodyDef.type = b2_staticBody;
  // groundBodyDef.type = b2_dynamicBody;
  groundBodyDef.position.Set(GetScreenWidth() / 2.0f,
                             GetScreenHeight() / 2.0f - 100);
  // groundBodyDef.enabled = true;

  // fixtureDef0.shape = &groundEdge;
  // fixtureDef0.shape = &groundBox;
  // fixtureDef0.density = 1.0f;
  // fixtureDef0.friction = 0.3f;

  groundBody = world.CreateBody(&groundBodyDef);
  groundBody->CreateFixture(&groundBox, 0.0f);
  // groundBody->CreateFixture(&fixtureDef0);

  // Define the dynamic body. We set its position and call the body factory.
  bodyDef.type = b2_dynamicBody;
  // const float
  const float box_width = 100.0f;
  const float box_height = 100.0f;
  bodyDef.position.Set(GetScreenWidth() / 2.0f,
                       GetScreenHeight() - box_height / 2.0f);
  body = world.CreateBody(&bodyDef);
  dynamicBox.SetAsBox(box_width / 2.0f, box_height / 2.0f);
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 1.0f;
  // fixtureDef.friction = 0.3f;
  body->CreateFixture(&fixtureDef);

  float timeStep = 1.0f / 60.0f;

  int velocityIterations = 5;
  int positionIterations = 3;

  while (!WindowShouldClose()) {
    const int horizontal_speed = 40;
    const int jump_speed = 40;

    if (IsKeyPressed(KEY_D)) {
      debug_on = !debug_on;
    }

    if (IsKeyDown(KEY_LEFT)) {

      body->SetLinearVelocity(
          b2Vec2(-horizontal_speed, body->GetLinearVelocity().y));

      // body->SetTransform(
      //     b2Vec2(body->GetPosition().x - 4, body->GetPosition().y), 0);
    }
    if (IsKeyDown(KEY_RIGHT)) {
      body->SetLinearVelocity(
          b2Vec2(horizontal_speed, body->GetLinearVelocity().y));
      // body->SetTransform(
      //     b2Vec2(body->GetPosition().x + 4, body->GetPosition().y), 0);
    }
    if (IsKeyDown(KEY_SPACE)) {
      body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, jump_speed));
      // body->ApplyLinearImpulseToCenter(b2Vec2(0, 100), true);
    }

    world.Step(timeStep, velocityIterations, positionIterations);

    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();

    BeginDrawing();
    BeginMode2D(camera);
    BeginTextureMode(target);

    // ClearBackground(RAYWHITE);
    ClearBackground(BLACK);

    // draw a red line representing the ground body
    // b2Vec2 v1 = groundBody->GetPosition();
    // get the vertices of the ground body
    // b2EdgeShape *edge = (b2EdgeShape
    // *)groundBody->GetFixtureList()->GetShape();

    // draw a rectangle representing the dynamic body
    b2Vec2 v0 = groundBody->GetPosition();
    DrawRectangle(v0.x, v0.y, 10, 10, RED);
    // get the vertices of the ground body

    b2Fixture *fixture = groundBody->GetFixtureList();
    for (b2Fixture *f = groundBody->GetFixtureList(); f; f = f->GetNext()) {
      b2PolygonShape *shape = (b2PolygonShape *)f->GetShape();
      b2Vec2 v1 = shape->m_vertices[0];
      b2Vec2 v2 = shape->m_vertices[1];
      b2Vec2 v3 = shape->m_vertices[2];
      b2Vec2 v4 = shape->m_vertices[3];
      // cout << "v0: " << v0.x << ", " << v0.y << " -- ";
      // cout << "v1: " << v1.x << ", " << v1.y << " -- ";
      // cout << "v2: " << v2.x << ", " << v2.y << " -- ";
      // cout << "v3: " << v3.x << ", " << v3.y << " -- ";
      // cout << "v4: " << v4.x << ", " << v4.y << endl;

      // DrawLine(v1.x, v1.y, v2.x, v2.y, GREEN);
      // DrawLine(v1.x, v1.y, v3.x, v3.y, GREEN);
      // DrawLine(v1.x, v1.y, v4.x, v4.y, GREEN);
      // DrawLine(v2.x, v2.y, v3.x, v3.y, GREEN);
      // DrawLine(v2.x, v2.y, v4.x, v4.y, GREEN);
      // DrawLine(v3.x, v3.y, v4.x, v4.y, GREEN);

      DrawRectangle(v0.x + v1.x, v0.y + v1.y - 20, 20, 20, GREEN);
      DrawRectangle(v0.x + v2.x, v0.y + v2.y - 20, 20, 20, BLUE);
      DrawRectangle(v0.x + v3.x, v0.y + v3.y - 20, 20, 20, PURPLE);
      DrawRectangle(v0.x + v4.x, v0.y + v4.y - 20, 20, 20, YELLOW);

      // DrawRectangle(v2.x, v2.y, 10, 10, GREEN);
      // DrawRectangle(v3.x, v3.y, 10, 10, PURPLE);
      // DrawRectangle(v4.x, v4.y, 10, 10, BLUE);

      // DrawLine(v1.x, v1.y, v2.x, v2.y, RED);
      // DrawLine(v1.x, v1.y, v2.x, v2.y, WHITE);
      // DrawLine(v2.x, v2.y, v3.x, v3.y, BLUE);
    }

    // cout << "v1: " << v1.x << ", " << v1.y << " -- ";
    // cout << "v2: " << v2.x << ", " << v2.y << endl;

    // DrawRectangleLines(v1.x, v1.y, v2.x, v2.y, RED);
    // DrawLine(v1.x, v1.y, v2.x, v2.y, RED);
    // DrawLine(v1.x, v1.y, v2.x, v2.y, GREEN);
    // DrawLine(v2.x, v2.y, v3.x, v3.y, BLUE);

    // DrawRectangleLines(v1.x - GetScreenWidth() / 2.0f, v1.y,
    // GetScreenWidth(),
    //                    10, RED);

    // position.x, y is actually center of the box
    // so we need to subtract half of the width and height
    // const float box_width = 2.0f;
    // const float box_height = 2.0f;

    const float box_x = position.x - box_width / 2.0f;
    const float box_y = position.y - box_height / 2.0f;

    // DrawTexturePro(texture, {0, 0, (float)texture.width,
    // (float)texture.height},
    //                {box_x, box_y, (float)texture.width,
    //                (float)texture.height}, {0, 0}, angle, WHITE);

    DrawRectangle(box_x, box_y, box_width, box_height, RED);

    EndMode2D();
    EndTextureMode();

    ClearBackground(RAYWHITE);
    DrawTextureRec(
        target.texture,
        {0, 0, (float)target.texture.width, (float)target.texture.height},
        //{0, 0, (float)target.texture.width, (float)-target.texture.height},
        {0, 0}, WHITE);

    if (debug_on) {
      string debug_str = "x: " + to_string(position.x) +
                         ", y: " + to_string(position.y) + "\n";
      DrawRectangle(0, 0, 500, 100, Fade(BLACK, 0.25f));
      DrawText(debug_str.c_str(), 10, 10, 20, WHITE);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
