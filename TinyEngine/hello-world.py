import mygameengine
import tinymath

import random

SCREEN_WIDTH = 500;
SCREEN_HEIGHT = 500;

engine = mygameengine.SDLGraphicsProgram(SCREEN_WIDTH, SCREEN_HEIGHT, "TinyEngine!");

class Rocket: # Static images!

    def draw():
        x = 450;
        y = 420;
        w = 32;
        h = 64;

        # Draw our rocket image file (of dimensions 32 x 64)
        #   at the coordinates 450, 420!
        engine.DrawImage("resources/hello-world/rocket.png", x, y, w, h);

class Braid: # Animated Sprites!

    def draw(frameTick):
        x = 0;
        y = 0;
        w = 130;
        h = 150;
        numFrames = 27;

        # Draw the braid guy (dimensions = 130 x 150) at the point (0, 0).
        #   Note that we need to specify the number of frames in
        #   our sprite sheet that we want rendered over one second!
        engine.DrawFrame("resources/hello-world/braid.png", frameTick, numFrames, x, y, w, h);

class Box:

    def __init__(self):
        self.w = 60
        self.h = 10
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

    def __init__(self):
        self.x = 450
        self.y = 50
        self.vy = 2;
        self.vx = 3;
        self.w = 32;
        self.h = 32;

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
        # Check if our ball colldies with the given box, and return true if it does.
        intersect = engine.RectIntersect(self.x, self.y, self.w, self.h, box.x, box.y, box.w, box.h);

        if intersect:
            self.vy *= -1;

        return intersect;

class Star:
    def __init__(self, center, shapePoints):
        self.centerPoint = center
        self.shapePoints = shapePoints

    def draw(self):
        engine.SetColor(255, 0, 0, 255)
        engine.DrawLines(self.getPoints(), True)

    def getPoints(self):
        return tinymath.TranslatePoints(self.shapePoints, self.centerPoint)

# ---

# Let TinyEngine know what framerate we would like to use - let's do 60fps!
framerate = 60;
engine.SetFramerate(60);

# Set the background color!
engine.SetBackgroundColor(255, 255, 255, 255);

# Play a song on loop!
engine.PlayMusic("resources/hello-world/dean-town.mp3");

# Create a bouncing ball!
ball = BouncingBall();

# Create a color-changing box!
box = Box();

# The center point of the star!
centerPoint = (50, 400);
# The coodinates of the star (in drawing order) relative to its center!
shapePoints = [(-40, 0), (40, 0), (-20, 40), (0, -20), (20, 40)]
star = Star(centerPoint, shapePoints);

# Keep track of our current frame number in the current second.
frameTick = 0;

def endGameLoop(frameTick):
    # Add a little delay
    engine.FrameRateDelay();

    frameTick = (frameTick + 1);
    if (frameTick >= framerate):
        frameTick = 0;

    return frameTick;

# Start our Game loop!
while not engine.pressed("q"):
    # Clear the screen!
    engine.clear();

    # Check if our ball collides with the color-changing box!
    ball.update(box);

    # Draw everything in our game!
    Rocket.draw();
    Braid.draw(frameTick);
    star.draw();
    box.draw();
    ball.draw();

    # Set the Color of our text!
    engine.SetTextColor(0, 0, 0, 255);
    engine.RenderCenteredText("Welcome to TinyEngine!", "resources/hello-world/arial.ttf", 12, 100);
    engine.RenderCenteredText("Move the paddle using the A and D Keys!", "resources/hello-world/arial.ttf", 12, 200);
    engine.RenderCenteredText("Play a sound by pressing spacebar!", "resources/hello-world/arial.ttf", 12, 300);

    # When the player presses space, play an explosion sound!
    if engine.pressed("space"):
        engine.PlaySFX("resources/hello-world/explosion.mp3");

    # Handle player movement!
    if engine.pressed("a"):
        box.moveLeft();
    if engine.pressed("d"):
        box.moveRight();

    # Smooth our the framerate!
    frameTick = endGameLoop(frameTick);

    # Refresh the screen!
    engine.flip();
