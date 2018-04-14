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

class Ship:
    basePoints = [(195, 195), (200, 200), (195, 205), (210, 200)]
    currentPoints = [(195, 195), (200, 200), (195, 205), (210, 200)]
    center = (200, 200)
    rotation = 0 # facing right

    def __init__(self, rot):
        self.rotation = rot
        self.currentPoints = tinymath.RotatePoints(self.basePoints, self.rotation);

    # def getPointsList(self):
    #     tailLength = 10
    #     noseLength = 15
    #     tailAngle = 45
    #
    #     tail1 = (self.center[0] - (tailLength * math.cos(degreeToRadians(self.rotation + tailAngle))), self.center[1] - (tailLength * math.sin(degreeToRadians(self.rotation + tailAngle))))
    #     tail2 = (self.center[0] - (tailLength * math.cos(degreeToRadians(self.rotation - tailAngle))), self.center[1] - (tailLength * math.sin(degreeToRadians(self.rotation - tailAngle))))
    #     nose = (self.center[0] + (noseLength * math.cos(degreeToRadians(self.rotation))), self.center[1] + (noseLength * math.sin(degreeToRadians(self.rotation))))
    #
    #     tail1 = (math.floor(tail1[0]), math.floor(tail1[1]))
    #     tail2 = (math.floor(tail2[0]), math.floor(tail2[1]))
    #     nose = (math.floor(nose[0]), math.floor(nose[1]))
    #
    #     pointsList = [tail1, self.center, tail2, nose]
    #     return pointsList

    def rotate(self, rot):
        self.rotation += rot;
        rotationVector = tinymath.Vector2D(self.currentPoints[1][0], self.currentPoints[1][1])
        self.currentPoints = tinymath.RotatePointsAround(self.basePoints, rotationVector, self.rotation);

    def draw(self):
        engine.SetColor(255, 255, 255, 255)
        engine.DrawLines(self.currentPoints, True)

ship = Ship(0)

# END DEFINITIONS, GAME LOOP HERE

# Music from https://opengameart.org/content/space-music-out-there
engine.PlayMusic("resources/OutThere.wav");

engine.SetBackgroundColor(0, 0, 0, 255)
engine.SetFramerate(30)
while not engine.pressed("q") :
    # Clear the screen
    engine.clear();

    ship.draw();

    if engine.pressed("a"):
        ship.rotate(10);
    if engine.pressed("d"):
        ship.rotate(-10);

    # Add a little delay
    engine.FrameRateDelay();
    # Refresh the screen
    engine.flip();
