#pragma once

#include "rpcs3/utils/sleep_queue.h"

namespace vm { using namespace ps3; }

// Aux
class PPUThread;
class cpu_thread;

struct sys_lwmutex_t;

struct sys_lwcond_attribute_t
{
	char name[8];
};

struct sys_lwcond_t
{
	vm::bptr<sys_lwmutex_t> lwmutex;
	be_t<u32> lwcond_queue; // lwcond pseudo-id
};

struct lv2_lwcond_t
{
	const u64 name;

	sleep_queue<cpu_thread> sq;

	lv2_lwcond_t(u64 name)
		: name(name)
	{
	}

	void notify(lv2_lock_t, cpu_thread* thread, const std::shared_ptr<lv2_lwmutex_t>& mutex, bool mode2);
};

// SysCalls
s32 _sys_lwcond_create(vm::ptr<u32> lwcond_id, u32 lwmutex_id, vm::ptr<sys_lwcond_t> control, u64 name, u32 arg5);
s32 _sys_lwcond_destroy(u32 lwcond_id);
s32 _sys_lwcond_signal(u32 lwcond_id, u32 lwmutex_id, u32 ppu_thread_id, u32 mode);
s32 _sys_lwcond_signal_all(u32 lwcond_id, u32 lwmutex_id, u32 mode);
s32 _sys_lwcond_queue_wait(PPUThread& ppu, u32 lwcond_id, u32 lwmutex_id, u64 timeout);
