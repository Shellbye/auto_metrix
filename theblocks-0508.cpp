#include<stdio.h>
#include"theblocks_function.h"


int main()
{
	Welcome();
	Init_blocks();
	old_hole = 0;
	srand((unsigned)time(NULL));						//use the time as the seed of srand()
	while(1)
	{
		int blknum = (rand()%19) + 1;					//generate random number from 1 to 19
		Unit_blocks(blknum);
		Show_new_block(blocks);							//Print the new blocks

		int b0[M] = {0};
		int b1[M] = {0};
		int b2[M] = {0};
		int b3[M] = {0};
		int orientBlknum = blknum;	
		
		int transformTime = 0;
		while(transformTime <= 3)
		{
			int transTime = transformTime;
			blknum = orientBlknum;
			while(transTime--)
			{
				blknum = Transform(blknum);//transform one time
			} 
			Test_each_right(blknum);					//Determine the best right move times and update the weighth[M]			
			switch(transformTime)
			{
				case 0: for(int i =0; i < M; i++) b0[i] = weighth[i];break;
				case 1: for(int i =0; i < M; i++) b1[i] = weighth[i];break;
				case 2: for(int i =0; i < M; i++) b2[i] = weighth[i];break;
				case 3: for(int i =0; i < M; i++) b3[i] = weighth[i];break;
			}		
			trans_weighth[transformTime] = weighth[Max_of_bkgrd(weighth)];//record the current max of weighth[]
																//Store the current weighth		
			transformTime++;
		}
		blknum = orientBlknum;	
		int BestTransformTime = Max_of_trans(trans_weighth);
		switch(BestTransformTime)
		{
			case 0: for(int i =0; i < M; i++) weighth[i] = b0[i];break;
			case 1: for(int i =0; i < M; i++) weighth[i] = b1[i];break;
			case 2: for(int i =0; i < M; i++) weighth[i] = b2[i];break;
			case 3: for(int i =0; i < M; i++) weighth[i] = b3[i];break;
		}
		while(BestTransformTime--) blknum = Transform(blknum);
		Show_best_layout(blknum);						//Print the best layout			
//		printf("%d\n",Check_pile_height(backgrd));
//		printf("%d\n",Check_pile_low(backgrd));
//		printf("%d\n",Check_hole(backgrd));
//		printf("%d\n",Check_pile_diff(backgrd));
		Remove_full_row();
		Game_over_check();
//		system("pause");
//		Sleep(1000);
		if(_kbhit()) exit(1);							//Press any key to exit
		system("cls");
	}

	return OK;
}

int Block_join_bkgrd()
{
	for(int i = 0; i<N; i++)
		for(int j = 0; j<M; j++)
			backgrd[i][j] += blocks[i][j];
	return OK;
}
int Block_join_bkgrd_temp()
{
	int temp[N][M] = {0};
	for(int i = 0; i<N; i++)
		for(int j = 0; j<M; j++)
		{
			temp[i][j] = backgrd[i][j];
			temp[i][j] += blocks[i][j];
		}
	return Weight(temp);
}

int Check(int a[N][M])
{
	int temp[N][M] ={0};
	for(int i = 0; i<N; i++)
		for(int j = 0; j<M; j++)
		{
			temp[i][j] = backgrd[i][j];
			temp[i][j] += a[i][j];
			if(temp[i][j] == 2)
				return FALSE;
		}
	return OK;
}
int Check_hole(int a[N][M])
{
	for(int i = N-1; i >= 1; i--)
	{
		for(int j = 0; j < M; j++)
		{
			if(a[i][j] ==0 && a[i-1][j] == 1)//There is a hole
			{
				new_hole++;
	//			return 1;
			}
		}		
	}
	old_hole = 0;
	for(int i = N-1; i >= 1; i--)
	{
		for(int j = 0; j < M; j++)
		{
			if(backgrd[i][j] ==0 && backgrd[i-1][j] == 1)//There is a hole
			{
				old_hole++;
			}
		}		
	}
	if(new_hole > old_hole)
	{
		old_hole = new_hole;
		new_hole = 0;
//		return old_hole;
		return 1;
	}
	else
	{
		new_hole = 0;
//		return old_hole;
		return 0;
	}

}
int Check_pile_height(int a[N][M])
{
	for(int i = 0; i<N; i++)
	{
		for(int j = 0; j<M; j++)
		{
			if(a[i][j] == 1)
			{
				return N - i;
			}
		}
	}
}
int Check_pile_low(int a[N][M])
{
	int low = 0;
	for(int i = N-1; i>=0; i--)
	{
		for(int j = 0; j<M; j++)
		{
			if(a[i][j] == 0)
			{
				int zero_test = 0;
				for(int k = i; k>=0; k--)
				{
					zero_test +=a[k][j];
				}
				if(zero_test == 0) 
				{
					low = (N - 1) - i;
					return low;
				}
			}
		}
	}
}
int Check_pile_diff(int a[N][M])
{
	return Check_pile_height(a) - Check_pile_low(a);
}

int Check_full_row(int a[N][M])
{
	int num = 0;
	for(int i = N-1; i >= 0; i--)
	{
		int full_row = 0;
		for(int j = 0; j < M; j++)
		{
			full_row += a[i][j];
		}
		if(full_row == 10) num++;
	}
	return num;
}
void Downward()
{
	while(Move_down(blocks))							//Haven't reach the bottom
	{
		if(Check(blocks) == FALSE)						//Collide
		{
			Undo_down(blocks);							//Move up one step and break
			break;
		}
	}
}
void Downward_show()
{
	while(Move_down_show(blocks))							//Haven't reach the bottom
	{
		if(Move_down(blocks) || 1)		//Collide
		{
			if(Check(blocks) == FALSE)
			{
				Undo_down(blocks);							//Move up one step and break
				break;
			}
			Undo_down(blocks);							//Move up one step and break
			break;	
		}
	}
}
void Game_over_check()
{

	int b[N][M] = {0};
	if(Check(b) == FALSE)								//Game over
	{
		system("cls");
		printf("***************\n");
		printf("***GAME OVER***\n");
		printf("***************\n");
		FILE * score_file;
		score_file = fopen("score.txt","a");
		if(game_numbers < 1)
		{
			if(score_file!=NULL)
			{
				fprintf(score_file,"ave:\t%d\n",score_ave/30);
				fclose(score_file);
			}
			exit(1);
		} 
		if(score_file!=NULL)
		{
			fprintf(score_file,"%d:\t%d\n",31 - game_numbers, score);
			fclose(score_file);
		}
		score_ave += score;
		score = 0;
		game_numbers--;
		for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
			backgrd[i][j] = 0;
//		system("pause");
//		exit(1);
	}
}

void Init_blocks()
{
	block01[0][0] = block01[0][1] = block01[1][0] = block01[1][1] = 1;
	block02[0][0] = block02[0][1] = block02[0][2] = block02[0][3] = 1;
	block03[0][0] = block03[1][0] = block03[2][0] = block03[3][0] = 1;
	block04[0][0] = block04[1][0] = block04[1][1] = block04[2][1] = 1;
	block05[0][1] = block05[0][2] = block05[1][0] = block05[1][1] = 1;
	block06[0][1] = block06[1][0] = block06[1][1] = block06[1][2] = 1;
	block07[0][0] = block07[0][1] = block07[0][2] = block07[1][1] = 1;
	block08[0][0] = block08[1][0] = block08[1][1] = block08[2][0] = 1;
	block09[0][1] = block09[1][0] = block09[1][1] = block09[2][1] = 1;
	block10[0][0] = block10[0][1] = block10[1][1] = block10[2][1] = 1;
	block11[0][0] = block11[0][1] = block11[0][2] = block11[1][0] = 1;
	block12[0][0] = block12[1][0] = block12[2][0] = block12[2][1] = 1;
	block13[0][2] = block13[1][0] = block13[1][1] = block13[1][2] = 1;
	block14[0][1] = block14[1][0] = block14[1][1] = block14[2][0] = 1;
	block15[0][0] = block15[0][1] = block15[1][1] = block15[1][2] = 1;
	block16[0][0] = block16[0][1] = block16[1][0] = block16[2][0] = 1;
	block17[0][0] = block17[0][1] = block17[0][2] = block17[1][2] = 1;
	block18[0][0] = block18[1][0] = block18[1][1] = block18[1][2] = 1;
	block19[0][1] = block19[1][1] = block19[2][0] = block19[2][1] = 1;

}

int Move_down(int a[N][M])
{
	int sum_of_last_row = 0;
	for(int k = 0; k<M; k++)							//Check have or not reach the bottom
		sum_of_last_row += a[N-1][k];
	if(!sum_of_last_row)								//Haven't reach the bottom, Move down 1 step
	{
		for(int i = N-1; i>=1; i--)
			for(int j = 0; j<M; j++)
				a[i][j] = a[i-1][j];
		for(int s = 0; s<M; s++)
			a[0][s] = 0;
//		system("cls");
//		Print_blocks(a);
		return OK;
	}
	else 
	{
//		system("cls");
//		Print_blocks(a);
		return FALSE;
	}
}
int Move_down_show(int a[N][M])
{
	int sum_of_last_row = 0;
	for(int k = 0; k<M; k++)							//Check have or not reach the bottom
		sum_of_last_row += a[N-1][k];
	if(!sum_of_last_row)								//Haven't reach the bottom, Move down 1 step
	{
		for(int i = N-1; i>=1; i--)
			for(int j = 0; j<M; j++)
				a[i][j] = a[i-1][j];
		for(int s = 0; s<M; s++)
			a[0][s] = 0;
		system("cls");
		Print_blocks(a);
		return OK;
	}
	else 
	{
		system("cls");
		Print_blocks(a);
		return FALSE;
	}
}
int Move_right(int a[N][M])
{
	int sum_of_rightest_column = 0;
	for(int k = 0; k<N; k++)
		sum_of_rightest_column += a[k][M-1];
	if(!sum_of_rightest_column)							//Haven't reach the rightest
	{
		for(int i = N-1; i>=0; i--)
			for(int j = M-2; j>=0; j--)	//这里有问题，不知道为什么运行到这里就修改了weighth[0] 
				a[i][j+1] = a[i][j];	//问题在这里，a[9][10]不是在数组中的，它与weighth[0]引用了同一个地址，造成了覆盖 
		for(int s = 0; s<N; s++)
			a[s][0] = 0;
//		system("cls");
//		Print_blocks(a);
		return OK;
	}
	else
	{
//		system("cls");
//		Print_blocks(a);
		return FALSE;
	}
}
int Move_right_show(int a[N][M])
{
	int sum_of_rightest_column = 0;
	for(int k = 0; k<N; k++)
		sum_of_rightest_column += a[k][M-1];
	if(!sum_of_rightest_column)							//Haven't reach the rightest
	{
		for(int i = N-1; i>=0; i--)
			for(int j = M-2; j>=0; j--)	//这里有问题，不知道为什么运行到这里就修改了weighth[0] 
				a[i][j+1] = a[i][j];	//问题在这里，a[9][10]不是在数组中的，它与weighth[0]引用了同一个地址，造成了覆盖 
		for(int s = 0; s<N; s++)
			a[s][0] = 0;
		system("cls");
		Print_blocks(a);
		return OK;
	}
	else
	{
		system("cls");
		Print_blocks(a);
		return FALSE;
	}
}
int Move_left(int a[N][M])
{
	int sum_of_leftest_column = 0;
	for(int k = 0; k<N; k++)
		sum_of_leftest_column += a[k][0];
	if(!sum_of_leftest_column)							//Haven't reach the leftest
	{
		for(int i = N-1; i>=0; i--)	
			for(int j = 0; j<M; j++)
				a[i][j] = a[i][j+1];
		for(int s = 0; s<N; s++)
			a[s][M-1] = 0;
//		system("cls");
//		Print_blocks(a);
		return OK;
	}
	else 
	{
//		system("cls");
//		Print_blocks(a);
		return FALSE;
	}
	
}
int Max_of_bkgrd(int w[M])
{
	int max = -1,i = 0,j = -1;
	while(i<M)
	{
		if(w[i] >= max) 
		{
			max = w[i];
			j = i;
		}
		i++;
	}
	return j;
}
int Max_of_trans(int w[M])
{
	int max = -1,i = 0,j = -1;
	while(i<4)
	{
		if(w[i] >= max) 
		{
			max = w[i];
			j = i;
		}
		i++;
	}
	return j;
}

void Print_blocks(int a[N][M])
{
//	system("cls");
	for(int i = 0; i<N; i++)
	{
		for(int j = 0; j<M; j++)
			printf("%d",a[i][j]);
		printf("\n");
	}
//	printf("\n");
}
void Remove_full_row()
{
	int a = 0;
	for(int i = N-1; i >= 0; i--)
	{
		for(int j = 0; j < M; j++)
		{
			a += backgrd[i][j];
		}
		if(a == 10)										//if the NO.i row is full, then remove it 
		{
			score++;
		
			for(int k = i; k>=1; k--)
				for(int t = 0; t<M; t++)
					backgrd[k][t] = backgrd[k-1][t];
			for(int s = 0; s<M; s++)
				backgrd[0][s] = 0;
			i++;	//Because the movingDown operation has made the all back grd dowenwards, so it's need start again
		}
		a = 0;
	}
	
}
void Show_best_layout(int block_number)
{
	int right_move_count_02 = Max_of_bkgrd(weighth);	//Choose the best layout
	Unit_blocks(block_number);							//Refresh the blocks
	while(right_move_count_02)							//Show the best layout
	{
		Move_right(blocks);
		right_move_count_02--;
	}	
	Downward();
	Block_join_bkgrd();									//Change the background
	Print_blocks(backgrd);							//Print the best layout
}
void Show_new_block(int a[N][M])
{
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
			printf("%d",a[i][j]);
		printf("\n");
	}
//	printf("\n");
}
void Test_each_right(int block_number)
{
	for(int i = 0; i<M; i++)						//Test the value of right_move
	{
		int right_move_count_01 = i;
		Unit_blocks(block_number);					//Unit blocks into the same form 'blocks'
		
		while(right_move_count_01)					//Here is the problem, the right_move has not 
		{											//been refreshed, so it move too fast
			Move_right(blocks);						//Test the weight of several right move separately
			right_move_count_01--;
		}
		Downward();									//Keep moving down untill collide happenned
		weighth[i] = Block_join_bkgrd_temp();		//Put the blocks onto the 
//		printf("%d : %d\t",i,weighth[i]);			//temp then calculate and store the current weighth
		
	}
//	system("pause");
}
int Transform(int block_number)
{
	switch(block_number)
	{
		case 1:		return 1;break;
		case 2:		return 3;break;
		case 3:		return 2;break;
		case 4:		return 5;break;
		case 5:		return 4;break;
		case 6:		return 8;break;
		case 8:		return 7;break;
		case 7:		return 9;break;
		case 9:		return 6;break;
		case 10:	return 13;break;
		case 13:	return 12;break;
		case 12:	return 11;break;
		case 11:	return 10;break;
		case 14:	return 15;break;
		case 15:	return 14;break;
		case 16:	return 17;break;
		case 17:	return 19;break;
		case 19:	return 18;break;
		case 18:	return 16;break;
		default:	return 0;break;	
	}
}


void Undo_down(int a[N][M])
{
	for(int i = 0; i<N-1; i++)
			for(int j = 0; j<M; j++)
				a[i][j] = a[i+1][j];
	for(int i = 0; i<M; i++)
		a[N-1][i] = 0;
}


void Unit_blocks(int block_number)
{
	switch(block_number)
	{
		case 1:											//consider using a pointer that point to 'block01'
		{
			for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block01[i][j];
			break;
		}
		case 2:
		{
			for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block02[i][j];
			break;
		}
		case 3:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block03[i][j];
			break;
		}
		case 4:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block04[i][j];
			break;
		}
		case 5:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block05[i][j];
			break;
		}
		case 6:
		{
			for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block06[i][j];
			break;
		}
		case 7:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block07[i][j];
			break;
		}
		case 8:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block08[i][j];
			break;
		}
		case 9:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block09[i][j];
			break;
		}
		case 10:
		{
			for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block10[i][j];
			break;
		}
		case 11:
		{
			for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block11[i][j];
			break;
		}
		case 12:
		{
			for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block12[i][j];
			break;
		}
		case 13:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block13[i][j];
			break;
		}
		case 14:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block14[i][j];
			break;
		}
		case 15:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block15[i][j];
			break;
		}
		case 16:
		{
			for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block16[i][j];
			break;
		}
		case 17:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block17[i][j];
			break;
		}
		case 18:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block18[i][j];
			break;
		}
		case 19:
		{
		for(int i = 0; i<N; i++)
				for(int j = 0 ; j<M; j++)
					blocks[i][j] = block19[i][j];
			break;
		}
		default:
			printf("illegal input!");
			exit(1);
	}
}
int Weight(int a[N][M])
{
	int w = 0;
	int w_hole_check  = Check_hole(a);
	int w_pile_height = Check_pile_height(a);
	int w_pile_diff   = Check_pile_diff(a);
	int w_full_row    = Check_full_row(a);
	for(int i = 0; i<N; i++)//Put as below as it can
	{
		for(int j = 0; j<M; j++)
		{
			w += a[i][j] * (i + 1);
		}
	}
	if(Check_hole(a)) 			  w -= 50;
	if(Check_pile_height(a) > 10) w -= 50;
	if(Check_pile_diff(a) > 10)   w -= 50;
	if(Check_full_row(a))		  w += 200;
	return w;//返回的应该是一个向量的模 
}
int Welcome()
{
	printf("***********************\n");
	printf("******GAME START!******\n");
	printf("***********************\n");
	printf("********YOU CAN********\n");
	printf("**HIT ANY KEY TO STOP**\n");
	printf("***********************\n");
	Sleep(2000);
	system("cls");	
	return 1;
}
