# Lab 3 - Allegro Mouse Click Interaction

This repository contains my Lab 3 project for CPSC 440 Game Programming.

## Description

This program uses Allegro in Visual Studio to draw an object at the center of the screen. When the user clicks the mouse, the object moves to the clicked location and the mouse x/y coordinates are displayed on the screen.

The background color and text color change depending on which quadrant of the screen is clicked.

## Quadrant Behavior

- Upper-left quadrant: white background, black text
- Upper-right quadrant: black background, white text
- Lower-left quadrant: blue background, yellow text
- Lower-right quadrant: yellow background, blue text

## Features

- Uses Allegro primitives to draw the object
- Uses mouse input with an event queue
- Moves the object to the clicked mouse location
- Displays the mouse x/y coordinates on screen
- Changes background and text color based on the clicked quadrant

## How to Run

1. Open the `.sln` file in Visual Studio.
2. Make sure Allegro is installed through NuGet.
3. Make sure the required Allegro add-ons are enabled:
   - Primitives Addon
   - Font Addon
4. Set the project as the Startup Project.
5. Run the program using Local Windows Debugger.
6. Click in different quadrants of the screen to test the color changes and object movement.

## Author

Christian Toliver
