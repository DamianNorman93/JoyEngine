#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int WIDTH = 800, HEIGHT = 600;
const char* NameEngine = "JoyEngine";

// Función para agregar la lógica del juego
void RunGame()
{
    // Agrega aquí la logica del juego
    

}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(NameEngine, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Error al crear la ventana: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr)
    {
        std::cout << "Error al crear el renderizador: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE );
    //SDL_RenderDrawLine(renderer, x1,y1,x2,y2);
                                     //largo 256   
    /*
    SDL_RenderDrawLine(renderer, 1,1,800,1);
    SDL_RenderDrawLine(renderer, 1,1,1,20);
    SDL_RenderDrawLine(renderer, 1,20,800,20);
    SDL_RenderDrawLine(renderer, 799,1,799,20);*/
    
    SDL_RenderDrawLine(renderer, 3,3,797,3);
    SDL_RenderDrawLine(renderer, 3,3,3,17);
    SDL_RenderDrawLine(renderer, 3,17,797,17);
    SDL_RenderDrawLine(renderer, 797,3,797,17);
    

       

    
    


    SDL_RenderPresent(renderer);
    


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

        // Lógica del juego que se ejecuta en cada iteración del bucle principal
        //RunGame();

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
