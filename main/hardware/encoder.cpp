#include "encoder.h"

namespace pizda {
	uint16_t EncoderRotateEvent::typeID = 0;

	int32_t EncoderRotateEvent::getRPS() const {
		return _RPS;
	}

	int16_t EncoderRotateEvent::getMappedRPS(uint16_t check1, int16_t value1, int16_t valueElse) {
		const auto absRPS = std::abs(_RPS);
		int16_t value;

		if (absRPS < check1) {
			value = value1;
		}
		else {
			value = valueElse;
		}

		return _RPS > 0 ? value : -value;
	}

	int16_t EncoderRotateEvent::getMappedRPS(uint16_t check1, uint16_t check2, int16_t value1, int16_t value2, int16_t valueElse) {
		const auto absRPS = std::abs(_RPS);
		int16_t value;

		if (absRPS < check1) {
			value = value1;
		}
		else if (absRPS < check2) {
			value = value2;
		}
		else {
			value = valueElse;
		}

		return _RPS > 0 ? value : -value;
	}

	uint16_t EncoderPushEvent::typeID = 0;

	bool EncoderPushEvent::isDown() const {
		return _down;
	}

	Encoder::Encoder(gpio_num_t clkPin, gpio_num_t dtPin, gpio_num_t swPin) :
		_clkPin(clkPin),
		_dtPin(dtPin),
		_swPin(swPin) {
	}

	void Encoder::setup() {
		// GPIO
		gpio_config_t config = {
			.pin_bit_mask = BIT64(_clkPin) | BIT64(_dtPin) | BIT64(_swPin),
			.mode = GPIO_MODE_INPUT,
			.pull_up_en = GPIO_PULLUP_ENABLE,
			.pull_down_en = GPIO_PULLDOWN_DISABLE,
			.intr_type = GPIO_INTR_ANYEDGE
		};

		gpio_config(&config);

		// Interrupts
		gpio_install_isr_service(ESP_INTR_FLAG_IRAM);
		gpio_isr_handler_add(_clkPin, clkDtInterruptHandler, this);
		gpio_isr_handler_add(_dtPin, clkDtInterruptHandler, this);
		gpio_isr_handler_add(_swPin, swInterruptHandler, this);
	}

	void Encoder::clkDtInterruptHandler(void* args) {
		auto instance = (Encoder*) args;

		instance->_interrupted = true;
		instance->readRotation();
	}

	void Encoder::swInterruptHandler(void* args) {
		auto instance = (Encoder*) args;

		instance->_interrupted = true;
		instance->readPressed();
	}

	void Encoder::readPressed() {
		_pressed = !gpio_get_level(_swPin);
	}

	void Encoder::readRotation() {
		auto clkAndDt = (gpio_get_level(_clkPin) << 1) | gpio_get_level(_dtPin);

		if (clkAndDt != _oldClkAndDt) {
			switch (_oldClkAndDt | (clkAndDt << 2)) {
				case 0:
				case 5:
				case 10:
				case 15:
					break;
				case 1:
				case 7:
				case 8:
				case 14:
					_rotation++;
					break;
				case 2:
				case 4:
				case 11:
				case 13:
					_rotation--;
					break;
				case 3:
				case 12:
					_rotation += 2;
					break;
				default:
					_rotation -= 2;
					break;
			}

			_oldClkAndDt = clkAndDt;
		}
	}

	bool Encoder::interrupted() const {
		return _interrupted;
	}

	int32_t Encoder::getRotation() const {
		return _rotation;
	}

	bool Encoder::isPressed() const {
		return _pressed;
	}

	void Encoder::acknowledgeInterrupt() {
		_interrupted = false;
	}

	void Encoder::setRotation(int32_t rotation) {
		_rotation = rotation;
	}
}