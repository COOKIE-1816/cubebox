#ifndef __CB__HARDWARECOMMUNICATION__PCI_H
#define __CB__HARDWARECOMMUNICATION__PCI_H
#include <cubebox/port.h>
#include <cubebox/drivers/driver.h>
#include <cubebox/types.h>
#include <cubebox/interrupts.h>
#include <cubebox/memorymanagement.h>
namespace cb
{
	namespace hardwarecommunication
	{
		enum BaseAddressRegisterType{
			MemoryMapping = 0,
			InputOutput = 1
		};
		class BaseAddressRegister{
			public:
				bool prefetchable;
				cb::common::uint8_t* address;
				cb::common::uint32_t size;
				BaseAddressRegisterType type;
		};
		class PeripheralComponentInterconnectDeviceDescriptor{
			public:
				cb::common::uint32_t portBase;
				cb::common::uint32_t interrupt;
				cb::common::uint16_t bus;
				cb::common::uint16_t device;
				cb::common::uint16_t function;
				cb::common::uint16_t vendor_id;
				cb::common::uint16_t device_id;
				cb::common::uint8_t class_id;
				cb::common::uint8_t subclass_id;
				cb::common::uint8_t interface_id;
				cb::common::uint8_t revision;
				PeripheralComponentInterconnectDeviceDescriptor();
				~PeripheralComponentInterconnectDeviceDescriptor();
		};
		class PeripheralComponentInterconnectController{
			Port32Bit dataPort;
			Port32Bit commandPort;
			public:
				PeripheralComponentInterconnectController();
				~PeripheralComponentInterconnectController();
				cb::common::uint32_t Read(cb::common::uint16_t bus, cb::common::uint16_t device, cb::common::uint16_t function, cb::common::uint32_t registeroffset);
				void Write(cb::common::uint16_t bus, cb::common::uint16_t device, cb::common::uint16_t function, cb::common::uint32_t registeroffset, cb::common::uint32_t value);
				bool DeviceHasFunctions(cb::common::uint16_t bus, cb::common::uint16_t device);
				void SelectDrivers(cb::drivers::DriverManager* driverManager, cb::hardwarecommunication::InterruptManager* interrupts);
				cb::drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, cb::hardwarecommunication::InterruptManager* interrupts);
				PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(cb::common::uint16_t bus, cb::common::uint16_t device, cb::common::uint16_t function);
				BaseAddressRegister GetBaseAddressRegister(cb::common::uint16_t bus, cb::common::uint16_t device, cb::common::uint16_t function, cb::common::uint16_t bar);
		};
	}
}
#endif