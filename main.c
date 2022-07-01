#include <stdio.h>
#include <gb/gb.h>
#include <rand.h>

#include "tetris_tiles.c"
#include "tetris_map.c"

int gaming = 1;

// draw the tetramino
int txOffset1 = 0;
int txOffset2 = -1;
int txOffset3 = 1;
int txOffset4 = 1;

int tyOffset1 = 0;
int tyOffset2 = 0;
int tyOffset3 = 0;
int tyOffset4 = 1;

int tD = 0;

// tetramino player controlled things
int tx = 6;
int ty = 4;
int tDir = 1;

// time based stuff
int tick = 1;
int reload = 0;
int reload2 = 0;
int reload3 = 0;
int onGroundTick = 0;
int shaking = 0;
int piece = 0;

const char blankmap[1] = {0x00};

void randomMino(){
	int r = rand() % 2 + 2;
	piece = r;
	if (r == 1){
		// j
		txOffset1 = 0;
		txOffset2 = -1;
		txOffset3 = 1;
		txOffset4 = 1;

		tyOffset1 = 0;
		tyOffset2 = 0;
		tyOffset3 = 0;
		tyOffset4 = 1;
	}
	if (r == 2){
		// t
		txOffset1 = 0;
		txOffset2 = -1;
		txOffset3 = 1;
		txOffset4 = 0;

		tyOffset1 = 0;
		tyOffset2 = 0;
		tyOffset3 = 0;
		tyOffset4 = 1;
	}
	if (r == 3){
		// i
		txOffset1 = 0;
		txOffset2 = -1;
		txOffset3 = 1;
		txOffset4 = 2;

		tyOffset1 = 1;
		tyOffset2 = 1;
		tyOffset3 = 1;
		tyOffset4 = 1;
	}
	if (r == 4){
		// o
		txOffset1 = 0;
		txOffset2 = 1;
		txOffset3 = 0;
		txOffset4 = 1;

		tyOffset1 = 0;
		tyOffset2 = 0;
		tyOffset3 = 1;
		tyOffset4 = 1;
	}
	if (r == 5){
		// s
		txOffset1 = 0;
		txOffset2 = -1;
		txOffset3 = 0;
		txOffset4 = 1;

		tyOffset1 = 0;
		tyOffset2 = 0;
		tyOffset3 = 1;
		tyOffset4 = 1;
	}
	if (r == 6){
		// z
		txOffset1 = 0;
		txOffset2 = 1;
		txOffset3 = 0;
		txOffset4 = -1;

		tyOffset1 = 0;
		tyOffset2 = 0;
		tyOffset3 = 1;
		tyOffset4 = 1;
	}
	if (r == 7){
		// l
		txOffset1 = 0;
		txOffset2 = -1;
		txOffset3 = 1;
		txOffset4 = -1;

		tyOffset1 = 0;
		tyOffset2 = 0;
		tyOffset3 = 0;
		tyOffset4 = 1;
	}
}

int gameGrid[180] =
{
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
};

void updateBoard(){
	int i;
	for (i = 0; i < 180; i+=1){
		if (gameGrid[i]==1){
			set_bkg_tiles((i % 10)+1,i/10,1,1,tetris_block);
		}else{
			set_bkg_tiles((i % 10)+1,i/10,1,1,blankmap[0]);
		}
	}
}
int fullLine,lineNumber,indexing,i,i2,i3;
void checkLine(){
	for (i = 0; i < 180; i+=1){
		if (gameGrid[i] == 1){
			lineNumber+=1;
			if (lineNumber>=10) {
				NR10_REG = 0x16; 
				NR11_REG = 0x40;
				NR12_REG = 0x73;  
				NR13_REG = 0x00;   
				NR14_REG = 0xCC;
				fullLine = 1;
				for (i2 = i; i2 > 1; i2-=1){
					gameGrid[i2] = gameGrid[i2-10];
				}
				for (i3 = 0; i3 <= 10; i3+=1){
					gameGrid[i3] = 0;
				}
				updateBoard(); 
			}
		}
		indexing+=1;
		if (indexing>=10) {
			indexing=0;
			lineNumber=0;
			fullLine = 0;
		}
	}
}

int collision(int x,int y){
	int iTlx,iTly,tITl;
	int result;
	
	iTlx = (x);
	iTly = (y);
	tITl = iTlx + (iTly*10);
	
	result = gameGrid[tITl];
	return result;
}

void collided(){
	// put tetramino on background
	//set_bkg_tiles((tx-txOffset1)-1,(ty-tyOffset1)-1,1,1,tetris_block);
	//set_bkg_tiles((tx-txOffset2)-1,(ty-tyOffset2)-1,1,1,tetris_block);
	//set_bkg_tiles((tx-txOffset3)-1,(ty-tyOffset3)-1,1,1,tetris_block);
	//set_bkg_tiles((tx-txOffset4)-1,(ty-tyOffset4)-1,1,1,tetris_block);
	
	gameGrid[(tx-txOffset1)-2 + ((ty-tyOffset1)*10)] = 1;
	gameGrid[(tx-txOffset2)-2 + ((ty-tyOffset2)*10)] = 1;
	gameGrid[(tx-txOffset3)-2 + ((ty-tyOffset3)*10)] = 1;
	gameGrid[(tx-txOffset4)-2 + ((ty-tyOffset4)*10)] = 1;
	
	// move spritemino back to starting position
	ty = 4;
	tx = 6;
	updateBoard();
	checkLine();
	
	randomMino();
}

void main(){
	randomMino();
	// these registers must be in this specific order!
	NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
	NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
	NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
	
	set_bkg_data(0,14,tetris);
	set_bkg_tiles(0,0,20,18,tetris_map);
	
	set_sprite_data(0,14,tetris);
	
	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	
	initrand(10);
	
	// tetramino (sprite)
	set_sprite_tile(1,1);
	set_sprite_tile(2,1);
	set_sprite_tile(3,1);
	set_sprite_tile(4,1);
	updateBoard();
	while(1){
		if (gaming == 1) {
			if (shaking > 1) {
				move_bkg(rand() % 2 - 1,rand() % 2 - 1);
				shaking -=1;
			}else{
				move_bkg(0,0);
			}
			if(joypad() == J_LEFT){
				if (reload2 < 1) {
					reload2 = 5;
					if (tx-txOffset1 > 3) {
						if (tx-txOffset2 > 3) {
							if (tx-txOffset3 > 3) {
								if (tx-txOffset4 > 3) {
									tx-=1;
								}
							}
						}
					}
				}
			}
			if(joypad() == J_RIGHT){
				if (reload2 < 1) {
					reload2 = 5;
					if (tx-txOffset1 < 11) {
						if (tx-txOffset2 < 11) {
							if (tx-txOffset3 < 11) {
								if (tx-txOffset4 < 11) {
									tx+=1;
								}
							}
						}
					}
				}
			}
			
			if(joypad() == J_DOWN){
				ty+=1;
			}
			reload-=1;
			if (reload<=1) {
				reload = 0;
			}
			reload2-=1;
			if (reload2<=1) {
				reload2 = 0;
			}
			if(joypad() == J_UP){
				shaking = 10;
				while (ty <= 16) {
					if (ty >=16 || collision( (tx-txOffset1)-2 , (ty-tyOffset1+1)) != 0 || collision( (tx-txOffset2)-2 , (ty-tyOffset2+1)) != 0 || collision( (tx-txOffset3)-2 , (ty-tyOffset3+1)) != 0 || collision( (tx-txOffset4)-2 , (ty-tyOffset4+1)) != 0) {
						collided();
						break;
					}
					ty+=1;
				}
				NR10_REG = 0xFF; 
				NR11_REG = 0x80;
				NR12_REG = 0x43;  
				NR13_REG = 0xFF;   
				NR14_REG = 0xC8;
			}
			if(joypad() == J_A){
				if (reload <= 1){
					shaking = 1;
					NR10_REG = 0x16; 
					NR11_REG = 0x80;
					NR12_REG = 0x73;  
					NR13_REG = 0xFF;   
					NR14_REG = 0xFC;	   
					reload = 8;
					tDir += 1;
					if (tDir == 2) {
						tD = txOffset1;
						txOffset1 = tyOffset1;
						tyOffset1 = tD;
						tD = txOffset2;
						txOffset2 = tyOffset2;
						tyOffset2 = tD;
						tD = txOffset3;
						txOffset3 = tyOffset3;
						tyOffset3 = tD;
						tD = txOffset4;
						txOffset4 = tyOffset4;
						tyOffset4 = tD;
					}
					if (tDir == 3) {
						tD = txOffset1;
						txOffset1 = tyOffset1;
						tyOffset1 = tD*-1;
						tD = txOffset2;
						txOffset2 = tyOffset2;
						tyOffset2 = tD*-1;
						tD = txOffset3;
						txOffset3 = tyOffset3;
						tyOffset3 = tD*-1;
						tD = txOffset4;
						txOffset4 = tyOffset4;
						tyOffset4 = tD*-1;
					}
					if (tDir == 4) {
						tD = txOffset1;
						txOffset1 = tyOffset1;
						tyOffset1 = tD*-1;
						tD = txOffset2;
						txOffset2 = tyOffset2;
						tyOffset2 = tD*-1;
						tD = txOffset3;
						txOffset3 = tyOffset3;
						tyOffset3 = tD*-1;
						tD = txOffset4;
						txOffset4 = tyOffset4;
						tyOffset4 = tD*-1;
						tDir = 1;
					}
				}
			}
			
			tick+=1;
			if (tick > 16) {
				tick = 0;
				ty+=1;
			}
			// render sprite tetramino
			move_sprite(1,(tx-txOffset1)*8,(ty-tyOffset1+2)*8);
			move_sprite(2,(tx-txOffset2)*8,(ty-tyOffset2+2)*8);
			move_sprite(3,(tx-txOffset3)*8,(ty-tyOffset3+2)*8);
			move_sprite(4,(tx-txOffset4)*8,(ty-tyOffset4+2)*8);
			if (ty >=16 || collision( (tx-txOffset1)-2 , (ty-tyOffset1+1)) != 0 || collision( (tx-txOffset2)-2 , (ty-tyOffset2+1)) != 0 || collision( (tx-txOffset3)-2 , (ty-tyOffset3+1)) != 0 || collision( (tx-txOffset4)-2 , (ty-tyOffset4+1)) != 0) {
				if(ty <= 5){
					gaming = 0;
				}
				collided();
			}
		}
		delay(20);
	}     
}
