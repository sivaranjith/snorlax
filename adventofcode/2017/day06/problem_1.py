from controller_abc import ControllerABC

class Solution061(ControllerABC):

	def line_reader(self, line):
		self.block_list = [int(val) for val in line.split()]
		self.block_list_len = len(self.block_list)

	def process_data(self):
		steps = 0
		self.pattern_list = []
		pattern = ''

		while not pattern in self.pattern_list:
			steps += 1
			self.pattern_list.append(pattern)
			self.distribute()
			pattern = ''.join([str(val) for val in self.block_list])
		self.matched_pattern = pattern

		return steps

	def distribute(self):
		index = self.get_max_val_index()
		max_val = self.block_list[index]
		starting_index = index
		mod_val = max_val%self.block_list_len
		min_inc_val = max_val//self.block_list_len
		self.block_list[index] = 0

		index = self.value_adder(index, min_inc_val+1, mod_val)
		self.value_adder(index, min_inc_val, self.block_list_len - mod_val)

	def value_adder(self, index, value, no_of_iterations):#adding value to the bucket as whole instead just adding 1 at a time
		while no_of_iterations > 0:
			index = (index+1)%self.block_list_len
			self.block_list[index] += value
			no_of_iterations -= 1
		return index


	def get_max_val_index(self):#getting max value index in O(n) instead of using list_obj.index(max(list_obj)) which is O(2n)
		max_val = self.block_list[0]
		index = 0

		for idx, val in enumerate(self.block_list):
			if val > max_val:
				max_val = val
				index = idx
		return index