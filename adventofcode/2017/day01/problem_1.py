class Solution011:

  def line_reader(self, line):
    self.line = line

  def process_data(self):
    self.total = 0
    for index in reversed(range(len(self.line))):
      self.total += self.condition_checker(index)
    print(self.total)

  def condition_checker(self, index):
    return 0 if self.line[index] != self.line[index-1] else int(self.line[index])
