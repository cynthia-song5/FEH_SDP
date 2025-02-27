#include <FEHLCD.h>
#include <FEHUtility.h>
#include <FEHImages.h>
#include <math.h>
#include <FEHRandom.h>
/* Authors: Alex Follmer & Cynthia Song
 * Instructor: Amy Kramer
 * Class Time: 8 AM
 * Assignment: SDP
 */

// create struct to store Data for the pomodoro feature 
struct Data{
    float startTime;
    float studyTime;
    float playTime;
    int highScore;
    float sTimeRemaining;
    float pTimeRemaining;
};
// struct to store values needed for the game
struct GameNumbers
{
    int r = 7;
    int touched = 0;
    float touchX;
    float touchY;
    float touchedtracker = 1;
    float up = 0;
    float down = 0;
    int dead = 0;
    float speed = 1;
    float JumperX = 70;
    float JumperY = 210-r;
    float obstacleRectangle1Height;
    float obstacleRectangle1Width;
    float obstacleRectangle1X = 0;
    float obstacleRectangle1Y;
    float obstacleRectangle2Height;
    float obstacleRectangle2Width;
    float obstacleRectangle2X = 0;
    float obstacleRectangle2Y;
    float gametime = 0;
    int accelCounter = 0;
    float acceleration = 1.2;
    int score =0;
    int highScore=0;
    int obstacleCounter = 1;
};
// struct to store information used to create background for the game
struct Aesthetics
{
    float StarSpeed = 1;
    float StarOddY = 30;
    float StarEvenY = 80;
    float Star1X = 300;
    float Star2X = 250;
    float Star3X = 200;
    float Star4X = 150;
    float Star5X = 100;
    float Star6X = 50;
    float Star7X = 0;
    int spacecraftRandom;
    float spacecraftX;
    float spacecraftY;
    float spaceCraftSpeed = 2;
    int makeSpacecraft = 0;
};

// declarations
struct GameNumbers gamemain(struct GameNumbers, struct Aesthetics);
void obstacle(struct GameNumbers);
void collision(struct GameNumbers);
void Menu(struct Data, struct GameNumbers, struct Aesthetics);
void Enter(struct Data, struct GameNumbers, struct Aesthetics);
void Instructions(struct Data, struct GameNumbers, struct Aesthetics);
void Credits(struct Data, struct GameNumbers, struct Aesthetics);
void Stats(struct Data, struct GameNumbers, struct Aesthetics);
void Settings(struct Data, struct GameNumbers, struct Aesthetics);
void Study(struct Data, struct GameNumbers, struct Aesthetics);
void Play(struct Data, struct GameNumbers, struct Aesthetics);

// create the menu
void Menu(struct Data info, struct GameNumbers game, struct Aesthetics stars) {
    // initialize variables
    float x, y;
    info.sTimeRemaining = info.studyTime;
    info.pTimeRemaining = info.playTime;
    int x1 = 90, y1 = 110;
    int width = 145, height = 20;
    int r = 10;
    LCD.Clear();
    LCD.SetBackgroundColor(BLACK);

    LCD.SetFontColor(LIGHTBLUE);

    // background
    FEHImage instr;
    // Open the image
    instr.Open("download.png");
    instr.Draw(0, 125);

    // buttons for different pages
    LCD.DrawRectangle(x1, y1, width, height);
    LCD.FillRectangle(x1, y1, width, height);

    LCD.DrawRectangle(x1, y1+25, width, height);
    LCD.FillRectangle(x1, y1+25, width, height);
    LCD.DrawRectangle(x1, y1+50, width, height);
    LCD.FillRectangle(x1, y1+50, width, height);

    LCD.DrawRectangle(x1, y1+75, width, height);
    LCD.FillRectangle(x1, y1+75, width, height);

    LCD.WriteAt("SPACE JUMP", 90, 80);
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt("Enter",89,112);
    LCD.WriteAt("Instructions",89,112+25);
    LCD.WriteAt("Credits",89,112+50);
    LCD.WriteAt("Stats",89,112+75);
    // make settings button
    LCD.SetFontColor(WHITE);
    LCD.FillCircle(297,16,10);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("*", 290, 10);
    LCD.Update();
    LCD.SetFontColor(PURPLE);

    //LCD.SetFontColor(BLUEVIOLET);
    while (!LCD.Touch(&x,&y)) {};

    // Touch - use x and y
    // direct user to page corresponding with button touched
    while (LCD.Touch(&x,&y)){
    };
    if (y >= y1 && y < (y1+25)){
            Enter(info, game, stars);
        } else if (y >= (y1+25) && y < (y1+50)){
            Instructions(info, game, stars);
        } else if (y >= (y1+50) && y < (y1+75)){
            Credits(info, game, stars);
        } else if (y >= (y1+75) && y <= (y1+100)){
            float elapsed = TimeNow() - info.startTime;
            Stats(info, game, stars);
        } else if (x > 250){
            Settings(info, game, stars);
        }
        else{
            Menu(info, game, stars);
        }
}
// display enter screen
void Enter(struct Data info, struct GameNumbers game, struct Aesthetics stars){
    float x,y;
    LCD.Clear();
    //LCD.SetBackgroundColor(HONEYDEW);
    int width = 75;
    int height = 75;
    // create the buttons
    LCD.SetFontColor(LIGHTBLUE);
    LCD.DrawRectangle(50, 75, width, height);
    LCD.FillRectangle(50, 75, width, height);
    LCD.DrawRectangle(175, 75, width, height);
    LCD.FillRectangle(175, 75, width, height);

    //text 
    //settings page for the game
    LCD.SetFontColor(LIGHTSKYBLUE);
    LCD.WriteAt("Play game here", 50, 15);
    // write text for the buttons
    LCD.WriteAt("Menu", 5, 225);
    LCD.DrawRectangle(5,220,50,25);
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt("Study", 50, 100);
    LCD.WriteAt("Play", 182, 100);
    LCD.Update();
    while (!LCD.Touch(&x,&y)) {};
    // Touch - use x and y
    while (LCD.Touch(&x,&y)){};
        if (y > 210 && x < 70){
            // return to menu
        Menu(info, game, stars);
        //enter study mode
        } else if (x > 50 && x < 125 && y > 100 && y < 150){
            Study(info, game, stars);
            //enter play mode
        } else if (x > 175 && x < 225 && y > 100 && y < 150){
            Play(info, game, stars);
        }
        else{
            Enter(info, game, stars);
        }
}
// redirect to instructions page
void Instructions(struct Data info, struct GameNumbers game, struct Aesthetics stars){
    float x, y;
    LCD.Clear();
    FEHImage instr;
    // write instructions
    LCD.WriteLine ("1. Start by studying for");
    LCD.WriteLine(info.studyTime);
    LCD.WriteAt("seconds", 90, 20);
    LCD.WriteLine ("2. Play as many rounds of Space Jump until");
    LCD.WriteLine(info.playTime);
    LCD.WriteAt("seconds is up", 90, 70);
    LCD.WriteLine("3. Repeat"); 
    LCD.WriteLine("You can change the times");
    LCD.WriteLine("for studying and for");
    LCD.WriteLine("breaks in the settings");

    // redirect to menu upon touch
    while (!LCD.Touch(&x,&y)) {};
    while (LCD.Touch(&x,&y)){};
        Menu(info, game, stars);
}
// display the credits screen
void Credits(struct Data info, struct GameNumbers game, struct Aesthetics stars){
    float x, y;
    LCD.Clear();
    LCD.SetBackgroundColor(BLACK);
    LCD.SetFontColor(LIGHTBLUE);
    // write credits
    LCD.WriteAt("Authors:", 40, 50);
    LCD.WriteAt("Alex Follmer", 40, 100);
    LCD.WriteAt("Cynthia Song", 40, 150);
    LCD.WriteAt("Menu", 5, 225);
    LCD.DrawRectangle(5,220,50,25);
    while (!LCD.Touch(&x,&y)) {};
    // redirect to menu
    while (LCD.Touch(&x,&y)){};
        if (y > 210 && x < 70){
        Menu(info, game, stars);
        }
        else{
            Credits(info, game, stars);
        }
}
// display the stats screen
void Stats(struct Data info, struct GameNumbers game, struct Aesthetics stars){
    float x, y;
    LCD.Clear();
    LCD.SetFontColor(LIGHTSKYBLUE);
    // display play time
    LCD.WriteAt("You've been playing for ", 15, 25);
    float time = TimeNow() - info.startTime;
    LCD.WriteAt(time, 15, 50);
    LCD.WriteAt("seconds", 15, 75);
    LCD.WriteAt("Menu", 5, 225);
    LCD.DrawRectangle(5,220,50,25);
    // display high score
    LCD.WriteAt("Your high score is ", 15, 100);
    LCD.WriteAt(info.highScore, 15, 130);
    while (!LCD.Touch(&x,&y)) {};
    // redirect to menu
    while (LCD.Touch(&x,&y)){};
        if (y > 210 && x < 70){
        Menu(info, game, stars);
        }
        else{
            Stats(info, game, stars);
        }
}
// display settings screen
void Settings(struct Data info, struct GameNumbers game, struct Aesthetics stars){
    float x, y;
    float study = info.studyTime;
    float play = info.playTime;
    LCD.Clear();
    LCD.SetFontColor(LIGHTBLUE);
    //settings logic
    LCD.WriteAt("Study Time:", 10, 25);
    LCD.WriteAt(study, 10, 50);
    // "buttons" to increase/decrease time
    LCD.WriteAt("+", 150, 25);
    LCD.WriteAt("-", 180, 25);
    LCD.WriteAt("Play Time:", 10, 75);
    LCD.WriteAt(play, 10, 100);
    // "buttons" to increase/decrease time
    LCD.WriteAt("+", 150, 75);
    LCD.WriteAt("-", 180, 75);
    LCD.WriteAt("Menu", 5, 225);
    LCD.DrawRectangle(5,220,50,25);

    // redirect to menu
    while (!LCD.Touch(&x,&y)) {};
    while (LCD.Touch(&x,&y)){};
        if (y > 210 && x < 50){
        Menu(info, game, stars);
        // otherwise update times and refresh
        } else if (y > 25 && y < 50 && x >= 150 && x <= 170){
            info.studyTime = info.studyTime + 1;
            Settings(info, game, stars);
        } else if (y > 25 && y < 50 && x >= 180 && x <= 200){
            info.studyTime = info.studyTime - 1;
            Settings(info, game, stars); 
        } else if (y > 75 && y < 100 && x >= 150 && x <= 170){
            info.playTime = info.playTime + 1;
            Settings(info, game, stars);
        }else if (y > 75 && y < 100 && x >= 180 && x <= 200){
            info.playTime = info.playTime - 1;
            Settings(info, game, stars);
        } else{
            Settings(info, game, stars);
        }
}
// display the study screen
void Study(struct Data info, struct GameNumbers game, struct Aesthetics stars){
    bool cont = true;
    float x, y;
    LCD.SetFontColor(LIGHTSTEELBLUE);
    // display the time remaining, pausing 1 sec every time, until 0 secs are left
    while(cont && info.sTimeRemaining > 0){
        LCD.SetBackgroundColor(BLACK);
        LCD.SetFontColor(LIGHTSTEELBLUE);
        LCD.Clear();
        LCD.Update();
        info.sTimeRemaining = info.sTimeRemaining - 1;
        // get minutes and seconds
        int min = (int) info.sTimeRemaining/60;
        int sec = (int) info.sTimeRemaining % 60;
        // formatting if over 10 mins
        if (min >= 10){
        LCD.WriteAt(min, 110, 75);
        } 
        // otherwise
        else{
        LCD.WriteAt(0, 110, 75);   
        LCD.WriteAt(min, 123, 75);   
        }
        LCD.WriteAt(":", 135, 75);
        if (sec >= 10){
        LCD.WriteAt(sec, 145, 75);
        } else {
        LCD.WriteAt(0, 145, 75);
        LCD.WriteAt(sec, 158, 75);   
        }
        LCD.DrawRectangle(5,220,50,25);
        LCD.WriteAt("Menu", 5, 225);
        while (!LCD.Touch(&x,&y)) {
            Sleep(1000);
            Study(info, game, stars);
        };
       while (LCD.Touch(&x,&y)){};
       if (y > 210 && x < 70){
       Menu(info, game, stars);
       cont = false;
       }

   }
   // redirect to play
    Play(info, game, stars);
}
// display the play/game screen
void Play(struct Data info, struct GameNumbers game, struct Aesthetics stars){
  // reset to starting time
  game.gametime = TimeNow();
  // play the game until the time runs out
   while (TimeNow()-game.gametime<info.playTime)
  {
       //run game and check if timer is over if game ends
       game = gamemain(game, stars);
       if (game.highScore > info.highScore){
        info.highScore = game.highScore;
       }
       if (game.dead == 1)
       {
           break;
       }
}
//redirect
Study(info, game, stars);
}

//main program of game//
struct GameNumbers gamemain(struct GameNumbers GameValues, struct Aesthetics Stars){
   //Clear background
   LCD.Clear();
   LCD.SetBackgroundColor(BLACK);

   //Write time & score to screen
   LCD.SetFontColor(WHITE);
   LCD.WriteAt(abs(GameValues.gametime-TimeNow()), 5, 5);
   LCD.WriteAt(GameValues.score, 260, 5);
 
   // Draw jumper at start
   LCD.SetFontColor(RED);
   LCD.FillCircle(GameValues.JumperX, GameValues.JumperY, GameValues.r);

   //Draw floor
   LCD.SetFontColor(SILVER);
   LCD.FillRectangle(0,210,319,20);

   //Draw stars at start
   LCD.SetFontColor(WHITE);
   LCD.DrawCircle(Stars.Star1X,Stars.StarOddY,1);
   LCD.DrawCircle(Stars.Star2X,Stars.StarEvenY,1);
   LCD.DrawCircle(Stars.Star3X,Stars.StarOddY,1);
   LCD.DrawCircle(Stars.Star4X,Stars.StarEvenY,1);
   LCD.DrawCircle(Stars.Star5X,Stars.StarOddY,1);
   LCD.DrawCircle(Stars.Star6X,Stars.StarEvenY,1);
   LCD.DrawCircle(Stars.Star7X,Stars.StarEvenY,1);
   LCD.Update();

   //Make other space craft (added fun) (make randomized number) (1000 max and 0 min)
   Stars.spacecraftRandom = Random.RandInt() % (1000 - 0 + 1) + 0;

   //wait till button pressed
   while (!LCD.Touch(&GameValues.touchX,&GameValues.touchY))
   {
           Sleep(1);
   }

   //Check to see if touched
   if (LCD.Touch(&GameValues.touchX,&GameValues.touchY))
   {

   //if not dead, run the program
   while (GameValues.dead == 0)
   {
       //Clear previous objects//
       LCD.Clear();

       //Reset obstacle at end; if obstacle x value is less than 100, reset obstacle
       if (GameValues.obstacleRectangle1X <= 0)
       {
           //Randomize the height of rectangle 1 with max of 40 and min of 10, plus make sure the base is on the ground
           GameValues.obstacleRectangle1Height = Random.RandInt() % (40 - 10 + 1) + 10;
           GameValues.obstacleRectangle1Y = 210-GameValues.obstacleRectangle1Height;

           //Randomize the width of rectangle 1 with max of 16 and min of, reset x value
           GameValues.obstacleRectangle1Width = Random.RandInt() % (16 - 8 + 1) + 8;
           GameValues.obstacleRectangle1X = 319 - GameValues.obstacleRectangle1Width;

           //Make speed faster
           if (GameValues.accelCounter>200)
           {
               //Divided acceleration by two for each time obstacleRectangle resets & then reset counter
               GameValues.acceleration = GameValues.acceleration/1.5;
               GameValues.accelCounter = 0;
           }
           //Make obstacle faster (make harder)
           GameValues.speed += GameValues.acceleration;

           //See if it wants to have two obstacles (40 to 100 is 2 obtacles) (0 to 39 is 1  obstacle)
           GameValues.obstacleCounter = Random.RandInt() % (100 - 0 + 1) + 0;

           //If counter is equal to or greater than 40, make another rectangle
           if (GameValues.obstacleCounter >= 40)
           {
               //Randomize the height of rectangle 2 with max of 40 and min of 10, plus make sure the base is on the ground
               GameValues.obstacleRectangle2Height = Random.RandInt() % (40 - 10 + 1) + 10;
               GameValues.obstacleRectangle2Y = 210-GameValues.obstacleRectangle2Height;

               //Randomize the width of rectangle 2 with max of 16 and min of 8
               GameValues.obstacleRectangle2Width = Random.RandInt() % (16 - 8 + 1) + 8;
               GameValues.obstacleRectangle2X = GameValues.obstacleRectangle1X+GameValues.obstacleRectangle1Width;
           }
           //If counter is less than 40, DO NOT make another rectangle & reset rectangle 2 values
           else
           {
               //reset values
               float obstacleRectangle2Height = 0;
               float obstacleRectangle2Width = 0;
               float obstacleRectangle2X = 0;
               float obstacleRectangle2Y = 0;
           }
           //If randomized number is equal to counter, make craft
           if (GameValues.score >= Stars.spacecraftRandom)
           {
               //set coordinates & make sure it doesn't repeat
               Stars.makeSpacecraft = 1;
               Stars.spacecraftX = 299;
               Stars.spacecraftY = 40;
               Stars.spacecraftRandom = 10000000000;
           }
       }

       //Move obstacleX closer (speed is defined by speed & starts at 4)
       GameValues.obstacleRectangle1X -= GameValues.speed;
       GameValues.obstacleRectangle2X -= GameValues.speed;

       //Write time & score to screen
       LCD.SetFontColor(WHITE);
       LCD.WriteAt(abs(GameValues.gametime-TimeNow()), 5, 5);
       LCD.WriteAt(GameValues.score, 260, 5);

       //Draw floor
       LCD.SetFontColor(SILVER);
       LCD.FillRectangle(0,210,319,20);

       //Draw new rectangle 1
       LCD.SetFontColor(WHITE);
       LCD.FillRectangle(GameValues.obstacleRectangle1X,GameValues.obstacleRectangle1Y,GameValues.obstacleRectangle1Width,GameValues.obstacleRectangle1Height);

       //Draw new rectangle 2
       LCD.FillRectangle(GameValues.obstacleRectangle2X,GameValues.obstacleRectangle2Y,GameValues.obstacleRectangle2Width,GameValues.obstacleRectangle2Height);

       //Move Stars closer
       Stars.Star1X -= Stars.StarSpeed;
       Stars.Star2X -= Stars.StarSpeed;
       Stars.Star3X -= Stars.StarSpeed;
       Stars.Star4X -= Stars.StarSpeed;
       Stars.Star5X -= Stars.StarSpeed;
       Stars.Star6X -= Stars.StarSpeed;
       Stars.Star7X -= Stars.StarSpeed;

       //Draw Stars
       LCD.SetFontColor(WHITE);
       LCD.DrawCircle(Stars.Star1X,Stars.StarOddY,1);
       LCD.DrawCircle(Stars.Star2X,Stars.StarEvenY,1);
       LCD.DrawCircle(Stars.Star3X,Stars.StarOddY,1);
       LCD.DrawCircle(Stars.Star4X,Stars.StarEvenY,1);
       LCD.DrawCircle(Stars.Star5X,Stars.StarOddY,1);
       LCD.DrawCircle(Stars.Star6X,Stars.StarEvenY,1);
       LCD.DrawCircle(Stars.Star7X,Stars.StarEvenY,1);

       //Move spacecraft closer & mayeb differenatie height of spacecraft
       Stars.spacecraftX -= Stars.spaceCraftSpeed;

       //Draw spacecraft
       if (Stars.makeSpacecraft == 1)
       {
       LCD.SetFontColor(SILVER);
       LCD.FillRectangle(Stars.spacecraftX, Stars.spacecraftY, 30, 20);
       LCD.SetFontColor(BLACK);
       LCD.FillRectangle(Stars.spacecraftX+4, Stars.spacecraftY+5, 22, 10);
       LCD.SetFontColor(LIGHTBLUE);
       LCD.FillRectangle(Stars.spacecraftX+5, Stars.spacecraftY+6, 20, 8);

       //Change makeSpacecraft to 0
       if (Stars.spacecraftX < 0)
       {
           Stars.makeSpacecraft = 0;
       }
       }
       //Check to see if touched
       if (LCD.Touch(&GameValues.touchX,&GameValues.touchY))
       {
           GameValues.touched = 1;
       }
       //If variable touched is equal to 1
           if (GameValues.touched == 1)
           {
               //If jumper hasn't gone up all the way (less than 150)
               if (GameValues.up < 80)
               {
                   // Change y coordinate
                   GameValues.JumperY -= 7;

                   //track how long it has been up
                   GameValues.up += 7;

                   // Draw new jumper
                   LCD.SetFontColor(RED);
                   LCD.FillCircle(GameValues.JumperX, GameValues.JumperY, GameValues.r);
               }

               //if up is greater than 150, start going down
               else if ((GameValues.up >= 80) && (GameValues.down < 80))
               {
                   // Change y coordinate
                   GameValues.JumperY += 7;

                   //track how long it has been going down
                   GameValues.down += 7;

                   // Draw new jumper
                   LCD.SetFontColor(RED);
                   LCD.FillCircle(GameValues.JumperX, GameValues.JumperY, GameValues.r);
               }
               //If both up & down are more than 100, reset values
               else if ((GameValues.up >= 80) && (GameValues.down >= 80))
               {
                   //reset values
                   GameValues.up = 0;
                   GameValues.down = 0;
                   GameValues.touched = 0;
               }
           }

       else
       {
           // Draw jumper from orginal position
           LCD.SetFontColor(RED);
           LCD.FillCircle(GameValues.JumperX, GameValues.JumperY, GameValues.r);
       }

       //If obstacle is too close to Jumper, break out of loop
       if (((abs((GameValues.obstacleRectangle1X- GameValues.JumperX)) < (GameValues.obstacleRectangle1Width)/2) && ((GameValues.obstacleRectangle1Y+GameValues.r - GameValues.JumperY) < (GameValues.obstacleRectangle1Height)/2)) ||  ((abs((GameValues.obstacleRectangle2X- GameValues.JumperX)) < (GameValues.obstacleRectangle2Width)/2) && ((GameValues.obstacleRectangle2Y+GameValues.r - GameValues.JumperY) < (GameValues.obstacleRectangle2Height)/2)))
       {
           GameValues.dead = 1;
           //LCD.Write at
           break;
       }
       //counter for number of loops + score counter
       GameValues.accelCounter +=1;
       GameValues.score +=1;

       //sleep timer & update
       LCD.Update();
       Sleep(0.001);
   }
   }

   //Draw Game over sign and wait
   LCD.SetFontColor(RED);
   LCD.FillRectangle(88,78,144,84);
   LCD.SetFontColor(BLACK);
   LCD.FillRectangle(90,80,140,80);
   LCD.SetFontColor(RED);
   LCD.WriteAt("Game Over", 105, 95);
   LCD.SetFontColor(WHITE);
   LCD.WriteAt("Score: ", 100, 120);
   LCD.WriteAt(GameValues.score, 175, 120);
   if (GameValues.score >= GameValues.highScore){
    GameValues.highScore = GameValues.score;
   }
   LCD.Update();

  //wait till button pressed
   while (!LCD.Touch(&GameValues.touchX,&GameValues.touchY))
   {
           Sleep(1);
   }
   return GameValues;
}

int main() {
   // Clear background
   LCD.SetBackgroundColor(BLACK);
   LCD.Clear();
   struct GameNumbers GameValues;
   struct Aesthetics Stars;

   //start timer for game time
   GameValues.gametime = TimeNow();

   struct Data info;

   info.startTime = TimeNow();
   info.studyTime = 25*60;
   info.playTime = 20;
   //info.sTimeRemaining = info.studyTime;
   //info.pTimeRemaining = info.playTime;

   //Menu(info);
   Menu(info, GameValues, Stars);
   while (1) {
       LCD.Update();
       // Never end
   }
}