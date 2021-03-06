//By Zack Alfakir

#define DEBUG
//#define BUTTON
#define DRIVE
//#define LEFT_ENCODER
//#define RIGHT_ENCODER
//#define TEST //THIS WILL NEGATE MOST OF MAIN AND JUST CALL test()
//#define ULTRASONIC
#define ULTRASONIC_PARALLEL
//#define ULTRASONIC_FILTER
//#define LOG
//#define PLAYBACK

#include "Tess.h"
#include "simpletools.h"
#include "Distance.c"
#include "DriveTrain.c"
#include "Ports.h"
#include "servo.h"
#include "ping.h"
#include "Logger.c"

int main(void)                    
{
    volatile long int char_count = 0;
    volatile long int* char_count_pointer = &char_count;

    robot_status = ENABLED;
    print("Robot Enabled!\n");

    pause(1000);

    #ifdef TEST
    test(char_count_pointer);
    return 0;
    #endif
    
    #ifdef PLAYBACK //make sure this is before LOG because it will reopen file with write
    logInit();
    playback("Main.txt", LOG_SIZE);
    pause(5000);
    #endif

    #ifdef LOG
    logInit();
    logData("Main.txt", "Hello File World!\n", 0, char_count_pointer);
    #endif

    #ifdef DRIVE
    initDrive();
    #endif

    filter_count = 0;
    counter = 0;
    print("Hello Robot\n");
    low(LED_2);
    low(LED_1);
    
    //distance_parallel();

    while(1)//main loop
    {
        debug("loop\n",0);
        //debug("Loop\n", 0);
        //button();
        navigate();
        //checkDriveTrain();
        //pause(100);   
        counter++; //VERY IMPORTANT
    }
    
    print("Robot disabled!\n");
}
void test(volatile long int* char_count)
{
    *char_count = 5;
    print("char_count = %d\n", (int)*char_count);
    logInit();
    logData("Main.txt", "This is a Test! %i \n", (int)char_count, char_count);
    
    //playback("Main.txt", 50);
    pause(5000);
    print("Finished!\n");
}
char* debug(char *string, int data)
{
    char asdf[128];
    #ifdef DEBUG
    if (counter % count_const == 0)
    {        
        sprintf(asdf,string,data);
        print(asdf);
    }
    #endif
    return *asdf;
}

void navigate()
{
    extern enum driveState tess_drive_state;
    tess_ping = ping_cm(ULTRASONIC_PIN);
    debug("Distance = %i\n", tess_ping);
    if (tess_ping == 0 && tess_drive_state != IDLE)
    {
        tess_drive_state = IDLE;
        debug("Ultrasonic Error!\n", 0);
        setServo(0,0,"Error: in void navigate()\n");
    }
    else
    {    
        if (tess_ping < OBJECT_DISTANCE && tess_drive_state != TURNING)
        {
            //TODO stop and turn
            stop();
            debug("Turning on LED!\n", 0);
            high(LED_1);
            debug("About to turn!\n", 0);
            turn(LEFT); //enum from drivetrain
        }
        else if(tess_ping >= OBJECT_DISTANCE && tess_drive_state != MOVING)
        {
            driveForward(-1);
            low(LED_1);
        }
    }
}
void button()
{
    #ifdef BUTTON
    if (input(BUTTON) > 0)
    {
        high(LED_2);
    }
    else
    {
        low(LED_2);
    }
    #endif
}
