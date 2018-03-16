/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <Spark.h>
#include <Timer.h>
#include <thread>
#include <CameraServer.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Solenoid.h>
#include <DoubleSolenoid.h>
#include <ADXRS450_Gyro.h>
#include <SmartDashboard/SmartDashboard.h>
#include <SpeedControllerGroup.h>

class Robot : public frc::IterativeRobot {
public:
	Robot() {
		m_timer.Start();
		m_robotDrive.SetExpiration(0.2);
	}

	void AutonomousInit() override {
		gyro.Calibrate();
		gyro.Reset();
		m_timer.Reset();
		m_timer.Start();
	}

	void AutonomousPeriodic() override {
		if (m_timer.Get() < 5.0) {
		double turningValue = 0 - (gyro.GetAngle()) * kP;
		frc::SmartDashboard::PutNumber("Tvalue", turningValue);
		// Invert the direction of the turn if we are going backwards
		m_robotDrive.ArcadeDrive(0.6, turningValue);
		}else{
			m_robotDrive.ArcadeDrive(0.0, 0.0);
		}
	}

	void TeleopInit() override {
		//std::thread ctrlThread(CtrlCaller);
		//ctrlThread.detach();
	}

	void TeleopPeriodic() override {
		if (m_stick.GetRawButton(kDoubleSolenoidForward)) {
			m_doubleSolenoid.Set(frc::DoubleSolenoid::kForward);
		} else if (m_stick.GetRawButton(kDoubleSolenoidReverse)) {
			m_doubleSolenoid.Set(frc::DoubleSolenoid::kReverse);
		} else {
			m_doubleSolenoid.Set(frc::DoubleSolenoid::kOff);
		}
		/*if(m_stick.GetRawButton(8)){
			m_grab.Set(0.8);
		}else if (m_stick.GetRawButton(7)){
			m_grab.Set(-0.8);
		}else{
			m_grab.Set(0.01);
		}*/
		if(m_stick.GetRawAxis(3) > 0.4){
			m_elevate.Set(m_stick.GetRawAxis(3) - 0.2);
		}
		else if(m_stick.GetRawAxis(3) < - 0.4){
			m_elevate.Set(m_stick.GetRawAxis(3) + 0.2);
		}else{
			m_elevate.Set(- 0.09);
		}

		if(m_stick.GetRawButton(9)){
			m_liftup.Set(-0.8);
		}
		else if(m_stick.GetRawButton(10)){
			m_liftup.Set(0.8);
		}else{
			m_liftup.Set(0);
		}

		if(m_stick.GetRawButton(7)){
			m_hold.Set(-0.2);
		}
		else if(m_stick.GetRawButton(8)){
			m_hold.Set(0.05);
		}else{
			m_hold.Set(-0.05);
		}
		m_robotDrive.ArcadeDrive(0 - m_stick.GetY(), m_stick.GetX());



		//m_stick.GetRawAxis(3);
	}

	void TestPeriodic() override {}

	void RobotInit() {
			std::thread visionThread(VisionThread);
			visionThread.detach();
			gyro.Calibrate();
			gyro.Reset();
		}

	static void VisionThread() {
		// Get the USB camera from CameraServer
		cs::UsbCamera camera0 = CameraServer::GetInstance()->StartAutomaticCapture();
		camera0.SetResolution(640, 480);
		cs::UsbCamera camera1 = CameraServer::GetInstance()->StartAutomaticCapture();
		camera1.SetResolution(640, 480);
	}
	//static void CtrlCaller (){
	//	CtrlThread();
	//}

	/*void CtrlThread() {
		while (true){
			if (m_stick.GetRawButton(kDoubleSolenoid)) {
				if (solState){
					m_doubleSolenoid.Set(frc::DoubleSolenoid::kForward);
					solState = false;
					while(m_stick.GetRawButton(kDoubleSolenoid)){;}
				}else{
					m_doubleSolenoid.Set(frc::DoubleSolenoid::kReverse);
					solState = true;
					while(m_stick.GetRawButton(kDoubleSolenoid)){;}
				}
			} else {
				m_doubleSolenoid.Set(frc::DoubleSolenoid::kOff);
			}
		}
	}*/

private:

	// Robot drive system
	frc::Spark m_left1{0};
	frc::Spark m_left2{1};
	frc::Spark m_right1{2};
	frc::Spark m_right2{3};
	frc::SpeedControllerGroup m_left{m_left1, m_left2};
	frc::SpeedControllerGroup m_right{m_right1, m_right2};
	//frc::Spark m_grabl{4};
	//frc::Spark m_grabr{5};

	frc::Spark m_elevate{6};
	frc::Spark m_liftup{7};
	frc::Spark m_hold{8};
	frc::DifferentialDrive m_robotDrive{m_left, m_right};
	frc::ADXRS450_Gyro gyro{};
	frc::Joystick m_stick{0};
	frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
	frc::Timer m_timer;

	frc::DoubleSolenoid m_doubleSolenoid{0, 1};
	static constexpr int kDoubleSolenoidForward = 1;
	static constexpr int kDoubleSolenoidReverse = 2;


	static constexpr double kAngleSetpoint = 0.0;
	static constexpr double kP = 0.05;  // Proportional turning constant
	bool solState = false;
};

START_ROBOT_CLASS(Robot)
