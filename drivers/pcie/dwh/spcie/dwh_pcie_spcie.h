/*
 * dwh_pcie_spcie.h - Secondary PCIe Extended Capability APIs
 */
#ifndef DWH_PCIE_SPCIE_H
#define DWH_PCIE_SPCIE_H

#include <stdint.h>
#include <stdbool.h>
#include "../common/dwh_pcie_status.h"
#include "../common/dwh_pcie_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

dwh_status_t dwh_spcie_get_link_control3(uint32_t *val);
dwh_status_t dwh_spcie_set_link_control3(uint32_t val);

dwh_status_t dwh_spcie_get_lane_err_status(uint32_t *val);
dwh_status_t dwh_spcie_clear_lane_err_status(uint32_t mask);

#ifdef __cplusplus
}
#endif

#endif /* DWH_PCIE_SPCIE_H */
