from controller_abc import ControllerABC
import sys
import os

sys.path.append(os.getcwd() + '/day10/')

from problem_10_2 import Solution102

class Solution141(ControllerABC):

	USED_SQUARES_INDEX = {'0':0,'1':1,'2':1,'3':2,'4':1,'5':2,'6':2,'7':3,'8':1,'9':2,'a':2,'b':3,'c':2,'d':3,'e':3,'f':4}

	def line_reader(self, line):
		self.line = line.rstrip('\n')

	def process_data(self):
		total_used_squares = 0
		for val in range(0, 128):
			knot_hash_obj = Solution102()
			knot_hash_obj.line_reader(self.line + '-' + str(val))
			for letter in knot_hash_obj.process_data():
				total_used_squares += Solution141.USED_SQUARES_INDEX[letter]

		return total_used_squares