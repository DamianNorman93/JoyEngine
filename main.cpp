#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <cmath>

const int WIDTH = 800, HEIGHT = 600;
int WIDTHW = 800, HEIGHTH = 600;
const char* NameEngine = "JoyEngine 0.1.23092023-2103";

// Función para agregar la lógica del juego
void RunGame();
void createGUI(SDL_Renderer* renderer);

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

        //Llamar a la interfaz
        createGUI(renderer);

        SDL_RenderPresent(renderer);
        
        // Lógica del juego que se ejecuta en cada iteración del bucle principal
        RunGame();

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
    ///sum logic here :3

}

void draw_rectangle(SDL_Renderer* renderer, int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b)
{
    // Asegurarse de que el renderer esté configurado correctamente
    if (renderer == nullptr)
    {
        //Mostrar un mensaje de error o manejar la falta de un renderer apropiado
        return;
    }

    // Definir las coordenadas y dimensiones del rectángulo
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    // Establecer el color de dibujo
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

    // Rellenar el rectángulo con el color especificado
    SDL_RenderFillRect(renderer, &rect);
}

void draw_filled_circle(SDL_Renderer* renderer, int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx*dx + dy*dy <= radius*radius) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void draw_rounded_rectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int cornerRadius, Uint8 r, Uint8 g, Uint8 b)
{
    // Asegurarse de que el renderer esté configurado correctamente
    if (renderer == nullptr)
    {
        // Mostrar un mensaje de error o manejar la falta de un renderer apropiado
        return;
    }

    // Establecer el color de dibujo
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

    // Dibujar círculos en las esquinas
    int circleRadius = cornerRadius;

    // Esquina superior izquierda
    draw_filled_circle(renderer, x + 10, y, circleRadius, r, g, b); //left top
    //draw_filled_circle(renderer, x + circleRadius + 1, y + h - circleRadius, circleRadius, r, g, b); //left bottom

    //SDL_RenderDrawLine(renderer, x + circleRadius, y, x + w - circleRadius, y);
    //SDL_RenderDrawLine(renderer, x, y + circleRadius, x, y + h - circleRadius);
    //SDL_RenderDrawLine(renderer, x + circleRadius, y + h, x + w - circleRadius, y + h);
    //SDL_RenderDrawLine(renderer, x + w, y + circleRadius, x + w, y + h - circleRadius);

    // Rectángulos en los bordes
    SDL_Rect rect;
    
    // Borde superior
    rect.x = x + cornerRadius;
    rect.y = y;
    rect.w = w - 2 * cornerRadius;
    rect.h = cornerRadius;
    SDL_RenderFillRect(renderer, &rect);

    // Borde inferior
    rect.x = x + cornerRadius;
    rect.y = y + h - cornerRadius;
    rect.w = w - 2 * cornerRadius;
    rect.h = cornerRadius;
    //SDL_RenderFillRect(renderer, &rect);

    // Borde izquierdo
    rect.x = x;
    rect.y = y + cornerRadius;
    rect.w = cornerRadius;
    rect.h = h - 2 * cornerRadius;
    SDL_RenderFillRect(renderer, &rect);

    // Borde derecho
    rect.x = x + w - cornerRadius;
    rect.y = y + cornerRadius;
    rect.w = cornerRadius;
    rect.h = h - 2 * cornerRadius;
    //SDL_RenderFillRect(renderer, &rect);

    // Rellenar el espacio central
    rect.x = x + cornerRadius;
    rect.y = y + cornerRadius;
    rect.w = w - 2 * cornerRadius;
    rect.h = h - 2 * cornerRadius;
    //SDL_RenderFillRect(renderer, &rect);
}


//Interfaz
void createGUI(SDL_Renderer* renderer)
{
      draw_rectangle(renderer, 0, 0, WIDTHW, 20, 255, 255, 255);
      draw_rectangle(renderer, 0,22,200,HEIGHTH-99, 250, 250, 250);
      draw_rectangle(renderer, 201,22,WIDTHW-2,HEIGHTH-99, 133, 133, 133);
      //draw_rectangle(renderer, 0, HEIGHTH-70, WIDTHW, 30, 194, 189, 199);
      draw_rounded_rectangle(renderer, 20, HEIGHTH-70, WIDTHW/2, 50, 5, 80, 130, 140);
      
      //draw_filled_circle(renderer, 0, HEIGHTH-200, 15, 80, 130, 140);
}