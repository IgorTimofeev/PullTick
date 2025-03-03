#pragma once

#include "../../../components/yoba/src/main.h"
#include "../../../components/yoba/src/ui.h"

#include "../theme.h"
#include "page.h"

namespace pizda {
	using namespace yoba;
	using namespace yoba::ui;

	class Tab : public SelectorItem, public TextElement {
		public:
			Tab(std::wstring_view text, const std::function<Page*()>& pageBuilder) : _pageBuilder(pageBuilder) {
				setText(text);
			}

			Page* newPage() const {
				return _pageBuilder();
			}

		protected:
			void onRender(Renderer* renderer, const Bounds& bounds) override {
				if (isSelected()) {
					// Background
					renderer->renderFilledRectangle(bounds, &Theme::bg3);

					// Line
					renderer->renderHorizontalLine(
						bounds.getBottomLeft(),
						bounds.getWidth(),
						&Theme::fg1
					);
				}

				// Text
				constexpr static const uint8_t textOffset = 1;

				renderer->renderString(
					Point(
						bounds.getXCenter() - Theme::fontNormal.getWidth(getText()) / 2,
						bounds.getYCenter() - Theme::fontNormal.getHeight() / 2 - textOffset
					),
					&Theme::fontNormal,
					isSelected() ? &Theme::fg1 : &Theme::fg4,
					getText()
				);
			}

		private:
			std::function<Page*()> _pageBuilder;
	};
}