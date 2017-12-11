from controller_abc import ControllerABC

class Solution111(ControllerABC):

	def __init__(self):
		self.count_dict = {'n' : 0, 'nw' : 0, 'ne' : 0, 's' : 0, 'se' : 0, 'sw' : 0}

	def line_reader(self, line):
		self.directions_list = line.rstrip('\n').split(',')

	def process_data(self):
		for direction in self.directions_list:
			self.count_dict[direction] += 1

		return self.distance_calculator()

	def distance_calculator(self):
		n = self.count_dict['n'] - self.count_dict['s']
		ne = self.count_dict['ne'] - self.count_dict['sw']
		nw = self.count_dict['nw'] - self.count_dict['se']

		if n > 0:
			if nw > 0 and ne > 0:
				min_val = min(nw, ne)
				n += min_val
				nw -= min_val
				ne -= min_val
			elif nw < 0 and ne > 0:
				min_val = min(n, nw*-1)
				n -= min_val
				ne += min_val
				nw += min_val
			elif nw > 0 and ne < 0:
				min_val = min(n, ne*-1)
				n -= min_val
				ne += min_val
				nw += min_val
			else:
				min_val = min(nw*-1, ne*-1)
				ne += min_val
				nw += min_val
				n -= min_val
		else:
			if nw > 0 and ne > 0:
				min_val = min(nw, ne)
				n += min_val
				nw -= min_val
				ne -= min_val
			elif nw < 0 and ne > 0:
				min_val = min(n*-1, ne)
				nw -= min_val
				ne -= min_val
				n += min_val
			elif nw > 0 and ne < 0:
				min_val = min(n*-1, nw)
				nw -= min_val
				ne -= min_val
				n += min_val
			else:
				min_val = min(nw*-1, ne*-1)
				ne += min_val
				nw += min_val
				n -= min_val

		return abs(n) + abs(nw) + abs(ne)