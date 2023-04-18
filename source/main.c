#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <citro2d.h>
#include "util.h"
#include <3ds.h>

#define HEIGHT 240
#define WIDTH 400

#define row 24
#define col 40

int temp_table[row][col];
void InitGameOfLife();
void GameOfLife(int a[row][col]);
void printTable(int a[row][col]);

typedef struct {
	float x, y;
	C2D_Sprite CellSprite;
} GameOfLifeCell;

GameOfLifeCell* CellArray;
int size = 0;
void updateSpriteList(int a[row][col], C2D_SpriteSheet sheet)
{	
	size = 0;
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			if(a[i][j] == 1)
			{
				size++;
			}
		}
	}
	CellArray = malloc(size * sizeof(GameOfLifeCell));
	int idx = 0;
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			if(a[i][j] == 1)
			{
				CellArray[idx].y = i * 10;
				CellArray[idx].x = j * 10;
				C2D_SpriteFromSheet(&CellArray[idx].CellSprite, sheet, 0);
				idx++;
			}
		}
	}
}

int CountLiveCells(int a[row][col], int r, int c)
{
     
    int count = 0;
    for(int i = r - 1; i <= r+1; i++)
    {
        for(int j = c-1; j <= c+1; j++)
        {
            if((i==r && j==c) || (i < 0 || j < 0) || (i>=row || j>=col))
            {
                continue;
            }
            if(a[i][j] == 1)
            {
                count++;
            }
        }
    }
        
    
    return count;
}



void GameOfLife(int a[row][col])
{
    int table1[row][col];
    int table2[row][col];
    int neightbour_live_cell;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            table1[i][j] = a[i][j];
            table2[i][j] = 0;
        }
    }

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            neightbour_live_cell = CountLiveCells(table1, i, j);
            if(table1[i][j] == 1 && (neightbour_live_cell==2 || neightbour_live_cell  == 3))
            {
                table2[i][j] = 1;
            }
            else if(table1[i][j]==0 && neightbour_live_cell == 3)
            {
                table2[i][j] = 1;
            }
            else{
                table2[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            temp_table[i][j] = table2[i][j];
        }
    }

}

void InitGameOfLife(int pattern)
{
    
    
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            temp_table[i][j] = 0;
        }
    }

	if(pattern == 0)
	{
		temp_table[2][0] = 1;
		temp_table[3][1] = 1;
		temp_table[3][2] = 1;
		temp_table[2][2] = 1;
		temp_table[1][2] = 1;
	}
    else if(pattern == 1)
	{
		temp_table[5][1] = 1;
		temp_table[5][2] = 1;
		temp_table[6][1] = 1;
		temp_table[6][2] = 1;
		temp_table[5][11] = 1;
		temp_table[6][11] = 1;
		temp_table[7][11] = 1;
		temp_table[4][12] = 1;
		temp_table[8][12] = 1;
		temp_table[3][13] = 1;
		temp_table[9][13] = 1;
		temp_table[3][14] = 1;
		temp_table[9][14] = 1;
		temp_table[6][15] = 1;
		temp_table[4][16] = 1;
		temp_table[8][16] = 1;
		temp_table[5][17] = 1;
		temp_table[6][17] = 1;
		temp_table[7][17] = 1;
		temp_table[6][18] = 1;
		temp_table[3][21] = 1;
		temp_table[4][21] = 1;
		temp_table[5][21] = 1;
		temp_table[3][22] = 1;
		temp_table[4][22] = 1;
		temp_table[5][22] = 1;
		temp_table[2][23] = 1;
		temp_table[6][23] = 1;
		temp_table[1][25] = 1;
		temp_table[2][25] = 1;
		temp_table[6][25] = 1;
		temp_table[7][25] = 1;
		temp_table[3][35] = 1;
		temp_table[4][35] = 1;
		temp_table[3][36] = 1;
		temp_table[4][36] = 1;
	}

	

    
}

void printTable(int a[row][col])
{
	
    printf("\x1b[1;1H\n\n\n\n\n\n\n\n");
    for(int i=0; i<row; i++){
        printf("\n");
        for(int j=0;j<col;j++){
            if(a[i][j] == 1)
            {
                printf("*"); 
            }
            else{
                printf(".");

            }
        }
        printf("\r\n");
    }
}


int main(int argc, char* argv[])
{
	//Init services
	romfsInit();
	gfxInitDefault(); 
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	InitGameOfLife(1);
	consoleInit(GFX_BOTTOM, NULL);

	
	int counter = 0;
	getSysLanguage();

	// Create Screen
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	// Load Sprites
	static C2D_SpriteSheet spriteSheet;
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if(!spriteSheet) svcBreak(USERBREAK_PANIC);
	
	
	
	//Init sprites
	
	
	int generations = 0;
	// Main loop
	while (aptMainLoop())
	{
		counter++;
		//gspWaitForVBlank();
		//gfxSwapBuffers();
		hidScanInput();
		//free(CellArray);
        updateSpriteList(temp_table, spriteSheet);
		svcSleepThread(100 * 1000000);
        GameOfLife(temp_table);
        generations++;
    
		
		printf("\x1b[1;1HSprites: %zu/%u\x1b[K", 1, 1);
		printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);
		printf("\n\n\n\n\n\r%d", counter);
		
		//Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(top);
		
		
		for(int idx = 0; idx < size; idx++)
		{
			C2D_SpriteSetCenter(&CellArray[idx].CellSprite, 0.0f, 0.0f);
			C2D_SpriteSetPos(&CellArray[idx].CellSprite, CellArray[idx].x, CellArray[idx].y);

			C2D_DrawSprite(&CellArray[idx].CellSprite);
			
			
		}
		size = 0;
		free(CellArray);
		C3D_FrameEnd(0);
		printf("\r%d", counter);

		
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
		if(kDown & KEY_A)
			InitGameOfLife(0);
		if(kDown & KEY_B)
			InitGameOfLife(1);
		
	}

	// Delete graphcis
	C2D_SpriteSheetFree(spriteSheet);
	
	// Exit the services
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	
	return 0;
}
