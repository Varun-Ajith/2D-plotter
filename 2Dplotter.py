import xml.etree.ElementTree as ET
import RPi.GPIO as GPIO
import time

X_STEP_PIN = 17
X_DIR_PIN = 27
Y_STEP_PIN = 23
Y_DIR_PIN = 24

SERVO_PIN = 18

# Initialize GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(X_STEP_PIN, GPIO.OUT)
GPIO.setup(X_DIR_PIN, GPIO.OUT)
GPIO.setup(Y_STEP_PIN, GPIO.OUT)
GPIO.setup(Y_DIR_PIN, GPIO.OUT)
GPIO.setup(SERVO_PIN, GPIO.OUT)

servo_pwm = GPIO.PWM(SERVO_PIN, 50)
servo_pwm.start(2.5)  # Adjust according to your servo's minimum angle


def move_stepper(direction, steps, stepper_pins):
    GPIO.output(stepper_pins['DIR'], direction)

    for _ in range(steps):
        GPIO.output(stepper_pins['STEP'], GPIO.HIGH)
        time.sleep(0.0001)
        GPIO.output(stepper_pins['STEP'], GPIO.LOW)
        time.sleep(0.0001)


def move_servo(angle):
    duty = angle / 18 + 2.5
    servo_pwm.ChangeDutyCycle(duty)
    time.sleep(1)


def parse_svg(filename):
    tree = ET.parse(filename)
    root = tree.getroot()

    paths = root.findall(".//{http://www.w3.org/2000/svg}path")

    gcode_commands = []
    for path in paths:
        d = path.attrib['d']
        path_commands = parse_svg_path(d)
        for command in path_commands:
            gcode_command = convert_to_gcode(command)
            gcode_commands.append(gcode_command)

    return gcode_commands


def parse_svg_path(d):
    commands = []
    parts = d.split()
    i = 0
    while i < len(parts):
        cmd = parts[i]
        coords = []
        i += 1
        while i < len(parts) and parts[i].isalpha() == False:
            coords.append(float(parts[i]))
            i += 1
        commands.append((cmd, coords))
    return commands


def convert_to_gcode(svg_command):
    cmd, coords = svg_command
    if cmd == 'M':
        x, y = coords
        gcode_command = f"G0 X{x} Y{y}"
    elif cmd == 'L':
        x, y = coords
        gcode_command = f"G1 X{x} Y{y}"
    return gcode_command


def execute_gcode(gcode_commands):
    current_position = {'x': 0, 'y': 0}

    for command in gcode_commands:
        if command.startswith('G0'):
            x_index = command.find('X')
            y_index = command.find('Y')
            if x_index != -1:
                x = float(command[x_index + 1:command.find(' ', x_index)])
                current_position['x'] = x
            if y_index != -1:
                y = float(command[y_index + 1:])
                current_position['y'] = y
            move_to(current_position['x'], current_position['y'])
        elif command.startswith('G1'):
            x_index = command.find('X')
            y_index = command.find('Y')
            if x_index != -1:
                x = float(command[x_index + 1:command.find(' ', x_index)])
                current_position['x'] = x
            if y_index != -1:
                y = float(command[y_index + 1:])
                current_position['y'] = y
            move_to(current_position['x'], current_position['y'])


def move_to(x, y):
    X_STEP_PIN = 17
    X_DIR_PIN = 27
    Y_STEP_PIN = 23
    Y_DIR_PIN = 24

    if x > 0:
        GPIO.output(X_DIR_PIN, GPIO.HIGH)
    else:
        GPIO.output(X_DIR_PIN, GPIO.LOW)

    if y > 0:
        GPIO.output(Y_DIR_PIN, GPIO.HIGH)
    else:
        GPIO.output(Y_DIR_PIN, GPIO.LOW)

    x_steps = abs(x)
    y_steps = abs(y)

    for _ in range(max(x_steps, y_steps)):
        if x_steps > 0:
            GPIO.output(X_STEP_PIN, GPIO.HIGH)
            time.sleep(0.0001)
            GPIO.output(X_STEP_PIN, GPIO.LOW)
            x_steps -= 1

        if y_steps > 0:
            GPIO.output(Y_STEP_PIN, GPIO.HIGH)
            time.sleep(0.0001)
            GPIO.output(Y_STEP_PIN, GPIO.LOW)
            y_steps -= 1

    time.sleep(0.1)


def print_svg(filename):
    gcode_commands = parse_svg(filename)
    execute_gcode(gcode_commands)


# Main function
def main():
    try:
        while True:
            move_stepper(GPIO.HIGH, 100, {'DIR': X_DIR_PIN, 'STEP': X_STEP_PIN})

            move_servo(90)

            print_svg("example.svg")

            time.sleep(1)

    except KeyboardInterrupt:
        servo_pwm.stop()
        GPIO.cleanup()


# Run main function
if __name__ == "__main__":
    main()
