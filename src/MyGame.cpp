#include "MyGame.h"
#include <SDL_image.h>
#include <SDL_ttf.h>


//void MyGame::init(SDL_Renderer* renderer) {
   // Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
   // background_music = Mix_LoadMUS("bgmusic.mp3");
    //Mix_PlayMusic(background_music, -1);
//

SDL_Texture* Txt::LoadTexture(const char* texture, SDL_Renderer* ren) {
    SDL_Surface* assetSurface = IMG_Load(texture);
    SDL_Texture* txt = SDL_CreateTextureFromSurface(ren, assetSurface);
    SDL_FreeSurface(assetSurface);

    return txt;
}

SDL_Texture* ballTxt;
SDL_Texture* bat1Txt;
SDL_Texture* bat2Txt;


void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 4) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
        }
    }
    else {
        std::cout << "Received: " << cmd << std::endl;
    }

    if (cmd == "SCORES") {
        if (args.size() == 2) {
            player1Score = stoi(args.at(0));
            player2Score = stoi(args.at(1));
        }
    }
}


    
      

void MyGame::send(std::string message) {
    messages.push_back(message);
}


void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        //checks for key down event on the W key
    case SDLK_w:
        send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
        break;

        //checks for key down event on the S key
    case SDLK_s:
        send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
        break;

        //checks for key down event on the I key
    case SDLK_i:
        send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");
        break;

        //checks for key down event on the K key
    case SDLK_k:
        send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");
        break;
    }
}



void MyGame::update() {

    //updates the Y position of the player 2
    player1.y = game_data.player1Y;

    //updates the Y position of the player 2 
    player2.y = game_data.player2Y;

    //updates the Y position of the ball
    ball.y = game_data.ballY;
    
    //updates the X position of the ball
    ball.x = game_data.ballX;

    player1Score = player1Score;
    player2Score = player2Score;

    
       



    
  
}


//Render bats and ball textures
void MyGame::render(SDL_Renderer* renderer) {

   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

   bat1Txt = Txt::LoadTexture("bat1.png", renderer);
   SDL_RenderCopy(renderer, bat1Txt, NULL, &player1);

   bat2Txt = Txt::LoadTexture("bat2.png", renderer);
   SDL_RenderCopy(renderer, bat2Txt, NULL, &player2);
    //SDL_RenderFillRect(renderer, &player1);
    //SDL_RenderFillRect(renderer, &player2);

    ballTxt = Txt::LoadTexture("ball.png", renderer);
    SDL_RenderCopy(renderer, ballTxt, NULL, &ball);

  

    


    //Initialise Font for Scoring

    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
        exit(1);
    }
    //load font from file location, font size
    TTF_Font* Sans = TTF_OpenFont("Sportsball.ttf", 18);

   //Converts score to string
    std::string scoreText = "P1 Ronaldo: " + std::to_string(player1Score) + "  |   P2 Messi: " + std::to_string(player2Score);

    SDL_Color Yellow = { 255, 255, 0 };

    //String to char conversion
    SDL_Surface* surfaceScoreText =
        TTF_RenderText_Solid(Sans, scoreText.c_str(), Yellow);
    // convert into texture
    SDL_Texture* ScoreText = SDL_CreateTextureFromSurface(renderer, surfaceScoreText);

    //Rectangle parameters that hold scores
    SDL_Rect ScoreText_rect;// rect struct to hold scores
    ScoreText_rect.x = 150;
    ScoreText_rect.y = 20;
    ScoreText_rect.w = 490;
    ScoreText_rect.h = 50;
    SDL_RenderCopy(renderer, ScoreText, NULL, &ScoreText_rect);

    //Frees up surface and texture
    SDL_FreeSurface(surfaceScoreText);
    SDL_DestroyTexture(ScoreText);



    
   

    //SDL_RenderFillRect(renderer, &score);
}

    
   



