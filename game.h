#ifndef GAME_H_INCLUDED
#define GAME_H_+INCLUDED
#include "levelmap.h"
#include "item.h"
#include "MYSQL.h"





typedef struct game{

    perso player1;
    perso player2;
    levelmap map;
    int debutManche;
    int numManche;
    Text numMancheAffich;
    int timeBoost;
    int nbrItem;
    item unItem;
    int numMatch;

    void Init(int nbrMatchAffile,Text pseudoJoueur1,Text pseudoJoueur2)
    {
        player1.Init(1,pseudoJoueur1);
        player2.Init(2,pseudoJoueur2);

        char txt[200];
        sprintf(txt,"SELECT MAX(NO_MATCH) FROM jeu");
        numMatch = MySQLRequest("127.0.0.1","root","","rush",txt);
        numMatch++;

        if(nbrMatchAffile==1)
        {
            map.createMap();
            map.InitMap();
        }

        debutManche=Time();
        numManche = player1.score+player2.score+1;
        numMancheAffich = CreateText("Manche 1",CreateColor(255,255,255),40);
        TextSetPosition(numMancheAffich,CreateVec2(700,700));

        unItem.NewItem();
        nbrItem=1;
        timeBoost=Time();
    }
    void Actu()
    {
        map.DrawMap();
        player1.Actu(player2.imgPerso,map.imgmap);
        player2.Actu(player1.imgPerso,map.imgmap);
        player1.DrawPerso();
        player2.DrawPerso();
        DrawText(numMancheAffich);

        if(Time()-timeBoost>15000)
        {
            if(player1.vitesseLigne>player2.vitesseLigne) player1.DeboostVitesse();
            if(player2.vitesseLigne>player1.vitesseLigne) player2.DeboostVitesse();
            unItem.NewItem();
            nbrItem=1;
            timeBoost=Time();
        }

        if(nbrItem==1)
        {
            unItem.Draw();
        }

        if(nbrItem==1 && ImgGetCollisionLite(player1.imgPerso,unItem.boosto))
        {
            player1.BoostVitesse();
            unItem.DestroyItem();
            nbrItem=0;
            timeBoost=Time();
        }

        if(nbrItem==1 && ImgGetCollisionLite(player2.imgPerso,unItem.boosto))
        {
            player2.BoostVitesse();
            unItem.DestroyItem();
            nbrItem=0;
            timeBoost=Time();
        }



        if (ImgGetCollision(player1.imgPerso,player2.imgBalle))
        {

            player2.score+=1;

            if(player1.vitesseLigne>player2.vitesseLigne) player1.DeboostVitesse();
            if(player2.vitesseLigne>player1.vitesseLigne) player2.DeboostVitesse();
            unItem.NewItem();
            nbrItem=1;

            player1.vitesseBalle=CreateVec2(0.0,0.0);
            player2.vitesseBalle=CreateVec2(0.0,0.0);

            switch(player1.configPlayer)
            {
                case 1 :
                    ImgSetPosition(player1.imgPerso,CreateVec2(40,40));
                    break;
                case 2 :
                    ImgSetPosition(player1.imgPerso,CreateVec2(1430,740));
                    break;
            }
            switch(player2.configPlayer)
            {
                case 1 :
                    ImgSetPosition(player2.imgPerso,CreateVec2(40,40));
                    break;
                case 2 :
                    ImgSetPosition(player2.imgPerso,CreateVec2(1430,740));
                    break;
            }

            ImgSetPosition(player1.imgBalle,ImgGetPosition(player1.imgPerso));
            ImgSetPosition(player2.imgBalle,ImgGetPosition(player2.imgPerso));

            char J1[50];
            char J2[50];
            sprintf(J1,"%s",TextGetText(player1.pseudo));
            sprintf(J2,"%s",TextGetText(player2.pseudo));
            char txt[200];
            int tempsManche = (Time()-debutManche)/100;
            sprintf(txt,"INSERT INTO jeu (NO_MATCH,NO_MANCHE,JOUEUR1,JOUEUR2,TEMPS_MANCHE,WINNER) VALUE (0,%d,%s,%s,%d;%s)",numManche,J1,J2,tempsManche,J2);
            int resultatRequete = MySQLRequest("127.0.0.1","root","","rush",txt);

            numManche=player1.score+player2.score+1;
            TextSetText(numMancheAffich,"Manche %d",numManche);
            debutManche=Time();
        }

        if (ImgGetCollision(player2.imgPerso,player1.imgBalle))
        {
            player1.score+=1;

            if(player1.vitesseLigne>player2.vitesseLigne) player1.DeboostVitesse();
            if(player2.vitesseLigne>player1.vitesseLigne) player2.DeboostVitesse();
            unItem.NewItem();
            nbrItem=1;

            player1.vitesseBalle=CreateVec2(0.0,0.0);
            player2.vitesseBalle=CreateVec2(0.0,0.0);

            switch(player1.configPlayer)
            {
                case 1 :
                    ImgSetPosition(player1.imgPerso,CreateVec2(40,40));
                    break;
                case 2 :
                    ImgSetPosition(player1.imgPerso,CreateVec2(1430,740));
                    break;
            }
            switch(player2.configPlayer)
            {
                case 1 :
                    ImgSetPosition(player2.imgPerso,CreateVec2(40,40));
                    break;
                case 2 :
                    ImgSetPosition(player2.imgPerso,CreateVec2(1430,740));
                    break;
            }
            ImgSetPosition(player1.imgBalle,ImgGetPosition(player1.imgPerso));
            ImgSetPosition(player2.imgBalle,ImgGetPosition(player2.imgPerso));

            char J1[50];
            char J2[50];
            sprintf(J1,"%s",TextGetText(player1.pseudo));
            sprintf(J2,"%s",TextGetText(player2.pseudo));
            char txt[200];
            int tempsManche = (Time()-debutManche)/100;
            sprintf(txt,"INSERT INTO jeu (NO_MATCH,NO_MANCHE,JOUEUR1,JOUEUR2,TEMPS_MANCHE,WINNER) VALUE (0,%d,%s,%s,%d;%s)",numManche,J1,J2,tempsManche,J1);
            int resultatRequete = MySQLRequest("127.0.0.1","root","","rush",txt);

            numManche=player1.score+player2.score+1;
            TextSetText(numMancheAffich,"Manche %d",numManche);
            debutManche=Time();
        }
    }

}game;

#endif // GAME_H_INCLUDED
