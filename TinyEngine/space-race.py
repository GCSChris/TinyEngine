import mygameengine

import random

SCREEN_WIDTH = 750
SCREEN_HEIGHT = 150
GROUND_HEIGHT = 10
engine = mygameengine.SDLGraphicsProgram(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Race!")

game_over = False;
paused = False;

class Star:
    x = 0;
    y = 0;
    w = 10
    h = 10

    def __init__(self):
        self.setRandStarXY();
        self.vx = random.uniform(0.85, 1.25) * -1;

    def setRandStarXY(self):
        self.x = random.randint(int(SCREEN_WIDTH), int(SCREEN_WIDTH * 1.5));
        self.y = random.randint(0, (SCREEN_HEIGHT - GROUND_HEIGHT) - self.h);

    def draw(self):
        engine.SetColor(255, 255, 255, 255);
        engine.DrawRectangle(int(self.x), int(self.y), int(self.w), int(self.h), True);

    def update(self):
        self.x = self.x + self.vx;
        if (self.x - self.w <= 0):
            self.setRandStarXY();
            self.vx = random.uniform(0.6, 1.25) * -1;


class Rocket:
    def draw():
        w = 32
        h = 64

        x = SCREEN_WIDTH - w - 15;
        y = (SCREEN_HEIGHT - GROUND_HEIGHT) - h;
        engine.DrawImage("resources/space-race/rocket.png", int(x), int(y), int(w), int(h));

class Player:
    w = 32
    h = 32

    vx = 0
    vy = 0

    def __init__(self, x):
        self.x = x
        self.y = SCREEN_HEIGHT // 2 - self.h // 2
        self.vy = 0;
        self.usedBooster = False;

    def draw(self, frameTick):
        engine.DrawFrame("resources/space-race/astronaut-walk.png", frameTick, 7, int(self.x), int(self.y), int(self.w), int(self.h));

    def jump(self):
        self.vy -= 4;

    def upBooster(self):
        self.vy -= 3.5;

    def downBooster(self):
        self.vy += 3;

    def update(self):
        self.y = self.y + self.vy;

        if (self.y + self.h < SCREEN_HEIGHT - GROUND_HEIGHT):
            self.vy += 0.1; # gravity
        else:
            self.y = (SCREEN_HEIGHT - GROUND_HEIGHT)- self.h;
            self.vy = 0;

        if engine.pressed("space") and (self.y + self.h >= SCREEN_HEIGHT - GROUND_HEIGHT):
            player.jump();
            self.usedBooster = False;

        if engine.pressed("s") and (not self.usedBooster):
            player.downBooster();
            self.usedBooster = True;

        if engine.pressed("w") and (not self.usedBooster):
            player.upBooster();
            self.usedBooster = True;

    def checkDie(self, star):
        if (engine.RectIntersect(int(self.x), int(self.y), int(self.w), int(self.h),
        int(star.x), int(star.y), int(star.w), int(star.h))):
            global paused;
            global game_over;
            paused = True;
            game_over = True;

# --------------------------

starQueue = [];
FRAMERATE = 60;
engine.SetFramerate(FRAMERATE);
frameTick = 0;
engine.PlayMusic("resources/space-race/music.wav");
player = Player(50);

def endGameLoop(frameTick):
    # Add a little delay
    engine.FrameRateDelay();

    frameTick = (frameTick + 1);
    if (frameTick >= FRAMERATE):
        frameTick = 0;

    return frameTick;


MAX_NUM_STARS = 10;
score = 0;

while not engine.pressed("q"):
    # Clear the screen
    engine.clear();

    engine.DrawImage("resources/space-race/blue-bg.png", 0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    engine.SetColor(145, 145, 145, 255);
    engine.DrawRectangle(0, SCREEN_HEIGHT - GROUND_HEIGHT, SCREEN_WIDTH, GROUND_HEIGHT, True);

    if game_over:
        engine.RenderCenteredText("GAME OVER!", "arial.ttf", 32, SCREEN_HEIGHT // 3);
        engine.RenderCenteredText("YOUR SCORE WAS: " + str(score) + "!", "arial.ttf", 32, ((SCREEN_HEIGHT // 3) * 2));
    elif paused:
        engine.RenderCenteredText("PAUSED", "arial.ttf", 32, SCREEN_HEIGHT // 2);

    if engine.pressed("p"):
        paused = True;
    if engine.pressed("o"):
        paused = False;

    engine.RenderText(str(score), "resources/space-race/arial.ttf", 12, 20, 20);

    if not paused:
        player.update();
    player.draw(frameTick);

    Rocket.draw();

    for star in starQueue:
        if not paused:
            star.update();
            player.checkDie(star);
        star.draw();

    if not paused:
        if ((len(starQueue) < MAX_NUM_STARS)
        and (frameTick == 0 and score % 10 == 0)): # max num stars
            starQueue.append(Star()); # rand star

        frameTick = endGameLoop(frameTick);

        if (frameTick % FRAMERATE == 0):
            score += 1;

    # Refresh the screen
    engine.flip();
