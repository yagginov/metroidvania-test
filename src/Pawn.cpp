#include "Pawn.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math.hpp>

using namespace godot;


void Pawn::_bind_methods() 
{
	ClassDB::bind_method(D_METHOD("get_maxSpeed"), &Pawn::get_maxSpeed);
	ClassDB::bind_method(D_METHOD("set_maxSpeed", "maxSpeed"), &Pawn::set_maxSpeed);
	ClassDB::add_property("Pawn", PropertyInfo(Variant::FLOAT, "_maxSpeed"), "set_maxSpeed", "get_maxSpeed");

	ClassDB::bind_method(D_METHOD("get_acceleration"), &Pawn::get_acceleration);
	ClassDB::bind_method(D_METHOD("set_acceleration", "acceleration"), &Pawn::set_acceleration);
	ClassDB::add_property("Pawn", PropertyInfo(Variant::FLOAT, "_acceleration"), "set_acceleration", "get_acceleration");

	ClassDB::bind_method(D_METHOD("get_isPhysicsEnabled"), &Pawn::get_isPhysicsEnabled);
	ClassDB::bind_method(D_METHOD("set_isPhysicsEnabled", "isPhysicsEnabled"), &Pawn::set_isPhysicsEnabled);
	ClassDB::add_property("Pawn", PropertyInfo(Variant::BOOL, "_isPhysicsEnabled"), "set_isPhysicsEnabled", "get_isPhysicsEnabled");

	ClassDB::bind_method(D_METHOD("get_dragCoefficient"), &Pawn::get_dragCoefficient);
	ClassDB::bind_method(D_METHOD("set_dragCoefficient", "dragCoefficient"), &Pawn::set_dragCoefficient);
	ClassDB::add_property("Pawn", PropertyInfo(Variant::FLOAT, "_dragCoefficient"), "set_dragCoefficient", "get_dragCoefficient");

}


Pawn::Pawn() 
{
	// Initialize any variables here.
	_maxSpeed = 500;
	_acceleration = 800;
	_isPhysicsEnabled = false;

	_dragCoefficient = 0.5;

	g = 198;
}

Pawn::~Pawn() 
{
	// Add your cleanup here.
}

void Pawn::_ready() 
{
	add_to_group("Pawn");
}

void Pawn::_process(double delta) 
{

}

void Pawn::_physics_process(double delta) 
{

}


void Pawn::move(double direction, double delta)
{
	Vector2 velocity = get_velocity();
	velocity.x = Math::move_toward((double)velocity.x, direction * _maxSpeed, _dragCoefficient * g);
	
	if (_isPhysicsEnabled && !is_on_floor())
	{
		velocity.y += _acceleration * delta;
	}

	set_velocity(velocity);
	move_and_slide();
}


void Pawn::set_maxSpeed(const double maxSpeed)
{
	_maxSpeed = maxSpeed;
}
double Pawn::get_maxSpeed() const
{
	return _maxSpeed;
}

void Pawn::set_acceleration(const double acceleration)
{
	_acceleration = acceleration;
}
double Pawn::get_acceleration() const
{
	return _acceleration;
}

void Pawn::set_isPhysicsEnabled(const bool isPhysicsEnabled)
{
	_isPhysicsEnabled = isPhysicsEnabled;
}
bool Pawn::get_isPhysicsEnabled() const
{
	return _isPhysicsEnabled;
}

void Pawn::set_dragCoefficient(const double dragCoefficient)
{
	_dragCoefficient = dragCoefficient;
}
double Pawn::get_dragCoefficient() const
{
	return _dragCoefficient;
}