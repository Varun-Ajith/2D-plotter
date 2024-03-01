# 2D Plotter Project

This project aims to create a simple 2D plotter using a Raspberry Pi and stepper motors, capable of drawing vector graphics specified in Scalable Vector Graphics (SVG) format.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Setup](#setup)
- [Usage](#usage)
- [Dependencies](#dependencies)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The 2D plotter project utilizes a Raspberry Pi along with stepper motor drivers to control the movement of a pen or drawing instrument on a 2D surface. By parsing SVG files, the plotter can replicate vector graphics drawings on various materials.

## Features

- Parses SVG files to extract drawing instructions.
- Controls stepper motors for precise movement along X and Y axes.
- Includes servo motor control for lifting and lowering the drawing instrument.
- Flexible and customizable for different drawing surfaces and materials.
- Scalable design for potential expansion and additional features.

## Setup

1. **Hardware Setup**: Connect stepper motors and servo motor to the Raspberry Pi GPIO pins according to the pin configuration specified in the script.
2. **Software Setup**: Clone this repository to your Raspberry Pi or download the script file directly.
3. **Install Dependencies**: Ensure that the required Python libraries (`xml.etree.ElementTree`, `RPi.GPIO`) are installed. You can install them using pip:
    ```
    pip install xml.etree.ElementTree RPi.GPIO
    ```
4. **Configure GPIO**: Make sure the GPIO pins used in the script match your hardware configuration.
5. **Calibration**: Calibrate the plotter by adjusting motor steps, servo angles, and other parameters as needed.

## Usage

1. Place your SVG file in the same directory as the script or specify the file path in the script.
2. Run the script using Python:
    ```
    python plotter.py
    ```
3. The plotter will execute the drawing instructions specified in the SVG file.

## Dependencies

- `xml.etree.ElementTree`: For parsing SVG files.
- `RPi.GPIO`: For controlling GPIO pins on the Raspberry Pi.

## Contributing

Contributions to this project are welcome! If you have ideas for improvements, feature requests, or bug reports, please open an issue or submit a pull request.

## Credits
This project was created by Varun Ajith, Bachu James and Ryan Biju Joseph.


