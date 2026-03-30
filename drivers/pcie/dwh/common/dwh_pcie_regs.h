/*
 * dwh_pcie_regs.h - Common register offsets/macros for DWC PCIe (v6.00a excerpts)
 * RCI-ag-DrvGen Agent
 */
#ifndef DWH_PCIE_REGS_H
#define DWH_PCIE_REGS_H

#include <stdint.h>
#include "dwh_pcie_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/* PCIe Capability common (DBI space) */
#define PCIE_CAP_OFFSET                 (0x70U)   /* typical; may vary */
#define PCIE_CAP_LINK_CONTROL           (PCIE_CAP_OFFSET + 0x10U)
#define PCIE_CAP_LINK_STATUS2           (PCIE_CAP_OFFSET + 0x34U) /* includes Flit Mode Status bit */

/* Link Control [1:0] ASPM */
#define PCIE_LC_ASPM_MASK               (0x3U)
#define PCIE_LC_ASPM_L0S                (0x1U)
#define PCIE_LC_ASPM_L1                 (0x2U)

/* Link Status2: Flit Mode Status bit (per excerpt) */
#define PCIE_LS2_FLIT_MODE_STATUS_BIT   (26U)
#define PCIE_LS2_FLIT_MODE_STATUS_MASK  (1UL << PCIE_LS2_FLIT_MODE_STATUS_BIT)

/* Secondary PCIe Extended Capability (discover base B via ext cap walk) */
#define SPCIE_CAP_ID                    (0x0023U) /* Secondary PCIe Extended Capability ID per spec */
#define SPCIE_CAP_HDR_OFF               (0x0U)
#define SPCIE_LINK_CONTROL3_OFF         (0x4U)
#define SPCIE_LANE_ERR_STATUS_OFF       (0x8U)

/* PL64G Extended Capability (discover base B via ext cap walk) */
#define PL64G_CAP_ID                    (0x0029U) /* Physical Layer 64.0 GT/s Extended Capability (spec-defined) */
#define PL64G_CAPABILITY_OFF            (0x4U)
#define PL64G_CONTROL_OFF               (0x8U)
#define PL64G_STATUS_OFF                (0xCU)

/* Port Logic (DWC_PCIE_DSP) base is DWC_PCIE_PORT_LOGIC_BASE */
#define VENDOR_SPEC_DLLP_OFF            (0x704U)
#define PORT_FORCE_OFF                  (0x708U)
#define ACK_F_ASPM_CTRL_OFF             (0x70CU)
#define PORT_LINK_CTRL_OFF              (0x710U)
#define GEN3_RELATED_OFF                (0x890U)
#define GEN3_EQ_LOCAL_FS_LF_OFF         (0x894U)

/* Bit fields: incomplete in excerpt; define safe masks used by drivers */
/* PORT_LINK_CTRL: define ASPM override enables if present (placeholder masks) */
#define PORT_LINK_CTRL_ASPM_EN_MASK     (0x00000003UL)

/* ACK_F_ASPM_CTRL: placeholder for ACK frequency and L0/L1 req enables */
#define ACK_F_ASPM_CTRL_L0S_EN          (0x00000001UL)
#define ACK_F_ASPM_CTRL_L1_EN           (0x00000002UL)

/* GEN3_EQ_LOCAL_FS_LF: FS [5:0], LF [13:8] typical encoding */
#define GEN3_EQ_FS_MASK                 (0x3FU)
#define GEN3_EQ_LF_SHIFT                (8U)
#define GEN3_EQ_LF_MASK                 (0x3FU << GEN3_EQ_LF_SHIFT)
#define GEN3_EQ_MAKE_FS_LF(fs, lf)      ((((uint32_t)(fs)) & GEN3_EQ_FS_MASK) | ((((uint32_t)(lf)) & 0x3FU) << GEN3_EQ_LF_SHIFT))

/* Helpers to access DBI and PORT LOGIC */
static inline uint32_t dwh_dbi_readl(uint32_t off)
{
    return dwh_readl((uintptr_t)DWC_PCIE_DBI_BASE + (uintptr_t)off);
}
static inline void dwh_dbi_writel(uint32_t val, uint32_t off)
{
    dwh_writel(val, (uintptr_t)DWC_PCIE_DBI_BASE + (uintptr_t)off);
}
static inline uint32_t dwh_pl_readl(uint32_t off)
{
    return dwh_readl((uintptr_t)DWC_PCIE_PORT_LOGIC_BASE + (uintptr_t)off);
}
static inline void dwh_pl_writel(uint32_t val, uint32_t off)
{
    dwh_writel(val, (uintptr_t)DWC_PCIE_PORT_LOGIC_BASE + (uintptr_t)off);
}

#ifdef __cplusplus
}
#endif

#endif /* DWH_PCIE_REGS_H */
