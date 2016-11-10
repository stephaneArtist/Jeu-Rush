#include "graphic.h"

#define teleportation 200.0
#define LaVitesseLigne 5.0
#define laVitesseDiagonale 3.0
#define zoom 0.66
#define zoomProgress 1.1
#define tempsTP 2500
#define vitesseBalleLigne 20.0
#define vitesseBalleDiagonale 10.0
#define posXDepartJoueur1 40
#define posYDepartJoueur1 40
#define posXDepartJoueur2 1430
#define posYDepartJoueur2 740

typedef struct perso{
    Image imgPerso;
    Image barreCdTp100;
    Image barreCdTp90;
    Image barreCdTp80;
    Image barreCdTp70;
    Image barreCdTp60;
    Image barreCdTp50;
    Image barreCdTp40;
    Image barreCdTp30;
    Image barreCdTp20;
    Image barreCdTp10;
    Image barreCdTp0;
    Image imgBalle;

    Vec2 vitesseBalle;
    Vec2 addPos;
    Vec2 posPerso;

    Text txtP1;
    Text scoreAffich;
    Text TextJoueur;
    Text pseudo;

    int cdTP=0;
    int toucheUp;
    int toucheDown;
    int toucheLeft;
    int toucheRight;
    int toucheTp;
    int toucheTirer;
    int score;
    int compteur=0;
    int configPlayer;
    int vitesseLigne;
    int vitesseDiagonale;
    int positionPersoX;
    int positionPersoY;


    void Init(int configJoueur,Text pseudoJoueur)
    {
        barreCdTp100=CreateImage("data/barre100.png"); ImgSetScale(barreCdTp100,zoomProgress);
        barreCdTp70=CreateImage("data/barre75.png"); ImgSetScale(barreCdTp70,zoomProgress);
        barreCdTp50=CreateImage("data/barre46.png"); ImgSetScale(barreCdTp50,zoomProgress);
        barreCdTp0=CreateImage("data/barre0.png"); ImgSetScale(barreCdTp0,zoomProgress);

        configPlayer = configJoueur;

        score=0;

        pseudo=pseudoJoueur;
        TextSetSize(pseudo,30);


        vitesseLigne = LaVitesseLigne;
        vitesseDiagonale = laVitesseDiagonale;

        switch(configJoueur)
        {
            case 1:
            {
                imgPerso = CreateImage("data/v2.png");
                ImgSetScale(imgPerso,zoom);

                imgBalle = CreateImage("data/BALLE/0.png");
                ImgSetScale(imgBalle,0.4);
                vitesseBalle = CreateVec2(0.0,0.0);

                toucheUp=SDLK_w;
                toucheDown=SDLK_s;
                toucheLeft=SDLK_a;
                toucheRight=SDLK_d;
                toucheTp=SDLK_f;
                toucheTirer=SDLK_g;

                ImgSetPosition(imgPerso,CreateVec2(posXDepartJoueur1,posYDepartJoueur1));

                ImgSetPosition(barreCdTp100,10,WindowGetSize().y-ImgGetSize(barreCdTp100).y);
                ImgSetPosition(barreCdTp70,10,WindowGetSize().y-ImgGetSize(barreCdTp70).y);
                ImgSetPosition(barreCdTp50,10,WindowGetSize().y-ImgGetSize(barreCdTp50).y);
                ImgSetPosition(barreCdTp0,10,WindowGetSize().y-ImgGetSize(barreCdTp0).y);

                TextJoueur = CreateText("Joueur 1",CreateColor(0,255,0),30);
                scoreAffich = CreateText("Score : 0",CreateColor(0,255,0),25);

                TextSetPosition(scoreAffich,CreateVec2(10,740-ImgGetSize(barreCdTp100).y));
                TextSetPosition(TextJoueur,CreateVec2(10,765-ImgGetSize(barreCdTp100).y));
                TextSetPosition(pseudo,CreateVec2(10,715-ImgGetSize(barreCdTp100).y));

                TextSetColor(pseudo,CreateColor(0,255,0));


                break;
            }

            case 2:
            {

                imgPerso = CreateImage("data/v3.png");
                ImgSetScale(imgPerso,zoom);

                imgBalle = CreateImage("data/BALLE/1.png");
                ImgSetScale(imgBalle,0.4);
                vitesseBalle = CreateVec2(0.0,0.0);

                toucheUp=SDLK_UP;
                toucheDown=SDLK_DOWN;
                toucheLeft=SDLK_LEFT;
                toucheRight=SDLK_RIGHT;
                toucheTp=SDLK_KP1;
                toucheTirer=SDLK_KP2;
                ImgSetPosition(imgPerso,CreateVec2(posXDepartJoueur2,posYDepartJoueur2));
                ImgSetPosition(barreCdTp100,WindowGetSize().x-ImgGetSize(barreCdTp100).x-10,WindowGetSize().y-ImgGetSize(barreCdTp100).y);
                ImgSetPosition(barreCdTp70,WindowGetSize().x-ImgGetSize(barreCdTp70).x-10,WindowGetSize().y-ImgGetSize(barreCdTp70).y);
                ImgSetPosition(barreCdTp50,WindowGetSize().x-ImgGetSize(barreCdTp50).x-10,WindowGetSize().y-ImgGetSize(barreCdTp50).y);
                ImgSetPosition(barreCdTp0,WindowGetSize().x-ImgGetSize(barreCdTp0).x-10,WindowGetSize().y-ImgGetSize(barreCdTp0).y);

                TextJoueur = CreateText("Joueur 2",CreateColor(255,0,0),30);
                scoreAffich = CreateText("Score : 0",CreateColor(255,0,0),25);

                TextSetPosition(scoreAffich,CreateVec2(1328,740-ImgGetSize(barreCdTp100).y));
                TextSetPosition(TextJoueur,CreateVec2(1328,765-ImgGetSize(barreCdTp100).y));
                TextSetPosition(pseudo,CreateVec2(1328,715-ImgGetSize(barreCdTp100).y));

                TextSetColor(pseudo,CreateColor(255,0,0));


                break;
            }

        }
        ImgSetPosition(imgBalle,ImgGetPosition(imgPerso));
    }



    void Actu(Image imgAdversaire,Image imgMap[46][24])
    {
        Mouvement(imgAdversaire,imgMap);
        Tirer();
    }

    void Tirer()
    {
        if (KeyGet(toucheTirer) && vitesseBalle.x == 0.0 && vitesseBalle.y == 0.0)
        {
            float vuePerso = ImgGetRotation(imgPerso);
            if(vuePerso==0.0)
            {
                vitesseBalle=CreateVec2(0.0,vitesseBalleLigne);
                ImgSetPosition(imgBalle,ImgGetPosition(imgPerso).x+15,ImgGetPosition(imgPerso).y+45);
            }
            if(vuePerso==45.0)
            {
                vitesseBalle=CreateVec2(-vitesseBalleDiagonale,vitesseBalleDiagonale);
                ImgSetPosition(imgBalle,ImgGetPosition(imgPerso).x-3,ImgGetPosition(imgPerso).y+30);
            }
            if(vuePerso==90.0)
            {
                vitesseBalle=CreateVec2(-vitesseBalleLigne,0.0);
                ImgSetPosition(imgBalle,ImgGetPosition(imgPerso).x-5,ImgGetPosition(imgPerso).y+13);
            }
            if(vuePerso==135.0)
            {
                vitesseBalle=CreateVec2(-vitesseBalleDiagonale,-vitesseBalleDiagonale);
                ImgSetPosition(imgBalle,ImgGetPosition(imgPerso).x+10,ImgGetPosition(imgPerso).y+5);
            }
            if(vuePerso==180.0)
            {
                vitesseBalle=CreateVec2(0.0,-vitesseBalleLigne);
                ImgSetPosition(imgBalle,ImgGetPosition(imgPerso).x+15,ImgGetPosition(imgPerso).y-5);
            }
            if(vuePerso==225.0)
            {
                vitesseBalle=CreateVec2(vitesseBalleDiagonale,-vitesseBalleDiagonale);
                ImgSetPosition(imgBalle,ImgGetPosition(imgPerso).x+25,ImgGetPosition(imgPerso).y+5);
            }
            if(vuePerso==270.0)
            {
                vitesseBalle=CreateVec2(vitesseBalleLigne,0);
                ImgSetPosition(imgBalle,ImgGetPosition(imgPerso).x+47,ImgGetPosition(imgPerso).y+12);
            }
            if(vuePerso==315.0)
            {
                vitesseBalle=CreateVec2(vitesseBalleDiagonale,vitesseBalleDiagonale);
                ImgSetPosition(imgBalle,ImgGetPosition(imgPerso).x+32,ImgGetPosition(imgPerso).y+35);
            }
        }
        if (vitesseBalle.x !=0.0 || vitesseBalle.y != 0.0)
        {
            ImgSetPosition(imgBalle,ImgGetPosition(imgBalle)+vitesseBalle);
            DrawImage(imgBalle);
        }
        if (ImgGetPosition(imgBalle).x > WindowGetSize().x || ImgGetPosition(imgBalle).y > WindowGetSize().y ||
            ImgGetPosition(imgBalle).x < 0 || ImgGetPosition(imgBalle).y < 0 )
        {
            vitesseBalle=CreateVec2(0.0,0.0);
            ImgSetPosition(imgBalle,ImgGetPosition(imgPerso));
        }
    }

    void DrawPerso()
    {
        TextSetText(scoreAffich,"Score : %d",score);

        DrawImage(imgPerso);
        DrawText(scoreAffich);
        DrawText(TextJoueur);
        DrawText(pseudo);

        if(Time()-cdTP>tempsTP)
            DrawImage(barreCdTp100);
        else
            if(Time()-cdTP>tempsTP*0.7)
                DrawImage(barreCdTp70);
        else
            if(Time()-cdTP>tempsTP*0.5)
                DrawImage(barreCdTp50);
        else
            if(Time()-cdTP>tempsTP*0)
                DrawImage(barreCdTp0);
    }

    void Mouvement(Image imgAdversaire,Image imgMap[46][24])
    {
        Vec2 addPos = CreateVec2(0.0,0.0);
        if(configPlayer==3)
        {
            if (fabs(StickGetAxis(0, 0))>=0.2)
            addPos.x += vitesseLigne*StickGetAxis(0, 0);
            if (fabs(StickGetAxis(0, 1))>=0.2)
            addPos.y -= vitesseLigne*StickGetAxis(0, 1);
        }
        else
        {
            if(KeyGet(toucheUp) && KeyGet(toucheRight))
            {
                ImgSetRotation(imgPerso,315.0);
                if (KeyGet(toucheTp) && Time()-cdTP>tempsTP)
                {
                    addPos.x += teleportation;
                    addPos.y += teleportation;
                    cdTP=Time();
                }
                else
                {
                    addPos.x += vitesseDiagonale;
                    addPos.y += vitesseDiagonale;
                }
            }
            else
            {
                if(KeyGet(toucheUp) && KeyGet(toucheLeft))
                {
                    ImgSetRotation(imgPerso,45.0);
                    if (KeyGet(toucheTp)&& Time()-cdTP>tempsTP)
                    {
                        addPos.x -= teleportation;
                        addPos.y += teleportation;
                        cdTP=Time();
                    }
                    else
                    {
                        addPos.x -= vitesseDiagonale;
                        addPos.y += vitesseDiagonale;
                    }
                }
                else
                {
                    if(KeyGet(toucheDown) && KeyGet(toucheRight))
                    {
                        ImgSetRotation(imgPerso,225.0);
                        if (KeyGet(toucheTp)&& Time()-cdTP>tempsTP)
                        {
                            addPos.x += teleportation;
                            addPos.y -= teleportation;
                            cdTP=Time();
                        }
                        else
                        {
                            addPos.x += vitesseDiagonale;
                            addPos.y -= vitesseDiagonale;
                        }
                    }
                    else
                    {
                        if(KeyGet(toucheDown) && KeyGet(toucheLeft))
                        {
                            ImgSetRotation(imgPerso,135.0);
                            if (KeyGet(toucheTp)&& Time()-cdTP>tempsTP)
                            {
                                addPos.x -= teleportation;
                                addPos.y -= teleportation;
                                cdTP=Time();
                            }
                            else
                            {
                                addPos.y -= vitesseDiagonale;
                                addPos.x -= vitesseDiagonale;
                            }
                        }
                        else
                        {
                            if (KeyGet(toucheUp))
                            {
                                ImgSetRotation(imgPerso,0);
                                if (KeyGet(toucheTp)&& Time()-cdTP>tempsTP)
                                {
                                    addPos.y += teleportation;
                                    cdTP=Time();
                                }
                                else
                                {
                                    addPos.y += vitesseLigne;
                                }
                            }
                            if (KeyGet(toucheDown))
                            {
                                ImgSetRotation(imgPerso,180.0);
                                if (KeyGet(toucheTp)&& Time()-cdTP>tempsTP)
                                {
                                    addPos.y -= teleportation;
                                    cdTP=Time();
                                }
                                else
                                {
                                    addPos.y -= vitesseLigne;
                                }
                            }
                            if (KeyGet(toucheLeft))
                            {
                                ImgSetRotation(imgPerso,90);
                                if (KeyGet(toucheTp) && Time()-cdTP>tempsTP)
                                {
                                    addPos.x -= teleportation;
                                    cdTP=Time();
                                }
                                else
                                {
                                    addPos.x -= vitesseLigne;
                                }
                            }
                            if (KeyGet(toucheRight))
                            {
                                ImgSetRotation(imgPerso,270);
                                if (KeyGet(toucheTp) && Time()-cdTP>tempsTP)
                                {
                                    addPos.x += teleportation;
                                    cdTP=Time();
                                }
                                else
                                {
                                    addPos.x += vitesseLigne;
                                }
                            }
                        }
                    }
                }
            }
        }

        ImgSetPosition(imgPerso,ImgGetPosition(imgPerso)+addPos);

        if(ImgGetCollision(imgPerso,imgAdversaire))
        {
            ImgSetPosition(imgPerso,ImgGetPosition(imgPerso)-addPos);
        }
        if ((ImgGetPosition(imgPerso).x + ImgGetSize(imgPerso).x) > WindowGetSize().x )
        {
            ImgSetPosition(imgPerso,WindowGetSize().x - ImgGetSize(imgPerso).x,ImgGetPosition(imgPerso).y);
        }
        if ((ImgGetPosition(imgPerso).y + ImgGetSize(imgPerso).y) > WindowGetSize().y)
        {
            ImgSetPosition(imgPerso,ImgGetPosition(imgPerso).x,WindowGetSize().y - ImgGetSize(imgPerso).y );
        }
        if (ImgGetPosition(imgPerso).x < 0)
        {
            ImgSetPosition(imgPerso,0,ImgGetPosition(imgPerso).y);
        }
        if (ImgGetPosition(imgPerso).y < 0)
        {
            ImgSetPosition(imgPerso,ImgGetPosition(imgPerso).x,0);
        }

        posPerso = ImgGetPosition(imgPerso);
        positionPersoX = (int)posPerso.x/32;
        positionPersoY = (int)posPerso.y/32;

        if (ImgGetCollision(imgMap[positionPersoX+2][positionPersoY+1],imgPerso))
        {
            ImgSetPosition(imgPerso,ImgGetPosition(imgPerso)-addPos);
        }

    }

    void BoostVitesse()
    {
        vitesseLigne=vitesseLigne*2;
        vitesseDiagonale=vitesseDiagonale*2;
    }

    void DeboostVitesse()
    {
        vitesseLigne=vitesseLigne/2;
        vitesseDiagonale=vitesseDiagonale/2;
    }

}perso;
