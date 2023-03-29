#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define N 30
#define M 60

int i,j, field[N][M],x,y,z,snake_head,snake_tail,game,frogs,a,b,var,direction,score,highscore,speed;

FILE *f;

/*order of functions = snake start, print game, reset position, Random position, getch noblock, movement, TailRemove, gameOver*/

void snake_start()
{
    f=fopen("highscore.txt","r");

    fscanf(f, "%d", &highscore);

    fclose(f);

    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            field[i][j]=0;
        }
    }

    x=N/2;
    y=M/2;
    z=y;
    snake_head=5;
    snake_tail=1;
    game=0;
    frogs=0;
    direction= 'd';
    score= 0;
    speed= 99;

    for(i=0; i<snake_head; i++)
    {
        z++;
        field[x][z-snake_head]=
        i+1;
    }
}

void print_game()
{
  for(i=0; i<=M+1; i++)
    {
        if(i==0)
        {
            printf("%c", 201);                                                                                                                                                                             /*201*/
        }
        else if(i== M+1)
        {
            printf("%c", 187);                                                                                                                                                                            /*187*/
        }
        else
        {
            printf("%c", 205);                                                                                                                                                                            /*205*/
        }
    }


    printf("    Current score: %d   Highscore: %d", score, highscore);
    printf("\n");

    for(i=0; i<N; i++)
    {
        printf("%c", 186);                                                                                                                                                                                                                                       /*186*/

        for(j=0; j<M; j++)
        {
            if(field[i][j]==0){printf(" ");}

            if(field[i][j]>0 && field[i][j]!=snake_head)
                {printf("%c", 176);}                                                                                                                                                                                                                             /*176*/

            if(field[i][j]==snake_head)
            {printf("%c",178);}                                                                                                                                                                                                                                  /*178*/

            if(field[i][j] == -1)
            {printf("%c", 15);}                                                                                                                                                                                                                                  /*15*/

            if(j==M-1)
            {printf("%c\n", 186);}                                                                                                                                                                                                                               /*186*/
        }
    }

    for(i=0; i<=M+1; i++)
    {
        if(i==0)
        {
            printf("%c", 200);                                                                                                                                                                                                                                   /*200*/
        }
        else if(i== M+1)
        {
            printf("%c", 188);                                                                                                                                                                                                                                   /*188*/
        }
        else
        {
            printf("%c", 205);                                                                                                                                                                                                                                  /*205*/
        }
    }
}

void reset_position()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X=0;
    Position.Y=0;

    SetConsoleCursorPosition(hOut,Position);
}

void Random_position()
{
    srand(time(0));
    a = 1+rand() %18;
    b = 1+rand() %38;

    if(frogs==0 && field[a][b] == 0)
    {
        field[a][b] = -1;
        frogs = 1;
        if(speed > 10 && score != 0)
            {speed=speed -10;}
    }
}

int getch_noblock()
{
    if(_kbhit())
    return _getch();
    else
    return -1;
}

void movement()
{
    var = getch_noblock();
    var = tolower(var);

    if(((var == 'd' || var == 'a') || (var == 'w' || var == 's'))&& (abs(direction-var)>5))
            {direction = var;}

    if(direction == 'd')
    {
        y++;
        if(y==M-1)
        {y=0;}

        if(field[x][y]!=0 && field[x][y]!= -1)
            {gameOver();}

        if(field[x][y] == -1)
        {
            frogs =0;
            score +=5;
            snake_tail -= 2;
        }
        snake_head++;
        field[x][y] = snake_head;
    }

    if( direction == 'a')
    {
        y--;
        if(field[x][y]!=0 && field[x][y]!= -1)
            gameOver();
        if(y == 0) y= M-1;

        if(field[x][y]== -1)
        {
           frogs = 0;
           score += 5;
           snake_tail -=2;
        }
        snake_head++;
        field[x][y] = snake_head;
    }

    if( direction == 'w')
    {
        x--;
        if(field[x][y]!=0 && field[x][y]!= -1)
            gameOver();
        if(x == -2)
        {x= N-1;}

        if(field[x][y]== -1)
        {
           frogs = 0;
           score += 5;
           snake_tail -= 2;
        }
        snake_head++;
        field[x][y] = snake_head;
    }

    if( direction == 's')
    {
        x++;
        if(field[x][y]!=0 && field[x][y]!= -1)
            {gameOver();}
        if(x==N-1)
        {x= 0;}

        if(field[x][y]== -1)
        {
           frogs = 0;
           score += 5;
           snake_tail -=2;
        }
        snake_head++;
        field[x][y] = snake_head;
    }
}

void TailRemove()
{
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
            {
                if(field[i][j] == snake_tail)
                {
                    field[i][j] = 0;
                }
            }
    }
    snake_tail++;
}

void gameOver()
{
    printf("\a");

    sleep(1);
    system("Cls");

    if(score>highscore)
    {
        printf("\n\n    New High Score : %d  !!!!\n\n", score);
        system("pause");
        f=fopen("highscore.txt", "w");
        fprintf(f, "%d", score);
        fclose(f);
    }

    system("Cls");
    printf("\n\n                  !!!! GAME OVER !!!! \n");
    printf("                         Score: \n                           %d \n\n", score);
    printf("          Press ENTER to play again or ESC to exit ...");

    while(1)
    {
        var = getch_noblock();
        if(var == 13)
        {
            game = 0;
            snake_start();
            break;
        }
        else if(var == 27)
        {
            game = 1;
            break;
        }
    }
    system("Cls");
}

void main()
{
    snake_start();

    while(game == 0)
    {
        print_game();
        reset_position();
        Random_position();
        movement();
        TailRemove();
        Sleep(speed);
    }
}


