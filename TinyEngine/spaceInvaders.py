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

MAX_SIZE = 800
engine = mygameengine.SDLGraphicsProgram(MAX_SIZE,MAX_SIZE)

class Player:
    w = 16
    h = 16
    x = 0;
    y = 0;

    def __init__(self):
        self.x =  MAX_SIZE // 2
        self.y = 32;

    def draw(self):
        # engine.SetColor(255, 255, 255, 255);
        # engine.DrawRectangle(self.x,self.y,self.w,self.h,True);
        engine.DrawImage("sprites/spaceInvader_player.png", self.x, self.y, self.w, self.h);


class Enemy:
    def __init__(self, x, y):
        self.x = x
        self.y = y

#class Projectile:
#    def __init__(self):

player = Player()

print("Setting up game loop")
engine.SetFramerate(90);
while not engine.pressed("q") :
    # Clear the screen
    engine.clear();

    player.draw();

    # Add a little delay
    engine.FrameRateDelay();
    # Refresh the screen
    engine.flip();
