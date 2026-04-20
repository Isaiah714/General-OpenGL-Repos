#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "textureclass.hpp"
#include "camera.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

void processInput( GLFWwindow * window );
void framebuffer_size_callback( GLFWwindow * window, int width, int height );
void mouseCallback( GLFWwindow * window, double xPos, double yPos );

float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* For mouse cursor calculation */
float lastX = WINDOW_WIDTH / 2;
float lastY = WINDOW_HEIGHT / 2;

Camera camera;

int main()
{
  ////////////////////////////////////CREATING WINDOWS && INTIALIZING GLAD AND GLFW/////////////////////////
  if( !glfwInit() )
  {
    std::cout << "There was error in initializing GLFW" << std::endl;
    return -1;
  }

  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3                 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3                 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

  GLFWwindow * window = glfwCreateWindow( WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          "OpenGL Journey",
                                          NULL,
                                          NULL );

  if( window == NULL )
  {
    std::cout << "There was an error when creating window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent( window );
  glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

  if( !( gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) )
  {
    std::cout << "There was an error in loading GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  glEnable( GL_DEPTH_TEST );

  ////////////////////////////PASSING DATA TO SHADERS && CREATING SHADERS HERE////////////////////////////
  Shader shader( "../shaders/vertexshader.vs", "../shaders/fragmentshader.fs" );

  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};
  ////////////////////////////////////////////////////////////////////////////////////////////////////////



  ///////////////////////////////////CREATING TEXTURES HERE///////////////////////////////////////////////
  Texture texture_obj1( "metal", 0 );
  texture_obj1.loadTexture( "../textures/tiles.jpg" );
  texture_obj1.getTextureLocation( shader );

  Texture texture_obj2( "tennis", 1 );
  texture_obj2.overlapTexture( "../textures/supamario.png" );
  texture_obj2.getTextureLocation( shader );
  ////////////////////////////////////////////////////////////////////////////////////////////////////////



  ////////////////////////////TRANSLATIONS, SCALING, AND ROTATIONS HERE///////////////////////////////////
  // Important Note: when multiplying matrices, it is important to multiply each modification in order.
  // It is important to do scaling first, rotation second, and translation third. Otherwise the matrix 
  // product will be prone to runtime errors when implementing the code.

  // Created a vector here and the last attribute is set to 1.0f to keep the object 2D
  //glm::vec4 vec( 1.0f, 0.0f, 0.0f, 1.0f );

  // We initialize the trans to an indentity matrix.
  // This is a starting point when translating a matrix
  //glm::mat4 trans = glm::mat4( 1.0f );

  // trans is then intialized to the translate function which would allow the object
  // to move from (1,0,0) to (2,1,0).
  //trans = glm::translate( trans, glm::vec3( 1.0f, 1.0f, 0.0f ) );

  // This is where the object would actually move on the screen.
  //vec = trans * vec;
  //std::cout << vec.x << vec.y << vec.z << std::endl;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////GOING 3D/////////////////////////////////////////////////////
  // This is the model matrix where you're able to perform rotation, scale, and translation. (local space)
  //glm::mat4 model = glm::mat4( 1.0f );
  //model = glm::rotate( model, glm::radians( -55.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
  
  // This is the view matrix where you're moving the camera away from the object specified by the third argument in glm::vec3. (view space)
  //glm::mat4 view( 1.0f );
  //view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) );
  
  // This is the projection matrix where it creates a fustrum (a space used to render objects on)
  // and if outside of the fustrum, objects become clipped preventing from being rendered onto the screen
  //glm::mat4 projection;
  //projection = glm::perspective( glm::radians( FOV ), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, NEAR_PLANE, FAR_PLANE );
  // To be written a vertex shader file, must do it this way in order for it to be rendered correctly. vec4 is local space.
  //gl_Position = projection * view * model * vec4(vPos, 1.0);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////

  glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED ); /* Hides the cursor and sets it in the middles of the window */

  /////////////////////////////////////////GAME LOOP//////////////////////////////////////////////////////
  while( !(glfwWindowShouldClose( window ) ) )
  {
    processInput( window );
    glfwSetCursorPosCallback(window, mouseCallback); 

    glClearColor( 0.0f, 0.2f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    texture_obj1.activateTexture();
    texture_obj2.activateTexture();
    
    glm::mat4 model = glm::mat4( 1.0f );
    
    model = glm::rotate( model, (float)glfwGetTime() * glm::radians( 50.0f ), glm::vec3( 0.5f, 1.0f, 0.0f ) );
    camera.move();
    

    shader.use();
    shader.bindArray();

    int model_loc = glGetUniformLocation( shader.shader_id, "model" );
    glUniformMatrix4fv( model_loc, 1, GL_FALSE, glm::value_ptr( model ) );
    
    int view_loc = glGetUniformLocation( shader.shader_id, "view" );
    glUniformMatrix4fv( view_loc, 1, GL_FALSE, glm::value_ptr( camera.view ) );

    int projection_loc = glGetUniformLocation( shader.shader_id, "projection" );
    glUniformMatrix4fv( projection_loc, 1, GL_FALSE, glm::value_ptr( camera.projection ) );
    
    for( unsigned int i = 0; i < 10; ++i )
    {
      glm::mat4 model = glm::mat4( 1.0f );
      model = glm::translate( model, cubePositions[i] );
      float angle = ( 20.0f * i ) + 20.0f;
      model = glm::rotate( model, (float)glfwGetTime() * glm::radians( angle ), glm::vec3( 1.0f, 0.3f, 0.5f ) );
      glUniformMatrix4fv( model_loc, 1, GL_FALSE, glm::value_ptr( model ) );

      glDrawArrays( GL_TRIANGLES, 0, 36 );
    }
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;



    glfwSwapBuffers( window );
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////FUNCTION DEFINITIONS////////////////////////////////////////////
void processInput( GLFWwindow *window )
{
  const float cameraSpeed = 3.0f * deltaTime;
  if( glfwGetKey( window, GLFW_KEY_ESCAPE) == GLFW_PRESS )
  {
    glfwSetWindowShouldClose( window, true );
  }
  if( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS )
  {
    //std::cout << "Moving forward\n";
    camera.position += cameraSpeed * camera.front;
  }
  if( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS )
  {
    //std::cout << "Moving Back\n";
    camera.position -= cameraSpeed * camera.front;
  }
  if( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )
  {
    //std::cout << "Moving left\n";
    camera.position -= glm::normalize( glm::cross( camera.front, camera.up ) ) * cameraSpeed;
  }
  if( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS )
  {
    //std::cout << "Moving right\n";
    camera.position += glm::normalize( glm::cross( camera.front, camera.up ) ) * cameraSpeed;
  }
  
}

void framebuffer_size_callback( GLFWwindow *window, int width, int height )
{
  glViewport( 0, 0, width, height );
}
/* This function will calculate the camera's current direciton vector after mouse updates */
void mouseCallback( GLFWwindow * window, double xPos, double yPos )
{
  /* The first step is to calculate the mouse's offset sine the last frame */
  float xOffset = xPos - lastX;
  float yOffset = lastY - yPos; /* reversed since y-coordinates range from bottom to top */
  lastX = xPos;
  lastY = yPos;

  const float sensitivity = 0.1f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
