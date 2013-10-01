#ifndef DIRECT_INPUT_DEFINITION_H_
#define DIRECT_INPUT_DEFINITION_H_

//direct input
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment( lib, "dinput8.lib")

#include <boost/intrusive_ptr.hpp>

typedef boost::intrusive_ptr< DirectInput >        DirectInputPtr;      ///< DirectInputオブジェクト
typedef boost::intrusive_ptr< DirectInputDevice >  DirectInputDevicePtr;///< DirectInputDeviceオブジェクト

#endif