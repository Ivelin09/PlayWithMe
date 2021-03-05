#ifndef IMAGES
#define IMAGES

#include<string>
#include<iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const std::string ImagePath = "Content/";
const std::string AudioPath = "Sound/";

extern const double width;
extern const double height;

class Image
{
public:
    std::string tag;
    Image()
    {

    }
    void play()
    {
        this->player.play();
    }

    void setTexture(const std::string& texture)
    {
        if (!this->texture.loadFromFile(ImagePath + texture))
            std::cout << "problem \n";
        shape.setTexture(&this->texture);
        shape.setSize(sf::Vector2f((width + height) / 19, (width + height) / 19));
    }

    void setTexture(const sf::Texture& texture)
    {
        this->texture = texture;
    }

    sf::Texture& getTexture()
    {
        return this->texture;
    }

    void setSound(const std::string& sound)
    {
        if (!this->sound.loadFromFile(AudioPath + sound)) {
            std::cout << "ERROR: " << sound << " WASN'T LOADED ! \n";
        }
        player.setBuffer(this->sound);
    }

    sf::RectangleShape& getShape()
    {
        return this->shape;
    }

    void setVisibility(const bool flag)
    {
        this->isVisible = flag;
        if (flag == false)
        {
            this->size = this->shape.getSize();
            shape.setSize(sf::Vector2f(0, 0));
        }
        else
            shape.setSize(this->size);
    }

protected:
    sf::Texture texture;
    sf::RectangleShape shape;

    bool isVisible = true;
    sf::Vector2f size;

    sf::SoundBuffer sound;
    sf::Sound player;
};

#endif
