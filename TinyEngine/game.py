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

MAX_SIZE = 400
engine = mygameengine.SDLGraphicsProgram(MAX_SIZE,MAX_SIZE)

class Paddle:
    w = 10
    h = 75

    def __init__(self, x):
        self.x = x
        self.y = MAX_SIZE//2 - self.h//2

    def draw(self):
        engine.SetColor(255, 255, 255, 255);
        engine.DrawRectangle(self.x,self.y,self.w,self.h,True);

    def move(self, up):
        change = 2
        if up:
            change = -2
        self.y += change

        if self.y>MAX_SIZE-self.h:
            self.y = MAX_SIZE-self.h
        if self.y<0:
            self.y = 0

    def bounce(self, ball):
        if (engine.RectIntersect(self.x, self.y, self.w, self.h, ball.x, ball.y, ball.size, ball.size)):
            ball.dx*=-1


class Ball:
    size = 10

    def __init__(self):
        self.x = MAX_SIZE//2 - self.size//2
        self.y = MAX_SIZE//2 - self.size//2
        self.dx = (random.randint(1,2) * 2 - 3)
        self.dy = (random.randint(1,2) * 2 - 3)

    def draw(self):
        engine.SetColor(255, 0, 0, 255);
        engine.DrawRectangle(self.x,self.y,self.size,self.size,True);

    def tick(self):
        self.x += self.dx
        self.y += self.dy

        if self.y>MAX_SIZE-self.size:
            self.y = MAX_SIZE-self.size
            self.dy*=-1
        if self.y<0:
            self.y = 0
            self.dy*=-1
        if self.x>MAX_SIZE-self.size:
            self.x = MAX_SIZE-self.size
            engine.delay(1000)
            self.__init__()
        if self.x<0:
            self.x = 0
            engine.delay(1000)
            self.__init__()


p1 = Paddle(20)
p2 = Paddle(370)
ball = Ball()

engine.PlayMusic("music.wav");

print("Setting up game loop")
engine.SetFramerate(90);
while not engine.pressed("q") :
    # Clear the screen
    engine.clear();

    p1.bounce(ball)
    p2.bounce(ball)
    ball.tick()

    if engine.pressed("space"):
        engine.PlaySFX("break.wav");
    if engine.pressed("tab") or engine.pressed("l_shift"):
        p1.move(engine.pressed("tab"))
    if engine.pressed("i") or engine.pressed("k"):
        p2.move(engine.pressed("i"))

    engine.SetTextColor(255, 0, 0, 255);
    engine.RenderText("Hello World!", "arial.ttf", 32, 100, 100)

    p1.draw()
    p2.draw()
    ball.draw()

    # Add a little delay
    engine.FrameRateDelay();
    # Refresh the screen
    engine.flip();
