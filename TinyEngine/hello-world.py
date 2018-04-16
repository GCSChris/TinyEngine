import mygameengine

SCREEN_WIDTH = 500
SCREEN_HEIGHT = 500

engine = mygameengine.SDLGraphicsProgram(SCREEN_WIDTH, SCREEN_HEIGHT)

class Rocket: # Static images!
    def draw():
        w = 32
        h = 64

        x = SCREEN_WIDTH // 5;
        y = SCREEN_HEIGHT // 5;

        engine.DrawImage("rocket.png", x, y, w, h);

class Braid: # Animated Sprites!

    def draw():
        x = 0
        y = 0
        w = 130
        h = 150
        engine.DrawFrame("braid.png", frameTick, 27, x, y, w, h);

# --------------------------
# class BouncingBall:
    # def draw(self):
        # engine.SetColor(255, 145, 145, 255);
        # engine.DrawRectangle(0, SCREEN_HEIGHT - GROUND_HEIGHT, SCREEN_WIDTH, GROUND_HEIGHT, True);

FRAMERATE = 60;
frameTick = 0;
engine.SetFramerate(FRAMERATE);
# engine.PlayMusic("music.wav");

def endGameLoop(frameTick):
    # Add a little delay
    engine.FrameRateDelay();

    frameTick = (frameTick + 1);
    if (frameTick >= FRAMERATE):
        frameTick = 0;

    return frameTick;

engine.SetBackgroundColor(255, 255, 255, 255);

while not engine.pressed("q"):
    # Clear the screen
    engine.clear();

    engine.SetTextColor(0, 0, 0, 255);
    engine.RenderCenteredText("WELCOME TO TINY ENGINE!", "arial.ttf", 12, SCREEN_HEIGHT);

    if engine.pressed("space"):
        # engine.PlaySFX TODO
        print("playSFX");


    Rocket.draw();
    Braid.draw();

    frameTick = endGameLoop(frameTick);

    # Refresh the screen
    engine.flip();
