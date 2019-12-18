#pragma once

#include <map>
#include <SFML\Graphics.hpp>

namespace Gabijects
{
	class AssetManager
	{
	public:
		// Empty constructor and destructor
		AssetManager() {}
		~AssetManager() {}

		// Methods for loading and getting a texture, mapping it with a string name
		void LoadTexture(std::string name, std::string fileName);
		sf::Texture &GetTexture(std::string name);

		// Methods for loading and getting a font, mapping it with a string name
		void LoadFont(std::string name, std::string fileName);
		sf::Font &GetFont(std::string name);

	private:
		std::map<std::string, sf::Texture> _textures;	// map with textures and their names
		std::map<std::string, sf::Font> _fonts;			// map with fonts and their names
	};
}