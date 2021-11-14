#ifndef __CB__SYSCALLS_H
#define __CB__SYSCALLS_H
#include <cubebox/types.h>
#include <cubebox/interrupts.h>
#include <cubebox/w/multitasking.h>
namespace cb
{
	class SyscallHandler : public hardwarecommunication::InterruptHandler{
		public:
			SyscallHandler(hardwarecommunication::InterruptManager* interruptManager, cb::common::uint8_t InterruptNumber);
			~SyscallHandler();
			virtual cb::common::uint32_t HandleInterrupt(myos::common::uint32_t esp);
	};
}
#endif