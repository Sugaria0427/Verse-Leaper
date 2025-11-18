#pragma once
#include<SDL.h>
#include<vector>
#include"Box.h"
#include"Drawable.h"
#include"Image.h"
#include"MouseInput.h"
#include"Camera.h"

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
    // ctor:
    Button(int x, int y, int width, int height, Name name, Image* buttonImage)
        : Box(x, y, width, height), isHover(false), name(name),buttonImage(buttonImage){
    }
    //setters & getters
    void setName(Name name) { name = name; }
    Name get_button_name() const { return name; }
    Image* getButtonImage() { return buttonImage; }
    void draw(SDL_Renderer* SDL_renderer) override;    // 绘制方块(使用surface方法)
    bool isMouseOn(MouseInput& msInput);    //判断鼠标是否在按钮上
    static void updateButtonHover(MouseInput &msInput, std::vector<Button*>& buttons);//判断鼠标是否在按钮vector中任意按钮上
    static Name findHoverInVec(std::vector<Button*>& buttons);
private:
    bool isHover;
    Name name;
    Image* buttonImage;
};
