# Single-clock research platform constraint file.
# Board IO assignment is intentionally out of scope for this repo; the focus is
# synthesis and implementation behavior under parameterized MAC-array variants.

create_clock -name sys_clk -period 10.000 [get_ports clk]

# TODO: Add tighter false-path or multicycle constraints only if later variants
# introduce clock-domain crossings or explicitly staged handshakes.
