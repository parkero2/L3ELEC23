/**
 * @brief This is the main file for the Mars Rover project for my L3ELEC course.
 * @details This file contains the main code for the Mars Rover project. The rover is guided by a GPS module to determine it's position. I don't think Mars has satelite coverage, so I'm not sure how this will work in production.
 * 
 * @note the forward() or backward() functions must be called before utilising or calling the changeSpeed() function
 * 
 * @author Oliver Parker (@parkero2)
 */

int leftForward = 3, leftBackward = 4, rightForward = 9, rightBackward = 10;

int lsp, rsp;
bool current_dir; // 0 = forward, 1 = backward

void forward()
{
    analogWrite(leftForward, lsp);
    analogWrite(rightForward, rsp);
    digitalWrite(leftBackward, LOW);
    digitalWrite(rightBackward, LOW);
    current_dir = 0;
}

void backward()
{
    analogWrite(leftBackward, lsp);
    analogWrite(rightBackward, rsp);
    digitalWrite(leftForward, LOW);
    digitalWrite(rightForward, LOW);
    current_dir = 1;
}

void changeSpeed(int l, int r)
{
    //Ensure that the direction is set, otherwise discard values and throw an error
    if (current_dir == NULL)
    {
        throw "No direction set";
    }
    // Discard negative values
    lsp = abs(l) > 255 ? 255 : abs(l);
    rsp = abs(r) > 255 ? 255 : abs(r);
    //Check if direction is forward or backward
    if (current_dir)
    {
        backward();
        return;
    }
    //No need for else statement, the return statment has handled all other cases
    forward();
}

void setup()
{
    // put your setup code here, to run once:
    pinMode(leftForward, OUTPUT);
    pinMode(leftBackward, OUTPUT);
    pinMode(rightForward, OUTPUT);
    pinMode(rightBackward, OUTPUT);
}

void loop()
{
}