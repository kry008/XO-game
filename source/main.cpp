#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <citro2d.h>


int player = 1; //1 - X 2 - O
bool win = false;
bool all9 = false;
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

void drawMoves(int display)
{
        for(int square = 0; square < 9; square++)
        {
                if(pressedSquares[square] == 1)
                {
                        if(display == 1)
                        {
                                C2D_DrawLine(10 + (square % 3) * 100, 10 + (square / 3) * 60, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 90 + (square % 3) * 100, 50 + (square / 3) * 60, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
                                C2D_DrawLine(90 + (square % 3) * 100, 10 + (square / 3) * 60, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 10 + (square % 3) * 100, 50 + (square / 3) * 60, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
                        }
                        else
                        {
                                C2D_DrawLine(10 + (square % 3) * 106, 10 + (square / 3) * 80, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 96 + (square % 3) * 106, 70 + (square / 3) * 80, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
                                C2D_DrawLine(96 + (square % 3) * 106, 10 + (square / 3) * 80, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 10 + (square % 3) * 106, 70 + (square / 3) * 80, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), 2, 0);
                        }
                }
                else if(pressedSquares[square] == 2)
                {
                        if(display == 1)
                        {
                                C2D_DrawCircleSolid(50 + (square % 3) * 100, 30 + (square / 3) * 60, 0, 25, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
                        }
                        else
                        {
                                C2D_DrawCircleSolid(53 + (square % 3) * 106, 40 + (square / 3) * 80, 0, 25, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
                        }
                }
        }
}

void touching(touchPosition touch)
{
        if(touch.px < 106 && touch.py < 80 && pressedSquares[0] == 0)
        {
                pressedSquares[0] = player;
                player = player == 1 ? 2 : 1;
        }
        else if(touch.px < 212 && touch.px > 80 && touch.py < 80 && pressedSquares[1] == 0)
        {
                pressedSquares[1] = player;
                player = player == 1 ? 2 : 1;
        }
        else if(touch.px < 320 && touch.px > 212 && touch.py < 80 && pressedSquares[2] == 0)
        {
                pressedSquares[2] = player;
                player = player == 1 ? 2 : 1;
        }
        else if(touch.px < 106 && touch.py < 160 && touch.py > 80 && pressedSquares[3] == 0)
        {
                pressedSquares[3] = player;
                player = player == 1 ? 2 : 1;
        }
        else if(touch.px < 212 && touch.px > 80 && touch.py < 160 && touch.py > 80 && pressedSquares[4] == 0)
        {
                pressedSquares[4] = player;
                player = player == 1 ? 2 : 1;
        }
        else if(touch.px < 320 && touch.px > 212 && touch.py < 160 && touch.py > 80 && pressedSquares[5] == 0)
        {
                pressedSquares[5] = player;
                player = player == 1 ? 2 : 1;
        }
        else if(touch.px < 106 && touch.py < 240 && touch.py > 160 && pressedSquares[6] == 0)
        {
                pressedSquares[6] = player;
                player = player == 1 ? 2 : 1;
        }
        else if(touch.px < 212 && touch.px > 80 && touch.py < 240 && touch.py > 160 && pressedSquares[7] == 0)
        {
                pressedSquares[7] = player;
                player = player == 1 ? 2 : 1;
        }
        else if(touch.px < 320 && touch.px > 212 && touch.py < 240 && touch.py > 160 && pressedSquares[8] == 0)
        {
                pressedSquares[8] = player;
                player = player == 1 ? 2 : 1;
        }
}

void checkWin()
{
        if(pressedSquares[0] == pressedSquares[1] && pressedSquares[1] == pressedSquares[2] && pressedSquares[0] != 0)
        {
                win = true;
        }
        else if(pressedSquares[3] == pressedSquares[4] && pressedSquares[4] == pressedSquares[5] && pressedSquares[3] != 0)
        {
                win = true;
        }
        else if(pressedSquares[6] == pressedSquares[7] && pressedSquares[7] == pressedSquares[8] && pressedSquares[6] != 0)
        {
                win = true;
        }
        else if(pressedSquares[0] == pressedSquares[3] && pressedSquares[3] == pressedSquares[6] && pressedSquares[0] != 0)
        {
                win = true;
        }
        else if(pressedSquares[1] == pressedSquares[4] && pressedSquares[4] == pressedSquares[7] && pressedSquares[1] != 0)
        {
                win = true;
        }
        else if(pressedSquares[2] == pressedSquares[5] && pressedSquares[5] == pressedSquares[8] && pressedSquares[2] != 0)
        {
                win = true;
        }
        else if(pressedSquares[0] == pressedSquares[4] && pressedSquares[4] == pressedSquares[8] && pressedSquares[0] != 0)
        {
                win = true;
        }
        else if(pressedSquares[2] == pressedSquares[4] && pressedSquares[4] == pressedSquares[6] && pressedSquares[2] != 0)
        {
                win = true;
        }
        
}

void checkAll9()
{
        for(int i = 0; i < 9; i++)
        {
                if(pressedSquares[i] == 0)
                {
                        return;
                }
        }
        all9 = true;
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
                C2D_TargetClear(bottom, C2D_Color32(0x09, 0x00, 0x00, 0xFF));
                if(!win && !all9)
                {
                        C2D_SceneBegin(top);
                        drawGridTopScreen();
                        drawWhoseMove();
                        drawMoves(1);
                        C2D_SceneBegin(bottom);
                        drawGridBottomScreen();
                        drawMoves(2);
                        //check if touched
                        if(touch.px != 0 && touch.py != 0)
                                touching(touch);
                        checkWin();
                }
                else
                {
                        if(win)
                        {
                                C2D_SceneBegin(top);
                                C2D_Text text;
                                C2D_TextBuf buf = C2D_TextBufNew(4096);
                                if(player == 1)
                                {
                                        C2D_TextParse(&text, buf, "O wins!");
                                        C2D_TextOptimize(&text);
                                        C2D_DrawText(&text, C2D_WithColor, 10, 200, 0, 0.5f, 0.5f, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
                                }
                                else
                                {
                                        C2D_TextParse(&text, buf, "X wins!");
                                        C2D_TextOptimize(&text);
                                        C2D_DrawText(&text, C2D_WithColor, 10, 200, 0, 0.5f, 0.5f, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
                                }
                                C2D_TextBufDelete(buf);
                                C2D_SceneBegin(bottom);
                        }
                        else if(all9)
                        {
                                C2D_SceneBegin(top);
                                C2D_Text text;
                                C2D_TextBuf buf = C2D_TextBufNew(4096);
                                C2D_TextParse(&text, buf, "Draw!");
                                C2D_TextOptimize(&text);
                                C2D_DrawText(&text, C2D_WithColor, 10, 200, 0, 0.5f, 0.5f, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
                                C2D_TextBufDelete(buf);
                                C2D_SceneBegin(bottom);
                        }
                        //press A to restart
                        if(kHeld & KEY_A)
                        {
                                player = 1;
                                all9 = false;
                                win = false;
                                for(int i = 0; i < 9; i++)
                                {
                                        pressedSquares[i] = 0;
                                }
                        }
                }
		C3D_FrameEnd(0);
        }
        C2D_Fini();
        C3D_Fini();
        gfxExit();
        romfsExit();
        return 0;
}