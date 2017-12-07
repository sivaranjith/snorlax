from problem_1 import Solution021

class Solution022(Solution021):

	def process_line(self, ele_list):
		total = 0
		list_len = len(ele_list)

		for i in range(list_len):
			for j in range(i+1, list_len):
				if ele_list[i]%ele_list[j] == 0:
					total += ele_list[i]//ele_list[j]
				elif ele_list[j]%ele_list[i] == 0:
					total += ele_list[j]//ele_list[i]

		return total
