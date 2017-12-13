from controller_abc import ControllerABC

class Solution131(ControllerABC):

	def __init__(self):
		self.firewall_details = {}

	def line_reader(self, line):
		line_split = line.rstrip('\n').split(': ')
		self.firewall_details[int(line_split[0])] = int(line_split[1])

	def process_data(self):
		severity = 0
		for key, value in self.firewall_details.items():
			if key % ((value - 1) << 1) == 0:
				severity += key * value

		return severity