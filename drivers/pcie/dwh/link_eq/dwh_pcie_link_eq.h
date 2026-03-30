/*
 * dwh_pcie_link_eq.h - Link Training and Equalization controls (debug)
 */
#ifndef DWH_PCIE_LINK_EQ_H
#define DWH_PCIE_LINK_EQ_H

#include <stdint.h>
#include <stdbool.h>
#include "../common/dwh_pcie_status.h"
#include "../common/dwh_pcie_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

dwh_status_t dwh_linkeq_set_local_fs_lf(uint8_t fs, uint8_t lf);
dwh_status_t dwh_linkeq_program_pset(uint8_t lane, uint8_t pset, uint8_t coef);
dwh_status_t dwh_linkeq_vendor_dllp(uint32_t cmd);
dwh_status_t dwh_linkeq_port_force(uint32_t ctrl, uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif /* DWH_PCIE_LINK_EQ_H */
