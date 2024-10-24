#ifndef ROBOT_H
#define ROBOT_H
void forward();
void left();
void right();
int atMarker();
int canMoveForward();
void pickUpMarker();
void dropMarker();
int markerCount();
#endif