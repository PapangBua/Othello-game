#define BOARD_SIZE 8
#define HISTORY_SIZE 1000
#include<stdio.h>
#include <stdlib.h>

void print_board(int board[][BOARD_SIZE]);
void init_board(int board[][BOARD_SIZE]);
int count_stone(int player_id, int board[][BOARD_SIZE]);
void place_stone(int player_id, int x, int y, int board[][BOARD_SIZE]);
int num_obtained_stone(int player_id, int x, int y, int board[][BOARD_SIZE]);
int asci_to_int(char string[]);
int input_place(int player_id, int board[][BOARD_SIZE]);
int computer(int player_id, int board[][BOARD_SIZE]);
int eightspot(int player_id, int board[][BOARD_SIZE],int importance);
void update_history(int location, int history[]);
void save_history(int history[]);

void print_board(int board[][BOARD_SIZE])
{
    printf("\t  ");
    for(int i=0;i<BOARD_SIZE;i++)
    {
        printf("%2d",i);
    }
    printf("\n");
    for(int j=0;j<BOARD_SIZE;j++) // y
    {
        printf("\t%2d ",j);
        for(int i=0;i<BOARD_SIZE;i++) //x
        {
            switch(board[i][j]) // x y
            {
                case 1: printf("o ");break;
                case -1: printf("x ");break;
                default : printf(". ");break;
            }
        }
        printf("\n");
    }
}

void init_board(int board[][BOARD_SIZE])
{
    for(int i=0;i<BOARD_SIZE;i++)
    {
        for(int j=0;j<BOARD_SIZE;j++)
        {
            board[j][i]=0; //x y
        }
    }
    board[(BOARD_SIZE/2)][(BOARD_SIZE/2)] = 1;
    board[(BOARD_SIZE/2)-1][(BOARD_SIZE/2)] = -1;
    board[(BOARD_SIZE/2)][(BOARD_SIZE/2)-1] = -1;
    board[(BOARD_SIZE/2)-1][(BOARD_SIZE/2)-1] = 1;
}

int count_stone(int player_id, int board[][BOARD_SIZE])
{
    int sum=0;
    for(int i=0;i<BOARD_SIZE;i++)
    {
        for(int j=0;j<BOARD_SIZE;j++)
        {
            if(board[j][i]==player_id) sum++; //x y
        }
    }
    return sum;
}

void place_stone(int player_id, int x, int y, int board[][BOARD_SIZE])
{
    int i;
    board[x][y]=player_id;
    //check up
    for(i=x-1;i>=0 && board[i][y]==-player_id;i--);
    if(i>=0 && board[i][y]==player_id)
    {
        for(;i!=x;i++) board[i][y]=player_id;
    }
    //check down
    for(i=x+1;i<BOARD_SIZE && board[i][y]==-player_id;i++);
    if(i<BOARD_SIZE && board[i][y]==player_id)
    {
        for(;i!=x;i--)  board[i][y]=player_id;
    }
    //check right
    for(i=y+1;i<BOARD_SIZE && board[x][i]==-player_id;i++);
    if(i<BOARD_SIZE && board[x][i]==player_id)
    {
        for(;i!=y;i--)board[x][i]=player_id;
    }
    //check left
    for(i=y-1;i>=0 && board[x][i]==-player_id;i--);
    if(i>=0 && board[x][i]==player_id)
    {
        for(;i!=y;i++)board[x][i]=player_id;
    }
    //check \up
    for(i=1;x-i>=0 && y-i>=0 &&board[x-i][y-i]==-player_id;i++);
    if(x-i>=0 && y-i>=0 && board[x-i][y-i]==player_id)
    {
        for(;i!=0;i--)board[x-i][y-i]=player_id;
    }
    //check /up
    for(i=1;x+i<BOARD_SIZE && y-i>=0 &&board[x+i][y-i]==-player_id;i++);
    if(x+i<BOARD_SIZE && y-i>=0 && board[x+i][y-i]==player_id)
    {
        for(;i!=0;i--)board[x+i][y-i]=player_id;
    }
    //check /down
    for(i=1;x-i>=0 && y+i<BOARD_SIZE &&board[x-i][x+i]==-player_id;i++);
    if(x-i>=0 && y+i<BOARD_SIZE && board[x-i][y+i]==player_id)
    {
        for(;i!=0;i--)board[x-i][y+i]=player_id;
    }
    //check \down
    for(i=1;x+i<BOARD_SIZE && y+i<BOARD_SIZE &&board[x+i][y+i]==-player_id;i++);
    if(x+i<BOARD_SIZE && y+i<BOARD_SIZE && board[x+i][y+i]==player_id)
    {
        for(;i!=0;i--)board[x+i][y+i]=player_id;
    }
}

int num_obtained_stone(int player_id, int x, int y, int board[][BOARD_SIZE])
{
    int i,sum=0;
    //printf("CHECKplayer_id = %d\n",player_id);
    //check up
    for(i=x-1;i>=0 && board[i][y]==-player_id;i--); //printf("UP");
    if(i>=0 && board[i][y]==player_id)
    {
        sum+=(x-i-1);
    }
    //check down
    for(i=x+1;i<BOARD_SIZE && board[i][y]==-player_id;i++);//printf("DOWN");
    if(i<BOARD_SIZE && board[i][y]==player_id)
    {
        sum+=(i-x-1);
    }
    //check right
    for(i=y+1;i<BOARD_SIZE && board[x][i]==-player_id;i++);//printf("RIGHT");
    if(i<BOARD_SIZE && board[x][i]==player_id)
    {
        sum+=(i-y-1);
    }
    //check left
    for(i=y-1;i>=0 && board[x][i]==-player_id;i--);//printf("LEFT");
    if(i>=0 && board[x][i]==player_id)
    {
        sum+=(y-i-1);
    }
    //check \up
    for(i=1;x-i>=0 && y-i>=0 &&board[x-i][y-i]==-player_id;i++);
    if(x-i>=0 && y-i>=0 && board[x-i][y-i]==player_id)
    {
        sum+=(i-1);
    }
    //check /up
    for(i=1;x+i<BOARD_SIZE && y-i>=0 &&board[x+i][y-i]==-player_id;i++);
    if(x+i<BOARD_SIZE && y-i>=0 && board[x+i][y-i]==player_id)
    {
        sum+=(i-1);
    }
    //check /down
    for(i=1;x-i>=0 && y+i<BOARD_SIZE &&board[x-i][y+i]==-player_id;i++);
    if(x-i>=0 && y+i<BOARD_SIZE && board[x-i][y+i]==player_id)
    {
        sum+=(i-1);
    }
    //check \down
    for(i=1;x+i<BOARD_SIZE && y+i<BOARD_SIZE &&board[x+i][y+i]==-player_id;i++);
    if(x+i<BOARD_SIZE && y+i<BOARD_SIZE && board[x+i][y+i]==player_id)
    {
        sum+=(i-1);
    }
    return sum;
}

int asci_to_int(char string[])
{
    int sum = 0,i=0;
    while(string[i]!='\0')
    {
        if(string[i]-'0'>=0 && string[i]-'0'<=9)
        {
            sum*=10;
            sum+=string[i]-'0';
            i++;
        }
        else return -1;
    }
    return sum;

}

int input_place(int player_id, int board[][BOARD_SIZE])
{
    char x[100],y[100];
    while(1)
    {
    printf("Input x: ");
    scanf("%s",x);
    if(x[0]=='P' && x[1]=='A' && x[2]=='S' && x[3]=='S' && x[4]=='\0') return -1;
    printf("Input y: ");
    scanf("%s",y);
    if(y[0]=='P' && y[1]=='A' && y[2]=='S' && y[3]=='S' && y[4]=='\0') return -1;
    int intx = asci_to_int(x);
    int inty = asci_to_int(y);
    //printf("INTX %d INTY %d\n",intx,inty);
    //printf("OBTAIN %d\n",num_obtained_stone(player_id,intx,inty,board));
    if(board[intx][inty]==0 && num_obtained_stone(player_id,intx,inty,board)!=0) return intx*BOARD_SIZE+inty;
    }
}

int computer(int player_id, int board[][BOARD_SIZE])
{
    srand(time(0));
    int current_id = -1,current_max = 0,k,i,j,p,q;
    //the most important part
    int special[] = {0,BOARD_SIZE-1};
    for(int p=0;p<2;p++)
    {
        for(int q=0;q<2;q++)
        {
            j=  special[p];
            i = special[q];
            if(board[j][i]==0){
                k= num_obtained_stone(player_id,j,i,board);
                if(k>current_max) {
                        current_max =k;
                        current_id =  j*BOARD_SIZE+i;
                }
                else if(k!=0 && k==current_max){
                    if(rand()%2==0)
                    {
                        current_max =k;
                        current_id =  j*BOARD_SIZE+i;
                    }
                }
            }
        }
    }
    if(current_id!=-1) {return current_id;}
    //8 vulnerable spot
    current_id = eightspot(player_id,board,0);
    if(current_id!=-1) {return current_id;}

    int side[] = {0,BOARD_SIZE-1};
    //the side(not include 8 spot)
    for(i=2;i<BOARD_SIZE-2;i++)
    {
        for(p=0;p<2;p++)
        {
            j= side[p];
            if(board[j][i] ==0)
            {
                k=num_obtained_stone(player_id,j,i,board);
                if(k>current_max) {
                        current_max =k;
                        current_id =  j*BOARD_SIZE+i;
                }
                else if(k!=0 && k==current_max){
                    if(rand()%2==0){
                        current_max =k;
                        current_id =  j*BOARD_SIZE+i;
                    }
                }
            }
            if(board[i][j] == 0)
            {
                k=num_obtained_stone(player_id,i,j,board);
                if(k>current_max) {
                        current_max =k;
                        current_id = i*BOARD_SIZE+j;
                }
                else if(k!=0 && k==current_max){
                    if(rand()%2==0)
                    {
                        current_max =k;
                        current_id = i*BOARD_SIZE+j;
                    }
                }

            }
        }
    }
    if(current_id!=-1) {return current_id;}
    //printf("CANNOT side\n");
    //the rest
    for(i=1;i<BOARD_SIZE-1;i++)
    {
        for(j=1;j<BOARD_SIZE-1;j++)
        {
            if((i==1 && j==1)||(i==1 && j==BOARD_SIZE-2)||(i==BOARD_SIZE-2 && j==1)||(i==BOARD_SIZE-2 && j==BOARD_SIZE-2));
            else{
                if(board[j][i]==0){
                    k= num_obtained_stone(player_id,j,i,board);
                    if(k>current_max)
                    {
                        current_max=k;
                        current_id = j*BOARD_SIZE+i;
                    }
                    else if(k!=0 && k==current_max){
                    if(rand()%2==0)
                    {
                        current_max =k;
                        current_id =  j*BOARD_SIZE+i;
                    }
                }
                }
            }
        }
    }
    if(current_id!=-1) {return current_id;}
    //printf("CANNOT rest\n");

    //8 vulnerable spot
    current_id = eightspot(player_id,board,1);
    if(current_id!=-1) {return current_id;}

    //(1,1)(1,6)(6,1)(6,6)
    if(count_stone(1,board)+count_stone(-1,board)>=48)
    {
        int xx[] = {1,BOARD_SIZE-2,BOARD_SIZE-2,1};
        int yy[] = {1,BOARD_SIZE-2,1,BOARD_SIZE-2};
        int save = -1;
        int plus,ending;
        for(int p=0;p<4;p++)
        {
            int x =xx[p];
            int y= yy[p];
            if(board[x][y]==0 && num_obtained_stone(player_id,x,y,board)!=0){
                if(xx[i]==1) plus =1;
                else plus = -1;
                while(x<BOARD_SIZE && y<BOARD_SIZE && x>=0 && y>=0)
                {
                    if(xx[p]==yy[p]) {x+=plus;y+=plus;}
                    else {x+=plus;y-=plus;}
                    if(board[x][y]!=0)ending = board[x][y];
                }
                if(ending==player_id) {return xx[p]*BOARD_SIZE+yy[p];}
                else save = xx[p]*BOARD_SIZE+yy[p];
            }
        }
        if(save!=-1) return save;
    }
    for(int i=0;i<BOARD_SIZE;i++)
    {
        for(int j=0;j<BOARD_SIZE;j++)
        {
            if(board[j][i]==0 && num_obtained_stone(player_id,j,i,board)!=0)
                return j*BOARD_SIZE+i;
        }
    }
}

int eightspot(int player_id, int board[][BOARD_SIZE],int importance)
{
    int yy[] = {0,0,1,1,BOARD_SIZE-2,BOARD_SIZE-2,BOARD_SIZE-1,BOARD_SIZE-1};
    int xx[] = {1,BOARD_SIZE-2,0,BOARD_SIZE-1,0,BOARD_SIZE-1,1,BOARD_SIZE-2};
    for(int i=0;i<8;i++){
        if(board[xx[i]][yy[i]]==0 && num_obtained_stone(player_id, xx[i], yy[i],board)>0){
            int aaa = sideisclear(player_id,xx[i],yy[i],board);
            if(aaa==1)
            {
                if(importance==1) return  xx[i]*BOARD_SIZE+yy[i];
                else{
                    if(xx[i]==0 || xx[i]==BOARD_SIZE-1){
                        if(yy[i]==BOARD_SIZE-2 && board[xx[i]][yy[i]-1]!=-player_id) return -1;
                        if(yy[i]==1 && board[xx[i]][yy[i]+1]!=-player_id) return -1;
                    }
                    else if(yy[i]==0 || yy[i]==BOARD_SIZE-1){
                        if(xx[i]==BOARD_SIZE-2 && board[xx[i]-1][yy[i]]!=-player_id) return -1;
                        if(xx[i]==1 && board[xx[i]+1][yy[i]+1]!=-player_id) return -1;
                    }
                    return xx[i]*BOARD_SIZE+yy[i];
                }
            }
        }
    }
    return -1;
}
int sideisclear(int player_id, int x, int y, int board[][BOARD_SIZE])
{
    int ans = 1,opponent=0,same=0,add;
    if(x==0 || x==BOARD_SIZE-1)
    {
        if(y==1) add = 1;
        else if(y==BOARD_SIZE-2) add=-1;
        if(board[x][y-add]==-player_id && board[x][y+add]==-player_id) return 1;
        y+=add;
        while(y<BOARD_SIZE && y>=0)
        {
            if(board[x][y]==player_id){
                same++;
                if(same==1) opponent=0;
            }
            else if(board[x][y]==-player_id){
                opponent++;
            }
            else break;
            y+=add;
        }
        if(opponent>0) return 0;
        return 1;
    }
    if(y==0 || y==BOARD_SIZE-1){
        if(x==1) add = 1;
        else if(x==BOARD_SIZE-2) add=-1;
            x+=add;
            while(x<BOARD_SIZE && x>=0)
            {
                if(board[x][y]==player_id){
                    if(same==0) opponent=0;
                    same++;
                }
                else if(board[x][y]==-player_id){
                    if(same>0) return 0;
                    opponent++;
                }
                else{
                    if(opponent==0) return 1;
                    else return 0;
                }
                x+=add;
            }
            if(opponent>0) return 0;
            return 1;
    }
}

void update_history(int location, int history[])
{
    int i;
    for(i=0;history[i]!=-2 && i<63;i++);
    history[i] = location;
    history[i+1]=-2;
}

void save_history(int history[])
{
    int a=0;
    int  number;
    FILE *f;
    f = fopen("history.txt", "w");

    while(history[a]!=-2)
    {
        fprintf(f,"Player%d %d %d\n",(a%2)+1,history[a]/8,history[a]%8);
        a++;
    }
    fclose(f);
}

main()
{
    int board[BOARD_SIZE][BOARD_SIZE],user,place,cnt=0;
    int history[HISTORY_SIZE];
    history[0]=-2;
    init_board(board);
    char ans[100];
    printf("Is player first(y/n):");
    scanf("%s",ans);
    if(ans[0]=='y' || ans[0]=='Y') user = 1;
    else user = -1;
    for(int turn=1;turn<HISTORY_SIZE;turn++)
    {
        int stone1 = count_stone(1, board);
        int stone2 = count_stone(-1, board);
        if(stone1==0 || stone2==0) break;
        else if(stone1+stone2==64) break;
        printf("Turn %d[%c]\n",turn,(turn%2==1)?'o':'x');
        printf("Score: P1 | P2\n");
        printf("       %d | %d \n",stone1,stone2);
        print_board(board);
        if((turn%2)*2-1 == user)
        {
            place = input_place(user, board);
            //place=  computer(user,board);
        }
        else
        {
            place=  computer(-user,board);
            //place = input_place(-user, board);
        }
        update_history(place,history);
        if(place!=-1)
        {
            cnt=0;
            place_stone((turn%2)*2-1, place/BOARD_SIZE, place%BOARD_SIZE,board);
            printf("PUT AT %d %d\n",place/BOARD_SIZE, place%BOARD_SIZE);
        }
        else{
            cnt++;
            if(cnt==2)
            {
                break;
            }
        }
        printf("---------------------\n");
    }
    printf("=================\n");
    printf("Game Ended!!!\n");
    print_board(board);
    printf("Score: P1 | P2\n");
    printf("       %d | %d \n",count_stone(1, board),count_stone(-1, board));
    save_history(history);
}
