#pragma once
#include<SDL.h>
#include<vector>
#include"Box.h"
#include"Drawable.h"

class Image;

class MouseInput;

class Button :
    public Box, public Drawable
{
public:
    enum class Name {
        menu_Continue,
        menu_Start,
        menu_Option,
        menu_Quit,
        Null
    };
public:
    Button(int x, int y, int width, int height, Name name, Image* buttonImage);
    ~Button() {}
public:
    void draw(SDL_Renderer* SDL_renderer) override;

    void setName(Name name) { name = name; }
    Name get_button_name() const { return name; }
    Image* getButtonImage() { return buttonImage; }
    bool isMouseOn(MouseInput& msInput);
    
    static void updateButtonsHover(MouseInput &msInput, std::vector<Button*>& buttons);
    static Name findHoverButton(std::vector<Button*>& buttons);
private:
    bool isHover;
    Name name;
    Image* buttonImage;
};
