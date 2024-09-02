#pragma once

#include "yoba/application.h"
#include "yoba/hardware/potentiometer.h"
#include "transceiver.h"
#include "onboard_led.h"
#include "../pid.h"

using namespace yoba;

namespace pizdanc {
	class MutualData {
		public:
			uint8_t getThrottle() const;
			void setThrottle(uint8_t throttle);

			uint8_t getAilerons() const;
			void setAilerons(uint8_t ailerons);

			uint8_t getRudder() const;
			void setRudder(uint8_t rudder);

			uint8_t getFlaps() const;
			void setFlaps(uint8_t flaps);

			AltimeterMode getAltimeterMode() const;
			void setAltimeterMode(AltimeterMode altimeterMode);

			float getAltimeterPressure() const;
			void setAltimeterPressure(float altimeterPressure);

			bool getStrobeLights() const;
			void setStrobeLights(bool strobeLights);

		private:
			uint8_t _throttle = 0;
			uint8_t _ailerons = 0;
			uint8_t _rudder = 0;
			uint8_t _flaps = 0;

			AltimeterMode _altimeterMode = AltimeterMode::QNH;
			float _altimeterPressure = 1013;

			bool _strobeLights = false;
	};

	class LocalData : public MutualData {

	};

	class RemoteData : public MutualData {
		public:
			float getPitch() const;
			void setPitch(float pitch);

			float getRoll() const;
			void setRoll(float roll);

			float getYaw() const;
			void setYaw(float yaw);

			float getTemperature() const;
			void setTemperature(float temperature);

			float getPressure() const;
			void setPressure(float pressure);

			float getAltitude() const;
			void setAltitude(float altitude);

			float getSpeed() const;
			void setSpeed(float speed);

		private:
			float _pitch = 0;
			float _roll = 0;
			float _yaw = 0;

			float _temperature = 30;
			float _pressure = 0;

			float _altitude = 0;
			float _speed = 0;
	};

	class RCApplication : public Application {
		public:
			RCApplication();

			static RCApplication& getInstance();

			void tick() override;
			void begin();

			LocalData& getLocalData();
			RemoteData& getRemoteData();
			OnboardLED& getOnboardLED();
			Transceiver& getTransceiver();

			PID &getSpeedPid();
			PID &getAltitudePid();
			PID &getPitchPid();
			PID &getRollPid();
			PID &getYawPid();
			PID &getSpeedTrendPid();
			PID &getAltitudeTrendPid();
			PID &getVerticalSpeedPid();

		private:
			// Shows where spd/alt should target in 10 sec
			const float _trendValueDeltaTime = 10 * 1000;
			uint32_t _tickTime = 0;

			uint32_t _testTickTime = 0;

			LocalData _localData = LocalData();
			RemoteData _remoteData = RemoteData();
			OnboardLED _onboardLED = OnboardLED();

			const float p = 0.8;
			const float i = 0.000;
			const float d = 0.03;

			PID _speedPID = PID(p, i, d);
			PID _speedTrendPID = PID(p, i, d);

			PID _altitudePID = PID(p, i, d);
			PID _altitudeTrendPID = PID(p, i, d);

			PID _verticalSpeedPID = PID(p, i, d);

			PID _pitchPID = PID(p, i, d);
			PID _rollPID = PID(p, i, d);
			PID _yawPID = PID(p, i, d);

			//
//			Potentiometer _pitchHall;
//			Potentiometer _rollHall;
//
			Transceiver _transceiver = Transceiver();
	};
}