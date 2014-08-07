#include "ECGUIElement.h"

namespace EnvironmentCore {

	ECGUIElement::ECGUIElement() {

	}

	ECGUIElement::~ECGUIElement() {

	}

	void ECGUIElement::setName(std::string Name) {
		m_Name = Name;
	}

	std::string ECGUIElement::getName() {
		return m_Name;
	}

}