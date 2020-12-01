from controller_abc import ControllerABC

class Solution241(ControllerABC):

	def __init__(self):
		self.ports = []
		self.max_strength = 0
		self.largest_bridge = None

	def line_reader(self, line):
		self.ports.append([int(i) for i in line.rstrip('\n').split('/')])

	def process_data(self):
		visited_listed = [ 0 for _ in range(0, len(self.ports))]
		self.back_propagate(0, visited_listed, [])
		return self.max_strength

	def back_propagate(self, strength, visited_listed, bridge):
		curr_ports = self.get_ports_with_strength(strength, visited_listed)
		if len(curr_ports) == 0:
			self.is_required_bridge(bridge)
		else:
			for port in curr_ports:
				bridge.append(port)
				port_index = self.ports.index(port)
				visited_listed[port_index] = 1
				next_strength = port[0] if port[1] == strength else port[1]
				self.back_propagate(next_strength, visited_listed, bridge)
				visited_listed[port_index] = 0
				bridge.pop()

	def is_required_bridge(self, bridge):
		bridge_strength = self.get_strength(bridge)
		if bridge_strength > self.max_strength:
			self.max_strength = bridge_strength
			self.largest_bridge = list(bridge)

	def get_strength(self, bridge):
		strength = 0
		for ele in bridge:
			strength += ele[0] + ele[1]
		return strength

	def get_ports_with_strength(self, strength, visited_listed):
		result = []
		for index in range(0, len(self.ports)):
			port = self.ports[index]
			if visited_listed[index] == 0 and (port[0] == strength or port[1] == strength):
				result.append(port)
		return result