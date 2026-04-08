#pragma once
#include <SFML/Graphics.hpp>
#include <string>

sf::Texture loadImage(const std::string& imageFilePath, int newWidth, int newHeight);
