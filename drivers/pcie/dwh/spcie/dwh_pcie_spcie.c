/*
 * dwh_pcie_spcie.c - Secondary PCIe Extended Capability implementation
 */
#include "dwh_pcie_spcie.h"

/* Reuse ext cap find from flit module by local copy to keep files independent. */
static uint32_t dwh_extcap_find(uint16_t cap_id)
{
    uint32_t off = 0x100U;
    while (off != 0U) {
        uint32_t hdr = dwh_dbi_readl(off);
        if (hdr == 0U) {
            break;
        }
        uint16_t id = (uint16_t)(hdr & 0xFFFFU);
        if (id == cap_id) {
            return off;
        }
        off = (hdr >> 20) & 0xFFFU;
    }
    return 0U;
}

dwh_status_t dwh_spcie_get_link_control3(uint32_t *val)
{
    if (val == NULL) {
        return DWH_E_PARAM;
    }
    uint32_t base = dwh_extcap_find(SPCIE_CAP_ID);
    if (base == 0U) {
        return DWH_E_UNSUPPORTED;
    }
    *val = dwh_dbi_readl(base + SPCIE_LINK_CONTROL3_OFF);
    return DWH_OK;
}

dwh_status_t dwh_spcie_set_link_control3(uint32_t v)
{
    uint32_t base = dwh_extcap_find(SPCIE_CAP_ID);
    if (base == 0U) {
        return DWH_E_UNSUPPORTED;
    }
    dwh_dbi_writel(v, base + SPCIE_LINK_CONTROL3_OFF);
    return DWH_OK;
}

dwh_status_t dwh_spcie_get_lane_err_status(uint32_t *val)
{
    if (val == NULL) {
        return DWH_E_PARAM;
    }
    uint32_t base = dwh_extcap_find(SPCIE_CAP_ID);
    if (base == 0U) {
        return DWH_E_UNSUPPORTED;
    }
    *val = dwh_dbi_readl(base + SPCIE_LANE_ERR_STATUS_OFF);
    return DWH_OK;
}

dwh_status_t dwh_spcie_clear_lane_err_status(uint32_t mask)
{
    uint32_t base = dwh_extcap_find(SPCIE_CAP_ID);
    if (base == 0U) {
        return DWH_E_UNSUPPORTED;
    }
    /* Assume W1C behavior; write mask to clear */
    dwh_dbi_writel(mask, base + SPCIE_LANE_ERR_STATUS_OFF);
    return DWH_OK;
}
