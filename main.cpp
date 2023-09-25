#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>
#include <cmath>
#include <vector>

const int WIDTH = 800, HEIGHT = 600;
int WIDTHW = 800, HEIGHTH = 600;
const char* NameEngine = "JoyEngine 0.1.23092023-2103";
SDL_Texture* spriteTexture = nullptr;


// Función para agregar la lógica del juego
void RunGame();
void createGUI(SDL_Renderer* renderer);
void draw_sprite(SDL_Renderer* renderer, int x, int y, SDL_Texture* spriteTexture, int alpha);


int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 2;
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

    // Load your sprite image with transparency (e.g., PNG)
    SDL_Surface* spriteSurface = IMG_Load("./sprite.png");
    if (spriteSurface == nullptr)
    {
        std::cout << "Error loading sprite: " << IMG_GetError() << std::endl;
        // Handle error and return
    }

    // Crea una textura a partir de spriteSurface
    SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);

    // Verifica si la creación de la textura fue exitosa
    if (spriteTexture == nullptr)
    {
        std::cout << "Error al crear la textura desde la superficie: " << SDL_GetError() << std::endl;
        // Maneja el error según sea necesario
    } else {
        std::cout << "ok" << std::endl;
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

        //draw_sprite(renderer, 16, 48, spriteTexture , 255);


        
        SDL_RenderPresent(renderer);
        
        // Lógica del juego que se ejecuta en cada iteración del bucle principal
        //RunGame();

        

    }
    SDL_FreeSurface(spriteSurface);  // Free the surface as it's no longer needed
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//funciones fuera del main
//Funcion para dibujar un rectangulo simple relleno de color
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

//Funcion para dibujar un circulo, esto se usa con el rectangulo con esquinas redondeadas
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

//Funcion para dibujar un rectangulo con esquinas redondeadas
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
    draw_filled_circle(renderer, x + circleRadius, y + circleRadius, circleRadius, r, g, b); //left top
    draw_filled_circle(renderer, x + circleRadius, y + h - circleRadius, circleRadius, r, g, b); //left bottom
    draw_filled_circle(renderer, x + (w - circleRadius), y + (h - circleRadius), circleRadius, r, g, b); //right bottom   
    draw_filled_circle(renderer, x + (w - circleRadius), y + circleRadius, circleRadius, r,g,b); //right top
    
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
    SDL_RenderFillRect(renderer, &rect);

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
    SDL_RenderFillRect(renderer, &rect);

    // Rellenar el espacio central
    rect.x = x + cornerRadius;
    rect.y = y + cornerRadius;
    rect.w = w - 2 * cornerRadius;
    rect.h = h - 2 * cornerRadius;
    SDL_RenderFillRect(renderer, &rect);
}

//Funcion para dibujar texto
void draw_text(SDL_Renderer* renderer, int x, int y, const std::string& text, int text_size, Uint8 r, Uint8 g, Uint8 b) {
    // Crear una estructura de color SDL_Color
    SDL_Color color = { r, g, b, 250 }; // El último valor es la opacidad (255 para opaco)

    // Cargar la fuente (ajusta la ruta a tu fuente TTF)
    TTF_Font* font = TTF_OpenFont("Arial.ttf", text_size);
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Crear una superficie de texto renderizada   
    SDL_Surface* text_surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);

    if (!text_surface) {
        printf("Failed to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    // Crear una textura a partir de la superficie de texto
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture) {
        printf("Failed to create text texture! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(text_surface);
        TTF_CloseFont(font);
        return;
    }

    // Definir el rectángulo de destino
    SDL_Rect dst_rect = { x, y, text_surface->w, text_surface->h };

    // Dibujar la textura en el renderer
    SDL_RenderCopy(renderer, text_texture, NULL, &dst_rect);

    // Definir e iniciar carga de sprites



    // Limpiar recursos
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
}

void draw_sprite(SDL_Renderer* renderer, int x, int y, SDL_Texture* spriteTexture, int alpha)
{

    // Set the alpha value (transparency) for the sprite
    SDL_SetTextureAlphaMod(spriteTexture, alpha);

    // Get the width and height of the sprite texture
    int spriteWidth, spriteHeight;
    SDL_QueryTexture(spriteTexture, nullptr, nullptr, &spriteWidth, &spriteHeight);

    // Create a destination rectangle for rendering
    SDL_Rect dstRect = { x, y, spriteWidth, spriteHeight };

    // Render the sprite
    SDL_RenderCopy(renderer, spriteTexture, nullptr, &dstRect);
}

//Interfaz siempre al final
void createGUI(SDL_Renderer* renderer)
{   
    bool show_gui = true;

    if (show_gui = true){
      draw_rectangle(renderer, 0, 0, WIDTHW, 27, 255, 255, 255);
      
      //draw_rectangle(renderer, 0,21,200,HEIGHTH-100, 250, 250, 250);
      //draw_rectangle(renderer, 201,21,WIDTHW-2,HEIGHTH-100, 133, 133, 133);
      //draw_rectangle(renderer, 0, HEIGHTH-70, WIDTHW, 30, 194, 189, 199);
      
      //draw_rounded_rectangle(renderer, 0, 0, WIDTHW, 20, 6, 255, 255, 255); //barra de menus
      //draw_rounded_rectangle(renderer, 0, 21, 200, HEIGHTH-100, 6, 200, 200, 200); //panel izquierdo
      
      draw_rounded_rectangle(renderer, 0, 28,WIDTHW/*-202*/, 20, 6, 200, 200, 200);//main toolbar canvas
                                        
      //draw_rounded_rectangle(renderer, 201,42,WIDTHW-202,HEIGHTH-120, 6, 133, 133, 133);//main canvas
      
      draw_rounded_rectangle(renderer, 0,49,WIDTHW/*-205*/,HEIGHTH-128, 6, 133, 133, 133);//main canvas

      draw_rounded_rectangle(renderer, 1, HEIGHTH-78, WIDTHW-2, 76, 6, 194, 189, 199);//panel de pestañas de interfaz
      
      //draw_filled_circle(renderer, 0, HEIGHTH-200, 15, 80, 130, 140);

      draw_text(renderer, 1, 1, "\u00A1a-string!", 15, 0, 0, 0); // Color del texto (blanco en formato RGB) 

      //currentFrame = (currentFrame + 1) % spriteFrames.size();
      //alpha = (alpha + 1) % 256; // Adjust alpha value as needed
      //draw_sprite(renderer, 100, 100, spriteTexture , 255);
      
      // Load your sprite image with transparency (e.g., PNG)
    SDL_Surface* spriteSurface = IMG_Load("./ground.png");
    if (spriteSurface == nullptr)
    {
        std::cout << "Error loading sprite: " << IMG_GetError() << std::endl;
        // Handle error and return
    }

    // Crea una textura a partir de spriteSurface
    SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);

    // Verifica si la creación de la textura fue exitosa
    if (spriteTexture == nullptr)
    {
        std::cout << "Error al crear la textura desde la superficie: " << SDL_GetError() << std::endl;
        // Maneja el error según sea necesario
    }
    /*  
    draw_sprite(renderer, 0, 20, spriteTexture , 128);
    draw_sprite(renderer, 0+64, 20, spriteTexture , 200);
    draw_sprite(renderer, 0+128, 20, spriteTexture , 255);*/

    draw_sprite(renderer, 16, 64, spriteTexture , 255);

    }
    
      
}

void RunGame()
{
    // Agrega aquí la logica del juego
    ///sum logic here :3
    //load game.asset
    //read game.json
    //load interpreter
    //display interpreter
}