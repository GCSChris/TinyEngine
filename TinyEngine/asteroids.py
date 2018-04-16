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
    shapePoints = [(-7, 13), (-5, 8), (2, 10), (1, -2), (-13, -5)]
    activeState = True
    velocity = (0, 0)
    centerPoint = (0, 0)

    def __init__(self, center, angle, shapePoints):
        self.centerPoint = center
        self.shapePoints = shapePoints
        self.velocity = (math.cos(degreeToRadians(angle)), -math.sin(degreeToRadians(angle)))

    def tick(self):
        if self.activeState:
            self.centerPoint = tinymath.TranslatePoint(self.centerPoint, self.velocity)
            tinymath.TranslatePoint(self.centerPoint, self.velocity)
            self.bounce()

    def bounce(self):
        leftCollision = False
        rightCollision = False
        topCollision = False
        bottomCollision = False

        for point in self.getPoints():
            if point[0] < 0 and not leftCollision:
                self.velocity = (-1 * self.velocity[0], self.velocity[1])
                leftCollision = True
            if point[0] > MAX_SIZE and not rightCollision:
                self.velocity = (-1 * self.velocity[0], self.velocity[1])
                rightCollision = True
            if point[1] < 0 and not topCollision:
                self.velocity = (self.velocity[0], -1 * self.velocity[1])
                topCollision = True
            if point[1] > MAX_SIZE and not bottomCollision:
                self.velocity = (self.velocity[0], -1 * self.velocity[1])
                bottomCollision = True

    def draw(self):
        if self.activeState:
            engine.SetColor(255, 255, 255, 255)
            engine.DrawLines(self.getPoints(), True)

    def getPoints(self):
        if not self.activeState:
            return []
        return tinymath.TranslatePoints(self.shapePoints, self.centerPoint)

    def isActive(self):
        return self.activeState

    def setActive(self, activeState):
        self.activeState = activeState


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
        for asteroid in asteroids:
            if engine.ShapeIntersect(self.getPoints(), asteroid.getPoints()):
                engine.PlaySFX("resources/Explosion.wav")
                asteroid.setActive(False)
                return True
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
        self.currentPoints = tinymath.RotatePointsAround(self.basePoints, self.currentPoints[1], self.rotation);

    def draw(self):
        engine.SetColor(255, 255, 255, 255)
        engine.DrawLines(self.currentPoints, True)

    def fireBullet(self):
        return Bullet(self.currentPoints[3], self.rotation)

    def checkCollisions(self, asteroids):
        for asteroid in asteroids:
            if engine.ShapeIntersect(self.currentPoints, asteroid.getPoints()):
                engine.PlaySFX("resources/Explosion.wav")
                return True
        return False

ship = Ship(0)
bullet = False
asteroidShapes = [
[(-7, 0), (-4, 4), (0, 7), (2, 4), (7, 0), (4, -4), (0, -7), (-4, -4)],
[(-5, 0), (-3, 5), (0, 2), (3, 5), (5, 0), (3, -5), (0, -2), (-3, -5)],
[(-8, 0), (-3, 7), (0, 6), (4, 7), (10, 0), (5, -5), (-3, -5), (-6, -1)],
[(-7, 13), (-5, 8), (2, 10), (1, -2), (-13, -5)]
]
asteroids = [
Asteroid((100, 150), 70, asteroidShapes[0]),
Asteroid((250, 125), 35,  asteroidShapes[1]),
Asteroid((375, 200), -120,  asteroidShapes[2]),
Asteroid((100, 360), -25,  asteroidShapes[3]),
Asteroid((175, 100), 254,  asteroidShapes[0]),
Asteroid((25, 30), 176,  asteroidShapes[1]),
Asteroid((75, 180), 254,  asteroidShapes[2]),
Asteroid((325, 15), 176,  asteroidShapes[3])
]
gameWon = False
gameOver = False
bulletDelay = 0

# END DEFINITIONS, GAME LOOP HERE

# Music from https://opengameart.org/content/space-music-out-there
# SFX from https://opengameart.org/content/sfx-the-ultimate-2017-8-bit-mini-pack
engine.PlayMusic("resources/OutThere.wav")

engine.SetBackgroundColor(0, 0, 0, 255)
engine.SetFramerate(30)
while not engine.pressed("q") :
    # Clear the screen
    engine.clear()

    if not gameOver and not gameWon:
        for asteroid in asteroids:
            asteroid.draw()
        ship.draw()
        if bullet:
            bullet.draw()

        bulletDelay = bulletDelay - 1

        if engine.pressed("a"):
            ship.rotate(10)
        if engine.pressed("d"):
            ship.rotate(-10)
        if engine.pressed("space") and not bullet and bulletDelay <= 0:
            bulletDelay = 30
            engine.PlaySFX("resources/Pew.wav")
            bullet = ship.fireBullet()

        # TODO move the asteroids
        for asteroid in asteroids:
            asteroid.tick()
        if bullet:
            bullet.tick()
            if bullet.checkCollisions(asteroids):
                bullet = False

        if ship.checkCollisions(asteroids):
            gameOver = True

        gameWon = True
        for asteroid in asteroids:
            isActive = asteroid.isActive()
            if isActive:
                gameWon = False


    if gameWon:
        engine.RenderCenteredText("You Win!", "resources/arial.ttf", 40, int(MAX_SIZE/2 - 20))

    if not gameWon and gameOver:
        engine.RenderCenteredText("Game Over", "resources/arial.ttf", 40, int(MAX_SIZE/2 - 20))

    # Add a little delay
    engine.FrameRateDelay()
    # Refresh the screen
    engine.flip()
