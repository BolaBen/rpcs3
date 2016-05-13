#include "stdafx.h"
#include "Emu/System.h"
#include "Emu/IdManager.h"
#include "Emu/Cell/PPUModule.h"

#include "sysPrxForUser.h"

extern logs::channel sysPrxForUser;

struct HeapInfo
{
	const std::string name;

	HeapInfo(const char* name)
		: name(name)
	{
	}
};

u32 _sys_heap_create_heap(vm::cptr<char> name, u32 arg2, u32 arg3, u32 arg4)
{
	sysPrxForUser.warning("_sys_heap_create_heap(name=*0x%x, arg2=0x%x, arg3=0x%x, arg4=0x%x)", name, arg2, arg3, arg4);

	return idm::make<HeapInfo>(name.get_ptr());
}

s32 _sys_heap_delete_heap(u32 heap)
{
	sysPrxForUser.warning("_sys_heap_delete_heap(heap=0x%x)", heap);

	idm::remove<HeapInfo>(heap);

	return CELL_OK;
}

u32 _sys_heap_malloc(u32 heap, u32 size)
{
	sysPrxForUser.warning("_sys_heap_malloc(heap=0x%x, size=0x%x)", heap, size);

	return vm::alloc(size, vm::main);
}

u32 _sys_heap_memalign(u32 heap, u32 align, u32 size)
{
	sysPrxForUser.warning("_sys_heap_memalign(heap=0x%x, align=0x%x, size=0x%x)", heap, align, size);

	return vm::alloc(size, vm::main, std::max<u32>(align, 4096));
}

s32 _sys_heap_free(u32 heap, u32 addr)
{
	sysPrxForUser.warning("_sys_heap_free(heap=0x%x, addr=0x%x)", heap, addr);

	vm::dealloc(addr, vm::main);

	return CELL_OK;
}

s32 _sys_heap_alloc_heap_memory()
{
	throw EXCEPTION("");
}

s32 _sys_heap_get_mallinfo()
{
	throw EXCEPTION("");
}

s32 _sys_heap_get_total_free_size()
{
	throw EXCEPTION("");
}

s32 _sys_heap_stats()
{
	throw EXCEPTION("");
}

void sysPrxForUser_sys_heap_init()
{
	REG_FUNC(sysPrxForUser, _sys_heap_create_heap);
	REG_FUNC(sysPrxForUser, _sys_heap_delete_heap);
	REG_FUNC(sysPrxForUser, _sys_heap_malloc);
	REG_FUNC(sysPrxForUser, _sys_heap_memalign);
	REG_FUNC(sysPrxForUser, _sys_heap_free);
	REG_FUNC(sysPrxForUser, _sys_heap_alloc_heap_memory);
	REG_FUNC(sysPrxForUser, _sys_heap_get_mallinfo);
	REG_FUNC(sysPrxForUser, _sys_heap_get_total_free_size);
	REG_FUNC(sysPrxForUser, _sys_heap_stats);
}
