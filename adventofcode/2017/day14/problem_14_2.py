from problem_14_1 import Solution141
import sys
import os

sys.path.append(os.getcwd() + '/day10/')

from problem_10_2 import Solution102

class Solution142(Solution141):

	hex_to_bin = {'0':'....','1':'...#','2':'..#.','3':'..##','4':'.#..','5':'.#.#','6':'.##.','7':'.###','8':'#...','9':'#..#','a':'#.#.','b':'#.##','c':'##..','d':'##.#','e':'###.','f':'####'}

	def __init__(self):
		self.line1 = '.' * 128
		self.region_count = 0
		self.bi_directional_map = BiDirectionalMap()

	def process_data(self):
		for line_no in range(0, 128):
			knot_hash_obj = Solution102()
			knot_hash_obj.line_reader(self.line + '-' + str(line_no))
			self.line2 = self.hex_to_bin_converter(knot_hash_obj.process_data())
			self.region_identifier(line_no)
			self.line1 = self.line2

		return len(self.bi_directional_map)

	def hex_to_bin_converter(self, line):
		output = ''
		for letter in line:
			output += Solution142.hex_to_bin[letter]
		return output

	def region_identifier(self, line_no):
		index = self.line2.find('#')
		while index < 128:
			dot_index = self.line2.find('.', index)
			dot_index = 128 if dot_index == -1 else dot_index

			if self.line1[index:dot_index].find('#') == -1:#if there is no # in the upper row along these columns then it's a new region mostly
				self.region_count += 1
				self.update_bi_directional_map_current_line(line_no, index, dot_index, self.region_count)
			else:
				self.update_bi_directional_map(line_no, index, dot_index)#for connecting groups that where early considered to be different
			index = self.line2.find('.#', dot_index)
			index = 128 if index == -1 else index + 1

	def update_bi_directional_map(self, line_no, index, dot_index):
		itr = self.line1.find('#', index)
		val = self.bi_directional_map.get_val(self.get_key(line_no - 1, itr))

		while itr < dot_index:
			to_val = self.bi_directional_map.get_val(self.get_key(line_no - 1, itr))
			if val != to_val:
				self.bi_directional_map.update_val(val, to_val)
			itr = self.line1.find('.#', itr)
			itr = dot_index if itr == -1 else itr+1
		self.update_bi_directional_map_current_line(line_no, index, dot_index, val)


	def update_bi_directional_map_current_line(self, line_no, index, dot_index, val):
		keys = []
		for itr in range(index, dot_index):
			keys.append(self.get_key(line_no, itr))
		self.bi_directional_map.add(keys, val)

	def get_key(self, line_no, itr):
		return (str(line_no) + ':' + str(itr))

class BiDirectionalMap():
	def __init__(self):
		self.key_to_val = {}
		self.val_to_key = {}

	def add(self, keys, val):
		for key in keys:
			self.key_to_val[key] = val
			if not val in self.val_to_key:
				self.val_to_key[val] = []
			self.val_to_key[val].append(key)

	def get_val(self, key):
		return self.key_to_val[key]

	def get_keys(self, val):
		return self.val_to_key[val]

	def update_val(self, from_val, to_val):
		self.add(self.val_to_key[to_val], from_val)
		del self.val_to_key[to_val]

	def __len__(self):
		return len(self.val_to_key)