#include <stdlib.h>
#include <stdio.h>
#include "graphic.h"
#include "personnage.h"



typedef struct levelmap{


    int levelmap[46][24]; // Initiallisation d'un tableau de valeur : x = 46 et y = 24
    Image imgmap[46][24]; // Initiallisation d'un tableau d'image de valeur : x = 46 et y = 24

    void createMap(){

    for (int i=0 ;i<46;i++) // Création d'un tableau avec deux boucles respectant les dimensions
    {
        for ( int j=0;j<24;j++)
        {
            levelmap[i][j]=0; // Initiallisation des cases à 0
        }
    }

    FILE* fichier = NULL;
    fichier = fopen("data/levelmap.txt","r"); // Lecture du fichier levelmap.txt
        if ( fichier != NULL )
        {
            for (int j=0 ;j<=24;j++)
            {
                for (int i=0;i<46;i++)
                {
                    fscanf(fichier,"%d",&levelmap[i][j]); // Attribution des valeurs du txt dans le tableau
                }
            }
        }
    }
    void CMapJ(Image imgPerso);
    void InitMap(){

        for(int i = 0 ; i < 46 ; i++){
            for(int j = 0 ; j <=24 ; j++){

                // disposition de l'image x , y
               /* switch(levelmap[i][j])
                {
                case 0:
                    imgmap[i][j]=CreateImage("data/chemin.png");
                    ImgSetPosition(imgmap[i][j],CreateVec2(i*32,j*32));
                    break;
                case 1:
                    imgmap[i][j]=CreateImage("data/mur.png");
                    ImgSetPosition(imgmap[i][j],CreateVec2(i*32,j*32));
                    break;
                case 2:
                    imgmap[i][j]=CreateImage("data/mur2.png");
                    ImgSetPosition(imgmap[i][j],CreateVec2(i*32,j*32));
                    break;
                case 3:
                    imgmap[i][j]=CreateImage("data/mur3.png");
                    ImgSetPosition(imgmap[i][j],CreateVec2(i*32,j*32));
                break;
                case 4:
                    imgmap[i][j]=CreateImage("data/mur4.png");
                    ImgSetPosition(imgmap[i][j],CreateVec2(i*32,j*32));
                    break;

                }*/


                imgmap[i][j]=CreateImage("data/wall5.jpg"); // Création d'image dans le tableau d'image
                if(levelmap[i][j] == 1 )
                {
                    ImgSetPosition(imgmap[i][j],CreateVec2(i*32,j*32)); // Taille de l'image
                }
                else
                {
                    ImgSetPosition(imgmap[i][j],CreateVec2(0.0,0.0));
                }
            }
        }

    }

    void DrawMap()
    {
        Image fond = CreateImage("data/background3.jpg");
        DrawImage(fond);
        for(int i = 0 ; i < 46 ; i++){
            for(int j = 0 ; j < 24 ; j++){
                if(levelmap[i][j] == 1 )
                {
                    DrawImage(imgmap[i][j]); // On remplit le tableau d'image avec le DrawImage
                }
            }
        }
    }

}levelmap;

