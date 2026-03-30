/*
 * dwh_pcie_pipe_phy.h - External PIPE PHY abstraction hooks
 */
#ifndef DWH_PCIE_PIPE_PHY_H
#define DWH_PCIE_PIPE_PHY_H

#include <stdint.h>
#include <stdbool.h>
#include "../common/dwh_pcie_status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef dwh_status_t (*dwh_phy_read_fn)(uint16_t reg, uint16_t *val);
typedef dwh_status_t (*dwh_phy_write_fn)(uint16_t reg, uint16_t val);

typedef struct {
    dwh_phy_read_fn  phy_read;
    dwh_phy_write_fn phy_write;
    uint32_t phy_type; /* vendor-specific selector */
} dwh_pipe_phy_if_t;

/* Weak default hooks that return unsupported; platform may override. */
dwh_status_t __attribute__((weak)) dwh_default_phy_read(uint16_t reg, uint16_t *val);
dwh_status_t __attribute__((weak)) dwh_default_phy_write(uint16_t reg, uint16_t val);

void dwh_pipe_phy_init(dwh_pipe_phy_if_t *iface);
dwh_status_t dwh_pipe_phy_select(dwh_pipe_phy_if_t *iface, uint32_t phy_type);
dwh_status_t dwh_pipe_phy_read(dwh_pipe_phy_if_t *iface, uint16_t reg, uint16_t *val);
dwh_status_t dwh_pipe_phy_write(dwh_pipe_phy_if_t *iface, uint16_t reg, uint16_t val);
dwh_status_t dwh_pipe_phy_apply_eq(dwh_pipe_phy_if_t *iface, uint8_t fs, uint8_t lf);

#ifdef __cplusplus
}
#endif

#endif /* DWH_PCIE_PIPE_PHY_H */
