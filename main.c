//
//  main.c
//  Tetris
//
//  Created by Sandra Bravo Marmolejo on 28/11/17.
//  Copyright © 2017 Sandra Bravo Marmolejo. All rights reserved.
//

#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Figuras.h"

float PaletaColor27[30][3] = {/*0*/0,0,0,/*1*/0,0,0.5,/*2*/0,0,1,/*3*/0,0.5,0,/*4*/0,0.5,0.5,/*5*/0,0.5,1,/*6*/0,1,0,/*7*/0,1,0.5,/*8*/0,1,1,/*9*/0.5,0,0,/*10*/0.5,0,0.5,/*11*/0.5,0,1,/*12*/0.5,0.5,0,/*13*/0.5,0.5,0.5,/*14*/0.5,0.5,1,/*15*/0.5,1,0,/*16*/0.5,1,0.5,/*17*/0.5,1,1,/*18*/1,0,0,/*19*/1,0,0.5,/*20*/1,0,1,/*21*/1,0.5,0,/*22*/1,0.5,0.5,/*23*/1,0.5,1,/*24*/1,1,0,/*25*/1,1,0.5,/*26*/1,1,1,/*27*/0.26,0.26,0.26,/*28*/0.16,0.16,0.16,/*29*/0.83,0.80,0.83};
//Callbacks
void display(void);
void Animar(void);
//Funciones auxiliares en dibujo y movimineto
void DibujaTexto(char *Text, float x, float y);
void Background(void);
void Coordenadas(void);
void BussyBlocks(void);
void Repintado(void);
int Encajar(void);
void EliminarRenglon(void);
//Funciones para interaccion
void Raton(int boton, int estado,int x, int y);
void SpecialKey(int key,int x,int y);
//Variables
int Limits[4];
int FigType;
int Punto[3]={111,111,1};
float MatrixRotation[3][3]={111,111,0,111,111,0,0,0,1};
int MatrixTraslation[3][3]={1,0,111,0,1,111,0,0,1};
unsigned char NewItemFlag=1;
FIGURA *figNew=NULL, *figArray=NULL, *figAux=NULL;
int blockJ[4], blockI[4];
int Block[10][20];
int slp=0;
int Puntaje=0;
int Nivel=1;
int flagMove=1;
char ScoreText[40]="Score";
char Score[40]="_";
char LevelText[40]="Level";
char Level[40]="_";

int main(int argc, char** argv)
{
     srand(time(NULL));
    /**************************************Configuraciones iniciales*/
    glutInit(&argc, argv);
    glutInitWindowPosition(300, 80);
    glutInitWindowSize(510, 780);
    glutCreateWindow("****TETRIS ****");
    glClearColor(0 ,0, 0, 0); //1,1,0
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,510,0,780);
    
    /***********************************Asignacion de CALLBACKS (Funciones de Servicio de eventos)*/
    glutDisplayFunc(&display);
    glutSpecialFunc(&SpecialKey);
    glutMouseFunc(&Raton);
    glutIdleFunc(&Animar);
    
    int i,j;
    for(i=0;i<20;i++)
    {
        for(j=0;j<10;j++)
            Block[i][j]=0;
    }
    
    FigType=rand()%((4)+1);
    figNew=CrearFigura();
    DatosFigura(figNew, FigType);
    Coordenadas();
    /************************************Estado de espera de eventos*/
    glutMainLoop();
    
    return 0;
}

void display()
{
    int i,j;
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    if(flagMove) //si no ha perdido el jugador
    {
        BussyBlocks();
        Background();
        Repintado();
        EliminarRenglon();
        
        GiveColor(VERDE_CLARO);
        DibujaTexto(ScoreText, 385, 400);
        sprintf(Score,"%d",Puntaje);
        DibujaTexto(Score, 400, 430);
        DibujaTexto(LevelText, 385, 600);
        sprintf(Level,"%d",Nivel);
        DibujaTexto(Level, 400, 630);
        
        if(Puntaje>Nivel*60)
            Nivel++;
        
        if(NewItemFlag==1) //Dibujar Nueva figura
        {
            DrawFig(figNew);
        }
        if(figNew!=NULL)
        {
            if(Encajar()) //Agregar nueva figura al arreglo Arreglo de figuras
            {
                for(i=0;i<4;i++)
                {
                    Block[blockI[i]][blockJ[i]]=1;
                }
                figArray=IngresaFigura(figArray, figNew);
                figNew=NULL;
                NewItemFlag=0;
            }
        }
        if(NewItemFlag==0) //Generar nueva Figura
        {
            figNew=CrearFigura();
            FigType=rand()%((4)+1);
            Coordenadas();
            DatosFigura(figNew, FigType);
            NewItemFlag=1;
        }
    }
    
    for(j=0;j<10;j++)
    {
        if(Block[j][1]==1)
            flagMove=0;
    }
    glFlush();
}

void Coordenadas(void)
{
    int i,k;
    switch (FigType) {
        case 0: //Cuadrado
            //Vertices de la figura
            figNew->vertices[0].x=30;
            figNew->vertices[0].y=750;
            figNew->vertices[1].x=60;
            figNew->vertices[1].y=750;
            figNew->vertices[2].x=90;
            figNew->vertices[2].y=750;
            figNew->vertices[3].x=90;
            figNew->vertices[3].y=720;
            figNew->vertices[4].x=90;
            figNew->vertices[4].y=690;
            figNew->vertices[5].x=60;
            figNew->vertices[5].y=690;
            figNew->vertices[6].x=30;
            figNew->vertices[6].y=690;
            figNew->vertices[7].x=30;
            figNew->vertices[7].y=720;
            figNew->vertices[8].x=30;
            figNew->vertices[8].y=750;
            figNew->vertices[9].x=30;
            figNew->vertices[9].y=750;
            
            //Puntos medios de los 4 cuadrados
            figNew->vertices[10].x=45;
            figNew->vertices[10].y=735;
            figNew->vertices[11].x=75;
            figNew->vertices[11].y=735;
            figNew->vertices[12].x=75;
            figNew->vertices[12].y=705;
            figNew->vertices[13].x=45;
            figNew->vertices[13].y=705;
            break;
        case 1: //Rectángulo 1x4
            k=30;
            for(i=0;i<5;i++)
            {
                figNew->vertices[i].x=k;
                figNew->vertices[i].y=750;
                k+=30;
            }
            k=150;
            for(i=5;i<10;i++)
            {
                figNew->vertices[i].x=k;
                figNew->vertices[i].y=720;
                k-=30;
            }
            //Puntos medios de los 4 cuadrados
            figNew->vertices[10].x=45;
            figNew->vertices[10].y=735;
            figNew->vertices[11].x=75;
            figNew->vertices[11].y=735;
            figNew->vertices[12].x=105;
            figNew->vertices[12].y=735;
            figNew->vertices[13].x=135;
            figNew->vertices[13].y=735;
            break;
        case 2: //Piramide
            figNew->vertices[0].x=30;
            figNew->vertices[0].y=720;
            figNew->vertices[1].x=60;
            figNew->vertices[1].y=720;
            figNew->vertices[2].x=60;
            figNew->vertices[2].y=750;
            figNew->vertices[3].x=90;
            figNew->vertices[3].y=750;
            figNew->vertices[4].x=90;
            figNew->vertices[4].y=720;
            figNew->vertices[5].x=120;
            figNew->vertices[5].y=720;
            figNew->vertices[6].x=120;
            figNew->vertices[6].y=690;
            figNew->vertices[7].x=90;
            figNew->vertices[7].y=690;
            figNew->vertices[8].x=60;
            figNew->vertices[8].y=690;
            figNew->vertices[9].x=30;
            figNew->vertices[9].y=690;
            
            //Puntos medios de los 4 cuadrados
            figNew->vertices[10].x=45;
            figNew->vertices[10].y=705;
            figNew->vertices[11].x=75;
            figNew->vertices[11].y=735;
            figNew->vertices[12].x=105;
            figNew->vertices[12].y=705;
            figNew->vertices[13].x=75;
            figNew->vertices[13].y=705;
            break;
        case 3: //L
            figNew->vertices[0].x=30;
            figNew->vertices[0].y=720;
            figNew->vertices[1].x=60;
            figNew->vertices[1].y=720;
            figNew->vertices[2].x=90;
            figNew->vertices[2].y=720;
            figNew->vertices[3].x=90;
            figNew->vertices[3].y=750;
            figNew->vertices[4].x=120;
            figNew->vertices[4].y=750;
            figNew->vertices[5].x=120;
            figNew->vertices[5].y=720;
            figNew->vertices[6].x=120;
            figNew->vertices[6].y=690;
            figNew->vertices[7].x=90;
            figNew->vertices[7].y=690;
            figNew->vertices[8].x=60;
            figNew->vertices[8].y=690;
            figNew->vertices[9].x=30;
            figNew->vertices[9].y=690;
            
            //Puntos medios de los 4 cuadrados
            figNew->vertices[10].x=45;
            figNew->vertices[10].y=705;
            figNew->vertices[11].x=75;
            figNew->vertices[11].y=705;
            figNew->vertices[12].x=105;
            figNew->vertices[12].y=705;
            figNew->vertices[13].x=105;
            figNew->vertices[13].y=735;
            break;
        case 4: //z
            figNew->vertices[0].x=30;
            figNew->vertices[0].y=720;
            figNew->vertices[1].x=60;
            figNew->vertices[1].y=720;
            figNew->vertices[2].x=60;
            figNew->vertices[2].y=750;
            figNew->vertices[3].x=90;
            figNew->vertices[3].y=750;
            figNew->vertices[4].x=90;
            figNew->vertices[4].y=720;
            figNew->vertices[5].x=90;
            figNew->vertices[5].y=690;
            figNew->vertices[6].x=60;
            figNew->vertices[6].y=690;
            figNew->vertices[7].x=60;
            figNew->vertices[7].y=660;
            figNew->vertices[8].x=30;
            figNew->vertices[8].y=660;
            figNew->vertices[9].x=30;
            figNew->vertices[9].y=720;
            
            //Puntos medios de los 4 cuadrados
            figNew->vertices[10].x=45;
            figNew->vertices[10].y=675;
            figNew->vertices[11].x=45;
            figNew->vertices[11].y=705;
            figNew->vertices[12].x=75;
            figNew->vertices[12].y=705;
            figNew->vertices[13].x=75;
            figNew->vertices[13].y=735;
            break;
        default:
            break;
    }
}

void Animar(void)
{
    int i;
    if(flagMove)
    {
        if(figNew->vertices[0].y-figNew->Limits[3]>150)
        {
            for(i=0;i<14;i++)
            {
                figNew->vertices[i].y-=30;
            }
            if(Nivel==1)
                slp=300100;
            else if(Nivel==2)
                slp=200010;
            else
                slp=100000;

            usleep(slp);
        }
    }
    glutPostRedisplay();
}

void Traslation(int Tx, int Ty,int x, int y)
{
    int k;
    for(k=0;k<14;k++)
    {
        Punto[0]=figNew->vertices[k].x;
        Punto[1]=figNew->vertices[k].y;
        MatrixTraslation[0][2]=Tx;
        MatrixTraslation[1][2]=Ty;
        
        int Pp[3],i,j;
        for(i=0;i<3;i++)
        {
            Pp[i]=0;
            for(j=0;j<3;j++)
            {
                Pp[i]+=MatrixTraslation[i][j]*Punto[j];
            }
        }
        figNew->vertices[k].x=Pp[0];
        figNew->vertices[k].y=Pp[1];
    }
}

void Rotation(float angle, int x, int y)
{
    int k;
    for(k=0;k<14;k++)
    {
        Punto[0]=figNew->vertices[k].x;
        Punto[1]=figNew->vertices[k].y;
        
        MatrixRotation[0][0]=cos(angle);
        MatrixRotation[0][1]=-sin(angle);
        MatrixRotation[1][0]=sin(angle);
        MatrixRotation[1][1]=cos(angle);
        
        int Pp[3],i,j;
        for(i=0;i<3;i++)
        {
            Pp[i]=0;
            for(j=0;j<3;j++)
            {
                Pp[i]+=MatrixRotation[i][j]*Punto[j];
            }
            
            //Condiciones para evitar perder decimales durante la Rotación
            if(k==12)
            {
                if(Pp[i]<0&&Pp[0]<-43.5 &&Pp[i]>-45.0)
                    Pp[i]=-45;
                else if(Pp[i]>0&&Pp[0]>43.5 &&Pp[i]<45.0)
                    Pp[i]=45;
            }
            if(k==4)
            {
                if(Pp[i]<0&&Pp[i]<-58.5 &&Pp[i]>-60.0)
                    Pp[i]=-60;
                else if(Pp[i]>0&&Pp[i]>58.5 &&Pp[i]<60.0)
                    Pp[i]=60;
            }            if(Pp[i]<0&&Pp[i]<-28.5 &&Pp[i]>-30.0)
                Pp[i]=-30;
            else if(Pp[i]>0&&Pp[i]>28.5 &&Pp[i]<30.0)
                Pp[i]=30;
            
            if(Pp[i]<0&&Pp[i]<-13.5 &&Pp[i]>-15.0)
                Pp[i]=-15;
            else if(Pp[i]>0&&Pp[i]>13.5 &&Pp[i]<15.0)
                Pp[i]=15;
            
        }
        figNew->vertices[k].x=Pp[0];
        figNew->vertices[k].y=Pp[1];
    }
    
    Limits[0]=figNew->Limits[1];
    Limits[1]=figNew->Limits[2];
    Limits[2]=figNew->Limits[3];
    Limits[3]=figNew->Limits[0];
    LImits(figNew, Limits[0], Limits[1], Limits[2], Limits[3]);
}

void SpecialKey(int key, int x, int y)
{
    int i,j,k,ready=1;
    int pivoteX, pivoteY;
    pivoteX=figNew->vertices[0].x;
    pivoteY=figNew->vertices[0].y;
    switch(key)
    {
        case GLUT_KEY_DOWN:
            if(figNew->vertices[0].y-figNew->Limits[3]>150)
            {
                for(i=0;i<14;i++)
                {
                    figNew->vertices[i].y-=30;
                }
            }
            break;
        case GLUT_KEY_LEFT:
            for(j=0;j<4;j++)
            {
                for(k=0;k<4;k++)
                {
                    if(Block[blockI[j]-1][blockJ[j]]  && (blockI[j]-1!=blockI[k]))
                        ready=0;
                }
            }
            if(figNew->vertices[0].x-figNew->Limits[0]-30>=30 && ready)
            {
                for(i=0;i<14;i++)
                {
                    figNew->vertices[i].x-=30;
                }
            }
            break;
        case GLUT_KEY_RIGHT:
            for(j=0;j<4;j++)
            {
                for(k=0;k<4;k++)
                {
                    if(Block[blockI[j]+1][blockJ[j]]  && (blockI[j]+1!=blockI[k]))
                    {
                        ready=0;
                    }
                }
            }
            if(figNew->vertices[0].x+figNew->Limits[2]<330 && ready)
            {
                for(i=0;i<14;i++)
                {
                    figNew->vertices[i].x+=30;
                }
            }
            break;
        case GLUT_KEY_UP:
            
            if(figNew->vertices[0].x-figNew->Limits[1]>29)
            {
                Traslation(-pivoteX, -pivoteY, 0, 0);
                Rotation(M_PI/2, 0, 0);
                Traslation(pivoteX, pivoteY, 0, 0);
            }
            break;
        default:
            break;
    }
}

void Raton(int boton, int estado,int x, int y)
{
    if(boton==GLUT_RIGHT_BUTTON && estado==GLUT_DOWN)
    {
        LiberarMemoria(figArray);
        exit(0);
    }
}

void Background(void)
{
    GiveColor(GRIS);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON); //Tools
    glVertex2f(330, 750);
    glVertex2f(480, 750);
    glVertex2f(480, 150);
    glVertex2f(330, 150);
    glEnd();
    GiveColor(GRIS);
    glBegin(GL_POLYGON);//Play zone
    glVertex2f(30, 750);
    glVertex2f(330, 750);
    glVertex2f(330, 150);
    glVertex2f(30, 150);
    glEnd();
    int i,j,k;
    GiveColor(GRIS1);
    for(i=0;i<10;i++)
    {
        for(j=0;j<20;j++)
        {
            glPolygonMode(GL_FRONT, GL_LINE);
            glBegin(GL_POLYGON);
            glVertex2f(i*30+30, 750-(j*30));
            glVertex2f(i*30+30, 720-(j*30));
            glVertex2f(i*30+60, 720-(j*30));
            glVertex2f(i*30+60, 750-(j*30));
            glEnd();
            glPolygonMode(GL_FRONT, GL_FILL);
            glBegin(GL_POLYGON);
            glVertex2f(i*30+35, 745-(j*30));
            glVertex2f(i*30+35, 725-(j*30));
            glVertex2f(i*30+55, 725-(j*30));
            glVertex2f(i*30+55, 745-(j*30));
            glEnd();
            
            for(k=0;k<4;k++)
            {
                if(blockI[k]==i&&blockJ[k]==j)
                {
                    GiveColor(GRIS2);
                    glPolygonMode(GL_FRONT, GL_LINE);
                    glBegin(GL_POLYGON);
                    glVertex2f(i*30+30, 750-(j*30));
                    glVertex2f(i*30+30, 720-(j*30));
                    glVertex2f(i*30+60, 720-(j*30));
                    glVertex2f(i*30+60, 750-(j*30));
                    glEnd();
                    glPolygonMode(GL_FRONT, GL_FILL);
                    glBegin(GL_POLYGON);
                    glVertex2f(i*30+35, 745-(j*30));
                    glVertex2f(i*30+35, 725-(j*30));
                    glVertex2f(i*30+55, 725-(j*30));
                    glVertex2f(i*30+55, 745-(j*30));
                    glEnd();
                }
                else
                {
                    GiveColor(GRIS1);
                }
            }
            GiveColor(GRIS1);
        }
    }
}

void BussyBlocks(void)
{
    int count,x,y;
    for(count=10;count<14;count++)
    {
        x= figNew->vertices[count].x;
        y= figNew->vertices[count].y;
        if(x>30 && x<330 && (y)>150 && (y)<750)//Asignación de color
        {
            blockI[count-10]= (x-30)/30;
            blockJ[count-10]=(750-y)/30;
        }
    }
}

void Repintado(void)
{
    int i,j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<20;j++)
        {
            if(Block[i][j]==1)
            {
                GiveColor(AZUL_MARINO);
                glPolygonMode(GL_FRONT, GL_LINE);
                glBegin(GL_POLYGON);
                glVertex2f(i*30+30, 750-(j*30));
                glVertex2f(i*30+30, 720-(j*30));
                glVertex2f(i*30+60, 720-(j*30));
                glVertex2f(i*30+60, 750-(j*30));
                glEnd();
                glPolygonMode(GL_FRONT, GL_FILL);
                glBegin(GL_POLYGON);
                glVertex2f(i*30+35, 745-(j*30));
                glVertex2f(i*30+35, 725-(j*30));
                glVertex2f(i*30+55, 725-(j*30));
                glVertex2f(i*30+55, 745-(j*30));
                glEnd();
            }
        }
    }
}

int Encajar(void)
{
    int flag=0,i,j;
    if(figNew->vertices[0].y-figNew->Limits[3]==150) //Si llega el borde infrior
        flag=1;
    else
    { //Si topa con un Bloque ya ocupado y si este bloque no forma parte de la figura actual
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                if(Block[blockI[i]][blockJ[i]+1] && (blockJ[i]+1!=blockJ[j]))
                    flag=1;
            }
        }    }
    return flag;
}

void EliminarRenglon(void)
{
    int i,j, count[20],k=0;
    
    for(i=0;i<20;i++)
    {
        count[i]=0;
        for(j=0;j<10;j++)
        {
            if(Block[j][i]==1)
            {
                count[i]++;
            }
        }
        if(count[i]==10)
        {
            Puntaje+=20;
            k=i;
            break;
        }
    }
    for(i=k;i>0;i--)
    {
        for(j=0;j<10;j++)
        {
            Block[j][i]=Block[j][i-1];
        }
    }
}

void GiveColor(COLOR27 color)
{
    glColor3f(PaletaColor27[color][0], PaletaColor27[color][1], PaletaColor27[color][2]);
}

void DibujaTexto(char *Text, float x, float y)
{
    char *c;
    glRasterPos2f(x, y);
    
    for(c=Text;*c!='\0';c++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
}
