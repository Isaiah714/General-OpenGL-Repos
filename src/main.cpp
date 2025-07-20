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

  float vertices[] =
  {  //  Vertices             Color         texture coords
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f  // top left
  };

  int indices[] = 
  {
    0, 1, 3,
    1, 2, 3
  };

  unsigned int VAO, VBO, EBO;
  
  glGenVertexArrays( 1, &VAO );
  glGenBuffers     ( 1, &VBO );
  glGenBuffers     ( 1, &EBO );

  glBindVertexArray( VAO );
  glBindBuffer( GL_ARRAY_BUFFER, VBO                                                );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW       );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO                                        );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 ); // side not: 2nd argument specifies the dimension of a vector being used
  glEnableVertexAttribArray( 0 );

  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float) ) ); // these two fuctions are using vec3: x, y, z && r, g, b
  glEnableVertexAttribArray( 1 );

  glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), (void*)(6 * sizeof(float) ) ); // this function is using a vec2: x, y
  glEnableVertexAttribArray( 2 );
  ///////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////CREATING TEXTURES HERE//////////////////////////////////////////////
  
  Texture texture_obj1( "crate", 0 );
  texture_obj1.loadTexture( "../textures/container.jpg" );
  texture_obj1.getTextureLocation( shader );

  Texture texture_obj2( "awesomeface", 1 );
  texture_obj2.overlapTexture( "../textures/awesomeface.png" );
  texture_obj2.getTextureLocation( shader );

  /////////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////GAME LOOP//////////////////////////////////////////////////
  while( !(glfwWindowShouldClose( window ) ) )
  {
    processInput( window );

    glClearColor( 0.0f, 0.2f, 0.2f, 1.0f );
    glClear     ( GL_COLOR_BUFFER_BIT    );

    texture_obj1.activateTexture();
    texture_obj2.activateTexture();

    shader.use();

    glBindVertexArray( VAO                                 );
    glDrawElements   ( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

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