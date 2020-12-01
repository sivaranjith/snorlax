from controller_abc import ControllerABC

class Solution091(ControllerABC):

	def line_reader(self, line):
		self.line = line

	def process_data(self):
		self.curr_index = 0
		return self.get_group_sum(1)

	def get_group_sum(self, group_val):
		'''could have avoided garbage if checks by removing character followed by ! using regex find and replace 
			then remove all characters with <> using regex but that will create a nfa and then new strings. 
			so choose this method'''
		return_group_val = group_val
		is_valid = True
		while self.curr_index < len(self.line):
			self.curr_index += 1
			if is_valid and self.line[self.curr_index] == '{':
				return_group_val += self.get_group_sum(group_val + 1)
			elif is_valid and self.line[self.curr_index] == '}':
				break
			elif self.line[self.curr_index] == '<':
				is_valid = False
			elif self.line[self.curr_index] == '!':
				self.curr_index += 1
			elif self.line[self.curr_index] == '>':
				is_valid = True

		return return_group_val