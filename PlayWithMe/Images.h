#ifndef IMAGES
#define IMAGES

#include<string>
#include<iostream>

#include<algorithm>

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

    Image(const Image& image) {
        this->tag = image.tag;
        this->pathImage = image.pathImage;
        this->shape = image.shape;
        if (!this->texture.loadFromFile(image.pathImage)) {
            std::cout << "PROBLEM " << image.pathImage << ' ' << image.tag << std::endl;
        }
        else
            this->shape.setTexture(&this->texture);
        this->isVisible = image.isVisible;
        this->size = image.size;

        this->pathSound = image.pathSound;
        if (this->pathSound != "") {
            this->sound.loadFromFile(this->pathSound);
            this->player.setBuffer(this->sound);
        }
    } 
    Image& operator=(const Image& image) {
        this->tag = image.tag;
        this->pathImage = image.pathImage;
        this->shape = image.shape;
        if (!this->texture.loadFromFile(this->pathImage)) {
            std::cout << "PROBLEM " << image.pathImage << ' ' << image.tag << std::endl;
        }
        else
            this->shape.setTexture(&this->texture);
        this->isVisible = image.isVisible;
        this->size = image.size;

        this->pathSound = image.pathSound;
        if (this->pathSound != "") {
            this->sound.loadFromFile(this->pathSound);
            this->player.setBuffer(this->sound);
        }
        return *this;
    }

    bool operator ==(Image& obj) {
        std::cout << this->pathImage << ' ' << obj.pathImage << std::endl;
        return (this->pathImage == obj.pathImage);
    }

    Image()
    {

    }
    void play()
    {
        this->player.play();
    }

    void setTexture(const std::string& texture)
    {
        this->pathImage = ImagePath + texture;

        if (!this->texture.loadFromFile(this->pathImage))
            std::cout << "problem \n";
        shape.setTexture(&this->texture);
        //shape.setSize(sf::Vector2f((width + height) / 19, (width + height) / 19));
    }

    sf::Texture& getTexture()
    {
        return this->texture;
    }

    void setSound(const std::string& sound)
    {
        this->pathSound = AudioPath + sound;
        if (!this->sound.loadFromFile(AudioPath + sound)) {
            std::cout << "ERROR: " << sound << " WASN'T LOADED ! \n";
        }
        player.setBuffer(this->sound);
    }

    void setSound(const sf::SoundBuffer& sound)
    {
        this->player.setBuffer(sound);
    }

    const sf::SoundBuffer& getSound() const {
        return this->sound;
    }

    const sf::Sound& getlayer() const {
        return this->player;
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

    std::string pathImage, pathSound;

protected:
    sf::Texture texture;
    sf::RectangleShape shape;

    bool isVisible = true;
    sf::Vector2f size;

    sf::SoundBuffer sound;
    sf::Sound player;
};

#endif