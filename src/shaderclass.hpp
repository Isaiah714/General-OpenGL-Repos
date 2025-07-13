#ifndef SHADERCLASS_H
#define SHADERCLASS_H

#include "../lib/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

class Shader
{
  public:
  unsigned int shader_id;

  Shader( const char * vertex_path, const char * fragment_path );

  void use();

  void setInt  ( const std::string & name, int value   ) const;
  void setFloat( const std::string & name, float value ) const;

  private:
  void getCompileStatus( unsigned int shader, std::string type );
};


#endif