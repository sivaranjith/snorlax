from problem_24_1 import Solution241

class Solution242(Solution241):

	def __init__(self):
		super().__init__()
		self.longest_bridge = 0

	def is_required_bridge(self, bridge):
		bridge_strength = self.get_strength(bridge)
		bridge_length = len(bridge)
		if bridge_length >= self.longest_bridge and bridge_strength > self.max_strength:
			self.max_strength = bridge_strength
			self.largest_bridge = list(bridge)
			self.longest_bridge = bridge_length