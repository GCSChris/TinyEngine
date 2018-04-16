# Run with:
#
# (Linux & Mac) python3.5 test.py -m ./mygameengine.so
# (Windows) python3.6 test.py -m ./mygameengine.pyd
#
# The program should also run with 'python2.7' but you will have
# to change the 3.5's to 2.7's in your respective build script as
# well as make sure you compiled with 3.5 or 2.7 load flags.

import mygameengine

w, h = 11, 5;
MAX_SIZE = 32 * (w + 4)
playerOffset = 32

engine = mygameengine.SDLGraphicsProgram(MAX_SIZE,MAX_SIZE,"SPACE INVADERS")

class Player:
    w = 16
    h = 16
    x = 0;
    y = 0;

    def __init__(self):
        self.x =  MAX_SIZE // 2
        self.y = MAX_SIZE - playerOffset;

    def draw(self):
        engine.DrawImage("resources/space-invaders/space-invader-player.png", self.x, self.y, self.w, self.h);

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
            engine.DrawImage("resources/space-invaders/space-invader.png", self.x, self.y, self.w, self.h);

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
        else:
            return False

    def disable(self):
        self.enabled = False
        engine.PlaySFX("resources/space-invaders/hit.mp3")

class Projectile:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.w = 2
        self.h = 4
        engine.PlaySFX("resources/space-invaders/fire.mp3")

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
enemySpeed = 2;

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
projSpeed = 4
projectile = None

#stuff for score
score = 0
scoreMultiplier = 100
maxScore = w * h * 100

#initialize enemy position
for x in range(0, w):
    for y in range(0, h):
        enemyMatrix[y][x] = Enemy(16 + x*32, 32 + 32*y)

player = Player()

won = False

engine.SetFramerate(framerate);
while not engine.pressed("q") and not hitBottom and not won:

    engine.SetBackgroundColor(0, 0, 0, 255)

    # Clear the screen
    engine.clear()

    #shift enemies left or right as appropriate, and shift down at the end of a row
    if numShifts <= 56 and not restFrame:
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

    #handle player input
    if engine.pressed("left"):
        player.move(0 - playerSpeed)
    elif engine.pressed("right"):
        player.move(playerSpeed)
    elif engine.pressed("space") and projectile == None:
        projectile = Projectile(player.x + player.w // 2 - 1, player.y)

    if (projectile != None):
        projectile.draw()
        if projectile.move(projSpeed) == 1:
            projectile = None
        else:
            # handle projectile collisions with enemies here
            for x in range(0, w):
                for y in range(0, h):
                    if (enemyMatrix[y][x].enabled and engine.RectIntersect(enemyMatrix[y][x].x,
                    enemyMatrix[y][x].y, enemyMatrix[y][x].w, enemyMatrix[y][x].h, projectile.x,
                    projectile.y, projectile.w, projectile.h)):
                        score += scoreMultiplier
                        enemyMatrix[y][x].disable()

    #draw player
    player.draw()

    #draw score
    engine.SetTextColor(255, 255, 255, 255)
    engine.RenderText("score: " + str(score), "resources/space-invaders/arial.ttf", 15, 10, 10)

    #check endgame
    if (score == maxScore):
        won = True

    # Add a little delay
    engine.FrameRateDelay()
    # Refresh the screen
    engine.flip()

while won and not engine.pressed("q"):
    engine.clear()

    engine.SetTextColor(255, 255, 255, 255)
    engine.RenderText("YOU WIN!!!", "arial.ttf", 25, 150, 200)

    engine.flip()

while not won and not engine.pressed("q"):
    engine.clear()

    engine.SetTextColor(255, 255, 255, 255)
    engine.RenderText("GAME OVER!", "arial.ttf", 20, 150, 200)

    engine.flip()
