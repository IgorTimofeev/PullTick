#pragma once

#include "Arduino.h"

#include "yoba/elements/layout.h"
#include "yoba/elements/selector.h"
#include "yoba/elements/selector_item.h"
#include "yoba/elements/image.h"
#include "yoba/animation.h"
#include "yoba/elements/button.h"
#include "yoba/elements/rectangle.h"

#include "ui/navigation/engine/engine_page.h"
#include "ui/theme.h"
#include "ui/navigation/radio/radio_page.h"
#include "side_bar_item.h"
#include "ui/navigation/battery/battery_page.h"
#include "ui/navigation/pfd/pfd_page.h"

using namespace yoba;

namespace ui {
	class SideBar : public Selector {
		public:
			SideBar() {
				addChild(&_background);

				// Menu
				const uint16_t menuSize = 20;
				_menu.setSize(Size(Size::calculated, menuSize));
				_menu.setVerticalAlignment(Alignment::end);
				_menu.addChild(&_menuBackground);

				_menuItemsLayout.setOrientation(Orientation::horizontal);
				_menu.addChild(&_menuItemsLayout);
				setItemsLayout(&_menuItemsLayout);

				addChild(&_menu);

				// Page
				_pageLayout.setMargin(Margin(0, 0, 0, menuSize));
				addChild(&_pageLayout);

				// Initialization
				addPage("PFD", &_pfdPage);
				addPage("ENG", &_enginePage);
				addPage("BAT", &_batteryPage);
				addPage("RAD", &_radioPage);
				setSelectedIndex(0);
			}

		protected:
			void onSelectionChanged() override {
				_pageLayout.removeChildren();

				if (getSelectedIndex() < 0)
					return;

				_pageLayout.addChild(_pages[getSelectedIndex()]);
			}

		private:
			Rectangle _background = Rectangle(&Theme::bg1);
			Layout _pageLayout = Layout();

			Layout _menu = Layout();
			Rectangle _menuBackground = Rectangle(&Theme::bg2);
			StackLayout _menuItemsLayout = StackLayout();

			std::vector<Page*> _pages {};

			// ----------------------------- Pages -----------------------------

			PFDPage _pfdPage = PFDPage();
			EnginePage _enginePage = EnginePage();
			BatteryPage _batteryPage = BatteryPage();
			RadioPage _radioPage = RadioPage();

			void addPage(const String& name, Page* page) {
				_pages.push_back(page);
				addItem(new SideBarItem(name));
			}
	};
}