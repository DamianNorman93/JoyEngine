#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

const int WIDTH = 800, HEIGHT = 600;
int WIDTHW = 800, HEIGHTH = 600;
const char* NameEngine = "JoyEngine 0.1.23092023-2103";

// Función para agregar la lógica del juego
void RunGame();
void createGUI();

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        //std::cout << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(NameEngine, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTHW, HEIGHTH, SDL_WINDOW_RESIZABLE);

    if (window == nullptr)
    {
        //std::cout << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr)
    {
        //std::cout << "Error al crear el renderizador: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    
    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
        }
        
        SDL_GetWindowSize(window, &WIDTHW, &HEIGHTH);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE );    

        // Definir las coordenadas y dimensiones del rectángulo
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = WIDTHW;
        rect.h = 20;

        // Rellenar el rectángulo con color
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 250, 250, 250, SDL_ALPHA_OPAQUE);
        SDL_Rect rect1;
        rect1.x = 0;
        rect1.y = 22;
        rect1.w = 200;
        rect1.h = HEIGHTH-99;
        
        SDL_SetRenderDrawColor(renderer, 133, 133, 133, SDL_ALPHA_OPAQUE );
        
        SDL_RenderFillRect(renderer, &rect1);

        SDL_RenderDrawLine(renderer, 0,0,WIDTHW-1,0);
        SDL_RenderDrawLine(renderer, 0,0,0,20);
        SDL_RenderDrawLine(renderer, 0,20,WIDTHW-1,20);
        SDL_RenderDrawLine(renderer, WIDTHW-1,0,WIDTHW-1,20);

        SDL_Rect rect2;
        rect2.x = 201;
        rect2.y = 22;
        rect2.w = WIDTHW-2;
        rect2.h = HEIGHTH-99;

        SDL_SetRenderDrawColor(renderer, 133, 133, 133, SDL_ALPHA_OPAQUE );

        SDL_RenderFillRect(renderer, &rect2);

        SDL_SetRenderDrawColor(renderer, 194, 189, 199, 128 );

        SDL_Rect rect3;
        rect3.x = 0;
        rect3.y = HEIGHTH-80;
        rect3.w = WIDTHW;
        rect3.h = 80;

        SDL_RenderFillRect(renderer, &rect3);      

        SDL_SetRenderDrawColor(renderer, 127, 63, 191, 128);

        SDL_Rect rect4;
        rect4.x = (WIDTHW/2)-120;
        rect4.y = HEIGHTH-60;
        rect4.w = 240;
        rect4.h = 40;

        SDL_RenderFillRect(renderer, &rect4);    

        SDL_RenderPresent(renderer);
        
        // Lógica del juego que se ejecuta en cada iteración del bucle principal
        //RunGame();

    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//funciones fuera del main

void RunGame()
{
    // Agrega aquí la logica del juego
    ///sum logic :3

}

void createGUI()
{
        
}