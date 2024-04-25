#include <U8g2lib.h>

// my ponguino project!!!!!

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0);

// paddle & ai paddle initial y position
int paddleYPOS = 34;
int paddleAIYPOS = 34;

int ballXPOS = 62;  // balls initial X and Y pos
int ballYPOS = 24;

int ballSpeedX = -1;  // ball initial X and Y speed
int ballSpeedY = 1;

int score = 0;  // starting player and AI score
int aiscore = 0;

// bitmap for player paddle
#define paddle_width 1
#define paddle_height 15
const static unsigned char paddle_bits[] PROGMEM = {
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01
};

// bitmap for AI's paddle
#define paddleAI_width 1
#define paddleAI_height 15
const static unsigned char paddleAI_bits[] PROGMEM = {
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01
};

// bitmap for the middle line
#define middlePongLine_width 1
#define middlePongLine_height 64
const static unsigned char middlePongLine_bits[] PROGMEM = {
0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0x01, 0x01
};

// bitmap for the ball,
#define ball_width 8
#define ball_height 8
const static unsigned char ball_bits[] U8X8_PROGMEM = {
  0x18, 0x5a, 0x24, 0xdb, 0xdb, 0x24, 0x5a, 0x18
};

void setup(void) {
pinMode(A3,INPUT);
pinMode(13,OUTPUT);
oled.begin();
oled.setFont(u8g2_font_ncenB08_tr);
}

// reset game is called to reset game, after win or loss and to start
void resetGame() {
score = 0;
aiscore = 0;
ballXPOS = 62;
ballYPOS = 24;
ballSpeedX = -1;
ballSpeedY = 1;
paddleAIYPOS = 24; 
paddleYPOS = 24;
}

void gameOvermsg(){
oled.clearDisplay();
oled.setCursor(26, 15);
oled.println("GAME OVER");
oled.setCursor(32, 30);
oled.println("you suck... ");
oled.setCursor(30,45);
oled.println("starting in 5");
oled.sendBuffer();
delay(1000);
oled.clearDisplay();
oled.setCursor(26, 15);
oled.println("GAME OVER");
oled.setCursor(32, 30);
oled.println("you suck... ");
oled.setCursor(30,45);
oled.println("starting in 4");
oled.sendBuffer();
delay(1000);
oled.clearDisplay();
oled.setCursor(26, 15);
oled.println("GAME OVER");
oled.setCursor(32, 30);
oled.println("you suck... ");
oled.setCursor(30,45);
oled.println("starting in 3");
oled.sendBuffer();
delay(1000);
oled.clearDisplay();
oled.setCursor(26, 15);
oled.println("GAME OVER");
oled.setCursor(32, 30);
oled.println("you suck... ");
oled.setCursor(30,45);
oled.println("starting in 2");
oled.sendBuffer();
delay(1000);
oled.clearDisplay();
oled.setCursor(26, 15);
oled.println("GAME OVER");
oled.setCursor(32, 30);
oled.println("you suck... ");
oled.setCursor(30,45);
oled.println("starting in 1");
oled.sendBuffer();
delay(1000);
resetGame();
}

void gameOvermsgAI() {
oled.clearDisplay();
oled.setCursor(26, 15);
oled.println("GAME OVER");
oled.setCursor(32, 30);
oled.println("YOU WIN!!! ");
oled.setCursor(30,45);
oled.println("starting in 5");
oled.sendBuffer();
delay(1000);
oled.clearDisplay();
oled.setCursor(26, 15);
oled.println("GAME OVER");
oled.setCursor(32, 30);
oled.println("YOU WIN!!! ");
oled.setCursor(30,45);
oled.println("starting in 4");
oled.sendBuffer();
delay(1000);
oled.clearDisplay();
oled.setCursor(26, 15);
oled.println("GAME OVER");
oled.setCursor(32, 30);
oled.println("YOU WIN!!! ");
oled.setCursor(30,45);
oled.println("starting in 3");
oled.sendBuffer();
delay(1000);
oled.clearDisplay();
oled.setCursor(26, 15);
oled.println("GAME OVER");
oled.setCursor(32, 30);
oled.println("YOU WIN!!! ");
oled.setCursor(30,45);
oled.println("starting in 2");
oled.sendBuffer();
delay(1000);
oled.clearDisplay();
oled.setCursor(26, 15);
oled.println("GAME OVER");
oled.setCursor(32, 30);
oled.println("YOU WIN!!! ");
oled.setCursor(30,45);
oled.println("starting in 1");
oled.sendBuffer();
delay(1000);
resetGame();
}

void loop(void) {
oled.clearBuffer();
// Players joystick input
int VRX = (analogRead(A1) - 512) / 150;
int VRY = (analogRead(A2) - 512) / 150;
paddleYPOS -= VRX;

// ai movement paddle
if (ballYPOS > paddleAIYPOS + paddleAI_height / 4) {
paddleAIYPOS += 2;
} else if (ballYPOS < paddleAIYPOS + paddleAI_height / 4) {
paddleAIYPOS -= 2;
}
//ball updated pos
ballXPOS += ballSpeedX;
ballYPOS += ballSpeedY;

// user paddle collision check
if (ballXPOS <= 1 && ballYPOS + ball_height >= paddleYPOS && ballYPOS <= paddleYPOS + paddle_height) {
  int paddlePOSball = ballYPOS - paddleYPOS;
  float posMULTI = float(paddlePOSball) / paddle_height;  
ballSpeedY = int(paddlePOSball * 1) - 1;
ballSpeedX = -ballSpeedX;
//calculating the position of the ball relative to the paddle, depending on where you hit the ball, the ball will go in a different direction. added this aspect because the physcis of the game before made it almost impossib
// for the player to win the game.

// increasing of the balls speed so that the game doesnt last forever
if (ballSpeedX > 0) {
  ++ballSpeedX;
} else {
  --ballSpeedX;
}
ballXPOS = 1;  // added this to update the position directly after impact because an issue was occuring when tHEBall was going so fast it would just phase through the paddle.
}

// ai paddles collison check
if (ballXPOS + ball_width >= 127 && ballYPOS + ball_height >= paddleAIYPOS && ballYPOS <= paddleAIYPOS + paddleAI_height) {
int aipaddlePOSball = ballYPOS - paddleAIYPOS;
float aiposMULTI = float(aipaddlePOSball) / paddleAI_height;  
//calculating the position of the ball relative to the paddle, depending on where you hit the ball, the ball will go in  a different direction. added this aspec  because the phys

ballSpeedY = int(aipaddlePOSball * 1) - 1;

ballSpeedX = -ballSpeedX;
--ballSpeedX;
}

// if ball is in contact with top or bottom of the oled screen it reverses the Y direction
if (ballYPOS <= 0 || ballYPOS + ball_height >= 64) {
ballSpeedY = -ballSpeedY;
}
// if the ball goes past the player side of the screen, ai scores a point and then every value is reset (excpet for score)
if (ballXPOS <= -ball_width -6) {
aiscore += 1;
delay(1500);
ballXPOS = 62;
ballYPOS = random(9, 55);
ballSpeedX = -1;
ballSpeedY = 1;
paddleAIYPOS = 34;
paddleYPOS = 34;
}
// same thing here, if the player scores increase our score, and reset values (except for the score)
if (ballXPOS >= 134) {
score += 1;
delay(1500);
ballXPOS = 62;
ballYPOS = random(9, 55);
ballSpeedX = 1;
ballSpeedY = -1;
paddleAIYPOS = 34;
paddleYPOS = 34;
}

// draw the bitmaps
oled.drawXBMP(1, paddleYPOS, paddle_width, paddle_height, paddle_bits);
oled.drawXBMP(127, paddleAIYPOS, paddleAI_width, paddleAI_height, paddleAI_bits);
oled.drawXBMP(64, 0, middlePongLine_width, middlePongLine_height, middlePongLine_bits);
oled.drawXBMP(ballXPOS, ballYPOS, ball_width, ball_height, ball_bits);


// display ai and player score
oled.setCursor(20, 12);
oled.println(score);
oled.setCursor(100, 12);
oled.println(aiscore);
oled.sendBuffer();


// if score reached, display game over msg eiter win or lose
if (score >= 2) {
gameOvermsgAI();
}
if (aiscore >= 2) {
gameOvermsg();
}
if (!analogRead(A3)){
resetGame();
}
}
// allows the user to reset game at will using the button on the joystick controller