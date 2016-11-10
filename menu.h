
//Define

#define posXPseudo 520
#define posYPseudo 334

#define posXTextJouer 280
#define posYTextJouer 50
#define posXTextCommande 620
#define posYTextCommande 50
#define posXTextQuitter 1050
#define posYTextQuitter 50

#define posXTextConfig 450
#define posYTextConfig 650
#define posXTextClicConfig 480
#define posYTextClicConfig 550
#define posXImageZQSD 300
#define posYImageZQSD 300
#define posXImageFleche 700
#define posYImageFleche 300

#define couleurTexte 255,255,255


typedef struct menu{
    int etat,matchAffile,configPlayer1,configPlayer2,numJoueur,choix,choixMax;
    Text nomJoueur1,nomJoueur2,nomWinner,clicConfig,textJouer,textQuitter,textCommande;
    Image bg,config,winner;
    game jeu;
    char texte[50];
    Color grey,white,blue;


    void Init()
    {
        matchAffile=1;
        Reinitialiser();
    }

    void Reinitialiser()
    {
        numJoueur=1;

        grey = CreateColor(96,96,96);
        white = CreateColor(255,255,255);
        blue = CreateColor(0,100,200);
        nomJoueur1 = CreateText("Pseudo Joueur 1",white,60);
        TextSetPosition(nomJoueur1,CreateVec2(posXPseudo,posYPseudo));
        TextSetAlterable(nomJoueur1,true);

        nomJoueur2 = CreateText("Pseudo Joueur 2",white,60);
        TextSetPosition(nomJoueur2,CreateVec2(posXPseudo,posYPseudo));
        TextSetAlterable(nomJoueur2,true);

        bg = CreateImage("data/xMyBg.png");

        config=CreateImage("data/Config.png");

        winner=CreateImage("data/Winner.png");

        textJouer = CreateText("Jouer",white,40);
        TextSetPosition(textJouer,CreateVec2(posXTextJouer,posYTextJouer));

        textCommande = CreateText("Commande",grey,40);
        TextSetPosition(textCommande,CreateVec2(posXTextCommande ,posYTextCommande));

        textQuitter = CreateText("Quitter",grey,40);
        TextSetPosition(textQuitter,CreateVec2(posXTextQuitter,posYTextQuitter));



        choix = 1;
        choixMax = 3;

        etat = 1;
    }

    void Draw()
    {
        switch (etat)
        {
                case 1:
                DrawImage(bg);
                DrawText(textJouer);
                DrawText(textCommande);
                DrawText(textQuitter);

                if (KeyGetOneShot(SDLK_RIGHT)){
                    choix ++;
                }
                if (KeyGetOneShot(SDLK_LEFT)){
                    choix --;
                }
                if(choix < 1){
                    choix = choixMax;
                }
                if(choix > choixMax){
                    choix = 1;
                }

                switch(choix){
                    case 1 :
                        TextSetColor(textJouer,white);
                        TextSetColor(textCommande,grey);
                        TextSetColor(textQuitter,grey);
                        if(KeyGetOneShot(SDLK_RETURN))
                        {
                            etat=2;
                        }
                    break;
                    case 2 :
                        TextSetColor(textJouer,grey);
                        TextSetColor(textCommande,white);
                        TextSetColor(textQuitter,grey);
                        if(KeyGetOneShot(SDLK_RETURN))
                        {
                            etat=6;
                        }
                    break;
                    case 3 :
                        TextSetColor(textJouer,grey);
                        TextSetColor(textCommande,grey);
                        TextSetColor(textQuitter,white);
                        if (KeyGet(SDLK_RETURN))
                        {
                            exit(1);
                        }

                    break;
                }
                break;

            case 2:
                DrawText(nomJoueur1);
                TextSetFocus(nomJoueur1);
                if(KeyGetOneShot(SDLK_RETURN))
                {
                    etat=3;
                }
                break;

            case 3:
                DrawText(nomJoueur2);
                TextSetFocus(nomJoueur2);
                if(KeyGetOneShot(SDLK_RETURN))
                {
                    jeu.Init(matchAffile,nomJoueur1,nomJoueur2);
                    etat=4;
                    TextShootFocus();
                }

                break;

            case 4: //Jeu
                if (jeu.player1.score<5 && jeu.player2.score<5)
                {
                    jeu.Actu();
                }
                else
                {
                    if(jeu.player1.score==5)nomWinner=nomJoueur1;
                    if(jeu.player2.score==5)nomWinner=nomJoueur2;
                    TextSetColor(nomWinner,blue);
                    TextSetAlterable(nomWinner,false);
                    TextSetPosition(nomWinner,CreateVec2(posXPseudo,posYPseudo));
                    TextSetSize(nomWinner,60);
                    etat=5;
                }
                break;

            case 5:
                DrawImage(winner);
                DrawText(nomWinner);
                if(KeyGetOneShot(SDLK_RETURN))
                {
                    Reinitialiser();
                    matchAffile ++;
                }
                break;

            case 6:
                DrawImage(config);
                if(KeyGetOneShot(SDLK_RETURN))
                {
                    etat=1;
                }
                break;


        }

    }

}menu;
