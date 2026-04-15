#pragma once

#include <SFML/Graphics.hpp>

#include "../Physical/Movable.h"

namespace kt::Shapes {
	class RectangleEntity : public sf::RectangleShape, public kt::Physical::Movable {
	private:
	public:
		using RectangleShape::RectangleShape;

		RectangleEntity();

		virtual ~RectangleEntity();
	};
}