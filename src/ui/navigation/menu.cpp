#include "menu.h"
#include "../rc_application.h"

namespace pizdanc {
	void Menu::begin() {
		addChild(&_background);

		// Menu
		const uint16_t menuSize = 20;
		_menu.setSize(Size(Size::Calculated, menuSize));
		_menu.setVerticalAlignment(Alignment::End);
		_menu.addChild(&_menuBackground);

		_menuItemsLayout.setOrientation(Orientation::Horizontal);
		_menu.addChild(&_menuItemsLayout);
		setItemsLayout(&_menuItemsLayout);

		addChild(&_menu);

		// Page
		_pageLayout.setMargin(Margin(0, 0, 0, menuSize));
		addChild(&_pageLayout);

		// Initialization
		addPage(L"PFD", &_pfdPage);
		addPage(L"A/P", &_autopilotPage);
		addPage(L"CTL", &_controlsPage);
		addPage(L"ENG", &_enginePage);
		addPage(L"COM", &_radioPage);
		addPage(L"BAT", &_batteryPage);
		addPage(L"DBG", &_debugPage);
		setSelectedIndex(0);
	}

	void Menu::onSelectionChanged() {
		_pageLayout.removeChildren();

		if (getSelectedIndex() < 0)
			return;

		_pageLayout.addChild(_pages[getSelectedIndex()]);
	}

	void Menu::addPage(const wchar_t *name, Page *page) {
		page->begin();
		_pages.push_back(page);
		addItem(new MenuItem(name));
	}
}