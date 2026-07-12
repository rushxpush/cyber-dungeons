#pragma once

struct Flags {
    bool position;
    bool speed;
    bool gravity;
    bool control;

    Flags(bool position, bool speed, bool gravity, bool control) :
        position(position), 
        speed(speed), 
        gravity(gravity),
        control(control) {}
};
