#ifndef CHARACTER_H
#define CHARACTER_H

#include "Pawn.h"
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/label.hpp>

#include "State.h"

namespace godot {


enum States
{
	idle = 0, 
	run = 1, 
	jump = 2,
	doubleJump = 3, 
	fall = 4, 
	slide = 5
};


class Character : public Pawn {
	GDCLASS(Character, Pawn)

protected:
	static void _bind_methods();

private:
    Input* i;
	bool inDoubleJump;
	States state;
	Vector<State*> v_states;
	Vector2 _velocity;
	double _direction;

	Label *label;

public:
	double _jumpMagnitude;
	bool _isAllowedDoubleJump;

public:
	Character();
	~Character();

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void idle(double delta);
	void run(double delta);
	void jump(double delta);
	void fall(double delta);
	void slide(double delta);


	void set_jumpMagnitude(const double jumpMagnitude);
	double get_jumpMagnitude() const;

	void set_isAllowedDoubleJump(const bool isAllowedDoubleJump);
	bool get_isAllowedDoubleJump() const;
};

}

#endif // CHARACTER_H