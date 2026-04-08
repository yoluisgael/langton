#include "graphics.h"
#include <iostream>

sf::Texture loadImage(const std::string& imageFilePath, int newWidth, int newHeight) {
    sf::Texture texture;
    sf::Image originalImage;
    if (!originalImage.loadFromFile(imageFilePath)) {
        std::cerr << "No existe la imagen en: " << imageFilePath << std::endl;
        exit(-1);
    }

    unsigned int originalWidth = originalImage.getSize().x;
    unsigned int originalHeight = originalImage.getSize().y;

    sf::Image resizedImage;
    resizedImage.create(newWidth, newHeight);

    for (unsigned int x = 0; x < (unsigned int)newWidth; ++x) {
        for (unsigned int y = 0; y < (unsigned int)newHeight; ++y) {
            unsigned int origX = (x * originalWidth) / newWidth;
            unsigned int origY = (y * originalHeight) / newHeight;
            resizedImage.setPixel(x, y, originalImage.getPixel(origX, origY));
        }
    }

    texture.loadFromImage(resizedImage);
    return texture;
}
