/*
 * dwh_pcie_link_eq.c - Link Training and Equalization controls (debug)
 */
#include "dwh_pcie_link_eq.h"

/* GEN3_EQ_PSET_COEF_MAP__i: assume base at 0x8A0 with i stride 4 as placeholder */
#define GEN3_EQ_PSET_COEF_MAP_BASE  (0x8A0U)
#define GEN3_EQ_PSET_COEF_MAP_STRIDE (0x4U)

static inline uint32_t pset_addr(uint8_t lane)
{
    return (uint32_t)(GEN3_EQ_PSET_COEF_MAP_BASE + ((uint32_t)lane * GEN3_EQ_PSET_COEF_MAP_STRIDE));
}

dwh_status_t dwh_linkeq_set_local_fs_lf(uint8_t fs, uint8_t lf)
{
    uint32_t v = GEN3_EQ_MAKE_FS_LF(fs, lf);
    dwh_pl_writel(v, GEN3_EQ_LOCAL_FS_LF_OFF);
    return DWH_OK;
}

dwh_status_t dwh_linkeq_program_pset(uint8_t lane, uint8_t pset, uint8_t coef)
{
    (void)pset; /* placeholder: full map per-lane/per-pset not in excerpt */
    uint32_t addr = pset_addr(lane);
    uint32_t v = (uint32_t)coef;
    dwh_pl_writel(v, addr);
    return DWH_OK;
}

dwh_status_t dwh_linkeq_vendor_dllp(uint32_t cmd)
{
    dwh_pl_writel(cmd, VENDOR_SPEC_DLLP_OFF);
    return DWH_OK;
}

dwh_status_t dwh_linkeq_port_force(uint32_t ctrl, uint32_t timeout)
{
    dwh_pl_writel(ctrl, PORT_FORCE_OFF);
    while (timeout > 0U) {
        timeout--;
    }
    return DWH_OK;
}
