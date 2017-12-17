from problem_17_1 import Solution171

class Solution172(Solution171):

	STOP_VAL = 50000000

	def process_data(self):
		self.run_insert_operation(Solution172.STOP_VAL)
		return self.val_at_index_1

	def operate(self, insert_val):
		if self.curr_position == 1:
			self.val_at_index_1 = insert_val