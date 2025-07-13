#include "shaderclass.hpp"

#include "../lib/include/stb_image/stb_image.h"

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
  {  //  Vertices             Color         texture coords
     0.5f, 0.5f,  0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
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
  glBindBuffer( GL_ARRAY_BUFFER, VBO );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 ); // side not: 2nd argument specifies the dimension of a vector being used
  glEnableVertexAttribArray( 0 );

  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float) ) ); // these two fuctions are using vec3: x, y, z && r, g, b
  glEnableVertexAttribArray( 1 );

  glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), (void*)(6 * sizeof(float) ) ); // this function is using a vec2: x, y
  glEnableVertexAttribArray( 2 );
  ///////////////////////////////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////CREATING TEXTURES HERE/////////////////////////////////////////////
  // Texture coordinates to tell opengl where to render the texture on ( range: (0,0) - (1,1) )
  float texture_coordinates[] =
  {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f
  };
  
  // Creating texuture ID to bind its data for opengl to recognize
  unsigned int texture_id;

  // Same steps when creating shaders applies to creating textures
  glGenTextures( 1, &texture_id );
  glBindTexture( GL_TEXTURE_2D, texture_id );

  // Setting the texture wrapping/filtering options (on currently bound texutre object)
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  // Creating arguments for stbi_load
  int width, height, nr_channel;

  // stbi_load loads texture into program
  unsigned char * data = stbi_load("../textures/container.jpg", &width, &height, &nr_channel, 0 );

  // Checking if texture loaded successfully
  if( data )
  {
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
    glGenerateMipmap( GL_TEXTURE_2D );
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  
  // Image is freed from memory
  stbi_image_free( data );
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  while( !(glfwWindowShouldClose( window ) ) )
  {
    processInput( window );

    glClearColor( 0.0f, 0.2f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    shader.use();
    
    glBindTexture( GL_TEXTURE_2D, texture_id );
    glBindVertexArray( VAO );
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

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
