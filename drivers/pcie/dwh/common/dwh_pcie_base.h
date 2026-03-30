/*
 * dwh_pcie_base.h - Platform-neutral base and MMIO accessors for Synopsys DWC PCIe
 * RCI-ag-DrvGen Agent
 */
#ifndef DWH_PCIE_BASE_H
#define DWH_PCIE_BASE_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Integration notes:
 * - Define DWC_PCIE_DBI_BASE and DWC_PCIE_PORT_LOGIC_BASE to valid MMIO base addresses
 *   in your platform config before including this header. If not provided, weak
 *   placeholders are declared here but compilation will error out unless overridden.
 */
#ifndef DWC_PCIE_DBI_BASE
#warning "DWC_PCIE_DBI_BASE not defined by platform; using 0U placeholder"
#define DWC_PCIE_DBI_BASE (0U)
#endif
#ifndef DWC_PCIE_PORT_LOGIC_BASE
#warning "DWC_PCIE_PORT_LOGIC_BASE not defined by platform; using 0U placeholder"
#define DWC_PCIE_PORT_LOGIC_BASE (0U)
#endif

/* If the controller MMIO window is little-endian while CPU is big-endian, set to 1 */
#ifndef DWC_PCIE_MMIO_LE_SPACE
#define DWC_PCIE_MMIO_LE_SPACE (0)
#endif

/* Memory barriers: provide weak definitions if not available */
static inline void dwh_pcie_mem_barrier(void)
{
    __asm__ volatile ("dsb sy" ::: "memory");
    __asm__ volatile ("isb" ::: "memory");
}

/* Byte-swap helpers */
static inline uint32_t dwh_bswap32(uint32_t v)
{
    return ((v & 0x000000FFUL) << 24) |
           ((v & 0x0000FF00UL) << 8)  |
           ((v & 0x00FF0000UL) >> 8)  |
           ((v & 0xFF000000UL) >> 24);
}

static inline uint64_t dwh_bswap64(uint64_t v)
{
    return ((uint64_t)dwh_bswap32((uint32_t)(v >> 32))      ) |
           ((uint64_t)dwh_bswap32((uint32_t)(v & 0xFFFFFFFFULL)) << 32);
}

/* Endianness-safe MMIO accessors (deterministic, volatile) */
static inline void dwh_writel(uint32_t val, uintptr_t addr)
{
    volatile uint32_t *p = (volatile uint32_t *)addr;
#if DWC_PCIE_MMIO_LE_SPACE
    *p = dwh_bswap32(val);
#else
    *p = val;
#endif
    dwh_pcie_mem_barrier();
}

static inline uint32_t dwh_readl(uintptr_t addr)
{
    volatile const uint32_t *p = (volatile const uint32_t *)addr;
    uint32_t v = *p;
#if DWC_PCIE_MMIO_LE_SPACE
    v = dwh_bswap32(v);
#endif
    dwh_pcie_mem_barrier();
    return v;
}

static inline void dwh_writeq(uint64_t val, uintptr_t addr)
{
    volatile uint64_t *p = (volatile uint64_t *)addr;
#if DWC_PCIE_MMIO_LE_SPACE
    *p = dwh_bswap64(val);
#else
    *p = val;
#endif
    dwh_pcie_mem_barrier();
}

static inline uint64_t dwh_readq(uintptr_t addr)
{
    volatile const uint64_t *p = (volatile const uint64_t *)addr;
    uint64_t v = *p;
#if DWC_PCIE_MMIO_LE_SPACE
    v = dwh_bswap64(v);
#endif
    dwh_pcie_mem_barrier();
    return v;
}

#ifdef __cplusplus
}
#endif

#endif /* DWH_PCIE_BASE_H */
