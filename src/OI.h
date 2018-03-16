/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Buttons/JoystickButton.h>
#include <Joystick.h>

class OI {
public:
	OI();
	frc::Joystick& GetJoystick();

private:
	frc::Joystick m_joy{0};

	// Create some buttons
	frc::JoystickButton m_joy1{&m_joy, 1};
	frc::JoystickButton m_joy2{&m_joy, 2};
	frc::JoystickButton m_joy3{&m_joy, 3};
	frc::JoystickButton m_joy4{&m_joy, 4};
	frc::JoystickButton m_joy5{&m_joy, 5};
	frc::JoystickButton m_joy6{&m_joy, 6};
	frc::JoystickButton m_joy7{&m_joy, 7};
	frc::JoystickButton m_joy8{&m_joy, 8};
	frc::JoystickButton m_joy9{&m_joy, 9};
	frc::JoystickButton m_joy10{&m_joy, 10};
	frc::JoystickButton m_joy11{&m_joy, 11};
	frc::JoystickButton m_joy12{&m_joy, 12};
};
