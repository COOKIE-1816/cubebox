#ifndef __CB__GDT_H
#define __CB__GDT_H
#include <cubebox/types.h>
namespace cb{
	class GlobalDescriptorTable{
		public:
			class SegmentDescriptor{
				private:
					cb::common::uint16_t limit_lo;
					cb::common::uint16_t base_lo;
					cb::common::uint8_t base_hi;
					cb::common::uint8_t type;
					cb::common::uint8_t limit_hi;
					cb::common::uint8_t base_vhi;
				public:
					SegmentDescriptor(cb::common::uint32_t base, cb::common::uint32_t limit, cb::common::uint8_t type);
					cb::common::uint32_t Base();
					cb::common::uint32_t Limit();
			} __attribute__((packed));
		private:
			SegmentDescriptor nullSegmentSelector;
			SegmentDescriptor unusedSegmentSelector;
			SegmentDescriptor codeSegmentSelector;
			SegmentDescriptor dataSegmentSelector;
		public:
			GlobalDescriptorTable();
			~GlobalDescriptorTable();
			cb::common::uint16_t CodeSegmentSelector();
			cb::common::uint16_t DataSegmentSelector();
	};

}
#endif