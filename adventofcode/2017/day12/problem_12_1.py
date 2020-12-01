from controller_abc import ControllerABC

class Solution121(ControllerABC):

	def __init__(self):
		self.program_connections = {}

	def line_reader(self, line):
		line_split = line.rstrip('\n').split(' <-> ')
		self.program_connections[int(line_split[0])] = {int(val) for val in line_split[1].split(', ')}

	def process_data(self):
		return len(self.get_connect_components(0))

	def get_connect_components(self, key):
		return self.dfs(key, set())

	def dfs(self, key, connect_components):
		if not key in connect_components:
			connect_components.add(key)
			for val in self.program_connections[key]:
				self.dfs(val, connect_components)
		return connect_components