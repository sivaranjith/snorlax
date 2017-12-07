from problem_1 import Solution041

class Solution042(Solution041):

	def is_valid_phassparse(self, set_container, token):
		return_val = True
		
		for set_element in set_container:
			if sorted(set_element) == sorted(token):
				return_val = False
				break
		
		return return_val
