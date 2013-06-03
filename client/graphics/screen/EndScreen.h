/*
 * EndScreen.h
 *
 *  Created on: 23 mai 2013
 *      Author: B�ni
 */

#ifndef ENDSCREEN_H_
#define ENDSCREEN_H_

#include "../component/Container.hpp"
#include "../inheritedComponent/FrameEndGame.h"
#include "../inheritedComponent/FrameExp.h"
#include "../component/Button.hpp"
#include "../inheritedListener/EndScreenListnerButton.h"
#include "../layout/VerticalLayout.hpp"
#include "../layout/SplitFixedLayout.hpp"
#include "../GUIStyle.hpp"

namespace graphics {

class EndScreen  : public Container {

public:
	EndScreen();
	~EndScreen();
	void load();
private:
	Container m_leftContainer, m_rightContainer, m_buttonContainer, m_rightBottomContainer, m_containerExp;
	FrameEndGame* m_frame;
	FrameExp* m_exp;
	Button* m_returnButton;
	Chat* m_chat;
};

} /* namespace graphics */
#endif /* ENDSCREEN_H_ */
