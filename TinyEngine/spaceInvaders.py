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

w, h = 11, 5;
MAX_SIZE = 32 * (w + 2)
engine = mygameengine.SDLGraphicsProgram(MAX_SIZE,MAX_SIZE)

class Player:
    w = 16
    h = 16
    x = 0;
    y = 0;

    def __init__(self):
        self.x =  MAX_SIZE // 2
        self.y = MAX_SIZE - 32;

    def draw(self):
        engine.DrawImage("sprites/spaceInvader_player.png", self.x, self.y, self.w, self.h);
    
    # def move(self, 


class Enemy:
    w = 16
    h = 16
    
    def __init__(self, x, y):
        self.x = x
        self.y = y
        
    def draw(self):
        engine.DrawImage("sprites/spaceInvader.png", self.x, self.y, self.w, self.h);

#class Projectile:
#    def __init__(self):


enemyMatrix = [[Enemy(0,0) for x in range(w)] for y in range(h)]

for x in range(0, w):
    for y in range(0, h):
        enemyMatrix[y][x] = Enemy(16 + x*32, 64 + 32*y)

player = Player()

print("Setting up game loop")
engine.SetFramerate(90);
while not engine.pressed("q") :

    engine.SetBackgroundColor(0, 0, 0, 255)
	
    # Clear the screen
    engine.clear();
    
    for x in range(0, w):
        for y in range(0, h):
            enemyMatrix[y][x].draw();

    player.draw();

    # Add a little delay
    engine.FrameRateDelay();
    # Refresh the screen
    engine.flip();
