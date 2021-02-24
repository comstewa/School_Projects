# Lab 3 Skeleton
#
# Based on of_tutorial by James McCauley

from pox.core import core
import pox.openflow.libopenflow_01 as of
from pox.lib.addresses import IPAddr, IPAddr6, EthAddr

log = core.getLogger()

class Firewall (object):
  """
  A Firewall object is created for each switch that connects.
  A Connection object for that switch is passed to the __init__ function.
  """
  def __init__ (self, connection):
    # Keep track of the connection to the switch so that we can
    # send it messages!
    self.connection = connection

    # This binds our PacketIn event listener
    connection.addListeners(self)
    

  def do_firewall (self, packet, packet_in):
    # The code in here will be executed for every packet.
    def flood (messege = None, duration = None):
      duration = (50,50)
      if duration is not None:
        #if not isinstance(duration, tuple):
        #duration = (50,50)
        msg = of.ofp_flow_mod()
        msg.match = of.ofp_match.from_packet(packet)
        msg.idle_timeout = 50
        msg.hard_timeout = 50
        msg.buffer_id = packet_in.buffer_id
        msg.data = packet_in
        msg.actions.append(of.ofp_action_output(port = of.OFPP_FLOOD))
        self.connection.send(msg)
      else:
        msg = of.ofp_packet_out()
        msg.buffer_id = packet_in.buffer_id
        msg.data = packet_in
        msg.actions.append(of.ofp_action_output(port = of.OFPP_FLOOD))
        self.connection.send(msg)
    def drop (duration = None):
      duration = (50,50)
      if duration is not None:
        #if not isinstance(duration, tuple):
        #duration = (50,50)
        msg = of.ofp_flow_mod()
        msg.match = of.ofp_match.from_packet(packet)
        msg.idle_timeout = 50
        msg.hard_timeout = 50
        msg.buffer_id = packet_in.buffer_id
        self.connection.send(msg)
      elif packet_in.buffer_id is not None:
        msg = of.ofp_packet_out()
        msg.buffer_id = packet_in.buffer_id
        self.connection.send(msg)
    arp = packet.find('arp')
    ip = packet.find('ipv4')
    icmp = packet.find('icmp')
    tcp = packet.find('tcp')
    if arp is not None or icmp is not None:
      flood()
    elif tcp is not None:
      if (ip.srcip == IPAddr("10.0.1.20") and ip.dstip == IPAddr("10.0.1.10")) or (ip.srcip == IPAddr("10.0.1.10") and ip.dstip == IPAddr("10.0.1.20")):
        flood()
      else:
        drop()
    else:
      drop()

  def _handle_PacketIn (self, event):
    """
    Handles packet in messages from the switch.
    """

    packet = event.parsed # This is the parsed packet data.
    if not packet.parsed:
      log.warning("Ignoring incomplete packet")
      return

    packet_in = event.ofp # The actual ofp_packet_in message.
    self.do_firewall(packet, packet_in)

def launch ():
  """
  Starts the component
  """
  def start_switch (event):
    log.debug("Controlling %s" % (event.connection,))
    Firewall(event.connection)
  core.openflow.addListenerByName("ConnectionUp", start_switch)
