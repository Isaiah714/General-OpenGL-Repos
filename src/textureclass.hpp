#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H

#include "shaderclass.hpp"
#include "../lib/include/stb_image/stb_image.h"

class Texture
{
  public:
  
  Texture( const std::string & texture_name, const int & tex_index );
 //~Texture();

  void loadTexture( const std::string & texture_path );
  void getTextureLocation( Shader & shader_object );
  void activateTexture();
  void overlapTexture( const std::string & texture_path );

  private:
  unsigned int texture_id__;
  unsigned char * data__;
  int width__, height__, nr_chanel__, texture_index__;
  std::string texture_name__;

};

#endif