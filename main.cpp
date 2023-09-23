#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

const int WIDTH = 800, HEIGHT = 600;
const char* NameEngine = "JoyEngine 0.1.23092023";

// Función para agregar la lógica del juego
void RunGame()
{
    // Agrega aquí la logica del juego
    ///sum logic :3

}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(NameEngine, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_MAXIMIZED);

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

    // Definir las coordenadas y dimensiones del rectángulo
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 800;
    rect.h = 20;

    // Rellenar el rectángulo con color
    SDL_RenderFillRect(renderer, &rect);


    //SDL_SetRenderDrawColor(renderer, 62, 86, 179, SDL_ALPHA_OPAQUE );
    SDL_SetRenderDrawColor(renderer, 247, 23, 255, SDL_ALPHA_OPAQUE );
    //SDL_RenderDrawLine(renderer, x1,y1,x2,y2);
                                     //largo 256   
    /*
    SDL_RenderDrawLine(renderer, 1,1,800,1);
    SDL_RenderDrawLine(renderer, 1,1,1,20);
    SDL_RenderDrawLine(renderer, 1,20,800,20);
    SDL_RenderDrawLine(renderer, 799,1,799,20);*/
    
    SDL_RenderDrawLine(renderer, 0,0,799,0);
    SDL_RenderDrawLine(renderer, 0,0,0,20);
    SDL_RenderDrawLine(renderer, 0,20,799,20);
    SDL_RenderDrawLine(renderer, 799,0,799,20);



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
