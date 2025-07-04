
#include "./includes/player.cpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <algorithm>

const int windowWidth = 1280;
const int windowHeight = 720;
const float max_length = 10;
const float FOV = 90.0f;
const float FOV_RAD = FOV * (PI / 180.0f);
const int MAP_W = 32;
const int MAP_H = 32;
const float BLOCK_HEIGHT = 2;

const short map[MAP_W][MAP_H] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

struct Ray {
    Vector2f start;
    Vector2f end;
    int wall_size;
    int idx;
    float angle;
};

float calculateDistance(Vector2f p_coords, Vector2f hit_coords) {
  float bottom = 0;
  float side = 0;

  if (hit_coords.x > p_coords.x) bottom = hit_coords.x - p_coords.x;
  else bottom = p_coords.x - hit_coords.x;
  
  if (hit_coords.y > p_coords.y) side = hit_coords.y - p_coords.y;
  else side = p_coords.y - hit_coords.y;

  return sqrt(bottom*bottom + side*side);
}

int main() {
  RenderWindow window(VideoMode({windowWidth, windowHeight}), "Ray Casting with 90° FOV");
  window.setFramerateLimit(60);

  vector<Ray> rays;
  Player player(MAP_W, MAP_H);
  player.x = 2;
  player.y = 2;

  float projectionPlaneDist = (windowWidth / 2.0f) / tan(FOV_RAD / 2.0f);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<Event::Closed>() || Keyboard::isKeyPressed(Keyboard::Key::Escape))
        window.close();
    }

    player.perform();
    Vector2f playerPos(player.x, player.y);
    float step = FOV / windowWidth;
    float ray_step = 0.1;

    for (int ray = 0; ray < windowWidth; ray++) {
        float ray_angle = player.rotation(-(FOV/2) + (step * ray));
        float d_x = cos(ray_angle);
        float d_y = sin(ray_angle);
        float c_x = playerPos.x;
        float c_y = playerPos.y;
        
        bool hit = false;
        Vector2f distance({0, 0});
        int wall_size = 0;

        while(!hit) {
            c_x += d_x * ray_step;
            c_y += d_y * ray_step;
            distance.x += fabs(d_x * ray_step);
            distance.y += fabs(d_y * ray_step);

            if (map[int(c_y)][int(c_x)] != 0) {
                hit = true;
                wall_size = map[int(c_y)][int(c_x)];
            }
        }

        Ray r;
        r.start = playerPos;
        r.end = {c_x, c_y};
        r.idx = ray;
        r.angle = ray_angle;
        r.wall_size = wall_size;
        rays.push_back(r);

    }

    window.clear();

    // Ground
    float ground_y = windowHeight;
    while(ground_y > windowHeight / 2) {
        float height = ground_y / 128;
        float proportion = (ground_y - (windowHeight/2)) / (windowHeight / 2);
        int shade = clamp<int>((255 * proportion - 0.2), 0, 255);
        Color c(shade, shade, shade);

        RectangleShape g;
        g.setSize({windowWidth, height});
        g.setPosition({0, ground_y});
        g.setFillColor(c);
        g.setOrigin({0, height});

        window.draw(g);
        ground_y -= height;
    }

    // Ground
    float sky_y = windowHeight;
    float draw_y = 0;
    while(draw_y < windowHeight / 2) {
        float height = sky_y / 128;
        float proportion = (sky_y - (windowHeight/2)) / (windowHeight / 2);
        int shade = clamp<int>((255 * proportion - 0.2), 0, 255);
        Color c(shade, shade, shade);

        RectangleShape g;
        g.setSize({windowWidth, height});
        g.setPosition({0, draw_y + height});
        g.setFillColor(c);
        g.setOrigin({0, height});

        window.draw(g);
        sky_y -= height;
        draw_y += height;
    }

    for(Ray r : rays) {
        float distance = calculateDistance(r.start, r.end);
        float height = (windowHeight / 2) * (1/distance) * BLOCK_HEIGHT;
        float shade = clamp<short>(static_cast<short>(255 * (1/distance)), 0, 200);
        Vector2f position = Vector2f({
            r.idx,
            (windowHeight / 2) - (height / 2)
        });

        Color c(shade, shade, shade);
        RectangleShape s;
        s.setFillColor(c);
        s.setPosition(position);
        s.setSize({1, height});
        window.draw(s);
    }

    float scale = 5;
    float origin_x = 20;
    float origin_y = 20;
    Vector2f block_size({scale, scale});

    for(int row = 0; row < MAP_W; ++row) {
        for(int col = 0; col < MAP_H; ++col) {
            if (map[row][col] != 1) continue; 
            RectangleShape s(block_size);
            s.setFillColor(Color::White);
            s.setPosition({ origin_x + col * block_size.x, origin_y + row * block_size.y});
            window.draw(s);
        }
    }

    RectangleShape s({5,5});
    s.setFillColor(Color::Blue);
    s.setPosition({origin_x + player.x * scale, origin_y + player.y * scale});
    window.draw(s);

    VertexArray drawableRays(PrimitiveType::Lines);
    for(Ray r : rays) {
        Vertex startV;
        Vertex endV;
        startV.position = Vector2f({origin_x + r.start.x * scale, origin_y + r.start.y * scale});
        endV.position = Vector2f({origin_x + r.end.x * scale, origin_y + r.end.y * scale});
        startV.color = Color::Yellow;
        endV.color = Color::Yellow;
        drawableRays.append(startV);
        drawableRays.append(endV);
    }

    window.draw(drawableRays);

    window.display();
    rays.clear();
  }

  return 0;
}