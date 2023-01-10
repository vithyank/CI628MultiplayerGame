#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;

    int ballX = 0;
    int ballY = 0;



    
    
} game_data;

class Txt {
public:
    static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* ren);
};


class MyGame {

private:
    SDL_Rect player1 = { 200, 0, 30, 80 };
    SDL_Rect player2 = { 580, 0, 30, 80 };
    SDL_Rect ball = { 0, 0, 25, 25 };
   
    
    int player1Score = 0;
    int player2Score = 0;

    //Mix_Music* background_music;

   
public:


    
    void init(SDL_Renderer* renderer);
    //void init_audio();
    std::vector<std::string> messages;
    void on_receive(std::string message, std::vector<std::string>& args);
    void send(std::string message);
    void input(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
};
 


#endif