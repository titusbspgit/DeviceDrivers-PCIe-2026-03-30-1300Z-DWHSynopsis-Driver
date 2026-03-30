#include <stdint.h>
#include <stdio.h>
#include "../../../drivers/pcie/dwh/link_eq/dwh_pcie_link_eq.h"
#include "../../../drivers/pcie/dwh/common/dwh_pcie_regs.h"

static volatile uint32_t mock_pl[0x1000/4];

#undef DWC_PCIE_PORT_LOGIC_BASE
#define DWC_PCIE_PORT_LOGIC_BASE ((uintptr_t)mock_pl)

int main(void)
{
    dwh_status_t rc;

    rc = dwh_linkeq_set_local_fs_lf(20U, 18U);
    printf("FS/LF rc=%d v=0x%08x\n", rc, mock_pl[GEN3_EQ_LOCAL_FS_LF_OFF/4]);

    rc = dwh_linkeq_program_pset(0U, 0U, 0x33U);
    printf("PSET rc=%d v=0x%08x\n", rc, mock_pl[0x8A0/4]);

    rc = dwh_linkeq_vendor_dllp(0xDEADU);
    printf("DLLP rc=%d v=0x%08x\n", rc, mock_pl[VENDOR_SPEC_DLLP_OFF/4]);

    rc = dwh_linkeq_port_force(0x1U, 10U);
    printf("PF rc=%d v=0x%08x\n", rc, mock_pl[PORT_FORCE_OFF/4]);

    return 0;
}
