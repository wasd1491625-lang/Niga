#include <Geode/Geode.hpp>
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/GJAccountRegisterLayer.hpp>

using namespace geode::prelude;

class $modify(MyEditLevelLayer, EditLevelLayer) {
	bool init(GJGameLevel* level) {
		if (!EditLevelLayer::init(level)) return false;

		// Level name input: add '-' to the allowed characters.
		// Field name may differ by bindings version; check EditLevelLayer.hpp.
		if (m_levelNameInput) {
			std::string allowed = m_levelNameInput->m_allowedChars;
			std::string extra = R"x(@.#_&-+()/*"':;!?|\{}=][%)x";
			for (char c : extra) {
				if (allowed.find(c) == std::string::npos) {
					allowed += c;
				}
			}
			m_levelNameInput->setAllowedChars(allowed);
		}
		return true;
	}
};

class $modify(MyRegisterLayer, GJAccountRegisterLayer) {
	bool init() {
		if (!GJAccountRegisterLayer::init()) return false;

		// Username input: allow '-' (and keep whatever was already allowed).
		// Field name may differ by bindings version; check GJAccountRegisterLayer.hpp.
		if (m_usernameInput) {
			std::string allowed = m_usernameInput->m_allowedChars;
			if (allowed.find('-') == std::string::npos) {
				allowed += "-";
				m_usernameInput->setAllowedChars(allowed);
			}
		}
		return true;
	}
};
