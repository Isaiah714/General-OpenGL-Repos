#include "light.hpp"

LightSource::~LightSource() noexcept {}

LightSource::LightSource( const std::string & vPath, const std::string & fPath )
{
	std::string v_shader_code;
  std::string f_shader_code;
  std::ifstream vertex_file;
  std::ifstream fragment_file;

  vertex_file.exceptions  ( std::ifstream::failbit | std::ifstream::badbit );
  fragment_file.exceptions( std::ifstream::failbit | std::ifstream::badbit );

  try
  {
    vertex_file.open  ( vPath   );
    fragment_file.open( fPath );

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

  ID = glCreateProgram();
  glAttachShader  ( ID, vertex_shader   );
  glAttachShader  ( ID, fragment_shader );
  glLinkProgram   ( ID                  );
  getCompileStatus( ID, "PROGRAM"       );
  
  glDeleteShader( vertex_shader   );
  glDeleteShader( fragment_shader );

float vertices[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
  };
  glGenVertexArrays( 1, &VAO__ );
	glGenBuffers( 1, &VBO__ );

	glBindVertexArray( VAO__ );
	glBindBuffer( GL_ARRAY_BUFFER, VBO__ );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );
  glBindVertexArray( VAO__ );
}

void LightSource::use()
{
	glUseProgram( ID );
}

void LightSource::setColor( const std::string & name, glm::vec3 & value)
{
	glUniform3f( glGetUniformLocation( ID, "lightColor"), value.x, value.y, value.z );
}

void LightSource::getCompileStatus( unsigned int shader, std::string type )
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