#ifndef __CAMERA__
#define __CAMERA__

#include <glm/glm.hpp>

class Camera
{
  public:
  Camera();
 ~Camera() noexcept;

 void move();

 glm::vec3 position;
 glm::vec3 direction;
 glm::vec3 right;
 glm::vec3 up;
 glm::vec3 front;
 glm::mat4 view;
 glm::mat4 projection;

  private:
  float yaw__;
  float pitch__;
  
};


#endif