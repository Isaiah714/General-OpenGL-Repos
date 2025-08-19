#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "textureclass.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

void processInput( GLFWwindow * window );
void framebuffer_size_callback( GLFWwindow * window, int width, int height );

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



  ////////////////////////////PASSING DATA TO SHADERS && CREATING SHADERS HERE////////////////////////////
  Shader shader( "../shaders/vertexshader.vs", "../shaders/fragmentshader.fs" );
  ////////////////////////////////////////////////////////////////////////////////////////////////////////



  ///////////////////////////////////CREATING TEXTURES HERE///////////////////////////////////////////////
  Texture texture_obj1( "crate", 0 );
  texture_obj1.loadTexture( "../textures/container.jpg" );
  texture_obj1.getTextureLocation( shader );

  Texture texture_obj2( "awesomeface", 1 );
  texture_obj2.overlapTexture( "../textures/awesomeface.png" );
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
  // This is the model matrix where you're able to perform rotation, scale, and translation.
  glm::mat4 model = glm::mat4( 1.0f );
  //model = glm::rotate( model, glm::radians( -55.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
  
  // This is the view matrix where you're moving the camera away from the object specified by the third argument in glm::vec3.
  glm::mat4 view( 1.0f );
  view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) );
  
  // This is the projection matrix where it creates a fustrum (a space used to render objects on)
  // and if outside of the fustrum, objects become clipped preventing from being rendered onto the screen
  glm::mat4 projection;
  projection = glm::perspective( glm::radians( 45.0f ), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f );
  ////////////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////GAME LOOP//////////////////////////////////////////////////////
  while( !(glfwWindowShouldClose( window ) ) )
  {
    processInput( window );

    glClearColor( 0.0f, 0.2f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 

    texture_obj1.activateTexture();
    texture_obj2.activateTexture();

    //glm::mat4 transR = glm::mat4( 1.0f );
    //transR = glm::translate( transR, glm::vec3( 0.5f, -0.5f, 0.0f ) );
    //transR = glm::rotate( transR, (float)glfwGetTime(), glm::vec3( 0.0, 0.0, 1.0 ) );
    glm::mat4 model = glm::mat4( 1.0f );
    glm::mat4 view = glm::mat4( 1.0f );
    glm::mat4 projection = glm::mat4( 1.0f );
    
    model = glm::rotate( model, (float)glfwGetTime() * glm::radians( 50.0f ), glm::vec3( 0.5f, 1.0f, 0.0f ) );
    view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) );
    projection = glm::perspective( glm::radians( 45.0f ), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f );

    shader.use();
    shader.bindArray();

    int model_loc = glGetUniformLocation( shader.shader_id, "model" );
    glUniformMatrix4fv( model_loc, 1, GL_FALSE, glm::value_ptr( model ) );

    int view_loc = glGetUniformLocation( shader.shader_id, "view" );
    glUniformMatrix4fv( view_loc, 1, GL_FALSE, glm::value_ptr( view ) );

    int projection_loc = glGetUniformLocation( shader.shader_id, "projection" );
    glUniformMatrix4fv( projection_loc, 1, GL_FALSE, glm::value_ptr( projection ) );

    //glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

    glDrawArrays( GL_TRIANGLES, 0, 36 );

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
  if( glfwGetKey( window, GLFW_KEY_ESCAPE) == GLFW_PRESS )
  {
    glfwSetWindowShouldClose( window, true );
  }
}

void framebuffer_size_callback( GLFWwindow *window, int width, int height )
{
  glViewport( 0, 0, width, height );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
