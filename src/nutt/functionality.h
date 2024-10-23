#pragma once

#include "device.h"

namespace nutt {

class Functionality {
public:
	Functionality(uint8_t index) : index_(index) {};
	~Functionality() {};

	static constexpr const char *TAG = "nutt.Functionality";
	//static constexpr const size_t NUM_EP_PER_LIGHT = 6;

	inline uint8_t index() const { return index_; }

	// attach to device specifying Zigbee Clusters
	virtual void attach(Device &device) = 0;

	virtual unsigned long run() = 0;

	// report changes to ui
	virtual void request_refresh() = 0;
	virtual void refresh() = 0;

protected:
	const uint8_t index_;
	Device *device_{nullptr};
	
};

} // namespace nutt
