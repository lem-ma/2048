#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char obtainchar(void) 
{
    char c=getchar();
    if(c=='\n'||c=='\r'||c==EOF) return '!';
    char d;
    while((d=getchar())!='\n'&&d!='\r'&&d!=EOF) c=d;
    return c;
}

int printboard(int* board)
{
    /*Check zero points*/
    int j=0;
    int won=0;
    int logging[16];
    for(int i=0;i<16;i++)
    {
        if(board[i]==0)
        {
            logging[j]=i;
            j++;
        }
        else if(board[i]==11)
        {
            won=1;
            j=0;
            break;
        }
    }
    if(j)
    {
        board[logging[rand()%j]]=1;
    }
    /*Start printing the board*/
    char* table[]={"    ","2   ","4   ","8   ","16  ","32  ","64  ","128 ","256 ","512 ","1024","2048"};
    if(won) puts("You have won.\n");
    else puts("\n");
    /*
     * -----------------------------
     * | 2048 | 2048 | 2048 | 2048 |
     * */
    for(int i=0;i<4;i++)
    {
        printf("-----------------------------\n");
        printf("| %s | %s | %s | %s |\n",table[board[4*i]],table[board[4*i+1]],table[board[4*i+2]],table[board[4*i+3]]);
    }
    printf("-----------------------------");
    puts("\nPlease enter a character.");
    puts("h -- left\tl -- right\nj -- down\tk -- up\n");
    printf("\n>>> ");
    return j;
}

void gaming(int* board, char command)
{
    /*
     * 0  1  2  3
     * 4  5  6  7
     * 8  9  10 11
     * 12 13 14 15
     * */
    int cache;
    int merge;
    if(command=='h')
    {
        for(int i=0;i<4;i++)
        {
            cache=0;
            merge=1;
            for(int j=0;j<4;j++)
            {
                if(board[4*i+j])
                {
                    if(cache&&merge&&board[4*i+cache-1]==board[4*i+j])
                    {
                        board[4*i+cache-1]++;
                        merge=0;
                    }
                    else
                    {
                        board[4*i+cache]=board[4*i+j];
                        cache++;
                        merge=1;
                    }
                }
            }
            for(int j=cache;j<4;j++) board[4*i+j]=0;
        }
    }
    else if(command=='l')
    {
        for(int i=0;i<4;i++)
        {
            cache=3;
            merge=1;
            for(int j=3;j>=0;j--)
            {
                if(board[4*i+j])
                {
                    if(cache!=3&&merge&&board[4*i+cache+1]==board[4*i+j])
                    {
                        board[4*i+cache+1]++;
                        merge=0;
                    }
                    else
                    {
                        board[4*i+cache]=board[4*i+j];
                        cache--;
                        merge=1;
                    }
                }
            }
            for(int j=0;j<=cache;j++) board[4*i+j]=0;
        }
    }
    else if(command=='j')
    {
        for(int i=0;i<4;i++)
        {
            cache=3;
            merge=1;
            for(int j=3;j>=0;j--)
            {
                if(board[i+4*j])
                {
                    if(cache!=3&&merge&&board[i+4*(cache+1)]==board[i+4*j])
                    {
                        board[i+4*(cache+1)]++;
                        merge=0;
                    }
                    else
                    {
                        board[i+4*cache]=board[i+4*j];
                        cache--;
                        merge=1;
                    }
                }
            }
            for(int j=0;j<=cache;j++) board[i+4*j]=0;
        }
    }
    else if(command=='k')
    {
        for(int i=0;i<4;i++)
        {
            cache=0;
            merge=1;
            for(int j=0;j<4;j++)
            {
                if(board[i+4*j])
                {
                    if(cache&&merge&&board[i+4*(cache-1)]==board[i+4*j])
                    {
                        board[i+4*(cache-1)]++;
                        merge=0;
                    }
                    else
                    {
                        board[i+4*cache]=board[i+4*j];
                        cache++;
                        merge=1;
                    }
                }
            }
            for(int j=cache;j<4;j++) board[i+4*j]=0;
        }
    }
    else puts("Wrong syntax!\n>>> "),gaming(board,obtainchar());
}

int main(void)
{
    srand(time(NULL));
    int cont=1;
    while(cont)
    {
        puts("Enter \"q\" to exit, enter any other key to start the game.\n");
        if(obtainchar()=='q')
        {
            cont=0;
        }
        else
        {
            int currentboard[16];
            for(int i=0;i<16;i++)
            {
                currentboard[i]=0;
            }
            int gamestill=1;
            while(gamestill)
            {
                if((gamestill=printboard(currentboard)))
                {
                    gaming(currentboard, obtainchar()); 
                }
            }
        }
    }
    return 0;
}
