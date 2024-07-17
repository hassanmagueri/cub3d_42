#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

// Function for finding absolute value 
int abs(int n) { return ((n > 0) ? n : (n * (-1))); }

// DDA Function for line generation 
void DDA(SDL_Renderer *renderer, int X0, int Y0, int X1, int Y1) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 

    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 

    // calculate increment in x & y for each steps 
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 

    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) { 
        SDL_RenderDrawPoint(renderer, round(X), round(Y)); 
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
        SDL_RenderPresent(renderer);
        SDL_Delay(100); // for visualization of line- 
                        // generation step by step 
    } 
} 

// Driver program 
int main() 
{ 
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("DDA Line Generation", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Set draw color to red (RGB)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Function call
    DDA(renderer, 2, 2, 14, 16); 

    // Wait for 5 seconds
    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0; 
}
