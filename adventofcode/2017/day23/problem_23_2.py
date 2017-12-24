from problem_23_1 import Solution231
import math

class Solution232(Solution231):

	def process_data(self):
		b = 79*100 + 100000
		c = b + 17000
		h = 0
		while True:
			if not self.is_prime(b):
				h += 1
			if b == c:
				break
			b += 17
		return h

	def is_prime(self, b):
		for i in range(2, int(math.sqrt(b))):
			if b%i == 0:
				return False
		return True

'''
	The program basically gets the sum of all non prime numbers from from initial value of b to c.
	Also it runs plus one time than intutively expected
'''