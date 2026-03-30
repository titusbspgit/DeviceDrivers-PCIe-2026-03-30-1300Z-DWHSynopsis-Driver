/*
 * dwh_pcie_aspm.c - ASPM L0s/L1 controls
 */
#include "dwh_pcie_aspm.h"

static uint32_t lc_read(void)
{
    return dwh_dbi_readl(PCIE_CAP_LINK_CONTROL);
}
static void lc_write(uint32_t v)
{
    dwh_dbi_writel(v, PCIE_CAP_LINK_CONTROL);
}

dwh_status_t dwh_aspm_set(dwh_aspm_mode_t mode)
{
    uint32_t v = lc_read();
    v &= ~PCIE_LC_ASPM_MASK;
    switch (mode) {
    case DWH_ASPM_DISABLE: v |= 0U; break;
    case DWH_ASPM_L0S:     v |= PCIE_LC_ASPM_L0S; break;
    case DWH_ASPM_L1:      v |= PCIE_LC_ASPM_L1; break;
    case DWH_ASPM_L0S_L1:  v |= (PCIE_LC_ASPM_L0S | PCIE_LC_ASPM_L1); break;
    default: return DWH_E_PARAM;
    }
    lc_write(v);

    /* Mirror to vendor controls if present */
    uint32_t ack = 0U;
    if ((mode == DWH_ASPM_L0S) || (mode == DWH_ASPM_L0S_L1)) {
        ack |= ACK_F_ASPM_CTRL_L0S_EN;
    }
    if ((mode == DWH_ASPM_L1) || (mode == DWH_ASPM_L0S_L1)) {
        ack |= ACK_F_ASPM_CTRL_L1_EN;
    }
    dwh_pl_writel(ack, ACK_F_ASPM_CTRL_OFF);

    /* Optionally reflect in PORT_LINK_CTRL override */
    uint32_t plc = dwh_pl_readl(PORT_LINK_CTRL_OFF);
    plc &= ~PORT_LINK_CTRL_ASPM_EN_MASK;
    plc |= (uint32_t)mode & PORT_LINK_CTRL_ASPM_EN_MASK;
    dwh_pl_writel(plc, PORT_LINK_CTRL_OFF);

    return DWH_OK;
}
