#include <stdio.h>
#include <gb/gb.h>
#include <rand.h>

#include "tetris_tiles.c"
#include "tetris_menu.c"
#include "tetris_map.c"
#include "tetri_logo_data.c"
#include "tetri_logo_map.c"

int gaming = 2;

// draw the tetramino
int txOffset1 = 0;
int txOffset2 = -1;
int txOffset3 = 1;
int txOffset4 = 1;

int tyOffset1 = 0;
int tyOffset2 = 0;
int tyOffset3 = 0;
int tyOffset4 = 1;

// draw the previews
int pxOffset1 = 0;
int pxOffset2 = -1;
int pxOffset3 = 1;
int pxOffset4 = 1;

int pyOffset1 = 0;
int pyOffset2 = 0;
int pyOffset3 = 0;
int pyOffset4 = 1;

int px2Offset1 = 0;
int px2Offset2 = -1;
int px2Offset3 = 1;
int px2Offset4 = 1;

int py2Offset1 = 0;
int py2Offset2 = 0;
int py2Offset3 = 0;
int py2Offset4 = 1;

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
int hardDrop = 0;
int holding = 0;
int holdEnabled = 1;
int pieceStore = 0;
int randomizer = 0;
int addGarbage = 0;
int selection = 0;

const char blankmap[1] = {0x00};
const char tetris_block[1] = {0x01};

void updateHoldPiece(){
	if (holding == 1){
		// j
		px2Offset1 = 0;
		px2Offset2 = -1;
		px2Offset3 = 1;
		px2Offset4 = 1;

		py2Offset1 = 0;
		py2Offset2 = 0;
		py2Offset3 = 0;
		py2Offset4 = 1;
	}
	if (holding == 2){
		// t
		px2Offset1 = 0;
		px2Offset2 = -1;
		px2Offset3 = 1;
		px2Offset4 = 0;

		py2Offset1 = 0;
		py2Offset2 = 0;
		py2Offset3 = 0;
		py2Offset4 = 1;
	}
	if (holding == 3){
		// i
		px2Offset1 = 0;
		px2Offset2 = -1;
		px2Offset3 = 1;
		px2Offset4 = 2;

		py2Offset1 = 1;
		py2Offset2 = 1;
		py2Offset3 = 1;
		py2Offset4 = 1;
	}
	if (holding == 4){
		// o
		px2Offset1 = 0;
		px2Offset2 = 1;
		px2Offset3 = 0;
		px2Offset4 = 1;

		py2Offset1 = 0;
		py2Offset2 = 0;
		py2Offset3 = 1;
		py2Offset4 = 1;
	}
	if (holding == 5){
		// s
		px2Offset1 = 0;
		px2Offset2 = -1;
		px2Offset3 = 0;
		px2Offset4 = 1;

		py2Offset1 = 0;
		py2Offset2 = 0;
		py2Offset3 = 1;
		py2Offset4 = 1;
	}
	if (holding == 6){
		// z
		px2Offset1 = 0;
		px2Offset2 = 1;
		px2Offset3 = 0;
		px2Offset4 = -1;

		py2Offset1 = 0;
		py2Offset2 = 0;
		py2Offset3 = 1;
		py2Offset4 = 1;
	}
	if (holding == 7){
		// l
		px2Offset1 = 0;
		px2Offset2 = -1;
		px2Offset3 = 1;
		px2Offset4 = -1;

		py2Offset1 = 0;
		py2Offset2 = 0;
		py2Offset3 = 0;
		py2Offset4 = 1;
	}
}
int r;
void updateNext(){
	r = rand() % 8 + 1;
	if (r == 1){
		// j
		pxOffset1 = 0;
		pxOffset2 = -1;
		pxOffset3 = 1;
		pxOffset4 = 1;

		pyOffset1 = 0;
		pyOffset2 = 0;
		pyOffset3 = 0;
		pyOffset4 = 1;
	}
	if (r == 2){
		// t
		pxOffset1 = 0;
		pxOffset2 = -1;
		pxOffset3 = 1;
		pxOffset4 = 0;

		pyOffset1 = 0;
		pyOffset2 = 0;
		pyOffset3 = 0;
		pyOffset4 = 1;
	}
	if (r == 3){
		// i
		pxOffset1 = 0;
		pxOffset2 = -1;
		pxOffset3 = 1;
		pxOffset4 = 2;

		pyOffset1 = 1;
		pyOffset2 = 1;
		pyOffset3 = 1;
		pyOffset4 = 1;
	}
	if (r == 4){
		// o
		pxOffset1 = 0;
		pxOffset2 = 1;
		pxOffset3 = 0;
		pxOffset4 = 1;

		pyOffset1 = 0;
		pyOffset2 = 0;
		pyOffset3 = 1;
		pyOffset4 = 1;
	}
	if (r == 5){
		// s
		pxOffset1 = 0;
		pxOffset2 = -1;
		pxOffset3 = 0;
		pxOffset4 = 1;

		pyOffset1 = 0;
		pyOffset2 = 0;
		pyOffset3 = 1;
		pyOffset4 = 1;
	}
	if (r == 6){
		// z
		pxOffset1 = 0;
		pxOffset2 = 1;
		pxOffset3 = 0;
		pxOffset4 = -1;

		pyOffset1 = 0;
		pyOffset2 = 0;
		pyOffset3 = 1;
		pyOffset4 = 1;
	}
	if (r == 7){
		// l
		pxOffset1 = 0;
		pxOffset2 = -1;
		pxOffset3 = 1;
		pxOffset4 = -1;

		pyOffset1 = 0;
		pyOffset2 = 0;
		pyOffset3 = 0;
		pyOffset4 = 1;
	}
}

void randomMino(int hold){
	if (hold == 0) {
		piece = r;
	}
	if (piece == 1){
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
	if (piece == 2){
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
	if (piece == 3){
		// i
		txOffset1 = 0;
		txOffset2 = -1;
		txOffset3 = 1;
		txOffset4 = 2;

		tyOffset1 = 0;
		tyOffset2 = 0;
		tyOffset3 = 0;
		tyOffset4 = 0;
	}
	if (piece == 4){
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
	if (piece == 5){
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
	if (piece == 6){
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
	if (piece == 7){
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
	if (hold == 0) {
	updateNext();
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

void resetGame(){
	int i;
	for (i = 0; i < 180; i+=1){
		gameGrid[i] = 0;
	}
	tD = 0;
	
	if (selection == 0) {addGarbage = 0;}
	if (selection == 1) {addGarbage = 1;}
	
	if (addGarbage == 1) {
		i = 0;
		for (i = 0; i < 60; i+=1){
			gameGrid[180 - i] = rand() % 2;
			if (gameGrid[180 - i] !=1) {
				gameGrid[180 - i] = 0;
			}
		}
	}
	
	set_bkg_data(0,48,tetris);
	set_bkg_tiles(0,0,20,18,tetris_map);
	
	initrand(DIV_REG);

	// tetramino player controlled things
	tx = 6;
	ty = 4;
	tDir = 1;

	// time based stuff
	tick = 1;
	reload = 0;
	reload2 = 0;
	reload3 = 0;
	onGroundTick = 0;
	shaking = 0;
	piece = 0;
	hardDrop = 0;
	holding = 0;
	holdEnabled = 1;
	pieceStore = 0;
	
	updateBoard();
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
				BGP_REG = 0xC0;
				for (i2 = i; i2 > 1; i2-=1){
					gameGrid[i2] = gameGrid[i2-10];
				}
				for (i3 = 0; i3 <= 10; i3+=1){
					gameGrid[i3] = 0;
				}
				//updateBoard(); 
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

void fixOverDrop(){
	if ((ty-tyOffset1) > 17) {
		if ((ty-tyOffset2) > 17) {
			if ((ty-tyOffset3) > 17) {
				if ((ty-tyOffset4) > 17) {
					while((ty-tyOffset1) > 17 && (ty-tyOffset2) > 17 && (ty-tyOffset3) > 17 && (ty-tyOffset4) > 17){
						ty-=1;
					}
				}
			}
		}
	}
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
	tDir = 1;
	ty = 4;
	tx = 6;
	checkLine();
	updateBoard();
	holdEnabled = 1;
	
	randomMino(0);
}

void main(){
	randomMino(0);
	// these registers must be in this specific order!
	NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
	NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
	NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
	
	set_sprite_data(0,48,tetris);
	
	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	
	// tetramino (sprite)
	set_sprite_tile(1,1);
	set_sprite_tile(2,1);
	set_sprite_tile(3,1);
	set_sprite_tile(4,1);
	
	// previews
	set_sprite_tile(5,1);
	set_sprite_tile(6,1);
	set_sprite_tile(7,1);
	set_sprite_tile(8,1);
	
	set_sprite_tile(9,1);
	set_sprite_tile(10,1);
	set_sprite_tile(11,1);
	set_sprite_tile(12,1);
	
	// selection
	set_sprite_tile(13,23);
	
	initrand(DIV_REG);
	
	updateBoard();
	while(1){
		if (gaming == 2) {
			set_bkg_data(0,104,tetri_logo_data);
			set_bkg_tiles(0,0,20,18,tetri_logo_map);
			if (joypad()){
				gaming = 0;
				move_sprite(13,6 * 8,10*8);
			}
		}
		if (gaming == 0) {
			
			move_sprite(1,-16,16);
			move_sprite(2,-16,16);
			move_sprite(3,-16,16);
			move_sprite(4,-16,16);
			move_sprite(5,-16,16);
			move_sprite(6,-16,16);
			move_sprite(7,-16,16);
			move_sprite(8,-16,16);
			move_sprite(9,-16,16);
			move_sprite(10,-16,16);
			move_sprite(11,-16,16);
			move_sprite(12,-16,16);
			
			set_bkg_data(0,48,tetris);
			set_bkg_tiles(0,0,20,18,tetris_menu);
			if (joypad() == J_UP) {
				selection = 0;
				move_sprite(13,6 * 8,10*8);
			}
			if (joypad() == J_DOWN) {
				selection = 1;
				move_sprite(13,6 * 8,16*8);
			}
			if (joypad() == J_A) {
				initrand(DIV_REG);
				resetGame();
				set_bkg_tiles(0,0,20,18,tetris_map);
				
				move_sprite(13,-16,16);
			
				updateBoard();
				gaming = 1;
			}
		}
		if (gaming == 1) {
			// previews
			move_sprite(5,(17-pxOffset1)*8,(5-pyOffset1+2)*8);
			move_sprite(6,(17-pxOffset2)*8,(5-pyOffset2+2)*8);
			move_sprite(7,(17-pxOffset3)*8,(5-pyOffset3+2)*8);
			move_sprite(8,(17-pxOffset4)*8,(5-pyOffset4+2)*8);
			
			if (holding != 0) {
				move_sprite(9,(17-px2Offset1)*8,(13-py2Offset1+2)*8);
				move_sprite(10,(17-px2Offset2)*8,(13-py2Offset2+2)*8);
				move_sprite(11,(17-px2Offset3)*8,(13-py2Offset3+2)*8);
				move_sprite(12,(17-px2Offset4)*8,(13-py2Offset4+2)*8);
			}else{
				move_sprite(9,-16,16);
				move_sprite(10,-16,16);
				move_sprite(11,-16,16);
				move_sprite(12,-16,16);
			}
			
			// game stuff
			if (shaking > 1) {
				move_bkg(rand() % 2 - 1,rand() % 2 - 1);
				shaking -=1;
			}else{
				BGP_REG = 0xE4;
				move_bkg(0,0);
			}
			if(joypad() == J_SELECT){
				if (holdEnabled == 1) {
					holdEnabled = 0;
					pieceStore = piece;
					piece = holding;
					holding = pieceStore;
					randomMino(1);
					updateHoldPiece();
					NR10_REG = 0x15; 
					NR11_REG = 0x80;
					NR12_REG = 0x63;  
					NR13_REG = 0xFF;   
					NR14_REG = 0xCC;
				}
			}
			updateHoldPiece();
			if(joypad() == J_LEFT){
				if (reload2 < 1) {
					reload2 = 5;
					if (tx-txOffset1 > 3) {
						if (tx-txOffset2 > 3) {
							if (tx-txOffset3 > 3) {
								if (tx-txOffset4 > 3) {
									if (collision( (tx-txOffset1)-3 , (ty-tyOffset1)) != 0 || collision( (tx-txOffset2)-3 , (ty-tyOffset2)) != 0 || collision( (tx-txOffset3)-3 , (ty-tyOffset3)) != 0 || collision( (tx-txOffset4)-3 , (ty-tyOffset4)) != 0) {
									}else{tx-=1;}
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
									if (collision( (tx-txOffset1)-1 , (ty-tyOffset1)) != 0 || collision( (tx-txOffset2)-1 , (ty-tyOffset2)) != 0 || collision( (tx-txOffset3)-1 , (ty-tyOffset3)) != 0 || collision( (tx-txOffset4)-1 , (ty-tyOffset4)) != 0) {
									}else{tx+=1;}
								}
							}
						}
					}
				}
			}
			
			if(joypad() == J_DOWN){
				if (ty >=17 || collision( (tx-txOffset1)-2 , (ty-tyOffset1+1)) != 0 || collision( (tx-txOffset2)-2 , (ty-tyOffset2+1)) != 0 || collision( (tx-txOffset3)-2 , (ty-tyOffset3+1)) != 0 || collision( (tx-txOffset4)-2 , (ty-tyOffset4+1)) != 0) {
				}else{ty+=1;}
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
				hardDrop=1;
				shaking = 10;
				while (ty <= 18) {
					if (ty >=17 || collision( (tx-txOffset1)-2 , (ty-tyOffset1+1)) != 0 || collision( (tx-txOffset2)-2 , (ty-tyOffset2+1)) != 0 || collision( (tx-txOffset3)-2 , (ty-tyOffset3+1)) != 0 || collision( (tx-txOffset4)-2 , (ty-tyOffset4+1)) != 0) {
						if (ty>=18) {
							ty=17;
						}
						fixOverDrop();
						collided();
						NR10_REG = 0x1C; 
						NR11_REG = 0x80;
						NR12_REG = 0x63;  
						NR13_REG = 0xFF;   
						NR14_REG = 0xCC;
						hardDrop = 0;
						break;
					}
					ty+=1;
				}
			}
			if(joypad() == J_A){
				if (reload <= 1){
					onGroundTick=2;
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
					}
					if (tDir == 5) {
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
			
			if (joypad() == J_START) {
				gaming = 0;
			}
			
			tick+=1;
			if (tick > 24) {
				tick = 0;
				if (ty >=17 || collision( (tx-txOffset1)-2 , (ty-tyOffset1+1)) != 0 || collision( (tx-txOffset2)-2 , (ty-tyOffset2+1)) != 0 || collision( (tx-txOffset3)-2 , (ty-tyOffset3+1)) != 0 || collision( (tx-txOffset4)-2 , (ty-tyOffset4+1)) != 0) {
				}else{ty+=1;}
			}
			// render sprite tetramino
			move_sprite(1,(tx-txOffset1)*8,(ty-tyOffset1+2)*8);
			move_sprite(2,(tx-txOffset2)*8,(ty-tyOffset2+2)*8);
			move_sprite(3,(tx-txOffset3)*8,(ty-tyOffset3+2)*8);
			move_sprite(4,(tx-txOffset4)*8,(ty-tyOffset4+2)*8);
			if (ty >=17 || collision( (tx-txOffset1)-2 , (ty-tyOffset1+1)) != 0 || collision( (tx-txOffset2)-2 , (ty-tyOffset2+1)) != 0 || collision( (tx-txOffset3)-2 , (ty-tyOffset3+1)) != 0 || collision( (tx-txOffset4)-2 , (ty-tyOffset4+1)) != 0) {
				if(ty <= 5){
					resetGame();
				}
				if (ty>=18) {
					ty=17;
				}
				fixOverDrop();
				if (hardDrop == 0) {
					reload3-=1;
					if (reload3 < 1) {
						reload3 = 10;
						onGroundTick+=1;
					}
					if (onGroundTick>5) {
						NR10_REG = 0xFF; 
						NR11_REG = 0x80;
						NR12_REG = 0x43;  
						NR13_REG = 0xFF;   
						NR14_REG = 0xCC;
						onGroundTick=0;
						collided();
						shaking = 3;
					}
				}
			}
		}
		delay(20);
	}     
}
