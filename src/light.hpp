#ifndef __LIGHT__
#define __LIGHT__

#include "../lib/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

class LightSource
{
	public:
	unsigned int ID;
	LightSource( const std::string & vPath, const std::string & fPath );
 ~LightSource() noexcept;

	void use();
	void bindArray();
	void setColor( const std::string & name, glm::vec3 & value );

  private:
  unsigned int VAO__, VBO__;

  void getCompileStatus( unsigned int shader, std::string type );
};

#endif