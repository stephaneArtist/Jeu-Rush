typedef struct item{
    Image boosto;

    void NewItem()
    {
        boosto = CreateImage("data/boosto.png");
        int posX,posY;
        posX=rand()%1472-32;
        posY=Time()%768-32;
        ImgSetPosition(boosto,CreateVec2(posX,posY));
    }

    void Draw()
    {
        DrawImage(boosto);
    }

    void DestroyItem()
    {
        FreeImage(boosto);
    }
}item;
