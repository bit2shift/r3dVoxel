#pragma once

#include <atomic>

namespace r3dVoxel
{
	namespace util
	{
		/*
		 * An std::atomic_flag-based spin-lock.
		 * Meets the Lockable concept.
		 * Therefore, usable with std::lock_guard.
		 */
		class spin_lock
		{
			std::atomic_flag m_flag = ATOMIC_FLAG_INIT;

		public:
			void lock()     noexcept {  while(m_flag.test_and_set(std::memory_order_acquire)); }
			void unlock()   noexcept {        m_flag.clear(std::memory_order_release);         }
			bool try_lock() noexcept { return m_flag.test_and_set(std::memory_order_acquire);  }
		};
	}
}
