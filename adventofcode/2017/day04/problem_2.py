from problem_1 import Solution041

class Solution042(Solution041):

	def is_valid_phassparse(self, set_container, token):
		return_val = True
		
		if len(set_container) != 0:
			for set_element in set_container:
				if self.is_anagram(set_element, token):
					return_val = False
					break
		
		return return_val

	def is_anagram(self, str1, str2):
		return sorted(str1) == sorted(str2)