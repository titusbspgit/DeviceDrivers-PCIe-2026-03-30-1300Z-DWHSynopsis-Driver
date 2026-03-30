/*
 * dwh_pcie_flit.h - PCIe 6.0 Flit Mode feature APIs
 */
#ifndef DWH_PCIE_FLIT_H
#define DWH_PCIE_FLIT_H

#include <stdint.h>
#include <stdbool.h>
#include "../common/dwh_pcie_status.h"
#include "../common/dwh_pcie_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Context for feature operations (DBI and Port Logic bases are global macros). */
typedef struct {
    uint32_t reserved; /* keep struct non-empty per C standard */
} dwh_pcie_ctx_t;

/** Initialize minimal context (placeholder for future use). */
dwh_status_t dwh_pcie_init(dwh_pcie_ctx_t *ctx);

/** Discover if PL64G capability exists; returns true if found. */
bool dwh_pcie_flit_cap_present(void);

/** Read PL64G capability and status registers into provided pointers (may be NULL). */
dwh_status_t dwh_pcie_flit_read_cap_status(uint32_t *cap, uint32_t *status);

/** Query if link is operating in Flit Mode (from Link Status2 bit). */
bool dwh_pcie_flit_link_active(void);

/** Attempt to enable flit operation; returns UNSUPPORTED if no control available. */
dwh_status_t dwh_pcie_flit_enable(uint32_t timeout_cycles);

/** Disable flit operation if controllable; UNSUPPORTED otherwise. */
dwh_status_t dwh_pcie_flit_disable(uint32_t timeout_cycles);

#ifdef __cplusplus
}
#endif

#endif /* DWH_PCIE_FLIT_H */
