#pragma once

#include <WinSock2.h>
#include <Windows.h>

#include <vector>
#include <string>
#include <memory>

#include "definitions.h"
#include "bitlocker.h"

#include "Utils/buffer.h"

typedef struct
{
	bool bitlocked = false;
	struct
	{
		FVE_BLOCK_HEADER block_header = { 0 };
		FVE_HEADER		 header = { 0 };
		std::vector<std::shared_ptr<Buffer<PFVE_ENTRY>>> entries;
	} metadata[3];
} bitlocker_info;

class Volume
{
	friend class Disk;
private:
	std::string _name;
	std::string _label;
	std::string _filesystem;
	std::vector<std::string> _mountpoints;
	std::string _guid_type;
	DWORD		_serial_number;
	DWORD		_partition_type;
	DWORD		_type;
	DWORD		_index;
	DWORD		_disk_index;
	DWORD64		_offset;
	DWORD64		_size;
	DWORD64		_free;
	BOOL		_bootable;
	bitlocker_info	_bitlocker;
	Buffer<PBYTE> _bootsector;

public:
	explicit Volume(HANDLE h, PARTITION_INFORMATION_EX p, int index);
	std::string name()					const { return _name; }
	std::string label()					const { return _label; }
	std::string filesystem()			const { return _filesystem; }
	std::vector<std::string> mountpoints()	const { return _mountpoints; }
	std::string guid_type()				const { return _guid_type; }
	DWORD serial_number()				const { return _serial_number; }
	DWORD partition_type()				const { return _partition_type; }
	DWORD type()						const { return _type; }
	DWORD index()						const { return _index; }
	DWORD disk_index()					const { return _disk_index; }
	DWORD64 offset()					const { return _offset; }
	DWORD64 size()						const { return _size; }
	DWORD64 free()						const { return _free; }
	BOOL bootable()						const { return _bootable; }
	bitlocker_info	bitlocker()			const { return _bitlocker; }
	bool is_mounted()					const { return _mountpoints.size() > 0; }
	PBYTE bootsector() { return _bootsector.data(); }
};


namespace core
{
	namespace win
	{
		namespace volumes
		{
			std::vector<std::shared_ptr<Volume>> list();
		}
	}
}