# macfetch
tiny, fast system information *fetch script for mac/darwin in C.

forked from https://github.com/danyisill/macfetch

updated gpu detection and version detection, also added MacPorts (https://www.macports.org/) to package count report.


example output:
[lennox@lennoxs-iMac] % ./macfetch                                                                                                                                                                         [~/Projects/macfetch]
                lennox@lennoxs-iMac.local
      (/        os:     macOS 13.2.0 Ventura (22D49)
 ,adAb  dAba.   kernel: x86_64 Darwin 22.3.0
d$$$$$$$$$$$$P  model:  iMac18,1
$$$$$$$$$$$P    cpu:    Intel(R) Core(TM) i5-4590 CPU @ 3.30GHz
$$$$$$$$$$$b    gpu:    AMD Radeon RX 560
V$$$$$$$$$$$$P  disk:   153.3 / 465.1 GiB
 Y$$$$$$$$$$P   memory: 6.699 / 16 GiB
  "*"~  ~"*"    uptime: 1d37m14s
                pkgs:   387
                shell:  zsh
                theme:  Dark Blue
