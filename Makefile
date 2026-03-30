CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -Werror
INCLUDES = -Idrivers/pcie/dwh/common

DRIVERS = \
	drivers/pcie/dwh/flit_mode/dwh_pcie_flit.c \
	drivers/pcie/dwh/pipe_phy/dwh_pcie_pipe_phy.c \
	drivers/pcie/dwh/spcie/dwh_pcie_spcie.c \
	drivers/pcie/dwh/link_eq/dwh_pcie_link_eq.c \
	drivers/pcie/dwh/aspm/dwh_pcie_aspm.c

all: flit_test pipe_phy_test spcie_test link_eq_test aspm_test

flit_test: tests/pcie/dwh/flit_mode/flit_test.c $(DRIVERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

pipe_phy_test: tests/pcie/dwh/pipe_phy/pipe_phy_test.c $(DRIVERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

spcie_test: tests/pcie/dwh/spcie/spcie_test.c $(DRIVERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

link_eq_test: tests/pcie/dwh/link_eq/link_eq_test.c $(DRIVERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

aspm_test: tests/pcie/dwh/aspm/aspm_test.c $(DRIVERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

clean:
	rm -f flit_test pipe_phy_test spcie_test link_eq_test aspm_test
