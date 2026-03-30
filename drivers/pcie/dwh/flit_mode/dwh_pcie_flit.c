/*
 * dwh_pcie_flit.c - PCIe 6.0 Flit Mode feature implementation
 */
#include "dwh_pcie_flit.h"

/* Extended capability walk helper: returns base offset for given cap ID or 0 if not found. */
static uint32_t dwh_extcap_find(uint16_t cap_id)
{
    /* Standard PCIe Ext Cap chain starts at 0x100 in DBI */
    uint32_t off = 0x100U;
    while (off != 0U) {
        uint32_t hdr = dwh_dbi_readl(off);
        if (hdr == 0U) {
            break; /* no more caps */
        }
        uint16_t id = (uint16_t)(hdr & 0xFFFFU);
        if (id == cap_id) {
            return off;
        }
        off = (hdr >> 20) & 0xFFFU; /* next capability pointer (DWORD aligned) */
    }
    return 0U;
}

dwh_status_t dwh_pcie_init(dwh_pcie_ctx_t *ctx)
{
    if (ctx == NULL) {
        return DWH_E_PARAM;
    }
    ctx->reserved = 0U;
    return DWH_OK;
}

bool dwh_pcie_flit_cap_present(void)
{
    uint32_t base = dwh_extcap_find(PL64G_CAP_ID);
    return (base != 0U);
}

dwh_status_t dwh_pcie_flit_read_cap_status(uint32_t *cap, uint32_t *status)
{
    uint32_t base = dwh_extcap_find(PL64G_CAP_ID);
    if (base == 0U) {
        return DWH_E_UNSUPPORTED;
    }
    if (cap != NULL) {
        *cap = dwh_dbi_readl(base + PL64G_CAPABILITY_OFF);
    }
    if (status != NULL) {
        *status = dwh_dbi_readl(base + PL64G_STATUS_OFF);
    }
    return DWH_OK;
}

bool dwh_pcie_flit_link_active(void)
{
    uint32_t v = dwh_dbi_readl(PCIE_CAP_LINK_STATUS2);
    return ((v & PCIE_LS2_FLIT_MODE_STATUS_MASK) != 0U);
}

static dwh_status_t dwh_wait_flit_active(bool exp, uint32_t timeout)
{
    while (timeout > 0U) {
        bool act = dwh_pcie_flit_link_active();
        if (act == exp) {
            return DWH_OK;
        }
        timeout--;
    }
    return DWH_E_TIMEOUT;
}

dwh_status_t dwh_pcie_flit_enable(uint32_t timeout_cycles)
{
    /* No known SW control per excerpt; treat as policy-based and poll status */
    return dwh_wait_flit_active(true, timeout_cycles);
}

dwh_status_t dwh_pcie_flit_disable(uint32_t timeout_cycles)
{
    return dwh_wait_flit_active(false, timeout_cycles);
}
