#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <citro2d.h>


int player = 1; //1 - X 2 - O
bool win = false;
int pressedSquares[9] = {0,0,0,0,0,0,0,0,0};

C3D_RenderTarget* top;
C3D_RenderTarget* bottom;

void drawGridTopScreen()
{
        C2D_DrawLine(0, 0, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 0, 180, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(1, 1, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 300, 1, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(100, 0, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 100, 180, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(200, 0, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 200, 180, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(300, 0, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 300, 180, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(0, 60, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 300, 60, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(0, 120, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 300, 120, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(0, 180, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 300, 180, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
}
void drawGridBottomScreen()
{
        //320x240
        C2D_DrawLine(0, 0, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 0, 240, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(1, 1, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 320, 1, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(0, 80, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 320, 80, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(0, 160, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 320, 160, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(0, 240, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 320, 240, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(106, 0, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 106, 240, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(212, 0, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 212, 240, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
        C2D_DrawLine(320, 0, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 320, 240, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);

}

void drawWhoseMove()
{
        C2D_Text text;
        C2D_TextBuf buf = C2D_TextBufNew(4096);

        if(player == 1)
        {
                C2D_TextParse(&text, buf, "X's move");
                C2D_TextOptimize(&text);
                C2D_DrawText(&text, C2D_WithColor, 10, 200, 0, 0.5f, 0.5f, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
        }
        else
        {
                C2D_TextParse(&text, buf, "O's move");
                C2D_TextOptimize(&text);
                C2D_DrawText(&text, C2D_WithColor, 10, 200, 0, 0.5f, 0.5f, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
        }
        
        C2D_TextBufDelete(buf);
}

int main(int argc, char **argv) {

	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();


	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
        C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
        // Main loop
        while (aptMainLoop())
        {
                hidScanInput();
                
                touchPosition touch;
                hidTouchRead(&touch);
        
                u32 kHeld = hidKeysHeld();
                if (kHeld & KEY_START) break; // break in order to return to hbmenu

                C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
                C2D_TargetClear(top, C2D_Color32(0x00, 0x00, 0x00, 0xFF));
                C2D_SceneBegin(top);

                drawGridTopScreen();
                drawWhoseMove();
                C2D_TargetClear(bottom, C2D_Color32(0x09, 0x00, 0x00, 0xFF));
                C2D_SceneBegin(bottom);
                drawGridBottomScreen();
		C3D_FrameEnd(0);
        }
        C2D_Fini();
        C3D_Fini();
        gfxExit();
        romfsExit();
        return 0;
}