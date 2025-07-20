#include "textureclass.hpp"

Texture::Texture( const std::string & tex_name, const int & tex_index ) : texture_name__{ tex_name }, texture_index__{ tex_index }
{
  // Flips the overlapping texture IF any
  stbi_set_flip_vertically_on_load( true );

  // Same steps when creating a shader also applies to creating textures
  glGenTextures( 1, &texture_id__ );
  glBindTexture( GL_TEXTURE_2D, texture_id__ );
  
  // Setting the texture wrapping/filtering options (on currently bound texutre object)
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT     );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT     );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
};

void Texture::loadTexture( const std::string & texture_path )
{
  // stbi_load loads texture into program
  unsigned char * texture_data = stbi_load( texture_path.c_str(), &width__, &height__, &nr_chanel__, 0 );
  
  // Checks if the texture loaded into program successfully
  if( texture_data )
  {
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width__, height__, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data );
    glGenerateMipmap( GL_TEXTURE_2D );
  }
  else
  {
    std::cout << "Failed to load texture!" << std::endl;
  }

  // Image is freed from memory
  stbi_image_free( texture_data );
}

void Texture::overlapTexture( const std::string & texture_path )
{
  // stbi_load loads texture into program
  unsigned char * texture_data = stbi_load( texture_path.c_str(), &width__, &height__, &nr_chanel__, 0 );
  
  // Checks if the texture loaded into program successfully
  if( texture_data )
  {
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width__, height__, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data );
    glGenerateMipmap( GL_TEXTURE_2D );
  }
  else
  {
    std::cout << "Failed to load texture!" << std::endl;
  }

  // Image is freed from memory
  stbi_image_free( texture_data );
}

void Texture::getTextureLocation( Shader & shader_object )
{
  shader_object.use();
  shader_object.setInt( texture_name__, texture_index__ );
}

void Texture::activateTexture()
{
  glActiveTexture( GL_TEXTURE0 + texture_index__ );
  glBindTexture( GL_TEXTURE_2D, texture_id__ );
}
