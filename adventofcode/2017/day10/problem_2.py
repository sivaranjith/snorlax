from problem_1 import Solution101

class Solution102(Solution101):

	salt = (17, 31, 73, 47, 23)
	total_iterations = 64

	def __init__(self):
		super().__init__()
		self.length_list = list(Solution102.salt)

	def line_reader(self, line):
		self.length_list = [ord(letter) for letter in line.strip('\n')] + self.length_list

	def process_data(self):
		for _ in range(0, Solution102.total_iterations):
			self.operate()

		return self.sparse_to_dense_hash()

	def sparse_to_dense_hash(self):
		hex_list = []
		for start_index in range(0, Solution101.numbers_list_len, 16):
			hash_val = self.numbers_list[start_index]
			for idx in range(start_index + 1, start_index + 16):
				hash_val ^= self.numbers_list[idx]

			hex_list.append("{:02x}".format(hash_val))
		return ''.join(hex_list)


