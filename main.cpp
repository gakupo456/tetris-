#include<SFML/Graphics.hpp>
#include<ctime>

const int gridLength = 20;
const int gridWidth = 10;

int grid[gridLength][gridWidth] = {0};

struct Point {
    int x,y;
    } a[4], b[4];

int tetraminos[7][4] = {

    1,3,5,7, // makes the I
    2,4,5,7, // makes the Z
    3,5,4,6, // makes the S
    3,5,4,7, // makes the T
    2,3,5,7, // makes the L
    3,5,7,6, // makes the J
    2,3,4,5, // makes the O

};

bool checkGrid() {
    for (int i = 0; i < 4; i++)
      if ( a[i].x < 0 || a[i].x >= gridWidth || a[i].y >= gridLength)
        return 0;
      else if (grid[a[i].y] [a[i].x])
      return 0;
   return 1;
};

int main () {

    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris++");

    sf::Texture tileT, backgroundT, frameT;

    tileT.loadFromFile("images/tiles1.png");
    backgroundT.loadFromFile("images/backgroud.png");
    frameT.loadFromFile("images/frame.png");

    sf::Sprite s(tileT), background(backgroundT), frame(frameT);

    int direction = 0;
    int colorNum = 1;
    bool rotate = 0;
    float timer = 0, delay = 0.9;

    sf::Clock clock;

    while ( window.isOpen() ) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::KeyPressed)
              if (e.key.code==sf::Keyboard::Up) rotate=true;
              else if (e.key.code==sf::Keyboard::Space) rotate = 1;
              else if (e.key.code==sf::Keyboard::Left) direction=-1;
              else if (e.key.code==sf::Keyboard::Right) direction=1;
              else if (e.key.code==sf::Keyboard::Escape) window.close();
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.03;

     //moving
    for (int i=0;i<4;i++)  { b[i]=a[i]; a[i].x+=direction; }
    if (!checkGrid()) for (int i=0;i<4;i++) a[i]=b[i];

    //rotation handle
    if (rotate)
      {
        Point p = a[1]; //center of rotation
        for (int i=0;i<4;i++)
          {
            int x = a[i].y-p.y;
            int y = a[i].x-p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
           }
           if (!checkGrid()) for (int i=0;i<4;i++) a[i]=b[i];
      }

    //tick
    if (timer>delay)
      {
        for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }

        if (!checkGrid())
        {
         for (int i=0;i<4;i++) grid[b[i].y][b[i].x]=colorNum;

         colorNum=1+rand()%7;
         int n=rand()%7;
         for (int i=0;i<4;i++)
           {
            a[i].x = tetraminos[n][i] % 2;
            a[i].y = tetraminos[n][i] / 2;
           }
        }

         timer=0;
      }

    //checkin lines
    int k = gridLength - 1;
    for (int i = gridLength - 1; i > 0; i--)
    {
        int count=0;
        for (int j = 0; j < gridWidth; j++)
        {
            if (grid[i][j])
                count++;
            grid[k][j] = grid[i][j];
        }
        if (count<gridWidth) k--;
    }

    direction=0; rotate=0; delay=0.3;

    ///drawing
    window.clear(sf::Color::White);
    window.draw(background);

    for (int i=0;i<gridLength;i++)
     for (int j=0;j<gridWidth;j++)
       {
         if (grid[i][j]==0) continue;
         s.setTextureRect(sf::IntRect(grid[i][j]*18,0,18,18));
         s.setPosition(j*18,i*18);
         s.move(28,31); //offset
         window.draw(s);
       }

    for (int i=0;i<4;i++)
      {
        s.setTextureRect(sf::IntRect(colorNum*18,0,18,18));
        s.setPosition(a[i].x*18,a[i].y*18);
        s.move(28,31); //offset
        window.draw(s);
      }

    //window.draw(frame);
    window.display();
}
return 0;
}
