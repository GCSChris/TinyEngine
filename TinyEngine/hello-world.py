import mygameengine

import random

SCREEN_WIDTH = 500
SCREEN_HEIGHT = 500

engine = mygameengine.SDLGraphicsProgram(SCREEN_WIDTH, SCREEN_HEIGHT)

class Rocket: # Static images!
    def draw():
        w = 32
        h = 64

        x = SCREEN_WIDTH // 5 * 4;
        y = SCREEN_HEIGHT // 5 * 4;

        engine.DrawImage("rocket.png", x, y, w, h);

class Braid: # Animated Sprites!

    def draw():
        x = 0
        y = 0
        w = 130
        h = 150
        engine.DrawFrame("braid.png", frameTick, 27, x, y, w, h);

# --------------------------
class Box:
    w = 60
    h = 10

    def __init__(self):
        self.x = SCREEN_WIDTH // 2 - self.w // 2
        self.y = SCREEN_HEIGHT // 2 - self.h // 2

    def draw(self):
        engine.SetColor(0, 0, 0, 255);
        engine.DrawRectangle(self.x, self.y, self.w, self.h, True);

    def moveLeft(self):
        self.x -= 3;

    def moveRight(self):
        self.x += 3;

class BouncingBall:
    w = 32
    h = 32

    vx = 0
    vy = 0

    def __init__(self):
        self.x = 70
        self.y = 50
        self.vy = 2;
        self.vx = 3;
        self.updateColor();

    def update(self, box):
        self.checkWallCollision();
        changeColor = self.handleBoxCollision(box);

        if (changeColor):
            self.updateColor();

        self.x += self.vx;
        self.y += self.vy;

    def draw(self):
        engine.SetColor(self.colorR, self.colorG, self.colorB, 255);
        engine.DrawRectangle(self.x, self.y, self.w, self.h, True);

    def checkWallCollision(self):
        if (self.x <= 0) or (self.x + self.w >= SCREEN_HEIGHT):
            self.vx *= -1;

        if (self.y <= 0) or (self.y + self.h >= SCREEN_HEIGHT):
            self.vy *= -1;

    def updateColor(self):
        self.colorR = random.randint(0, 255);
        self.colorG = random.randint(0, 255);
        self.colorB = random.randint(0, 255);

    def handleBoxCollision(self, box):
        intersect = engine.RectIntersect(self.x, self.y, self.w, self.h, box.x, box.y, box.w, box.h);

        if intersect:
            # self.vx *= -1;
            self.vy *= -1;

        return intersect;

# class

FRAMERATE = 60;
frameTick = 0;
engine.SetFramerate(FRAMERATE);
engine.PlayMusic("dean-town.mp3");

def endGameLoop(frameTick):
    # Add a little delay
    engine.FrameRateDelay();

    frameTick = (frameTick + 1);
    if (frameTick >= FRAMERATE):
        frameTick = 0;

    return frameTick;

engine.SetBackgroundColor(255, 255, 255, 255);
ball = BouncingBall();
box = Box();

while not engine.pressed("q"):
    # Clear the screen
    engine.clear();

    engine.SetTextColor(0, 0, 0, 255);
    engine.RenderCenteredText("Welcome to TinyEngine!", "arial.ttf", 12, 100);
    engine.RenderCenteredText("Move the paddle using the A and D Keys!", "arial.ttf", 12, 200);
    engine.RenderCenteredText("Play a sound by pressing spacebar!", "arial.ttf", 12, 300);

    ball.update(box);

    Rocket.draw();
    Braid.draw();
    ball.draw();
    box.draw();

    if engine.pressed("space"):
        engine.PlaySFX("explosion.mp3");

    if engine.pressed("a"):
        box.moveLeft();
    if engine.pressed("d"):
        box.moveRight();

    frameTick = endGameLoop(frameTick);

    # Refresh the screen
    engine.flip();
