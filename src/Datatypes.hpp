#ifndef __PBRCTYPES_HPP__FA25AD5E_D235_4C44_88AE_DCAF7423C619
#define __PBRCTYPES_HPP__FA25AD5E_D235_4C44_88AE_DCAF7423C619

#include <cmath>
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <bitset>
#include <memory>
#include <QString>


namespace nst {

class RobotControl;

/**
 * struct DVSEvent - A single DVS event.
 *
 */
struct DVSEvent {
	uint8_t id;
	uint64_t t;
	uint16_t x, y;
	uint8_t  p;

	typedef enum {
		TIMEFORMAT_0BYTES,
		TIMEFORMAT_2BYTES,
		TIMEFORMAT_3BYTES,
	} timeformat_t;
};

/**
 * struct IMUEvent - A single sensors sample.from the IMU
 *
 */
struct IMUEvent {
	double a[3] = {0.0};
	double g[3] = {0.0};
	double m[3] = {0.0};

	typedef enum {
		GYROSCOPE,
		ACCELEROMETER,
		MAGNETOMETER,
	} sensortype_t;

	typedef enum {
		YAXIS,
		ZAXIS,
		XAXIS,
	} sensoraxis_t;
};

/**
 * struct RPYEvent - A single estimate of RPY from all sensors.
 *
 */
struct RPYEvent {
	double roll[3]  = {0.0};
	double pitch[3] = {0.0};
	double yaw[3]   = {0.0};
};


/**
 * struct SensorEvent - event from the sensor processing system. it contains
 * both the raw data as well as an estimate of the current rpy. namely
 */
struct SensorEvent {
	IMUEvent imu;
	RPYEvent rpy;
};


/**
 * A user function
 */
struct UserFunction {
	const char *name;
	void (*fn)(RobotControl * const control,
	           std::shared_ptr<DVSEvent> dvs_ev,
		   std::shared_ptr<SensorEvent> sensor_ev);
};


}

/**
 * ostream conversion of an event to a textual representation
 */
inline
std::ostream& operator<<(std::ostream &out, nst::DVSEvent &e)
{
	out << "(" << e.x << "," << e.y << "," << (e.p > 0 ? 1 : 0) << "," << e.t << ")";
	return out;
}


#endif /* __PBRCTYPES_HPP__FA25AD5E_D235_4C44_88AE_DCAF7423C619 */

