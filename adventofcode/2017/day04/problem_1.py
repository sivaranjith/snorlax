class Solution041:

	def __init__(self):
		self.correct_passpharse_count = 0

	def line_reader(self, line):
		set_container = set()
		
		for token in line.strip().split():
			if not self.is_valid_phassparse(set_container, token):
				return
			set_container.add(token)
		
		self.correct_passpharse_count += 1

	def process_data(self):
		return self.correct_passpharse_count

	def is_valid_phassparse(self, set_container, token):
		return not token in set_container
