import mygameengine

import random

MAX_SIZE = 600
engine = mygameengine.SDLGraphicsProgram(MAX_SIZE, MAX_SIZE)

class Star:
    x = 0;
    y = 0;
    w = 10
    h = 10
    vx = -0.1;

    def __init__(self):
        self.x = random.randint(MAX_SIZE, MAX_SIZE + 150);
        self.y = random.randint(MAX_SIZE - 50, MAX_SIZE);
        self.vx = -1;

    def draw(self):
        engine.SetColor(255, 255, 255, 255);
        engine.DrawRectangle(int(self.x), int(self.y), int(self.w), int(self.h), True);

    def update(self):
        self.x = self.x + self.vx;
        if (self.x < 0):
            self.x = MAX_SIZE;
            self.y = random.randint(MAX_SIZE - 50, MAX_SIZE);


starQueue = []

class Player:
    w = 16
    h = 32
    vx = 0
    vy = 0

    def __init__(self, x):
        self.x = x
        self.y = MAX_SIZE//2 - self.h//2
        self.vy = 0;
        self.usedBooster = False;

    def draw(self, frameTick):
        engine.DrawFrame("tiger_walk.png", frameTick, 4, int(self.x), int(self.y), int(self.w), int(self.h));

    def jump(self):
        self.vy -= 4;

    def upBooster(self):
        print("boost UP!");
        self.vy -= 2;

    def downBooster(self):
        print("boost DOWN!");
        self.vy += 3;

    def update(self):
        self.y = self.y + self.vy;

        if (self.y + self.h < 600):
            self.vy += 0.1; # gravity
        else:
            self.y = 600 - self.h;
            self.vy = 0;

        if engine.pressed("space") and (self.y + self.h >= MAX_SIZE):
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
            print("DEAD!\n");


player = Player(50);

engine.PlayMusic("music.wav");
engine.SetBackgroundColor(95, 65, 245, 255); # dark blue

FRAMERATE = 60;
engine.SetFramerate(FRAMERATE);
frameTick = 0;

def endGameLoop(frameTick):
    # Add a little delay
    engine.FrameRateDelay();

    frameTick = (frameTick + 1);
    if (frameTick >= FRAMERATE):
        frameTick = 0;

    return frameTick;

MAX_NUM_STARS = 10;
score = 0
while not engine.pressed("q") :
    # Clear the screen
    engine.clear();

    engine.RenderText(str(score), "arial.ttf", 12, 20, 20);

    player.update();
    player.draw(frameTick);

    for star in starQueue:
        star.update();
        star.draw();
        player.checkDie(star);

    # player.checkDie(star1);

    if ((len(starQueue) < MAX_NUM_STARS) and (frameTick == 0 and score % 10 == 0)): # max num stars
        print("making new Star!");
        starQueue.append(Star()); # rand star

    frameTick = endGameLoop(frameTick);

    if (frameTick % FRAMERATE == 0):
        score += 1;

    # Refresh the screen
    engine.flip();
