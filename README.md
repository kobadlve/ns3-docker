# NS3-Docker

Docker image for [NS-3](https://www.nsnam.org)

Moduels
```
Modules built:
antenna                   aodv                      applications
bridge                    buildings                 config-store
core                      csma                      csma-layout
dsdv                      dsr                       energy
fd-net-device             flow-monitor              internet
internet-apps             lr-wpan                   lte
mesh                      mobility                  mpi
netanim (no Python)       network                   nix-vector-routing
olsr                      point-to-point            point-to-point-layout
propagation               sixlowpan                 spectrum
stats                     tap-bridge                test (no Python)
topology-read             traffic-control           uan
virtual-net-device        visualizer                wave
wifi                      wimax

Modules not built (see ns-3 tutorial for explanation):
brite                     click                     openflow
```

## Build Image

Build image - `$ docker build -t ns3 .`

## GUI on MacOS

1. Install XQuartz (Enable "Allow connections from network clients" in preferences)
2. `$ xhost + 127.0.0.1`
3. Run `$ docker run -it -e DISPLAY=docker.for.mac.localhost:0 -v /tmp/.X11-unix:/tmp/.X11-unix -v /path/to/ns3-docker/scracth:/opt/ns3/ns-3.29/scratch ns3`

## Run script

* Run C++ simulation - `$ ./waf --run ex.cc`
* Run Python simulation - `$ ./waf --pyrun ex.py`

