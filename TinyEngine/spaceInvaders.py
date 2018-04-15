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
playerOffset = 32

engine = mygameengine.SDLGraphicsProgram(MAX_SIZE,MAX_SIZE)

class Player:
    w = 16
    h = 16
    x = 0;
    y = 0;

    def __init__(self):
        self.x =  MAX_SIZE // 2
        self.y = MAX_SIZE - playerOffset;

    def draw(self):
        engine.DrawImage("sprites/spaceInvader_player.png", self.x, self.y, self.w, self.h);
    
    def move(self, moveAmount):
        if (self.x + moveAmount > 0 and self.x + moveAmount + self.w < MAX_SIZE):
            self.x = self.x + moveAmount


class Enemy:
    w = 16
    h = 16
    enabled = True
    
    def __init__(self, x, y):
        self.x = x
        self.y = y
        
    def draw(self):
        if self.enabled:
            engine.DrawImage("sprites/spaceInvader.png", self.x, self.y, self.w, self.h);
        
    def move(self, moveAmount):
        if self.enabled:
            if (self.x + moveAmount > 0 and self.x + moveAmount + self.w < MAX_SIZE):
                self.x = self.x + moveAmount
            
    def moveDownRow(self, moveAmount):
        if self.enabled:
            if self.y + moveAmount < MAX_SIZE - playerOffset:
                self.y += moveAmount
                return False
            else:
                self.disable()
                return True
            
    def disable(self):
        self.enabled = False

class Projectile:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.w = 2
        self.h = 4
    
    def move(self, speed):
        if (self.y > 0):
            self.y = self.y - speed
            return 0
        else:
            return 1
        
    def draw(self):
        engine.SetColor(255, 255, 255, 255)
        engine.DrawRectangle(self.x, self.y, self.w, self.h, True)

# a 2D array of enemies 
enemyMatrix = [[Enemy(0,0) for x in range(w)] for y in range(h)]

#enemy speed
enemySpeed = 1;

#are enemies moving left?
movingLeft = False

#adds some delay to enemy movement
restFrame = False

#has an enemy hit the bottom?
hitBottom = False

#keeps track of number of enemy shifts
numShifts = 0

#player speed
playerSpeed = 2

#framerate
framerate = 30

#stuff for projectiles
projList = []
projSpeed = 4
projCountdown = 0;

#initialize enemy position
for x in range(0, w):
    for y in range(0, h):
        enemyMatrix[y][x] = Enemy(16 + x*32, 64 + 32*y)

player = Player()

engine.SetFramerate(framerate);
while not engine.pressed("q") and not hitBottom:

    engine.SetBackgroundColor(0, 0, 0, 255)
	
    # Clear the screen
    engine.clear()
    
    #shift enemies left or right as appropriate, and shift down at the end of a row
    if numShifts <= 48 and not restFrame:
        for x in range(0, w):
            for y in range(0, h):
                if movingLeft:
                    enemyMatrix[y][x].move(0 - enemySpeed)
                else:
                    enemyMatrix[y][x].move(enemySpeed)
        numShifts += 1
        restFrame = True
    # it is a rest frame so do nothing
    elif restFrame:
        restFrame = False
    # enemies have reached the edge of the screen so move down a row 
    # and then move back in other direction
    else:
        numShifts = 0
        if movingLeft:
            movingLeft = False
        else:
            movingLeft = True
        for x in range(0, w):
            for y in range(0, h):
                hitBottom = enemyMatrix[y][x].moveDownRow(16)
    
    #draw enemies
    for x in range(0, w):
        for y in range(0, h):
            enemyMatrix[y][x].draw()
     
    # count down projectile counter
    if (projCountdown > 0):
        projCountdown -= 1
     
    #handle player input
    if engine.pressed("left"):
        player.move( 0 - playerSpeed)
    elif engine.pressed("right"):
        player.move(playerSpeed)
    elif engine.pressed("space"):
        if (projCountdown == 0):
            projList.append(Projectile(player.x + player.w // 2, player.y))
            projCountdown = framerate * 3
            
            
    for x in range(len(projList)):
        projList[x].draw()
        if projList[x].move(projSpeed) == 1:
            projList.pop(x)
            x -= 1

    #draw player
    player.draw()

    # Add a little delay
    engine.FrameRateDelay()
    # Refresh the screen
    engine.flip()
    
while not engine.pressed("q"):
    engine.clear()

    engine.SetTextColor(255, 255, 255, 255)
    engine.RenderText("GAME OVER!", "arial.ttf", 20, 150, 200)
    
    engine.flip()
