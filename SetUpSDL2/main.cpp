#include "Graphics.h"
#include "Objects.h"
#include "Logic.h"
#include "Resource.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    Graphics graphics;
    graphics.init();

    SDL_Texture* background = graphics.loadTexture(SKY_BACKGROUND_PATH);
    SDL_Texture* birdTex = graphics.loadTexture(BIRD_PATH);
    SDL_Texture* pipeTex = graphics.loadTexture(PIPE_PATH);

    Bird bird;
    Pipe pipes;
    startGameSetUp(pipes);

    waitUntilKeyPressed(); // chờ người chơi bấm phím bắt đầu

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) {
            quit = true;
        }

        // Cập nhật logic chim bay
        birdFly(currentKeyStates, quit, bird);

        // Vẽ nền
        graphics.prepareScene(background);

        // Vẽ ống
        pipeRunning(pipes, graphics, pipeTex, pipeSpeed, true);

        // Vẽ chim
        graphics.renderTexture(birdTex, bird.birdPosX, bird.birdPosY);

        // Kiểm tra va chạm
        checkCollision(pipes, bird, quit);

        graphics.presentScene();
        SDL_Delay(16); // ~60 FPS
    }

    graphics.quit();
    SDL_Quit();
    IMG_Quit();

    return 0;
}
