#include "controlsPage.h"

#include "../../rc.h"

namespace pizdanc {
	const ControlsImage ControlsView::controlsImage = ControlsImage();

	ControlsView::ControlsView() : ImageView(&controlsImage) {

	}

	void ControlsView::onRender(Renderer* renderer) {
		ImageView::onRender(renderer);

		auto& rc = RC::getInstance();

		const auto& bounds = getBounds();

		int32_t position;
		uint16_t size;

		auto calc = [&](int32_t coord, float value) {
			position = coord;
			int32_t position2 = position + (int32_t) round(value * (float) maxPixelValue);

			if (position2 < position)
				std::swap(position, position2);

			size = position2 == position ? 1 : position2 - position;
		};

		auto horiz = [&](const Point& point, uint16_t width, float value) {
			calc(point.getY(), value);

			renderer->renderFilledRectangle(
				Bounds(point.getX(), position, width, size),
				&Theme::green
			);
		};

		auto vert = [&](const Point& point, uint16_t height, float value) {
			calc(point.getX(), value);

			renderer->renderFilledRectangle(
				Bounds(position, point.getY(), size, height),
				&Theme::green
			);
		};

		// Ailerons
		horiz(
			Point(
				bounds.getX() + 11,
				bounds.getY() + 58
			),
			30,
			rc.getAileronsInterpolator().getValue()
		);

		horiz(
			Point(
				bounds.getX() + 238,
				bounds.getY() + 58
			),
			30,
			-rc.getAileronsInterpolator().getValue()
		);

		// Flaps
		horiz(
			Point(
				bounds.getX() + 49,
				bounds.getY() + 59
			),
			32,
			rc.getFlapsInterpolator().getValue()
		);

		horiz(
			Point(
				bounds.getX() + 198,
				bounds.getY() + 59
			),
			32,
			rc.getFlapsInterpolator().getValue()
		);

		// Elevator
		horiz(
			Point(
				bounds.getX() + 95,
				bounds.getY() + 3
			),
			37,
			rc.getElevatorInterpolator().getValue()
		);

		horiz(
			Point(
				bounds.getX() + 148,
				bounds.getY() + 3
			),
			37,
			rc.getElevatorInterpolator().getValue()
		);

		// Rudder
		vert(
			Point(
				bounds.getX() + 139,
				bounds.getY() + 8
			),
			36,
			rc.getRudderInterpolator().getValue()
		);
	}
}