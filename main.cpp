// #include "./includes/player.cpp"
// #include <SFML/Graphics.hpp>
// #include <cmath>
// #include <vector>

// const int windowWidth = 1280;
// const int windowHeight = 720;
// const float vision_limit = 3;
// const float FOV = 90.0f;
// const float FOV_RAD = FOV * (PI / 180.0f);
// const int MAP_W = 8;
// const int MAP_H = 8;

// const short map[MAP_W][MAP_H] = {
//   {1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,1},
//   {1,0,0,0,1,1,1,1},
//   {1,0,0,0,1,1,1,1},
//   {1,0,0,0,0,0,0,1},
//   {1,0,0,0,0,1,1,1},
//   {1,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1}
// };

// struct Wall {
//   float distance;
//   int ray_idx;
// };

// float calculateDistance(Vector2f p_coords, Vector2f hit_coords) {
//   float bottom = 0;
//   float side = 0;

//   if (hit_coords.x > p_coords.x) bottom = hit_coords.x - p_coords.x;
//   else bottom = p_coords.x - hit_coords.x;
  
//   if (hit_coords.y > p_coords.y) side = hit_coords.y - p_coords.y;
//   else side = p_coords.y - hit_coords.y;

//   return sqrt(bottom*bottom + side*side);
// }

// int main() {
//   RenderWindow window(VideoMode({windowWidth, windowHeight}), "Ray Casting with 90° FOV");
//   window.setFramerateLimit(60);

//   vector<Wall> walls;
//   Player player(MAP_W, MAP_H);
//   player.x = 2.5;
//   player.y = 3.0;

//   float projectionPlaneDist = (windowWidth / 2.0f) / tan(FOV_RAD / 2.0f);

//   while (window.isOpen()) {
//     while (const std::optional event = window.pollEvent()) {
//       if (event->is<Event::Closed>())
//         window.close();
//     }

//     player.perform();
//     Vector2f playerPos(player.x, player.y);
//     float step = FOV / windowWidth;

//     for(int ray_idx = 0; ray_idx < windowWidth; ray_idx++) {
//       float rot = player.rotation((FOV/2) - (step * ray_idx));
//       Vector2f counter = {0, 0};
//       float d_x = cos(rot);
//       float d_y = sin(rot);
//       float c_x = player.x;
//       float c_y = player.y;
      
//       bool is_hit = false;

//       while(!is_hit) {
//         if (counter.x >= vision_limit || counter.y >= vision_limit || c_x >= MAP_W || c_y >= MAP_H || c_x < 0 || c_y < 0) break;
        
//         c_x += d_x;
//         c_y += d_y;
//         counter.x += d_x;
//         counter.y += d_y;

//         int map_x = int(c_x);
//         int map_y = int(c_y);
//         if (map[map_y][map_x] == 1) {
//           is_hit = true;
//           break;
//         }
//       }

//       if (is_hit) {
//         Wall w;
//         w.ray_idx = ray_idx;
//         w.distance = calculateDistance(playerPos, {c_x, c_y});
//         walls.push_back(w);
//       }
//     }

//     window.clear(Color::Black);

//     for(Wall w: walls) {
//       float wall_height = (windowHeight * projectionPlaneDist) / w.distance;
//       Vector2f size({1, wall_height});
//       Vector2f origin({0.5, wall_height / 2});

//       RectangleShape wall;
//       wall.setOrigin(origin);
//       int shade = std::max(0, 255 - int(w.distance * 40));
//       wall.setFillColor(Color(shade, shade, shade));
//       wall.setPosition({w.ray_idx, windowHeight / 2});
//       wall.setSize(size);

//       window.draw(wall);
//     }

//     window.display();
//     walls.clear();
//   }

//   return 0;
// }

#include "./includes/player.cpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

const int windowWidth = 1280;
const int windowHeight = 720;
const float vision_limit = 3;
const int MAP_W = 8;
const int MAP_H = 8;

const short map[MAP_W][MAP_H] = {
  {1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,1,1,1,1},
  {1,0,0,0,1,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1}
};

struct Wall {
  float distance;
  int ray_idx;
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

const float FOV_DEGREES = 90.0f;
const float FOV = FOV_DEGREES * (PI / 180.0f);  // Convert to radians

// ... Your map and other code remains unchanged

int main() {
    RenderWindow window(VideoMode({windowWidth, windowHeight}), "Ray Casting with 90° FOV");
    window.setFramerateLimit(60);

    vector<Wall> walls;
    Player player(MAP_W, MAP_H);
    player.x = 2.5f;
    player.y = 3.0f;

    // Calculate projection plane distance
    float projectionPlaneDist = (windowWidth / 2.0f) / tan(FOV / 2.0f);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }

        player.perform();
        Vector2f playerPos(player.x, player.y);
        float step = FOV_DEGREES / windowWidth;  // degrees per ray

        for (int ray_idx = 0; ray_idx < windowWidth; ray_idx++) {
            // Calculate ray angle in radians relative to player view
            float ray_angle_deg = (FOV_DEGREES / 2.0f) - (step * ray_idx);
            float ray_angle = player.rotation(ray_angle_deg);

            Vector2f counter = {0, 0};
            float d_x = cos(ray_angle);
            float d_y = sin(ray_angle);
            float c_x = player.x;
            float c_y = player.y;

            bool is_hit = false;

            while (!is_hit) {
                if (counter.x >= vision_limit || counter.y >= vision_limit || c_x >= MAP_W || c_y >= MAP_H || c_x < 0 || c_y < 0)
                    break;

                c_x += d_x * 0.01f;  // Smaller increments for more accurate hit detection
                c_y += d_y * 0.01f;
                counter.x += fabs(d_x * 0.01f);
                counter.y += fabs(d_y * 0.01f);

                int map_x = int(c_x);
                int map_y = int(c_y);
                if (map[map_y][map_x] == 1) {
                    is_hit = true;
                    break;
                }
            }

            if (is_hit) {
                Wall w;
                w.ray_idx = ray_idx;

                // Calculate raw distance from player to wall hit
                float raw_distance = calculateDistance(playerPos, {c_x, c_y});

                // Correct distance to remove fish-eye effect:
                float player_angle = player.rotation(0);
                float corrected_distance = raw_distance * cos(ray_angle - player_angle);

                w.distance = corrected_distance;
                walls.push_back(w);
            }
        }

        window.clear(Color::Black);

        for (Wall w : walls) {
            // Perspective projection: wall height based on corrected distance
            float wall_height = (windowHeight * projectionPlaneDist) / w.distance;

            Vector2f size({1, wall_height});
            Vector2f origin({0.5f, wall_height / 2.0f});

            RectangleShape wall;
            wall.setOrigin(origin);

            // Shade based on distance for depth effect
            int shade = std::max(0, 255 - int(w.distance * 40));
            wall.setFillColor(Color(shade, shade, shade));

            wall.setPosition({float(w.ray_idx), windowHeight / 2});
            wall.setSize(size);

            window.draw(wall);
        }

        window.display();
        walls.clear();
    }

    return 0;
}
