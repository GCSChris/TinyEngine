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
import tinymath
import math

# Now use some python libraries for random numbers!
import random

MAX_SIZE = 400
engine = mygameengine.SDLGraphicsProgram(MAX_SIZE,MAX_SIZE)

def degreeToRadians(deg):
    return deg * 3.14159265 / 180

class Asteroid:
    points = []
    isActive = True
    velocity = (0, 0)

    def __init__(self, points, speed):
        print("make asteroid UwU")
        # TODO generate random velocity based on speed

    def tick(self):
        if self.isActive:
            self.points = tinymath.translatePoints(self.points, tinymath.Vector2D(self.velocity[0], self.velocity[1]))

    def draw(self):
        if self.isActive:
            engine.SDL_SetRenderDrawColor(255, 255, 255, 255)
            engine.DrawLines(self.points, True)

    def getPoints(self):
        return self.points

    def isActive(self):
        return self.isActive

    def setPoints(self, newPoints):
        self.points = newPoints

    def setActive(self, activeState):
        self.isActive = activeState


class Bullet:
    angle = 0
    magnitude = 10
    speed = 3
    origin = (0,0)

    def __init__(self, point, rotation):
        self.angle = rotation
        self.origin = point

    def getPoints(self):
        rads = degreeToRadians(self.angle)
        endX = self.magnitude * math.cos(rads) + self.origin[0]
        endY = self.magnitude * math.sin(rads) + self.origin[1]
        return [self.origin, (endX, endY)]

    def tick(self):
        rads = degreeToRadians(self.angle)
        newX = self.speed * math.cos(rads) + self.origin[0]
        newY = self.speed * math.sin(rads) + self.origin[1]
        self.origin = (newX, newY)

    def draw(self):
        engine.SetColor(255, 255, 255, 255)
        engine.DrawLines(self.getPoints(), False)

    def checkCollisions(self, asteroids):
        # if out of bounds
        if (0 >= self.origin[0] or self.origin[0] >= MAX_SIZE or 0 >= self.origin[1] or self.origin[1] >= MAX_SIZE):
            return True
        # TODO check collision with all the asteroids in the asteroids list, if colliding, set inactive and return True
        return False

class Ship:
    basePoints = [(195, 195), (200, 200), (195, 205), (210, 200)]
    currentPoints = [(195, 195), (200, 200), (195, 205), (210, 200)]
    center = (200, 200)
    rotation = 0 # facing right

    def __init__(self, rot):
        self.rotation = rot
        self.currentPoints = tinymath.RotatePoints(self.basePoints, self.rotation);

    def rotate(self, rot):
        self.rotation += rot;
        rotationVector = tinymath.Vector2D(self.currentPoints[1][0], self.currentPoints[1][1])
        self.currentPoints = tinymath.RotatePointsAround(self.basePoints, rotationVector, self.rotation);

    def draw(self):
        engine.SetColor(255, 255, 255, 255)
        engine.DrawLines(self.currentPoints, True)

    def fireBullet(self):
        return Bullet(self.currentPoints[3], self.rotation)

    def checkCollisions(self, asteroids):
        # TODO check collisions with asteroids
        return False

ship = Ship(0)
bullet = False
# TODO make asteroids
asteroids = []

gameWon = False
gameOver = False

# END DEFINITIONS, GAME LOOP HERE

# Music from https://opengameart.org/content/space-music-out-there
# SFX from https://opengameart.org/content/sfx-the-ultimate-2017-8-bit-mini-pack
engine.PlayMusic("resources/OutThere.wav")

engine.SetBackgroundColor(0, 0, 0, 255)
engine.SetFramerate(30)
while not engine.pressed("q") :
    # Clear the screen
    engine.clear()

    # TODO draw the asteroids
    ship.draw()
    if bullet:
        bullet.draw()

    if not gameOver and not gameWon:
        if engine.pressed("a"):
            ship.rotate(10)
        if engine.pressed("d"):
            ship.rotate(-10)
        if engine.pressed("space") and not bullet:
            engine.PlaySFX("resources/Pew.wav")
            bullet = ship.fireBullet()

        # TODO move the asteroids
        if bullet:
            bullet.tick()
            if bullet.checkCollisions(asteroids):
                bullet = False

        if ship.checkCollisions(asteroids):
            gameOver = True

        #TODO check if any asteroids still alive


    if gameWon:
        print("game won")
        # TODO draw game won text

    if not gameWon and gameOver:
        print("game over")
        # TODO draw game over text

    # Add a little delay
    engine.FrameRateDelay()
    # Refresh the screen
    engine.flip()
