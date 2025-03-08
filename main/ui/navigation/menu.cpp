#include "menu.h"
#include "../../rc.h"

namespace pizda {
	void MenuOverlayBackground::onEvent(Event* event) {
		Element::onEvent(event);

		if (!ScreenEvent::isScreen(event))
			return;

		event->setHandled(true);

		RC::getInstance().setMenuVisibility(false);
	}

	Menu::Menu() {
		*this += &overlayBackground;

		// Holder
		_slideLayout.setWidth(_menuWidth);
		_slideLayout.setHorizontalAlignment(Alignment::start);

		// Items background
		_slideBackground.setFillColor(&Theme::bg2);
		_slideLayout += &_slideBackground;

		// Items selector
		addTitleItem(&_mainTitleItem);
		addPageItem(&_PFDItem);
		addPageItem(&_NDItem);
		addPageItem(&_APItem);

		addTitleItem(&_settingsTitleItem);
		addPageItem(&_WiFiItem);
		addPageItem(&_axisItem);
		addPageItem(&_debugItem);

		_slideRows += &_slideItemsLayout;

		_slideLayout += &_slideRows;

		*this += &_slideLayout;
	}

	void Menu::addItem(MenuItem* item) {
		_slideItemsLayout += item;
	}

	void Menu::addTitleItem(TitleMenuItem* item) {
		addItem(item);
	}

	void Menu::addPageItem(PageMenuItem* item) {
		item->setSelected(RC::getInstance().getRoute() == item->getRoute());

		addItem(item);
	}

	void Menu::updateItemsSelection() {
		for (auto element : _slideItemsLayout) {
			if (!element->isEnabled())
				continue;

			auto item = dynamic_cast<PageMenuItem*>(element);

			item->setSelected(RC::getInstance().getRoute() == item->getRoute());
		}
	}
}