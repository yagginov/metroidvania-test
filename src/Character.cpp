#include "Character.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Character::_bind_methods() 
{
    ClassDB::bind_method(D_METHOD("get_jumpMagnitude"), &Character::get_jumpMagnitude);
	ClassDB::bind_method(D_METHOD("set_jumpMagnitude", "jumpMagnitude"), &Character::set_jumpMagnitude);
	ClassDB::add_property("Character", PropertyInfo(Variant::FLOAT, "_jumpMagnitude"), "set_jumpMagnitude", "get_jumpMagnitude");

	ClassDB::bind_method(D_METHOD("get_isAllowedDoubleJump"), &Character::get_isAllowedDoubleJump);
	ClassDB::bind_method(D_METHOD("set_isAllowedDoubleJump", "isAllowedDoubleJump"), &Character::set_isAllowedDoubleJump);
	ClassDB::add_property("Character", PropertyInfo(Variant::BOOL, "_isAllowedDoubleJump"), "set_isAllowedDoubleJump", "get_isAllowedDoubleJump");
}


Character::Character()
{
	// Initialize any variables here.
    i = Input::get_singleton();

	state = States::idle;
	v_states.push_back(new State(60));		// idle
	v_states.push_back(new State(0.0));		// run
	v_states.push_back(new State(0.4));		// jump
	v_states.push_back(new State(0.4));		// double jump
	v_states.push_back(new State(0.1));		// fall
	v_states.push_back(new State(0.8));		// slide

    _direction = 0.0;
    _jumpMagnitude = -400;

	_isAllowedDoubleJump = false;
	inDoubleJump = true;

	maxAnimationSpeed = 20;

}

Character::~Character() 
{
	// Add your cleanup here.
}

void Character::_ready() 
{
	add_to_group("Character");


	animatedSprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
}

void Character::_process(double delta) 
{

}

void Character::_physics_process(double delta) 
{
	_direction = i->get_axis("ui_left", "ui_right");
	_velocity = get_velocity();


	if (i->is_action_just_pressed("ui_accept") && is_on_floor())
	{
		v_states[state]->reset();
		state = States::jump;
	}

	if (_velocity.x == 0)
	{
		animatedSprite->play("idle");
	}
	else
	{
		animatedSprite->play("move", abs(_velocity.x) / _maxSpeed);
		if (_velocity.x < 0)
		{
			animatedSprite->set_flip_h(true);
		}
		else
		{
			animatedSprite->set_flip_h(false);
		}
	}

	switch(state)
	{
	case States::idle : 
		//UtilityFunctions::print("idle");
		idle(delta);
		break;

	case States::run :
		run(delta);
		break;

	case States::jump :
	case States::doubleJump:
		jump(delta);
		break;

	case States::fall :
		fall(delta);
		break;

	case States::slide :
		slide(delta);
		break;
	}

	set_velocity(_velocity);
	move(_direction, delta);
}


void Character::idle(double delta)
{
	if (v_states[state]->is_start()) 
	{
		inDoubleJump = false;
	}
    
	if (!is_on_floor())
	{
		v_states[state]->reset();
		state = States::fall;
		return;
	}

	if (_direction != 0.0)
	{
		v_states[state]->reset();
		state = States::run;
	}
}

void Character::run(double delta)
{
	if (!is_on_floor())
	{
		v_states[state]->reset();
		state = States::fall;
		return;
	}

	if (_direction == 0.0)
	{
		v_states[state]->reset();
		state = States::idle;
	}
}

void Character::jump(double delta)
{
	if (v_states[state]->is_start())
	{
		_velocity.y = _jumpMagnitude;
		return;
	}

	if (i->is_action_just_pressed("ui_accept") && _isAllowedDoubleJump && !inDoubleJump)
	{
		inDoubleJump = true;
		v_states[state]->reset();
		state = States::jump;
		return;
	}

	if (_velocity.y > 0.5)
	{
		v_states[state]->reset();
		state = States::fall;
	}

}

void Character::fall(double delta)
{
	if (i->is_action_just_pressed("ui_accept") && _isAllowedDoubleJump && !inDoubleJump)
	{
		inDoubleJump = true;
		v_states[state]->reset();
		state = States::jump;
		return;
	}

	if (is_on_floor())
	{
		v_states[state]->reset();
		state = States::idle;
	}
}

void Character::slide(double delta)
{
	
}


void Character::set_jumpMagnitude(const double jumpMagnitude)
{
	_jumpMagnitude = jumpMagnitude;
}
double Character::get_jumpMagnitude() const
{
	return _jumpMagnitude;
}

void Character::set_isAllowedDoubleJump(const bool isAllowedDoubleJump)
{
	_isAllowedDoubleJump = isAllowedDoubleJump;
}
bool Character::get_isAllowedDoubleJump() const
{
	return _isAllowedDoubleJump;
}