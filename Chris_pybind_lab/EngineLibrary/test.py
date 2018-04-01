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

windowX = 400;
windowY = 400;

class Ball:
    x = 200;
    y = 240;
    w = 10;
    h = 10;
    vx = 2;
    vy = 1;

class Paddle:
    x = 0
    y = 0
    w = 10
    h = 100	

#START INIT
test = mygameengine.SDLGraphicsProgram(windowX, windowY);
print("Setting up game loop")

quit = False;
ball = Ball();

leftPaddle = Paddle();
leftPaddle.x = 5;
leftPaddle.y = 5;

rightPaddle = Paddle();
rightPaddle.x = windowX - (rightPaddle.w + 5);
rightPaddle.y = 5;

#END INIT

def updateBall():
    bounceOffLeftPaddle = checkOverlap(leftPaddle, ball);
    bounceOffRightPaddle = checkOverlap(rightPaddle, ball);
        
    if (ball.x <= 0 or windowX <= (ball.x + ball.w)):
        ball.vx = -1 * ball.vx;
		
    bouncePaddle = bounceOffLeftPaddle or bounceOffRightPaddle;
    if bouncePaddle:
        ball.vx = -1 * ball.vx;
    
    if (ball.y <= 0 or windowY <= (ball.y + ball.h)):
        ball.vy = -1 * ball.vy;
	
    ball.x += ball.vx
    ball.y += ball.vy
    return;

def renderRects(left, right, ball):
    test.FillRectangle(left.x, left.y, left.w, left.h, 255, 255, 255, 255);
    test.FillRectangle(right.x, right.y, right.w, right.h, 255, 255, 255, 255);
    test.FillRectangle(ball.x, ball.y, ball.w, ball.h, 255, 0, 0, 0);
    return;

def handleEvents():
    #print("handle events");
    keyPressed = test.PollEvent();
    
    if (keyPressed == 1):
        global quit;
        quit = True;
	
    #move left paddle up
    if (keyPressed == 2):
        leftPaddle.y -= 20;
    #move left paddle down
    if (keyPressed == 3):
        leftPaddle.y += 20;
		
	#move left paddle up
    if (keyPressed == 4):
        rightPaddle.y -= 20;
    #move left paddle down
    if (keyPressed == 5):
        rightPaddle.y += 20;
    
    return;
	
def checkOverlap(left, ball):
    leftPaddleTopLeftX = left.x
    leftPaddleTopLeftY = left.y

    leftPaddleBottomRightX = left.x + left.w;
    leftPaddleBottomRightY = left.y + left.h;
	
    ballTopLeftX = ball.x
    ballTopLeftY = ball.y

    ballBottomRightX = ball.x + ball.w;
    ballBottomRightY = ball.y + ball.h;
	
    if (ballTopLeftX > leftPaddleBottomRightX or leftPaddleTopLeftX > ballBottomRightX):
        return False;
    
    if (ballTopLeftY > leftPaddleBottomRightY or leftPaddleTopLeftY > ballBottomRightY):
        return False;
	
    return True;

while (not quit):
    # Clear the screen
    test.clear();
	
    handleEvents();

    updateBall();

    renderRects(leftPaddle, rightPaddle, ball);

    # Add a little delay
    test.delay(10);
    # Refresh the screen
    test.flip();

