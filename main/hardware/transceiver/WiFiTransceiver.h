#pragma once

#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"

#include "packet.h"
#include "../TCPClient.h"
#include "../WiFi.h"
#include "../../constants.h"

namespace pizda {
	class WiFiTransceiver {
		public:
			void setup();
			void tick();

		private:
			uint32_t _tickTime = 0;
			uint32_t _WiFiConnectTime = 0;
			uint32_t _TCPConnectTime = 0;

			TCPClient _TCP;
			WiFi _WiFi;

			RemotePacket _remotePacket;
			AircraftPacket _aircraftPacket;

			void fillRemotePacket();
	};
}