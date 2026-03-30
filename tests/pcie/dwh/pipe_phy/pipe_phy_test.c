#include <stdint.h>
#include <stdio.h>
#include "../../../drivers/pcie/dwh/pipe_phy/dwh_pcie_pipe_phy.h"

int main(void)
{
    dwh_pipe_phy_if_t phy;
    dwh_pipe_phy_init(&phy);

    dwh_status_t st = dwh_pipe_phy_select(&phy, 1U);
    printf("sel=%d type=%u\n", st, phy.phy_type);

    uint16_t v=0;
    st = dwh_pipe_phy_read(&phy, 0x10U, &v);
    printf("read st=%d v=%u\n", st, v);

    st = dwh_pipe_phy_write(&phy, 0x10U, 0x55U);
    printf("write st=%d\n", st);

    st = dwh_pipe_phy_apply_eq(&phy, 10U, 12U);
    printf("eq st=%d\n", st);

    return 0;
}
