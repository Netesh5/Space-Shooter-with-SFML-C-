#include <iostream>
#include<graphics.h>
#include<fstream>
using namespace std;
void arrow(int,int);
void loadingscreen();
void startgame();
void highscore();
void instruction();
void exit();
void credits();
void enemy();
void startgame();

class maingame{
private:
    int x=getmaxx();
    int y=getmaxy();
    int key=0;
public:
    void menu();
};

class loadingScreen{
private:
    int i;
public :
     void loading(){
         readimagefile("Images/loading.jpg",0,0,getmaxx(),getmaxy());
         PlaySound(TEXT("Sounds/background.wav"),NULL,SND_ASYNC);
         for(i=0;i<getmaxx();i+=5){
            setfillstyle(SOLID_FILL,3);
            bar3d(0,getmaxy()/2+200,i,getmaxy()/2+210,0,0);
            delay(1);
         }
    }



};

void maingame::menu(){
    int position=70,key=0;
    while(key!=13)
    {
    readimagefile("Images/bg.jpg",0,0,getmaxx(),getmaxy());
    arrow(70,position);
    arrow(140,position);
    arrow(210,position);
    arrow(280,position);
    arrow(350,position);
    key=getch();
    if(key==80 && position!=350)
    {
        position+=70;
        PlaySound(TEXT("Sounds/menu sound.wav"),NULL,SND_ASYNC);
    }
    else if(key==72 && position!=70)
    {
        position-=70;
        PlaySound(TEXT("Sounds/menu sound.wav"),NULL,SND_ASYNC);
    }
    else
    {
        position=position;
    }

}
switch(position){
    case 70:
        PlaySound(TEXT("Sounds/enter.wav"),NULL,SND_ASYNC);
        closegraph();
        startgame();
        break;
    case 140:
        PlaySound(TEXT("Sounds/enter.wav"),NULL,SND_ASYNC);
        highscore();
        PlaySound(TEXT("Sounds/background.wav"),NULL,SND_ASYNC);
        key=getch();
        if(key==27)
        {
            PlaySound(TEXT("Sounds/cancel.wav"),NULL,SND_ASYNC);
            menu();
        }
        break;
    case 210:
        PlaySound(TEXT("Sounds/enter.wav"),NULL,SND_ASYNC);
        instruction();
        PlaySound(TEXT("Sounds/background.wav"),NULL,SND_ASYNC);
        key=getch();
        if(key==27)
        {
            PlaySound(TEXT("Sounds/cancel.wav"),NULL,SND_ASYNC);
            menu();
        }
        break;
    case 280:
        PlaySound(TEXT("Sounds/enter.wav"),NULL,SND_ASYNC);
        credits();
        PlaySound(TEXT("Sounds/background.wav"),NULL,SND_ASYNC);
        key=getch();
        if(key==27)
        {
            PlaySound(TEXT("Sounds/cancel.wav"),NULL,SND_ASYNC);
            menu();
        }
        break;
    case 350:
        PlaySound(TEXT("Sounds/enter.wav"),NULL,SND_ASYNC);
        closegraph();
    }
}
void arrow(int realposition ,int arrowposition)
{
    if(realposition==arrowposition)
    {
        settextstyle(4,HORIZ_DIR,3);
        outtextxy(80,70+arrowposition,"=>");
    }
}

void highscore()
{
    int highscore;
    char score[9];
    readimagefile("Images/highscore.jpg", 0, 0, getmaxx(), getmaxy());
    ifstream fin;
    fin.open("Score.txt");
    fin>>highscore;
    sprintf(score,"%d\n",highscore);
    settextstyle(4,HORIZ_DIR,4);
    outtextxy(400,260,score);

}


void credits()
{
    readimagefile("Images/credits.jpg",0,0,getmaxx(),getmaxy());
}


void instruction()
{
    readimagefile("Images/instructions.jpg",0,0,getmaxx(),getmaxy());
}

int main()
{
    int gd=DETECT,gm;
    initwindow(getmaxwidth(),getmaxheight());
    loadingScreen l;
    l.loading();
    maingame m;
    m.menu();
    getch();
    return 0;
}
