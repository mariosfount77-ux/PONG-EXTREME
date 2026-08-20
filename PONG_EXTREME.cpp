/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~[LIBRARIES]~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include "raylib.h"
using namespace std;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/******************************************************************/
/*****************************[CLASSES]****************************/
/******************************************************************/
class BALL
{
    private:
    int speedX=8;
    int speedY=8;
    int radius;
    int x;
    int y;
    Color color;
    public:
    BALL(int X,int Y, int R, Color col);
    ~BALL();
    void DrawBall();
    void Move();
    float getY()const;
    float getX()const;
    float getR()const;
    void ChangeDirectionOnImpactX();
    void ChangeDirectionOnImpactY();
};
/********************************************************************/
/********************************************************************/
/********************************************************************/
class Paddle
{
    private:
    int x;
    int y;
    int width;
    int height;
    int speedP=0;
    Color color;
    public:
    Paddle(int X, int Y, int W, int H, Color col);
    ~Paddle();
    void DrawPaddle();
    void MovePaddle();
    void MovePaddleAuto(int ballPosition);
    float getX()const;
    float getY()const;
    float getW()const;
    float getH()const;
};
/******************************************************************/
/******************************************************************/
/******************************************************************/
class Obstacles
{
    private:
    int x;
    int y;
    float radius;
    int speedY=20;
    Color color;
    public:
    Obstacles(int X, int Y, float R, Color col);
    ~Obstacles();
    void MoveObst();
    void DrawObstacle();
    float getX()const;
    float getY()const;
    float getR()const;
};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class Corner
{
    private:
    float x1;
    float x2;
    float x3;
    float y1;
    float y2;
    float y3;
    Color color;
    public:
    Corner(float X1,float Y1, float X2,float Y2, float X3, float Y3,Color col);
    ~Corner();
    void DrawTr();
    float getX1()const;
    float getX2()const;
    float getX3()const;
    float getY1()const;
    float getY2()const;
    float getY3()const;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[MAIN]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*SCORE*/
    int Player1Score=0;
    int Player2Score=0;
int main(void)
{
    
    /*SCREEN*/
    int screenWidth=1200;
    int screenHeight=800;
    /*PADDLES*/
    //int paddleWidth=20;
    //int paddleHeight=100;
    
    char c;
    int difficulty;
    bool n=true;
    
    cout<<"Welcome to PONG EXTREME."<<endl;
    cout<<"SCORE 20 POINTS TO WIN!!!"<<endl;
    cout<<"You are the white paddle. Press 'W' for up and 'S' for down."<<endl;
    while(n)
    {
        cout<<"Select difficulty: [1]  EASY, [2] NORMAL, [3] EXTREME."<<endl;    
        cin>>difficulty ;
        if(difficulty==1 || difficulty==2 || difficulty==3)
        n=false;
    }
    cout<<"Press any key to start! (exept <SPACE> and <ENTER>)"<<endl;
    cin>>ws>>c;
    
    InitWindow(screenWidth,screenHeight,"PONG-EXTREME");
    InitAudioDevice(); //Activate sound!

    Sound PaddleStrike=LoadSound("freesound_community-hit-94706.mp3");//
    Sound BoundaryStrike=LoadSound("11325622-metal-hit-sound-effect-241374.mp3");
    Sound Victory=LoadSound("u_ss015dykrt-brass-fanfare-with-timpani-and-winchimes-reverberated-146260.mp3");
    Sound Lost=LoadSound("freesound_community-game-over-38511.mp3");
    Sound Point=LoadSound("floraphonic-90s-game-ui-10-185103.mp3");

    BALL ball(screenWidth/2,screenHeight/2,15,RED);
    
    Paddle PLAYER(10,screenHeight/2-50,20,100,WHITE);
    Paddle PLAYER2(screenWidth-30,screenHeight/2-50,20,100,BLACK);
    
    Obstacles Object1(screenWidth/4,10,10,YELLOW);
    Obstacles Object2(screenWidth*0.75,10,10,YELLOW);

    Corner Corner1(40,0,0,0,0,40,YELLOW);
    Corner Corner2(screenWidth,0,screenWidth-40,0,screenWidth,40,YELLOW);
    Corner Corner3(0,screenHeight,40,screenHeight,0,screenHeight-40,YELLOW);
    Corner Corner4(screenWidth,screenHeight,screenWidth,screenHeight-40,screenWidth-40,screenHeight,YELLOW);//(screenWidth,screenHeight,screenWidth-40,screenHeight,screenWidth,screenHeight-40,YELLOW);
    
    if(difficulty==1)
    SetTargetFPS(60);
    if(difficulty==2)
    SetTargetFPS(100);
    if(difficulty==3)
    SetTargetFPS(120);

    while(WindowShouldClose()==false)
    {
//START DRAWING
        BeginDrawing();
//PAINT BACKGROUND BLUE
        ClearBackground(DARKBLUE);
//DRAW MIDDLE LINE, Circle AND SCORE NUMBERS
        DrawLine(screenWidth/2,0,screenWidth/2,screenHeight,GREEN);
        DrawText(TextFormat("%i",Player1Score),screenWidth/4,5,80,WHITE);
        DrawText(TextFormat("%i",Player2Score),screenWidth*0.75,5,80,BLACK);
        DrawCircleLines(screenWidth/2,screenHeight/2,100,GREEN);
//DRAW AND MOVE THE YELLOW BALLS
        Object1.DrawObstacle();
        Object1.MoveObst();
        Object2.DrawObstacle();
        Object2.MoveObst();
//DRAW THE FOR CORNERS OF THE MAP
        Corner1.DrawTr();
        Corner2.DrawTr();
        Corner3.DrawTr();
        Corner4.DrawTr();
//DRAW AND MOVE THE RED BALL AROUND
        ball.DrawBall();
        ball.Move();
//DRAW THE TWO PLAYER PADDLES
        PLAYER.DrawPaddle();
        PLAYER2.DrawPaddle();
//MOVE THE TWO PLAYER PADDLES
        PLAYER.MovePaddle();
        PLAYER2.MovePaddleAuto(ball.getY());
//BALL WITH YELLOW BALL [1]!!!!
        if(CheckCollisionCircles(Vector2{ball.getX(),ball.getY()},ball.getR(),Vector2{Object1.getX(),Object1.getY()},Object1.getR()))
        {
            ball.ChangeDirectionOnImpactX();///C:\Users\mario\Pro_graming\CODING_C++\GAMES\PONG
            PlaySound(BoundaryStrike);
        }
//BALL WITH YELLOW BALL [2]!!!!
        if(CheckCollisionCircles(Vector2{ball.getX(),ball.getY()},ball.getR(),Vector2{Object2.getX(),Object2.getY()},Object2.getR()))
        {
            ball.ChangeDirectionOnImpactX();
            PlaySound(BoundaryStrike);
        }
//BALL WITH WHITE PADDLE
        if(CheckCollisionCircleRec(Vector2{ball.getX(),ball.getY()},ball.getR(),Rectangle{PLAYER.getX(),PLAYER.getY(),PLAYER.getW(),PLAYER.getH()}))
        {
            ball.ChangeDirectionOnImpactX();
            PlaySound(PaddleStrike);
        }
//BALL WITH BLACK PADDLE
        if(CheckCollisionCircleRec(Vector2{ball.getX(),ball.getY()},ball.getR(),Rectangle{PLAYER2.getX(),PLAYER2.getY(),PLAYER2.getW(),PLAYER2.getH()}))
        {
            ball.ChangeDirectionOnImpactX();
            PlaySound(PaddleStrike);
        }
//BALL WITH CORNER [1]
        if(CheckCollisionCircleLine(Vector2{ball.getX(),ball.getY()},ball.getR(),Vector2{40,0},Vector2{0,40}))
        {
            ball.ChangeDirectionOnImpactX();
            ball.ChangeDirectionOnImpactY();
            PlaySound(BoundaryStrike);
        }
//BALL WITH CORNER [2]
        if(CheckCollisionCircleLine(Vector2{ball.getX(),ball.getY()},ball.getR(),Vector2{screenWidth-(float)40,0},Vector2{(float)screenWidth,40}))
        {
            ball.ChangeDirectionOnImpactX();
            ball.ChangeDirectionOnImpactY();
            PlaySound(BoundaryStrike);
        }
//BALL WITH CORNER [3]
        if(CheckCollisionCircleLine(Vector2{ball.getX(),ball.getY()},ball.getR(),Vector2{0,(float)screenHeight-40},Vector2{40,(float)screenHeight}))
        {
            ball.ChangeDirectionOnImpactX();
            ball.ChangeDirectionOnImpactY();
            PlaySound(BoundaryStrike);
        }
//BALL WITH CORNER [4]
        if(CheckCollisionCircleLine(Vector2{ball.getX(),ball.getY()},ball.getR(),Vector2{(float)screenWidth,(float)screenHeight-40},Vector2{(float)screenWidth-40,(float)screenHeight}))
        {
            ball.ChangeDirectionOnImpactX();
            ball.ChangeDirectionOnImpactY();
            PlaySound(BoundaryStrike);
        }
///SOUNDS POINTS AND BOUNDARY
        if(     (ball.getX()+ball.getR()>screenWidth) || ball.getX()-ball.getR()<0    )
        {
            PlaySound(Point);
        }

        if(ball.getY()-ball.getR()<0 || ball.getY()+ball.getR()>screenHeight)
        {
            PlaySound(BoundaryStrike);
        }
//FINISH DRAWING!        
        EndDrawing();
        if(Player1Score==20)
        {
            PlaySound(Victory);
            cout<<"CONGRATS YOU WON!!!!"<<endl;
            cout<<"YOU: "<<Player1Score<<" CPU: "<<Player2Score<<endl;
            break;
        }
        else if(Player2Score==20)
        {
            PlaySound(Lost);
            cout<<"I AM SORRY YOU LOST!!!"<<endl;
            cout<<"YOU: "<<Player1Score<<" CPU: "<<Player2Score<<endl;
            break;
        }
    }
   

    cout<<"Game closed!"<<endl;
    UnloadSound(PaddleStrike);
    UnloadSound(BoundaryStrike);
    UnloadSound(Victory);
    UnloadSound(Lost);
    UnloadSound(Point);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~[FUNCTIONS-BALL]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
BALL::BALL(int X, int Y, int R, Color col)
{
    cout<<"Ball created!"<<endl;
    x=X;
    y=Y;
    radius=R;
    color=col;
}

BALL::~BALL()
{
    cout<<"Ball destroyed!"<<endl;
}

void BALL::DrawBall()
{
    DrawCircle(x,y,radius,color);
}

void BALL::Move()
{
    if(x+radius>GetScreenWidth() || x-radius<0)
    {
        x=GetScreenWidth()/2;
        y=GetScreenHeight()/2;
        int speedChoices[2]={-1,1};
        speedX*=speedChoices[GetRandomValue(0,1)];
        speedY*=speedChoices[GetRandomValue(0,1)];
    }
    x+=speedX;

    if(x+radius>GetScreenWidth())
    {
        Player1Score++;
    }
    if(x-radius<0)
    {
        Player2Score++;
    }
    
    if(y+radius>GetScreenHeight() || y-radius<0)
    {
        speedY*=-1;
    }
    y+=speedY;    
}

float BALL::getY()const
{
    return y;
}

float BALL::getX()const
{
    return x;
}

float BALL::getR()const
{
    return radius;
}

void BALL::ChangeDirectionOnImpactX()
{
    speedX*=-1;
}

void BALL::ChangeDirectionOnImpactY()
{
    speedY*=-1;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~[FUNCTIONS-PADDLE]~~~~~~~~~~~~~~~~~~~~~~~~*/

Paddle::Paddle(int X, int Y, int W, int H, Color col)
{
    cout<<"Paddle created!"<<endl;
    x=X;
    y=Y;
    width=W;
    height=H;
    color=col;
}

Paddle::~Paddle()
{
    cout<<"Paddle destroyed!"<<endl;
}

void Paddle::DrawPaddle()
{
    DrawRectangle(x,y,width,height,color);
}

void Paddle::MovePaddle()
{
    if(IsKeyDown(KEY_W))
    {
        if(y<40)
        speedP=0;
        else
        speedP=-7;
        
        y+=speedP;
    }
    if(IsKeyDown(KEY_S))
    {
        if(y+height>GetScreenHeight()-40)
        speedP=0;
        else
        speedP=7;

        y+=speedP;
    }
}

void Paddle::MovePaddleAuto(int ballPosition)
{
    
    if(ballPosition<y)
    {
        if(y<40)
        speedP=0;
        else
        speedP=-7;
    }
    if(ballPosition>y)
    {   
        if(y+height>GetScreenHeight()-40)
        speedP=0;
        else
        speedP=7;
    }

    y+=speedP;
}

float Paddle::getX()const
{
    return x;
}
float Paddle::getY()const
{
    return y;
}
float Paddle::getW()const
{
    return width;
}
float Paddle::getH()const
{
    return height;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~[FUNCTIONS-OBSTACLE]~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Obstacles::Obstacles(int X, int Y, float R, Color col)
{
    cout<<"Obstacle created!"<<endl;
    x=X;
    y=Y;
    radius=R;
    color=col;
}

Obstacles::~Obstacles()
{
    cout<<"Obstacle destroyed!"<<endl;
}

void Obstacles::MoveObst()
{
    if(y+radius>GetScreenHeight())
    {
        speedY*=-1;
    }
    if(y-radius<0)
    {
        speedY*=-1;
    }
    y+=speedY;
}

void Obstacles::DrawObstacle()
{
    DrawCircle(x,y,radius,color);
}

float Obstacles::getX()const
{
    return x;
}

float Obstacles::getY()const
{
    return y;
}

float Obstacles::getR()const
{
    return radius;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~[FUNCTION-TRIANGLE]~~~~~~~~~~~~~~~~~~*/

Corner::Corner(float X1,float Y1, float X2,float Y2, float X3, float Y3,Color col)
{
    cout<<"Corner created!"<<endl;
    x1=X1;
    x2=X2;
    x3=X3;
    y1=Y1;
    y2=Y2;
    y3=Y3;
    color=col;
}

Corner::~Corner()
{
    cout<<"Corner destroyed!"<<endl;
}

void Corner::DrawTr()
{
    DrawTriangle(Vector2{x1,y1},Vector2{x2,y2},Vector2{x3,y3},color);
}

float Corner::getX1()const
{
    return x1;
}
float Corner::getX2()const
{
    return x2;
}
float Corner::getX3()const
{
    return x3;
}
float Corner::getY1()const
{
    return y1;
}
float Corner::getY2()const
{
    return y2;
}
float Corner::getY3()const
{
    return y3;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~[END OF FILE]~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
