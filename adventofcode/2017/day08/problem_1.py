from controller_abc import ControllerABC

class Solution081(ControllerABC):

	operation_map = {
		'<': lambda x, y: x < y,
		'<=': lambda x, y: x <= y,
		'>': lambda x, y: x > y,
		'>=': lambda x, y: x >= y,
		'==': lambda x, y: x == y,
		'!=': lambda x, y: x != y,
		'inc': lambda x, y: x + y,
		'dec': lambda x, y: x - y
	}

	def __init__(self):
		self.register_values = {}

	def line_reader(self, line):
		line_split = line.split()
		if Solution081.operation_map[line_split[5]](self.get_register_value(line_split[4]), int(line_split[6])):
			self.register_values[line_split[0]] = Solution081.operation_map[line_split[1]](self.get_register_value(line_split[0]), int(line_split[2]))


	def get_register_value(self, key):
		return self.register_values[key] if key in self.register_values else 0

	def process_data(self):
		max_val = None
		for key, value in self.register_values.items():
			if max_val == None or value > max_val:
				max_val = value

		return max_val
