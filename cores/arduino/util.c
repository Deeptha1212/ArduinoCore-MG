#include "utils.h"

/** @fn long int ReadData(size_t *addr)
 * @brief Returns the value stored at a given address
 * @param size_t* addr
 * @return Unsigned Long
 */
unsigned long ReadData(size_t *addr)
{
	log_debug("addr = %x data = %x\n", addr, *addr);
	return *addr;
}

/** @fn void WriteData(size_t *addr, unsigned long val)
 * @brief  Writes a value to an address
 * @param size_t*
 * @param unsigned long
 * @return void
 */
void WriteData(size_t *addr, unsigned long val)
{
	*addr = val;
	log_debug("addr = %x data = %x\n", addr, *addr);
}
