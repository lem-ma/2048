/* 2048 Version 2.1
 * Author: Lem-ma
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

char obtainchar(void)
{
    char c=getchar();
    if(c=='\n'||c=='\r'||c==EOF) return EOF;
    char d;
    while((d=getchar())!='\n'&&d!='\r'&&d!=EOF);
    return c;
}

int writeboard(int* board, int end)
{
    char* table[]={"    ","2   ","4   ","8   ","16  ","32  ","64  ","128 ","256 ","512 ","1024","2048"};
    puts("\n");
    /*
     * -----------------------------
     * | 2048 | 2048 | 2048 | 2048 |
     * */
    for(int i=0;i<4;i++)
    {
        puts("-----------------------------");
        printf("| %s | %s | %s | %s |\n",table[board[4*i]],table[board[4*i+1]],table[board[4*i+2]],table[board[4*i+3]]);
    }
    puts("-----------------------------");
    if(end==1) puts("\nGame ends.\n");
    else
    {
        puts("\nPlease enter a character.");
        puts("h -- left\tl -- right\nj -- down\tk -- up\nq -- exit\ts -- save\n");
        fputs("\n>>> ",stdout);
    }
    return end;
}

void gaming(int* board, char command)
{
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
}

size_t readalnum(char str[], size_t length)
{
    size_t i;
    for(i=0;i<length&&isalnum((str[i]=getchar()));i++);
    if(str[i]=='\n'||str[i]=='\r'||str[i]==EOF)
    {
        str[i]='\0';
        return i;
    }
    str[i]='\0';
    char d;
    while((d=getchar())!='\n'&&d!='\r'&&d!=EOF);
    return i;
}

void add_2048_extension(char name[], size_t length)
{
    char extension[]=".2048";
    strcpy(name+length, extension);
}

char launchboard(int* board, int putstone)
{
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
    if(j&&putstone)
    {
        board[logging[rand()%j]]=1;
    }
    if(writeboard(board, won||(j==0))) return 0;
    else
    {
        char c;
        while((c=obtainchar())!='h'&&c!='j'&&c!='k'&&c!='l'&&c!='q')
        {
            if(c=='s')
            {
                fputs("\nPlease enter the file name to save (without extension, MAX. 10 characters): ",stdout);
                char filename[16];
                size_t length=readalnum(filename, 10);
                add_2048_extension(filename, length);
                FILE* pfile=fopen(filename,"wb");
                if(pfile==NULL) puts("\nFile error!");
                else
                {
                    if(fwrite(board,sizeof(int),16,pfile)!=16)
                    {
                        puts("File saving fails.");
                    }
                    fclose(pfile);
                    puts("File saved.");
                }
                fputs(">>> ",stdout);
            }
            else
            {
                fputs("Wrong syntax! Please input again.\n>>> ",stdout);
            }
        }
        if(c=='q') return 0;
        else return c;
    }
}

int main(void)
{
    puts("2048 Version 2.1 by Lem-ma");
    srand(time(NULL));
    int cont=1;
    while(cont)
    {
        char init;
        puts("Enter \"q\" to exit, \"s\" to open saved game, or any other key to start a new game.");
        if((init=obtainchar())=='q')
        {
            cont=0;
        }
        else
        {
            int currentboard[16];
            if(init=='s')
            {
                fputs("\nPlease enter the file name, without extension: ",stdout);
                char name[16];
                size_t k=readalnum(name, 10);
                add_2048_extension(name, k);
                FILE* pfile=fopen(name, "rb");
                if(pfile==NULL)
                {
                    printf("\nFile %s does not exist!\n",name);
                    continue;
                }
                else
                {
                    if(fread(currentboard,sizeof(int),16,pfile)!=16)
                    {
                        printf("\nFile %s is broken!\n", name);
                        fclose(pfile);
                        continue;
                    }
                    else
                    {
                        k=0;
                        for(int i=0;i<16;i++)
                        {
                            if(currentboard[i]>11||currentboard[i]<0)
                            {
                                printf("\nFile %s is broken\n", name);
                                fclose(pfile);
                                k=1;
                                break;
                            }
                        }
                        if(k) continue;
                        init=1;
                        fclose(pfile);
                    }
                }
            }
            else
            {
                for(int i=0;i<16;i++)
                {
                    currentboard[i]=0;
                }
                init=0;
            }
            char gamestill=1;
            if(init&&(gamestill=launchboard(currentboard,0)))
            {
                gaming(currentboard,gamestill);
            }
            while(gamestill)
            {
                if((gamestill=launchboard(currentboard,1))) gaming(currentboard, gamestill);
            }
        }
    }
    return 0;
}
