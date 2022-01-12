#include "head.h"

typedef struct
{
    SDL_Window* player_window;
    SDL_Renderer* player_render;
    SDL_Texture* player_texture;

    FILE* err_log;
    int err_code;
    char err_inf[100];

}vp_sdl_t;

vp_sdl_t vp_sdl;
void vpinit(vp_sdl_t* vp_sdl);
void vpclose(vp_sdl_t* vp_sdl);
int main(int argc, char* args[])
{
    vpinit(&vp_sdl);
	


    SDL_Delay(4000);
    return 0;

    
}

void write_error(vp_sdl_t* vp_sdl,int num,const char ch[])
{
    fprintf_s(vp_sdl->err_log,"error = %d\t%s\n\r",num,ch);
}
void vpinit(vp_sdl_t* vp_sdl)
{
    if (vp_sdl->err_code != 0)
        return;
    fopen_s(&vp_sdl->err_log,"error.log", "wb+");
    if (vp_sdl->err_log == NULL)
    {
        vp_sdl->err_code = 1;
        printf_s("\n\rerror = 1\n\r");
        vpclose(vp_sdl);
        exit(-1);
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        write_error(vp_sdl, 2, "sdl初始化失败！");
        return;
    }
    
    
    vp_sdl->player_window = SDL_CreateWindow("VedioPlayer",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE );

    if (vp_sdl->player_window == NULL)
    {
        write_error(vp_sdl, 3, "sdl窗口建立失败！");
        return;
    }

    if (SDL_SetWindowOpacity(vp_sdl->player_window, 0.9) != 0)
    {
        write_error(vp_sdl, 4, "sdl窗口透明度设置失败！");
        return;
    }


}


void vpclose(vp_sdl_t* vp_sdl)
{
    fclose(vp_sdl->err_log);
}