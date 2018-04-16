# Run with:
#
# (Linux & Mac) python3.5 test.py -m ./mygameengine.so
# (Windows) python3.6 test.py -m ./mygameengine.pyd
#
# The program should also run with 'python2.7' but you will have
# to change the 3.5's to 2.7's in your respective build script as
# well as make sure you compiled with 3.5 or 2.7 load flags.
#
# You will see `python3.5-config --includes` for example which corresponds
# to which version of python you are building.
# (In fact, run `python3.5-config --includes` in the terminal to see what it does!)
import mygameengine

# Now use some python libraries for random numbers!
import random

MAX_SIZE = 1000
engine = mygameengine.SDLGraphicsProgram(MAX_SIZE,MAX_SIZE,"Game!")

class Player:
    w = 16
    h = 32

    def __init__(self, x):
        self.x = x
        self.y = MAX_SIZE//2 - self.h//2

    def draw(self, frameTick):
        engine.DrawFrame("tiger_walk.png", frameTick, 4, self.x, self.y, self.w, self.h);

    def jump(self):
        self.y -= 2;

    def update(self):
        # checkDie(self
        self.y += 1;

    def checkDie(self, ball):
        if (engine.RectIntersect(self.x, self.y, self.w, self.h, ball.x, ball.y, ball.size, ball.size)):
            ball.dx*=-1


player = Player(20);

engine.PlayMusic("music.wav");

print("Setting up game loop")
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

while not engine.pressed("q") :
    # Clear the screen
    engine.clear();

    if engine.pressed("up"):
        player.jump();

    player.update();
    player.draw(frameTick);

    frameTick = endGameLoop(frameTick);
    # Refresh the screen
    engine.flip();
