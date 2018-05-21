//
//  Figuras.c
//  Tetris
//
//  Created by Sandra Bravo Marmolejo on 28/11/17.
//  Copyright © 2017 Sandra Bravo Marmolejo. All rights reserved.
//

#include "Figuras.h"

FIGURA* CrearFigura(void)
{
    FIGURA * fig;
    fig= (FIGURA*)malloc(sizeof(FIGURA));
    if (fig == NULL){
        printf("\n No hay memoria ");
        return 0;
    }
    return fig;
}

FIGURA *IngresaFigura(FIGURA *figArray, FIGURA *newF)
{
    FIGURA *fig2;
    if(figArray==NULL)
    {
        figArray=newF;
    }
    else
    {
        fig2=figArray;
        while (fig2->next!=NULL) {
            fig2=fig2->next;
        }
        fig2->next=newF;
    }
    newF->next=NULL;
    return figArray;
}

void DatosFigura(FIGURA *newF, int indexType)
{
    newF->indexType=indexType;
    
    switch (newF->indexType) {
        case 0: //Cuadrado 2x2
            newF->Limits[0]=0;
            newF->Limits[1]=0;
            newF->Limits[2]=60;
            newF->Limits[3]=60;
            break;
        case 1: //Rectangulo 1x4
            newF->Limits[0]=0;
            newF->Limits[1]=0;
            newF->Limits[2]=120;
            newF->Limits[3]=30;
            break;
        case 2: //Piramide
            newF->Limits[0]=0;
            newF->Limits[1]=30;
            newF->Limits[2]=90;
            newF->Limits[3]=30;
            break;
        case 3: //L
            newF->Limits[0]=0;
            newF->Limits[1]=30;
            newF->Limits[2]=90;
            newF->Limits[3]=30;
            break;
        case 4: //Z
            newF->Limits[0]=0;
            newF->Limits[1]=30;
            newF->Limits[2]=60;
            newF->Limits[3]=60;
            break;
        default:
            break;
    }
    
}

void DrawFig(FIGURA *fig)
{
    int i;
    glLineWidth(3);
    switch (fig->indexType) {
        case 0: //Cuadrado 2x2
            GiveColor(AZUL_CYAN);
            glBegin(GL_LINE_LOOP);
            for(i=0;i<10;i++)
            {
                if(i==0)
                    GiveColor(AMARILLO);
                else
                    GiveColor(AZUL_CYAN);
                glVertex2f(fig->vertices[i].x, fig->vertices[i].y);
            }
            glEnd();
            
            glBegin(GL_LINE_STRIP);
            for(i=10;i<14;i++)
            {
                GiveColor(AMARILLO);
                glVertex2f(fig->vertices[i].x, fig->vertices[i].y);
            }
            glEnd();
            break;
        case 1: //Rectángulo 1x4
            GiveColor(ROSA);
            glBegin(GL_LINE_LOOP);
            for(i=0;i<10;i++)
            {
                if(i==0)
                    GiveColor(VERDE_PASTO);
                else
                    GiveColor(ROSA);
                glVertex2f(fig->vertices[i].x, fig->vertices[i].y);
            }
            glEnd();
            
            glBegin(GL_LINE_STRIP);
            for(i=10;i<14;i++)
            {
                GiveColor(VERDE_PASTO);
                glVertex2f(fig->vertices[i].x, fig->vertices[i].y);
            }
            glEnd();
            break;
        case 2: //Piramide
            GiveColor(NARANJA);
            glBegin(GL_LINE_LOOP);
            for(i=0;i<10;i++)
            {
                if(i==0)
                    GiveColor(MORADO_FUERTE);
                else
                    GiveColor(NARANJA);
                glVertex2f(fig->vertices[i].x, fig->vertices[i].y);
            }
            glEnd();
            
            glBegin(GL_LINE_STRIP);
            for(i=10;i<14;i++)
            {
                GiveColor(MORADO_FUERTE);
                glVertex2f(fig->vertices[i].x, fig->vertices[i].y);
            }
            glEnd();
            break;
        case 3: //L
            GiveColor(MORADO);
            glBegin(GL_LINE_LOOP);
            for(i=0;i<10;i++)
            {
                if(i==0)
                    GiveColor(AMARILLO_OPACO);
                else
                    GiveColor(MORADO);
                glVertex2f(fig->vertices[i].x, fig->vertices[i].y);
            }
            glEnd();
            
            glBegin(GL_LINE_STRIP);
            for(i=10;i<14;i++)
            {
                GiveColor(AMARILLO_OPACO);
                glVertex2f(fig->vertices[i].x, fig->vertices[i].y);
            }
            glEnd();
            break;
        case 4: //z
            GiveColor(ROJO);
            glBegin(GL_LINE_LOOP);
            for(i=0;i<10;i++)
            {
                if(i==0)
                    GiveColor(BLANCO);
                else
                    GiveColor(ROJO);
                glVertex2f(fig->vertices[i].x, fig->vertices[i].y);
            }
            glEnd();
            
            glBegin(GL_LINE_STRIP);
            for(i=10;i<14;i++)
            {
                GiveColor(BLANCO);
                glVertex2f(fig->vertices[i].x, fig->vertices[i].y);
            }
            glEnd();
            break;
        default:
            break;
    }
    glLineWidth(1);
}

void LiberarMemoria(FIGURA *figArray)
{
    FIGURA *fig2;
    while (figArray!=NULL) {
        fig2=figArray;
        figArray=figArray->next;
        free(fig2);
    }
}

void LImits( FIGURA *fig,int xmin, int ymin, int xmax, int ymax)
{
    fig->Limits[0]=xmin;
    fig->Limits[1]=ymin;
    fig->Limits[2]=xmax;
    fig->Limits[3]=ymax;
}
