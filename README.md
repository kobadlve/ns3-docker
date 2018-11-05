# NS3-Docker

Docker image for [NS-3](https://www.nsnam.org)

## Build Image

Build image - `$ docker build -t ns3 .`

## GUI on MacOS

1. Install XQuartz (Enable "Allow connections from network clients" in preferences)
2. `$ xhost + 127.0.0.1`
3. Run `$ docker run -it -e DISPLAY=docker.for.mac.localhost:0 -v /tmp/.X11-unix:/tmp/.X11-unix ns3`

## Copy and build your scripts

```
$ docker cp scirpt <Container ID>:/opt/ns3/ns-3.29/scratch/script
$ docker run -it -e DISPLAY=docker.for.mac.localhost:0 -v /tmp/.X11-unix:/tmp/.X11-unix ns3
$ ./waf
```
