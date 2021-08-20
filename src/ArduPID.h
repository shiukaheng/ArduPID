#pragma once
#include "Arduino.h"
#include "FireTimer.h"




enum pOn { P_ON_E, P_ON_M };
enum mode { OFF, ON };
enum dir { FORWARD, BACKWARD };




class ArduPID
{
public:
	double* input;
	double* output;
	double* setpoint;




	void begin(double* _input,
		       double* _output,
		       double* _setpoint,
		       const double& _p = 0,
		       const double& _i = 0,
		       const double& _d = 0,
		       const pOn& _pOn = P_ON_E,
		       const dir& _direction = FORWARD,
		       const unsigned int& _minSamplePeriodMs = 0,
		       const double& _bias = 0);
	void start();
	void reset();
	void stop();
	virtual void compute();
	void setOutputLimits(const double& min, const double& max);
	void setWindUpLimits(const double& min, const double& max);
	void setDeadBand(const double& min, const double& max);
	void setPOn(const pOn& _pOn);
	void setBias(const double& _bias);
	void setCoefficients(const double& _p, const double& _i, const double& _d);
	void setDirection(const dir& _direction);
	void setSampleTime(const unsigned int& _minSamplePeriodMs);

	double B();
	double P();
	double I();
	double D();




protected:
	double bias;

	double outputMax = 255;
	double outputMin = 0;

	double windupMax = 1000;
	double windupMin = -1000;

	double deadBandMax = 0;
	double deadBandMin = 0;

	double curError;
	double curSetpoint;
	double curInput;

	double lastError;
	double lastSetpoint;
	double lastInput;

	double pIn;
	double iIn;
	double dIn;

	double kp;
	double ki;
	double kd;

	double pOut;
	double iOut;
	double dOut;

	pOn pOnType;
	mode modeType;
	dir direction;

	FireTimer timer;
};