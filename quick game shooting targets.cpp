#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

/// This code has been written to simulate a ball shot from a sling into a target.
/// The purpose of the code is to show familiarity and skills in C++ for application of Vehicle Physics Programmer.
/// The game randomly generates a target to shoot at and then asks for the angle (degrees) at which the boll is shot and the Energy used to launch it.
/// The code then simulates the path that the ball has taken and outputs whether it has hit the target or not. The path is simulated in only 30x30 matrix therefore
/// The path is not exactly accurate, but the physics are accurate down to set [dt] time



void print_map (char image[31][31]) ///prints out the map
{
    for (int y = 9; y>=0; y--)
    {
        for(int x = 0; x<30; x++)
        {
            cout<<image[y][x]; //printing out the image of the game
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void blank (char image[31][31]) ///resets the map to empty
{
    for (int y = 29; y>=0; y--)
    {
        for(int x = 0; x<30; x++)
        {
            image[y][x] = ' '; //Making the map blank again
        }
    }
}
int main()
{

    int target_position_x; // where on the x grid the target is (in metres [m])
    int target_position_y; // where on the y grid the target is (in metres [m])
    int angle; // at what angle the string is pulled back (degrees)
    float strength; //how much energy is used to pull back the string (Joules [J])
    float g = 9.81; //(gravitational pull [m/s^2])
    bool success = false; //game ending bool
    bool flight = false; //bool to stop time if the throw was unsuccessful
    float t = 0; //time [s]
    float dt = 0.01; //time step [s]
    float ball_x = 0; //x position of the ball [m]
    float ball_y = 0; //y position of the ball [m]
    int mass = 1; // mass of the ball, set to 1 [kg]
    char image [31][31] = {};// creating the image to show
    int x_temp = 0;//temporary integer for x value
    int y_temp = 0;//temporary integer for y value
    char game = 'y'; //char for starting a new game
    char structure = 'y'; //char for keeping same generated structure

    while(game == 'y')
    {
        srand (time(NULL)); // initialize random seed

        target_position_x = rand() % 29 + 1; //setting up the x position of the target target (distance to target horizontally) from 0 to 29 m (will be from 1 to 30 in code)

        srand (time(NULL)); // making sure x and y values are not the same all the time (resetting random function)

        target_position_y = rand() % 9 + 1; //setting up the y position of the target target (distance to target vertically) from 0 to 9 m

        image[0][0] = 'Y';//initial position the ball is shot from

        image[target_position_y][target_position_x] = 'O';//position of the target we are shooting at

        print_map(image); //printing the current image

        while(success == false)
        {
            cout<<"the target is "<<target_position_x<<" metres away and "<<target_position_y<<" metres above ground\n";
            cout<<"\n";
            cout<< "At what angle was the ball shot? (0 to 90 degrees)" << "\n";
            cin >> angle; //insert angle value

            cout<< "How strongly was the string pulled back?(suggestion: 100)" << "\n";
            cin >> strength; //Insert strength (in Joules) that the sling was pulled back

            t = 0;
            flight = false;
            while(flight == false)
            {
                t = t + dt; //updating time every dt [s]

                ball_x = cos (angle*3.1415/180)*sqrt(2*strength/mass)*t; //Calculating the x position of the ball at given moment t
                ball_x = cos (angle*3.1415/180)*sqrt(2*strength/mass)*t; //Calculating the x position of the ball at given moment t
                ball_y = sin (angle*3.1415/180)*sqrt(2*strength/mass)*t - g*t*t/2; //Calculating the y position of the ball at given moment t

                x_temp = ball_x/1; //current x position of the ball (ignoring remainder)
                y_temp = ball_y/1; //current y position of the ball (ignoring remainder)

                image[y_temp][x_temp] = '`'; //marking the travel path

                if (ball_x >= 30 || ball_x <=0)
                {
                    image[0][0] = 'Y';//resetting initial position the ball is shot from
                    image[target_position_y][target_position_x] = 'O';//resetting position of the target we are shooting at

                    print_map(image); //printing the current image

                    cout <<"shot was unsuccessful - went out of bounds, please try again with new angle and/or strength:\n\n";
                    flight = true;

                    blank(image); //Making the image empty

                    image[0][0] = 'Y'; //resetting initial position the ball is shot from
                    image[target_position_y][target_position_x] = 'O';//resetting position of the target we are shooting at

                }
                else
                {
                    if(ball_y < 0)
                    {

                        image[0][0] = 'Y';//resetting initial position the ball is shot from
                        image[target_position_y][target_position_x] = 'O';//resetting position of the target we are shooting at

                        print_map(image); //printing the current image

                        cout <<"shot was unsuccessful - went to the ground, please try again with new angle and/or strength:\n\n";
                        flight = true;
                        //now creating empty horizon again:
                        blank(image); //Making the image empty

                        image[0][0] = 'Y';//resetting initial position the ball is shot from
                        image[target_position_y][target_position_x] = 'O';//resetting position of the target we are shooting at
                    }
                    else
                    {

                        if(ball_y/target_position_y > 0.95 && ball_y/target_position_y < 1.05 )
                        {
                            if(ball_x/target_position_x > 0.95 && ball_x/target_position_x < 1.05 )
                            {
                                flight = true;
                                success = true;
                                image[0][0] = 'Y';//resetting initial position the ball is shot from
                                image[target_position_y][target_position_x] = 'O';//resetting position of the target we are shooting at

                                print_map(image); //printing the current image

                                cout<<" Well done, you have won!\n";
                                cout<<" Do you want to start a new game? If yes type 'y', if no type 'n' \n";
                                cin>> game;
                                if(game == 'y')
                                {
                                    success = false;
                                    cout<< "do you want to play with the same structure? If yes type 'y', if no type 'n' \n";
                                    cin>>structure;

                                    blank(image); //Making the image empty

                                    if (structure == 'n')
                                    {
                                        srand (time(NULL)); // initialize random seed

                                        target_position_x = rand() % 29 + 1; //setting up the x position of the target target (distance to target horizontally) from 0 to 29 m (will be from 1 to 30 in code)

                                        srand (time(NULL)); // making sure x and y values are not the same all the time (resetting random function)

                                        target_position_y = rand() % 9 + 1; //setting up the y position of the target target (distance to target vertically) from 0 to 9 m

                                        image[0][0] = 'Y';//initial position the ball is shot from

                                        image[target_position_y][target_position_x] = 'O';//position of the target we are shooting at

                                        print_map(image); //printing the current image
                                        cout<<"\n";
                                    }
                                    else
                                    {
                                        image[0][0] = 'Y';//resetting initial position the ball is shot from
                                        image[target_position_y][target_position_x] = 'O';//resetting position of the target we are shooting at
                                        print_map(image); //printing the current image
                                        cout<<"\n";
                                    }
                                }
                            }
                        }

                    }
                }
            }
        }

    }

    return 0;
}
