/*
 * dwh_pcie_pipe_phy.c - External PIPE PHY abstraction hooks
 */
#include "dwh_pcie_pipe_phy.h"

/* Default weak hooks */
dwh_status_t __attribute__((weak)) dwh_default_phy_read(uint16_t reg, uint16_t *val)
{
    (void)reg;
    if (val == NULL) {
        return DWH_E_PARAM;
    }
    *val = 0U;
    return DWH_E_UNSUPPORTED;
}

dwh_status_t __attribute__((weak)) dwh_default_phy_write(uint16_t reg, uint16_t val)
{
    (void)reg;
    (void)val;
    return DWH_E_UNSUPPORTED;
}

void dwh_pipe_phy_init(dwh_pipe_phy_if_t *iface)
{
    if (iface != NULL) {
        iface->phy_read = dwh_default_phy_read;
        iface->phy_write = dwh_default_phy_write;
        iface->phy_type = 0U;
    }
}

dwh_status_t dwh_pipe_phy_select(dwh_pipe_phy_if_t *iface, uint32_t phy_type)
{
    if (iface == NULL) {
        return DWH_E_PARAM;
    }
    iface->phy_type = phy_type;
    return DWH_OK;
}

dwh_status_t dwh_pipe_phy_read(dwh_pipe_phy_if_t *iface, uint16_t reg, uint16_t *val)
{
    if ((iface == NULL) || (iface->phy_read == NULL)) {
        return DWH_E_PARAM;
    }
    return iface->phy_read(reg, val);
}

dwh_status_t dwh_pipe_phy_write(dwh_pipe_phy_if_t *iface, uint16_t reg, uint16_t val)
{
    if ((iface == NULL) || (iface->phy_write == NULL)) {
        return DWH_E_PARAM;
    }
    return iface->phy_write(reg, val);
}

dwh_status_t dwh_pipe_phy_apply_eq(dwh_pipe_phy_if_t *iface, uint8_t fs, uint8_t lf)
{
    if (iface == NULL) {
        return DWH_E_PARAM;
    }
    /* Example EQ: write FS to 0x0100, LF to 0x0101 (placeholder addresses) */
    dwh_status_t st = dwh_pipe_phy_write(iface, 0x0100U, (uint16_t)fs);
    if (st != DWH_OK) {
        return st;
    }
    st = dwh_pipe_phy_write(iface, 0x0101U, (uint16_t)lf);
    return st;
}
