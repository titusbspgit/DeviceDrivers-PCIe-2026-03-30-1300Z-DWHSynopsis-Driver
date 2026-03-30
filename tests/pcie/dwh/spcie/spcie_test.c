#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../../drivers/pcie/dwh/spcie/dwh_pcie_spcie.h"
#include "../../../drivers/pcie/dwh/common/dwh_pcie_regs.h"

static volatile uint32_t mock_dbi[0x1000/4];

#undef DWC_PCIE_DBI_BASE
#define DWC_PCIE_DBI_BASE ((uintptr_t)mock_dbi)

static void mock_extcap_chain(void)
{
    /* SPCIE at 0x120; chain: 0x100 -> 0x120 */
    mock_dbi[0x100/4] = (uint32_t)0xEEEE0029U; /* some other cap with next=0x120 */
    mock_dbi[0x120/4] = (uint32_t)SPCIE_CAP_ID; /* id */
}

int main(void)
{
    mock_extcap_chain();
    /* initialize registers */
    mock_dbi[(0x120 + SPCIE_LINK_CONTROL3_OFF)/4] = 0x5U;
    mock_dbi[(0x120 + SPCIE_LANE_ERR_STATUS_OFF)/4] = 0xA5A5U;

    uint32_t v=0;
    dwh_status_t rc = dwh_spcie_get_link_control3(&v);
    printf("LC3 rc=%d v=0x%08x\n", rc, v);

    rc = dwh_spcie_set_link_control3(v | 0x10U);
    printf("set LC3 rc=%d new=0x%08x\n", rc, mock_dbi[(0x120 + SPCIE_LINK_CONTROL3_OFF)/4]);

    rc = dwh_spcie_get_lane_err_status(&v);
    printf("LANE_ERR rc=%d v=0x%08x\n", rc, v);

    rc = dwh_spcie_clear_lane_err_status(0xA5A5U);
    printf("CLR rc=%d wrote=0x%08x\n", rc, mock_dbi[(0x120 + SPCIE_LANE_ERR_STATUS_OFF)/4]);

    return 0;
}
