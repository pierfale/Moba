/*
 * EndScreen.h
 *
 *  Created on: 23 mai 2013
 *      Author: Béni
 */

#ifndef ENDSCREEN_H_
#define ENDSCREEN_H_

#include "../component/Container.hpp"
#include "../inheritedComponent/FrameEndGame.h"
#include "../component/Button.hpp"
#include "../inheritedListener/EndScreenListnerButton.h"
#include "../GUIStyle.hpp"
#include "../inheritedComponent/Chat.hpp"

namespace graphics {

class EndScreen  : public Container {

public:
	EndScreen();
	virtual ~EndScreen();
	void load();
	std::string getComponentName();
	static std::string getName();
	Chat* getChat();
private:
	FrameEndGame* m_frame;
	Button* m_returnButton;
};

} /* namespace graphics */
#endif /* ENDSCREEN_H_ */
