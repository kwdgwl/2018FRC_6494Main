/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../../../2018FRC_6494Main/src/Commands/Pickup.h"

//#include "SetElevatorSetpoint.h"
//#include "SetWristSetpoint.h"
#include "../../../2018FRC_6494Main/src/Commands/CloseClaw.h"

Pickup::Pickup()
    : frc::CommandGroup("Pickup") {
	AddSequential(new CloseClaw());
	//AddParallel(new SetWristSetpoint(-45));
	//AddSequential(new SetElevatorSetpoint(0.25));
}
