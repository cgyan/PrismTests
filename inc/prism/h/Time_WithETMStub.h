/*
 * ElapsedTimeMonitorStub.h
 * v0.*
 *
 *  Created on: 15 Mar 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_ELAPSED_TIME_MONITOR_STUB_H_
#define PRISM_ELAPSED_TIME_MONITOR_STUB_H_

#include <prism/global>
#include <prism/Time>
#include <prism/h/IElapsedTimeMonitor.h>

PRISM_BEGIN_NAMESPACE
PRISM_BEGIN_TEST_NAMESPACE

//=============================================================================================
// ElapsedTimeMonitorStub
//=============================================================================================
struct ElapsedTimeMonitorStub : public IElapsedTimeMonitor {
	enum { ElapsedTimeInMs = 6 };

	void
	start() override {}

	const int
	elapsed() const override {
		return ElapsedTimeInMs;
	}
};
//=============================================================================================
// Time_WithElapsedTimeMonitorStub
//=============================================================================================
class Time_WithElapsedTimeMonitorStub : public prism::Time {
public:
	Time_WithElapsedTimeMonitorStub()
	: Time()
	{
		setEtm(std::make_shared<ElapsedTimeMonitorStub>());
	}
};

PRISM_END_TEST_NAMESPACE
PRISM_END_NAMESPACE

#endif /* PRISM_ELAPSED_TIME_MONITOR_STUB_H_ */
