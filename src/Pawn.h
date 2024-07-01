#ifndef PAWN_H
#define PAWN_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/variant/vector2.hpp>


namespace godot {

class Pawn : public CharacterBody2D {
	GDCLASS(Pawn, CharacterBody2D)

protected:
	static void _bind_methods();

private:
	double g;

public:
	double _maxSpeed;
	double _acceleration;
	bool _isPhysicsEnabled;
	double _dragCoefficient;

public:
	Pawn();
	~Pawn();

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;

	void move(double direction, double delta);

	void set_maxSpeed(const double maxSpeed);
	double get_maxSpeed() const;

	void set_acceleration(const double acceleration);
	double get_acceleration() const;

	void set_isPhysicsEnabled(const bool isPhysicsEnabled);
	bool get_isPhysicsEnabled() const;

	void set_dragCoefficient(const double dragCoefficient);
	double get_dragCoefficient() const;
};

}	// namespace godot

#endif // BASE_PAWN_H