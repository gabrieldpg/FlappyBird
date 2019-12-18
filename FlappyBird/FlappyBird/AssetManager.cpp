#include "AssetManager.hpp"

namespace Gabijects
{
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;

		// if texture is successfully loaded from file
		if (tex.loadFromFile(fileName))
		{
			// save it and map it to the name
			this->_textures[name] = tex;
		}
	}

	sf::Texture &AssetManager::GetTexture(std::string name)
	{
		// return texture mapped to name enquired
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		// if font is successfully loaded from file
		if (font.loadFromFile(fileName))
		{
			// save it and map it to the name
			this->_fonts[name] = font;
		}

	}

	sf::Font &AssetManager::GetFont(std::string name)
	{
		// return font mapped to name enquired
		return this->_fonts.at(name);
	}
}