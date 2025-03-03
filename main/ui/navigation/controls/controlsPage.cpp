#include "controlsPage.h"

#include "../../../rc.h"
#include "../../theme.h"

namespace pizda {
	ControlsPage::ControlsPage() :
		_aileronsAxisEditor(AxisEditor(&RC::getInstance().getJoystickHorizontal())),
		_elevatorAxisEditor(AxisEditor(&RC::getInstance().getJoystickVertical())),
		_rudderAxisEditor(AxisEditor(&RC::getInstance().getRing())),
		_spoilersAxisEditor(AxisEditor(&RC::getInstance().getLeverLeft())),
		_flapsAxisEditor(AxisEditor(&RC::getInstance().getLeverRight()))
	{
		// Page title
		pageTitle.setText(L"Axis calibration");

		// Axis
		Theme::apply(&_aileronsAxisEditorTitle);
		rows += &_aileronsAxisEditorTitle;

		Theme::apply(&_elevatorAxisEditorTitle);
		rows += &_elevatorAxisEditorTitle;

		Theme::apply(&_rudderAxisEditorTitle);
		rows += &_rudderAxisEditorTitle;

		Theme::apply(&_spoilersAxisEditorTitle);
		rows += &_spoilersAxisEditorTitle;

		Theme::apply(&_flapsAxisEditorTitle);
		rows += &_flapsAxisEditorTitle;

		// Low pass slider
		Theme::apply(&_lowPassFactorSlider);

		_lowPassFactorSlider.setValue(RC::getInstance().getSettings().axis.lowPassFactor);

		_lowPassFactorSlider.valueChanged += [this]() {
			auto& settings = RC::getInstance().getSettings();

			settings.axis.lowPassFactor = _lowPassFactorSlider.getValue();
			settings.enqueueWrite();
		};

		Theme::apply(&_lowPassFactorSliderTitle);
		rows += &_lowPassFactorSliderTitle;
	}

	void ControlsPage::onTick() {
		Layout::onTick();

		invalidate();
	}
}