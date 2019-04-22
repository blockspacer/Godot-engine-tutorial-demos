#include "gdexample.h"
#include <Label.hpp>
#include <Input.hpp>

using namespace godot;

void GDExample::_register_methods() {
    register_method("_process", &GDExample::_process, GODOT_METHOD_RPC_MODE_DISABLED);
    register_property<GDExample, float>("amplitude", &GDExample::amplitude, 10.0, GODOT_METHOD_RPC_MODE_DISABLED);
    register_property<GDExample, float>("speed", &GDExample::set_speed, &GDExample::get_speed, 1.0);

    register_signal<GDExample>((char *)"position_changed", "node", GODOT_VARIANT_TYPE_OBJECT, "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
}

GDExample::GDExample() {
}

GDExample::~GDExample() {
    // add your cleanup here
}

void GDExample::_init() {
    // initialize any variables here
    time_passed = 0.0;
    amplitude = 20.0;
    speed = 1.0;
}

void GDExample::_process(float delta) {
    time_passed += speed * delta;

    Input* input = Input::get_singleton();
    bool left = input->is_action_pressed("ui_left");
    bool right = input->is_action_pressed("ui_right");

    Vector2 new_position = Vector2(
        amplitude + (amplitude * sin(time_passed * 2.0)),
        amplitude + (amplitude * cos(time_passed * 1.5))
    );

    if(left)
    {
        Godot::print("left pressed");
        new_position.x = 0;
    }

    if(right)
    {
        Godot::print("right pressed");
        new_position.y = 0;
    }

    set_position(new_position);

    time_emit += delta;
    if (time_emit > 1.0) {
        emit_signal("position_changed", this, new_position);

        time_emit = 0.0;

        if(has_node("Label"))
        {
            static_cast<Label*>(get_node("Label"))->set_visible(true);
        }
    }
}

void GDExample::set_speed(float p_speed) {
    speed = p_speed;
}

float GDExample::get_speed() {
    return speed;
}
