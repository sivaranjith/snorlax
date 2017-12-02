from problem_1 import Solution011

class Solution012(Solution011):

  def line_reader(self, line):
    super().line_reader(line)
    self.half_length = int(len(self.line)/2)

  def condition_checker(self, index):
    return 0 if self.line[index] != self.line[index-self.half_length] else int(self.line[index])
