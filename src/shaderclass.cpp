#include "shaderclass.hpp"

Shader::Shader( const char * vertex_path, const char * fragment_path )
{
  std::string v_shader_code;
  std::string f_shader_code;
  std::ifstream vertex_file;
  std::ifstream fragment_file;

  vertex_file.exceptions  ( std::ifstream::failbit | std::ifstream::badbit );
  fragment_file.exceptions( std::ifstream::failbit | std::ifstream::badbit );

  try
  {
    vertex_file.open  ( vertex_path   );
    fragment_file.open( fragment_path );

    std::stringstream vertex_file_stream;
    std::stringstream fragment_file_stream;

    vertex_file_stream << vertex_file.rdbuf();
    fragment_file_stream << fragment_file.rdbuf();

    vertex_file.close();
    fragment_file.close();

    v_shader_code = vertex_file_stream.str();
    f_shader_code = fragment_file_stream.str();
  }
  catch( std::ifstream::failure error )
  {
    std::cout << "Failed to read file" << std::endl;
  }

  const char * vshader_code = v_shader_code.c_str();
  const char * fshader_code = f_shader_code.c_str();

  unsigned int vertex_shader, fragment_shader;

  vertex_shader = glCreateShader( GL_VERTEX_SHADER );
  glShaderSource  ( vertex_shader, 1, &vshader_code, NULL );
  glCompileShader ( vertex_shader                         );
  getCompileStatus( vertex_shader, "VERTEX"               );

  fragment_shader = glCreateShader( GL_FRAGMENT_SHADER );
  glShaderSource  ( fragment_shader, 1, &fshader_code, NULL );
  glCompileShader ( fragment_shader                         );
  getCompileStatus( fragment_shader, "FRAGMENT"             );

  shader_id = glCreateProgram();
  glAttachShader  ( shader_id, vertex_shader   );
  glAttachShader  ( shader_id, fragment_shader );
  glLinkProgram   ( shader_id                  );
  getCompileStatus( shader_id, "PROGRAM"       );
  
  glDeleteShader( vertex_shader   );
  glDeleteShader( fragment_shader );

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
  
  glGenVertexArrays( 1, &VAO__ );
  glGenBuffers     ( 1, &VBO__ );
  glGenBuffers     ( 1, &EBO__ );

  glBindVertexArray( VAO__ );
  glBindBuffer( GL_ARRAY_BUFFER, VBO__                                                );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW         );
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO__                                        );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW   );

  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 ); // side not: 2nd argument specifies the dimension of a vector being used
  glEnableVertexAttribArray( 0 );

  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float) ) ); // these two fuctions are using vec3: x, y, z && r, g, b
  glEnableVertexAttribArray( 1 );

  glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), (void*)(6 * sizeof(float) ) ); // this function is using a vec2: x, y
  glEnableVertexAttribArray( 2 );
}

void Shader::use()
{
  glUseProgram( shader_id );
}

void Shader::bindArray()
{
  glBindVertexArray( VAO__ );
}

void Shader::setInt( const std::string & name, int value ) const
{
  glUniform1i( glGetUniformLocation( shader_id, name.c_str() ), value );
}

void Shader::setFloat( const std::string & name, float value ) const
{
  glUniform1f( glGetUniformLocation( shader_id, name.c_str() ), value );
}

void Shader::getCompileStatus( unsigned int shader, std::string type )
{
  int success;
  char infoLog[512];

  if( type != "PROGRAM" )
  {
    glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
    if( !success )
    {
      glGetShaderInfoLog( shader, 1024, NULL, infoLog );
      std::cout << "Failed to compile shader of type" << type << '\n' << infoLog << std::endl;
    }
  }
  else
  {
    glGetProgramiv( shader, GL_LINK_STATUS, &success );
    if( !success )
    {
      glGetProgramInfoLog( shader, 1024, NULL, infoLog );
      std::cout << "Failed to compile shader of type" << type << '\n' << infoLog << std::endl;
    }
  }
}
