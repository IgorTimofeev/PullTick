#include "debugOverlay.h"
#include "rc.h"
#include <sstream>

namespace pizdanc {
	void DebugOverlay::onRender(Renderer* renderer) {
		auto& rc = RC::getInstance();

		int32_t y = 0;
		static std::wstringstream stream;

		const auto renderLine = [renderer, &y](std::function<void()> streamWriter) {
			stream.str(std::wstring());
			streamWriter();

			renderer->renderString(Point(0, y), &Theme::fontNormal, &Theme::purple, stream.str());

			y += Theme::fontNormal.getHeight() + 2;
		};

		const auto renderTimeLine = [&renderLine, &rc](const std::wstring_view& key, uint32_t time) {
			renderLine([&rc, time, &key]() {
				stream
					<< key
					<< L": "
					<< time
					<< L" ms, "
					<< (time * 100 / rc.getTickDeltaTime())
					<< L"%";
			});
		};

		renderLine([]() {
			stream << L"Freq: " << ESP.getCpuFreqMHz() << L" MHz";
		});

		renderLine([]() {
			stream
				<< L"Heap: "
				<< yoba::round((float) ESP.getFreeHeap() / 1024.f, 2)
				<< L" kB / "
				<< yoba::round((float) ESP.getHeapSize() / 1024.f, 2)
				<< L" kB";
		});

		renderTimeLine(L"Tick", rc.getApplication().getTickDeltaTime());
		renderTimeLine(L"Layout", rc.getApplication().getLayoutDeltaTime());
		renderTimeLine(L"Render", rc.getApplication().getRenderDeltaTime());
		renderTimeLine(L"Flush", rc.getApplication().getFlushDeltaTime());

		renderLine([&rc]() {
			stream << L"Total: " << rc.getTickDeltaTime() << L" ms";
		});

		renderLine([&rc]() {
			stream << L"FPS: " << (1000 / rc.getTickDeltaTime());
		});
	}
}