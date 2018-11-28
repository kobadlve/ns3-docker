// udp-echo-sample.cc

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/point-to-point-layout-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Test1");

int main (int argc, char *argv[]) {
  std::string animFile = "star-animation.xml";

  Time::SetResolution(Time::NS);

  // Setting udp
  LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

  // Define node
  NodeContainer n1_nodes, n2_nodes;
  n1_nodes.Create(2);
  n2_nodes.Add(n1_nodes.Get(1));
  n2_nodes.Create(1);

  // Define point-to-point
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute("DataRate", StringValue("1Mbps"));
  pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));
  NetDeviceContainer dev1 = pointToPoint.Install(n1_nodes);
  NetDeviceContainer dev2 = pointToPoint.Install(n2_nodes);

  // Internet protocol stack install to node
  InternetStackHelper stack;
  stack.InstallAll();

  // Setting address
  Ipv4AddressHelper n1_address;
  n1_address.SetBase("10.1.1.0", "255.255.255.0", "0.0.0.1");
  Ipv4InterfaceContainer n1_interfaces = n1_address.Assign(dev1);
  Ipv4AddressHelper n2_address;
  n2_address.SetBase("10.2.2.0", "255.255.255.0", "0.0.0.1");
  Ipv4InterfaceContainer n2_interfaces = n2_address.Assign(dev2);

  // Create Udp echo server by port number
  UdpEchoServerHelper echoServer(9);

  // Setting server
  ApplicationContainer serverApps;
  serverApps = echoServer.Install(n1_nodes.Get(1));
  serverApps.Start(Seconds(1.0));
  serverApps.Stop(Seconds(10.0));

  // Create Udp echo client
  UdpEchoClientHelper echoClient(n1_interfaces.GetAddress(1), 9);

  // Setting client
  echoClient.SetAttribute("MaxPackets", UintegerValue(1));
  echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
  echoClient.SetAttribute("PacketSize", UintegerValue(1024));

  // Install client to node0
  ApplicationContainer clientApps;
  clientApps = echoClient.Install(n1_nodes.Get(0));
  clientApps.Start(Seconds(2.0));
  clientApps.Stop(Seconds(10.0));

  // Setting node position 
  AnimationInterface::SetConstantPosition(n1_nodes.Get(0), 0, 10, 0);
  AnimationInterface::SetConstantPosition(n1_nodes.Get(1), 10, 10, 0);
  AnimationInterface::SetConstantPosition(n2_nodes.Get(1), 20, 10, 0);

  AnimationInterface anim(animFile);

  Simulator::Run();
  Simulator::Destroy();
  return 0;
}
