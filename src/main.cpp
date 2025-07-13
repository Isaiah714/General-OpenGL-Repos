#include "shaderclass.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

void processInput( GLFWwindow * window );
void framebuffer_size_callback( GLFWwindow * window, int width, int height );

int main()
{
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

  ////////////////////////////PASSING DATA TO SHADERS && CREATING SHADERS HERE////////////////////////////
  Shader shader( "../shaders/vertexshader.vs", "../shaders/fragmentshader.fs" );

  float vertices[] =
  {  //  Vertices         Color
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f 
  };

  unsigned int VAO, VBO;
  
  glGenVertexArrays( 1, &VAO );
  glGenBuffers     ( 1, &VBO );

  glBindVertexArray( VAO );
  glBindBuffer( GL_ARRAY_BUFFER, VBO );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0 );
  glEnableVertexAttribArray( 0 );

  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float) ) );
  glEnableVertexAttribArray( 1 );

  ///////////////////////////////////////////////////////////////////////////////////////////////////////

  while( !(glfwWindowShouldClose( window ) ) )
  {
    processInput( window );

    glClearColor( 0.0f, 0.2f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    shader.use();

    glBindVertexArray( VAO );
    glDrawArrays( GL_TRIANGLES, 0, 3 );

    glfwSwapBuffers( window );
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

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
