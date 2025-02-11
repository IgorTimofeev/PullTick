#pragma once

#include "../sound.h"

namespace pizda::resources::sounds {
	static Sound boot() {
		return Sound({
			Note(7500, 40000),
			Delay(40000),
			Note(7500, 40000)
		});
	}
}