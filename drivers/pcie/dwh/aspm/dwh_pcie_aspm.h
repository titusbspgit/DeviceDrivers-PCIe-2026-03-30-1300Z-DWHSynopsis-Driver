/*
 * dwh_pcie_aspm.h - ASPM L0s/L1 controls
 */
#ifndef DWH_PCIE_ASPM_H
#define DWH_PCIE_ASPM_H

#include <stdint.h>
#include <stdbool.h>
#include "../common/dwh_pcie_status.h"
#include "../common/dwh_pcie_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DWH_ASPM_DISABLE = 0,
    DWH_ASPM_L0S     = 1,
    DWH_ASPM_L1      = 2,
    DWH_ASPM_L0S_L1  = 3
} dwh_aspm_mode_t;

/** Enable/disable ASPM via standard Link Control and vendor acks. */
dwh_status_t dwh_aspm_set(dwh_aspm_mode_t mode);

#ifdef __cplusplus
}
#endif

#endif /* DWH_PCIE_ASPM_H */
