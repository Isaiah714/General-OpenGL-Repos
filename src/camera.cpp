#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "camera.hpp"

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 800.0f
#define NEAR_PLANE 0.1f
#define FAR_PLANE 100.0f
#define FOV 45.0f

/* 
  This is how to define a camera
  You need its world position, its direction of what the camera
  is looking at, a vector pointing to the right and a vector 
  pointing upwards from the camera. Let's do it with a default
  constructor
*/
Camera::Camera() {
  glm::vec3 target = glm::vec3( 0.0f, 0.0f, 0.0f );                           /* Needed to obtain the direction vector                                               */
  glm::vec3 upVec = glm::vec3 ( 0.0f, 1.0f, 0.0f );                           /* Using this vector to get the right vector from camera                               */
  this->position = glm::vec3  ( 0.0f, 0.0f, 3.0f );                           /* Position defined                                                                    */
  this->front = glm::vec3( 0.0f, 0.0f, -1.0f );                               /* Front vector is used to let the user to have the camera always focus on the target  */
  this->direction = glm::normalize( position - target );                      /* Normal linear algebra to obtain direction vector                                    */
  this->right = glm::cross( upVec, direction );                               /* We do cross product of the up vector and direction vector to get the right vector   */
  this->up = glm::cross( right, direction );                                  /* Same idea when obtaining the right vector                                           */
  this->view = glm::lookAt( this->position, target + this->front, this->up ); /* This matrix allows rotation and translation using the three vectors we just created */
  yaw__ = -90.0f;                                                             /* yaw corresponds to rotating on the x axis  */
  pitch__ = 0.0f;                                                             /* pitch correspondsto rotating on the z axis */

  /*
  This section allows the camera to be able to look around. The direction vector will be changed completely 
  Here we use trigonometry to successfully create a rotating camera. We have to multiply cosine pitch to
  the x and z axes since it's influenced when trying to obtain rotation on the y axis  
  */
  this->direction.x = cos( glm::radians( yaw__ ) ) * cos( glm::radians( pitch__ ) );
  this->direction.y = sin( glm::radians( pitch__ ) );
  this->direction.z = sin( glm::radians( yaw__ ) ) * cos( glm::radians( pitch__ ) );

}

Camera::~Camera() noexcept {}

void Camera::move()
{
  glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
  this->view = glm::lookAt( this->position, this->position + this->front, this->up );
  this->projection = glm::perspective( glm::radians( FOV ), WINDOW_WIDTH / WINDOW_HEIGHT, NEAR_PLANE, FAR_PLANE );
}