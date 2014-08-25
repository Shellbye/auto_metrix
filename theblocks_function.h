#ifndef _BLOCKS_
#define _BLOCKS_

#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<conio.h>
#include<math.h>

#define N 		20 										//row
#define M 		10 										//column
#define OK 		1
#define FALSE 	0
#define MAX		2147483647 								//max of int type

int block01[N][M] = {0};int block02[N][M] = {0};int block03[N][M] = {0};
int block04[N][M] = {0};int block05[N][M] = {0};int block06[N][M] = {0};
int block07[N][M] = {0};int block08[N][M] = {0};int block09[N][M] = {0};
int block10[N][M] = {0};int block11[N][M] = {0};int block12[N][M] = {0};
int block13[N][M] = {0};int block14[N][M] = {0};int block15[N][M] = {0};
int block16[N][M] = {0};int block17[N][M] = {0};int block18[N][M] = {0};
int block19[N][M] = {0};int backgrd[N][M] = {0};int blocks[N][M]  = {0};
int weighth[M] = {0};	
int trans_weighth[4] = {0};
int score = 0; 
int score_ave = 0;
int game_numbers = 30;
int new_hole = 0;
int old_hole = 0;

int Block_join_bkgrd();
int Block_join_bkgrd_temp();
int Check(int a[N][M]);
int Check_hole(int a[N][M]);
int Check_pile_diff(int a[N][M]);
int Check_pile_low(int a[N][M]);
int Check_pile_height(int a[N][M]);
void Downward();
void Downward_show();
void Game_over_check();
void Init_blocks();
int Move_left(int a[N][M]);
int Move_right(int a[N][M]);
int Move_right_show(int a[N][M]);
int Move_down(int a[N][M]);
int Move_down_show(int a[N][M]);
int Max_of_bkgrd(int w[M]);
int Max_of_trans(int w[M]);
void Print_blocks(int a[N][M]);
void Remove_full_row();
void Show_new_block(int a[N][M]);
void Show_best_layout(int block_number);
int Transform(int block_number);
void Test_each_right(int block_number);
void Unit_blocks(int block_number);
void Undo_down(int a[N][M]);
int Weight(int a[N][M]);
int Welcome();

#endif /* BLOCKS */
