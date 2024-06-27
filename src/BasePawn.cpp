#include "BasePawn.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


void BasePawn::_bind_methods() {
}


BasePawn::BasePawn() {
	// Initialize any variables here.
}

BasePawn::~BasePawn() {
	// Add your cleanup here.
}

void BasePawn::_ready() {
	add_to_group("BasePawn");
}

void BasePawn::_process(double delta) {
}

void BasePawn::_physics_process(double delta) {
}
