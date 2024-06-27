#ifndef CUSTOM_CHARACTER_BODY2D_H
#define CUSTOM_CHARACTER_BODY2D_H

#include <godot_cpp/classes/character_body2d.hpp>


namespace godot {

class BasePawn : public CharacterBody2D {
	GDCLASS(BasePawn, CharacterBody2D)

protected:
	static void _bind_methods();

public:
	BasePawn();
	~BasePawn();

	void _ready() override;
	void _process(double delta) override;
	void _physics_process(double delta) override;
};

}

#endif